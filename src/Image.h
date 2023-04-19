#pragma once

#include <string>

#include "Vector.h"

class Image
{
public:
	Image(int width, int heigth);

	void WritePixel(int x, int y, const Vector& color);
	Vector GetPixel(int x, int y) const;
	void WriteImageTofile(std::string fileName) const;

	~Image();
	
private:
	int width;
	int heigth;

	Vector** image;
};

void WriteColor(std::ostream& out, const Vector&);