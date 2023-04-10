#include "Image.h"

#include <fstream>

Image::Image(int width, int heigth) : width{width}, heigth{heigth}
{
	image = new Vector * [heigth];

	for (int y = 0; y < heigth; y++)
	{
		image[y] = new Vector[width];
	}
}

void Image::WritePixel(int x, int y, const Vector& color)
{
	image[y][x] = color;
}

Vector Image::GetPixel(int x, int y) const
{
	return image[y][x];
}

void Image::WriteImageTofile(std::string fileName) const
{
	std::ofstream file("image.ppm", std::ios::out | std::ios::binary);
	file.imbue(std::locale::classic());

	file << "PF" << ' ' << width << ' ' << heigth << ' ' << "-1" << '\n';

	for (int y = 0; y < heigth; y++) {
		for (int x = 0; x < width; x++) {
			WriteColor(file, image[y][x]);
		}
	}

	file.close();
}

Image::~Image()
{
	for (int y = 0; y < heigth; y++) {
		delete image[y];
	}
}

void WriteColor(std::ostream& out, const Vector& vec)
{
	float x, y, z;
	x = static_cast<float>(vec.x);
	y = static_cast<float>(vec.y);
	z = static_cast<float>(vec.z);

	out.write((const char*)&x, 4);
	out.write((const char*)&y, 4);
	out.write((const char*)&z, 4);
}
