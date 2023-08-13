

#include "util.h"

float min(float a, float b) {
	return a < b ? a : b;
}

float max(float a, float b) {
	return a > b ? a : b;
}

void swap(float* a, float* b) {
	float t = *a;
	*a = *b;
	*b = t;
}