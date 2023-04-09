#include <iostream>
#include <fstream>
#include "Vector.h"

#define WIDTH 2048
#define HEIGHT 2048

int main() {
	const int width = 512;
	const int height = 512;

	auto Image = new Vector[width][height];

	std::ofstream file("image.ppm", std::ios::out | std::ios::binary);
	file.imbue(std::locale::classic());

	file << "PF" << ' ' << WIDTH << ' ' << HEIGHT << ' ' << "-1" << '\n';

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			WriteColor(file, { double(x) / (WIDTH - 1), double(y) / (HEIGHT - 1), 0.5 });
		}
	}

	file.close();
}