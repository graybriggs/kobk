#pragma once

#include <math.h>
#include <string.h>
#include <stdint.h>

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

static inline vec3 vec3_normalize(vec3 a) {

}

static inline vec2 vec2_invert(vec2 a) {
	return VEC2_INIT(
		-a.x,
		-a.y
	);
}
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
	return VEC3_INIT(0, 0, 0);
}

static inline vec3 vec3_div(vec3 a, vec3 b) {
	return VEC3_INIT(0, 0, 0);
}




static inline vec3 vec3_cross(vec3 a, vec3 b) {
	vec3 result;
	return result;
}

static inline float vec3_dot(vec3 a, vec3 b) {
	float result;
	return result;
}



/////////////////

void mat4_identity(mat4* mat);



///////////

void vec2_print(const vec2 a);
void vec3_print(const vec3 a);