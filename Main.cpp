#include <iostream>
#include "Vector.h"

int main() {
	Vector vec(1, 2);
	Vector Vec(1, 2, 3);
	auto vec3 = vec + Vec;
	std::cout << ~(Vec + vec + vec3) << '\n';
	return 0;
}