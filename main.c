#include <stdio.h>

#include "math_util.h"

int main() {

	vec3 v1 = VEC3_INIT(1, 2, 3);
	vec3 v2 = VEC3_INIT(4, 5, 6);

	vec3 v3 = vec3_add(v1, v2);

	vec3_print(v3);

	return 0;
}