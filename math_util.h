#pragma once


#define PI 3.14159265
#define DEG2RAD(A) (A) * (PI / 180)

static inline float deg2rad(float angle) {
	return angle * (PI / 180);
}

typedef struct {
	float x;
	float y;
} vec2;

typedef struct {
	float x;
	float y;
	float z;
} vec3;

typedef struct {
	float m[4 * 4];
} mat4;


#define VEC2_INIT(X, Y) ((vec2){.x = X, .y = Y})
#define VEC3_INIT(X, Y, Z) ((vec3){.x = X, .y = Y, .z = Z})

#define MAT4_IDENT(m) \
	(mat4){.m = { \
		1.0f, 0.0f, 0.0f, 0.0f, \
		0.0f, 1.0f, 0.0f, 0.0f, \
		0.0f, 0.0f, 1.0f, 0.0f, \
		0.0f, 0.0f, 0.0f, 1.0f  \
	}}

#define MAT4_INIT(m0,m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15) \
	(mat4){.m = { \
		m0,   m1,  m2,  m3, \
		m4,   m5,  m6,  m7, \
		m8,   m9, m10, m11, \
		m12, m13, m14, m15  \
	}}

// |v|
float vec2_mag(vec2 a);


// vec2

vec2 vec2_invert(vec2 a);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul(vec2 a, vec2 b);
vec2 vec2_mulf(vec2 a, float f);

// vec3

// |u|
float vec3_mag(vec3 a);
vec3 vec3_invert(vec3 a);
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 a, vec3 b);

//static inline vec3 vec3_div(vec3 a, vec3 b); // ??


vec3 vec3_mulf(vec3 a, float f);

/////

float vec3_dot(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);
vec2 vec2_from_2d_points(vec3 init, vec3 term);
vec3 vec3_from_3d_points(vec3 init, vec3 term);


/////////////////

void mat4_set_identity(mat4* mat);
void mat4_translate(mat4* mat, vec3 trans);
void mat4_scale(mat4* mat, float x, float y, float z);
void mat4_rotate(mat4* mat, float angle, vec3 u);
void mat4_mul(mat4* res, mat4* a, mat4* b);

void look_at(vec3 position, vec3 target, vec3 up);

void mat4_perspective(mat4* mat);
void mat4_ortho(mat4* mat);

///////////

void vec2_print(const vec2 a);
void vec3_print(const vec3 a);
void mat4_print(const mat4* a);