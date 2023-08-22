#pragma once

#include "math_util.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>


void mat4_set_identity(mat4* mat) {
	memset(mat->m, 0, sizeof(mat->m));
	mat->m[0] = mat->m[5] = mat->m[10] = mat->m[15] = 1.0f;
}


vec3 vec3_transform(vec3 a, mat4* mat) {
	float w = mat->m[3] * a.x + mat->m[7] * a.y + mat->m[11] * a.z + mat->m[15];
	if (w == 0) {
		w = 1;
	}
	return VEC3_INIT(
		(mat->m[0] * a.x + mat->m[4] * a.y + mat->m[8] * a.z + mat->m[12]) / w,
		(mat->m[1] * a.x + mat->m[5] * a.y + mat->m[9] * a.z + mat->m[13]) / w,
		(mat->m[2] * a.x + mat->m[6] * a.y + mat->m[10] * a.z + mat->m[14]) / w
	);
}


void mat4_translate(mat4* mat, vec3 trans) {
	mat->m[12] = mat->m[0] * trans.x + mat->m[4] * trans.y + mat->m[8] * trans.z + mat->m[12];
	mat->m[13] = mat->m[1] * trans.x + mat->m[5] * trans.y + mat->m[9] * trans.z + mat->m[13];
	mat->m[14] = mat->m[2] * trans.x + mat->m[6] * trans.y + mat->m[10] * trans.z + mat->m[14];
	mat->m[15] = mat->m[3] * trans.x + mat->m[7] * trans.y + mat->m[11] * trans.z + mat->m[15];
}


void mat4_scale(mat4* mat, float x, float y, float z) {

}

void mat4_rotate(mat4* mat, float angle, vec3 u) {

	float c = cos(angle);
	float s = sin(angle);
	float t = 1.0f - c;

	float x = u.x;
	float y = u.y;
	float z = u.z;

	// Normalize the axis vector
	float length = sqrt(x * x + y * y + z * z);
	if (length > 0.0f) {
		x /= length;
		y /= length;
		z /= length;
	}

	float tx = t * x;
	float ty = t * y;
	float tz = t * z;

	float sx = s * x;
	float sy = s * y;
	float sz = s * z;

	// Rotation matrix
	//mat4 rotation_matrix;
	mat4 rotation_matrix = MAT4_INIT(
		tx * x + c, tx * y - sz, tx * z + sy, 0.0f,
		tx * y + sz, ty * y + c, ty * z - sx, 0.0f,
		tx * z - sy, ty * z + sx, tz * z + c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// Apply rotation to the input matrix
	mat4 result_matrix;
	mat4_set_identity(&result_matrix);
		
	for (int i = 0; i < 16; ++i) {
		result_matrix.m[i] = 0.0f;
		for (int j = 0; j < 4; ++j) {
			result_matrix.m[i] += rotation_matrix.m[i % 4 + j * 4] * mat->m[j * 4 + i / 4];
		}
	}

	// Copy the result back to the input matrix
	for (int i = 0; i < 16; ++i) {
		mat->m[i] = result_matrix.m[i];
	}
}

void mat4_mul(mat4* res, mat4* a, mat4* b) {
	res->m[0] = b->m[0] * a->m[0] + b->m[1] * a->m[4] + b->m[2] * a->m[8] + b->m[3] * a->m[12];
	res->m[1] = b->m[0] * a->m[1] + b->m[1] * a->m[5] + b->m[2] * a->m[9] + b->m[3] * a->m[13];
	res->m[2] = b->m[0] * a->m[2] + b->m[1] * a->m[6] + b->m[2] * a->m[10] + b->m[3] * a->m[14];
	res->m[3] = b->m[0] * a->m[3] + b->m[1] * a->m[7] + b->m[2] * a->m[11] + b->m[3] * a->m[15];
	res->m[4] = b->m[4] * a->m[0] + b->m[5] * a->m[4] + b->m[6] * a->m[8] + b->m[7] * a->m[12];
	res->m[5] = b->m[4] * a->m[1] + b->m[5] * a->m[5] + b->m[6] * a->m[9] + b->m[7] * a->m[13];
	res->m[6] = b->m[4] * a->m[2] + b->m[5] * a->m[6] + b->m[6] * a->m[10] + b->m[7] * a->m[14];
	res->m[7] = b->m[4] * a->m[3] + b->m[5] * a->m[7] + b->m[6] * a->m[11] + b->m[7] * a->m[15];
	res->m[8] = b->m[8] * a->m[0] + b->m[9] * a->m[4] + b->m[10] * a->m[8] + b->m[11] * a->m[12];
	res->m[9] = b->m[8] * a->m[1] + b->m[9] * a->m[5] + b->m[10] * a->m[9] + b->m[11] * a->m[13];
	res->m[10] = b->m[8] * a->m[2] + b->m[9] * a->m[6] + b->m[10] * a->m[10] + b->m[11] * a->m[14];
	res->m[11] = b->m[8] * a->m[3] + b->m[9] * a->m[7] + b->m[10] * a->m[11] + b->m[11] * a->m[15];
	res->m[12] = b->m[12] * a->m[0] + b->m[13] * a->m[4] + b->m[14] * a->m[8] + b->m[15] * a->m[12];
	res->m[13] = b->m[12] * a->m[1] + b->m[13] * a->m[5] + b->m[14] * a->m[9] + b->m[15] * a->m[13];
	res->m[14] = b->m[12] * a->m[2] + b->m[13] * a->m[6] + b->m[14] * a->m[10] + b->m[15] * a->m[14];
	res->m[15] = b->m[12] * a->m[3] + b->m[13] * a->m[7] + b->m[14] * a->m[11] + b->m[15] * a->m[15];
}


void look_at(vec3 position, vec3 target, vec3 up) {

}


void mat4_perspective(mat4* mat) {
	float frustum_scale = 1.0f;
	float z_near = 0.5f;
	float z_far = 3.0f;
	
	mat->m[0] = frustum_scale;
	mat->m[5] = frustum_scale;
	mat->m[10] = (z_far + z_near) / (z_near - z_far);
	mat->m[11] = (2 * z_far * z_near) / (z_near - z_far);
	mat->m[14] = -1.0f;
}

void mat4_ortho(mat4* mat) {

}

///////

void vec2_print(const vec2 a) {
	printf("%f %f\n", a.x, a.y);
}

void vec3_print(const vec3 a) {
	printf("%f %f %f\n", a.x, a.y, a.z);
}

void mat4_print(const mat4* a) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%.2f ", a->m[count++]);
		}
		printf("\n");
	}
}