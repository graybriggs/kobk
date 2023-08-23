#pragma once

#include <stdint.h>
#include <stdio.h>

#include "math_util.h"

#define MAX_VERTICES_PER_OBJECT 256
#define MAX_POLYS_PER_OBJECT 64
#define MAX_POINTS_PER_POLY 3 // want triangles; 4 would be quad

typedef struct {
	float x;
	float y;
	float z;
} vec3;

#define VEC3_INIT(X, Y, Z) ((vec3){.x = X, .y = Y, .z = Z})

typedef struct {
	int num_points; // number of points in polygon (usually 3 or 4)
	int vertex_list[MAX_POINTS_PER_POLY]; // the index number of
	// vertices
	int color; // color of polygon
	int shade; // the final shade of color after lighting
	int shading; // type of lighting, flat or constant shading
	int two_sided; // flags if the polygon is two sided
	int visible; // used to remove backfaces
	int active; // used to turn faces on and off
	int clipped; // flags that polygon has been clipped or removed
	float normal_length; // pre-computed magnitude of normal
} polygon;

typedef struct {
	uint32_t num_vertices;
	uint32_t num_polys;
	polygon polys[MAX_POLYS_PER_OBJECT];
	float radius;
	uint32_t state;
	vec3 vertices_local[MAX_VERTICES_PER_OBJECT];
	vec3 vertices_camera[MAX_VERTICES_PER_OBJECT];
	vec3 world_pos;
	uint32_t id;
	char name[64];
} object;

char* plg_get_line(char* string, int max_length, FILE* fp);
int plg_load_object(object* obj, const char* filename, float scale);
float compute_object_radius(object* obj);