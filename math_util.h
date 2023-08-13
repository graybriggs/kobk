#pragma once

#include <math.h>
#include <string.h>
#include <stdint.h>

#define PI 3.14159265
#define DEG2RAD(A) (A) *  (PI / 180)

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



static inline float vec3_length(vec3 a) {
	return (float)sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

static inline float vec3_mag(vec2 a) {

static inline float vec3_mag(vec3 a) {

}

static inline vec3 vec3_normalize(vec3 a) {

}

static inline vec2 vec2_invert(vec2 a) {
	return VEC2_INIT(
		-a.x,
		-a.y
	);
}

// vec2

static inline vec2 vec2_invert(vec2 a) {
	return VEC2_INIT(
		-a.x,
		-a.y
	);
}

static inline vec2 vec2_add(vec2 a, vec2 b) {
	return VEC2_INIT(
		a.x + b.x,
		a.y + b.y,
	);
}

static inline vec2 vec2_sub(vec2 a, vec2 b) {
	return VEC2_INIT(
		a.x - b.x,
		a.y - b.y
	);
}

static inline vec2 vec2_mul(vec2 a, vec2 b) {
	return VEC2_INIT(
		a.x * b.x,
		a.y * b.y
	);
}


static inline vec2 vec_mulf(vec2 a, float f) {
	return VEC2_INIT(
		a.x * f,
		a.y* f;
	);
}


// vec3

static inline vec3 vec3_invert(vec3 a) {
	return VEC3_INIT(
		-a.x,
		-a.y,
		-a.z
	);
}

static inline vec3 vec3_add(vec3 a, vec3 b) {
	return VEC3_INIT(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}

static inline vec3 vec3_sub(vec3 a, vec3 b) {
	return VEC3_INIT(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
}

static inline vec3 vec3_mul(vec3 a, vec3 b) {
	return VEC3_INIT(
		a.x * b.x,
		a.y * b.y,
		a.z * b.z
	);
}

//static inline vec3 vec3_div(vec3 a, vec3 b); // ??


static inline vec3 vec_mulf(vec3 a, float f) {
	return VEC3_INIT(
		a.x * f,
		a.y * f,
		a.z * f
	);
}


/////

static inline vec3 vec3_cross(vec3 a, vec3 b) {
	return VEC3_INIT(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

static inline float vec3_dot(vec3 a, vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}



/////////////////

void mat4_identity(mat4* mat);
void mat4_translation(mat4* mat);


///////////

void vec2_print(const vec2 a);
void vec3_print(const vec3 a);