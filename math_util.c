#pragma once

#include "math_util.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>


void mat4_identity(mat4* mat) {
	memset(mat->m, 0, sizeof(mat->m));
	mat->m[0] = 1.0f;
	mat->m[5] = 1.0f;
	mat->m[10] = 1.0f;
	mat->m[15] = 1.0f;
}

void mat4_translation(mat4* mat, vec3 a) {
	
}

// void mat4_mult(mat4* res, mat4* a, mat4* b);

///////

void vec2_print(const vec2 a) {
	printf("%f %f\n", a.x, a.y);
}

void vec3_print(const vec3 a) {
	printf("%f %f %f\n", a.x, a.y, a.z);
}