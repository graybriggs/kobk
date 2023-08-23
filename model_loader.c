
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "model_loader.h"

// this function gets a line from a PLG file and strips comments

char* plg_get_line(char* string, int max_length, FILE* fp) {

    char buffer[80]; // temporary string storage

    int length,      // length of line read
        index = 0,     // looping variables
        index_2 = 0,
        parsed = 0;    // has the current input line been parsed

    // get the next line of input, make sure there is something on the line

    while (1) {
        if (!fgets(buffer, max_length, fp))
            return NULL;

        length = strlen(buffer);
        // remove carriage return
        buffer[length - 1] = 0;
        index = 0;

        // eat leading white space

        while (buffer[index] == ' ')
            index++;

        // read line into buffer, if "#" arrives in data stream then disregard rest of line
        parsed = 0;
        index_2 = 0;

        while (!parsed) {
            if (buffer[index] != '#' && buffer[index] != ';') {
                // insert character into output string
                string[index_2] = buffer[index];

                // test if this is a null terminator
                if (string[index_2] == 0)
                    parsed = 1;

                // move to next character
                index++;
                index_2++;
            }
            else {
                // insert a null termination since this is the end of the
                // string for all intents and purposes
                string[index_2] = 0;
                parsed = 1;
            } // end else

        } // end while parsing string

        if (strlen(string))
            return(string);
    }
}

// this function loads a PLG object from disk and allows it to be scaled
int plg_load_object(object* obj, const char* filename, float scale) {
    FILE* fp; // disk file
    static int id_number = 0;
    char buffer[80];
    char object_name[32];
    char* token; // current parsing token

    uint32_t total_vertices; // total vertices in object
    uint32_t total_polys; // total polygons per object
    uint32_t num_vertices; // number of vertices on a polygon
    uint32_t color_des; // the color descriptor of a polygon
    uint32_t logical_color; // the final color of polygon
    uint32_t shading; // the type of shading used on polygon
    uint32_t vertex_num;
    uint32_t vertex_0;
    uint32_t vertex_1;
    uint32_t vertex_2;
    float x, y, z; // a single vertex
    vec3 u;
    vec3 v;
    vec3 normal;

    if ((fp = fopen(filename, "r")) == NULL) {

        printf("\nCouldn't open file %s", filename);
        return 0;
    } // end if
    // first we are looking for the header line that has the object name and
    // the number of vertices and polygons

    if (!plg_get_line(buffer, 80, fp)) {
        printf("\nError with PLG file %s", filename);
        fclose(fp);
        return 0;
    }

    // extract object name and number of vertices and polygons
    sscanf(buffer, "%s %d %d", object_name, &total_vertices, &total_polys);

    // set proper fields in object
    obj->num_vertices = total_vertices;
    obj->num_polys = total_polys;
    obj->state = 1;
    obj->world_pos.x = 0;
    obj->world_pos.y = 0;
    obj->world_pos.z = 0;
    // set id number, maybe later also add the name of object in the
    // structure???
    obj->id = id_number++;
    // based on number of vertices, read vertex list into object
    for (int i = 0; i < total_vertices; i++) {
        // read in vertex
        if (!PLG_Get_Line(buffer, 80, fp)) {
            printf("\nError with PLG file %s", filename);
            fclose(fp);
            return 0;
        }
        sscanf(buffer, "%f %f %f", &x, &y, &z);
        // insert vertex into object
        obj->vertices_local[i].x = x * scale;
        obj->vertices_local[i].y = y * scale;
        obj->vertices_local[i].z = z * scale;
    }
    // now read in polygon list
    for (int i = 0; i < total_polys; i++) {
        // read in color and number of vertices for next polygon
        if (!PLG_Get_Line(buffer, 80, fp)) {
            printf("\nError with PLG file %s", filename);
            fclose(fp);
            return 0;
        }
        // intialize token getter and get first token which is color descriptor
        if (!(token = strtok(buffer, " "))) {
            printf("\nError with PLG file %s", filename);
            fclose(fp);
            return 0;
        }
        // test if number is hexadecimal
        if (token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {
            sscanf(&token[2], "%x", &color_des);
        }
        else {
            color_des = atoi(token);
        }
        // extract base color and type of shading
        logical_color = color_des & 0x00ff;
        shading = color_des >> 12;
        // read number of vertices in polygon
        if (!(token = strtok(NULL, " "))) {
            printf("\nError with PLG file %s", filename);
            fclose(fp);
            return 0;
        }
        if ((num_vertices = atoi(token)) <= 0) {
            printf("\nError with PLG file (number of vertices) %s", filename);
            fclose(fp);
            return 0;
        } // end if no vertices or error

        // set fields in polygon structure
        obj->polys[i].num_points = num_vertices;
        obj->polys[i].color = logical_color;
        obj->polys[i].shading = shading;
        obj->polys[i].two_sided = 0;
        obj->polys[i].visible = 1;
        obj->polys[i].clipped = 0;
        obj->polys[i].active = 1;

        // now read in polygon vertice list
        for (int j = 0; j < num_vertices; j++) {
            // read in next vertex number
            if (!(token = strtok(NULL, " "))) {
                printf("\nError with PLG file %s", filename);
                fclose(fp);
                return 0;
            }
            vertex_num = atoi(token);
            // insert vertex number into polygon
            obj->polys[i].vertex_list[j] = vertex_num;
        }

        // compute length of the two co-planar edges of the polygon, since they
        // will be used in the computation of the dot-product later
        vertex_0 = obj->polys[i].vertex_list[0];
        vertex_1 = obj->polys[i].vertex_list[1];
        vertex_2 = obj->polys[i].vertex_list[2];
        // the vector u = vo->v1


        //vec3 u = vec3_from_3d_points(obj->vertices_local[vertex_0], obj->vertices_local[vertex_1]);
        //vec3 v = vec3_from_3d_points(obj->vertices_local[vertex_0], obj->vertices_local[vertex_2]);

        vec3 u;
        u.x = obj->vertices_local[vertex_1].x, obj->vertices_local[vertex_0].x;
        u.y = obj->vertices_local[vertex_1].y, obj->vertices_local[vertex_0].y;
        u.z = obj->vertices_local[vertex_1].z, obj->vertices_local[vertex_0].z;

        vec3 v;
        v.x = obj->vertices_local[vertex_2].x - obj->vertices_local[vertex_0].x;
        v.y = obj->vertices_local[vertex_2].y - obj->vertices_local[vertex_0].y;
        v.z = obj->vertices_local[vertex_2].z - obj->vertices_local[vertex_0].z;

        /*
            Make_Vector_3D(
              (vec3*)&obj->vertices_local[vertex_0],
              (vec3*)&obj->vertices_local[vertex_1]
              (vec3*)&u
            );
              // the vector v = vo->v2
            Make_Vector_3D(
              (vec3*)&obj->vertices_local[vertex_0],
              (vec3*)&obj->vertices_local[vertex_2]
              (vec3*)&v
            );
            */
            /*
            Cross_Product_3D(
              (vec3*)&v,
              (vec3*)&u,
              (vec3*)&normal
            );
            */
            //vec3 normal = vec3_cross(u, v);
        vec3 normal;
        test_vec3_cross(&normal, u, v);

        // compute magnitude of normal and store in polygon structure
        obj->polys[i].normal_length = vec3_mag(normal);
    }
    fclose(fp);
    // compute object radius
    compute_object_radius(obj);

    return 1;
} 


float compute_object_radius(object* obj)
{

    // this function computes maximum radius of object, maybe a better method would
    // use average radius? Note that this function shouldn't be used during
    // runtime but when an object is created

    float new_radius;   // used in average radius calculation of object
    // coords for a single vertex
    float x;
    float y;
    float z;

    // reset object radius

    obj->radius = 0;

    for (int i = 0; i < obj->num_vertices; i++)
    {

        x = obj->vertices_local[i].x;
        y = obj->vertices_local[i].y;
        z = obj->vertices_local[i].z;

        // compute distance to point

        new_radius = (float)sqrt(x * x + y * y + z * z);

        // is this radius bigger than last?

        if (new_radius > obj->radius)
            obj->radius = new_radius;

    } // end for index

// return radius just in case

    return(obj->radius);

}