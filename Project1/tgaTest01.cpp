#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void drawPoint(int x, int y, TGAImage &image, TGAColor color){

	image.set(x, y, color);
}


void BresenhamLine01(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color){
	// basic algorithm of drawing a line
	for (float i = 0; i < 1.0f; i = i + 0.01){
		int x = x0 + (x1 - x0) * i;
		int y = y0 + (y1 - y0) * i;
		image.set(x, y, color);
	}

}


void BresenhamLine02(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color){
	// first improvement
	bool steep = false;

	if (abs(x0 - x1) < abs(y0 - y1)){
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	// select a longer path

	if (x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	// keep the smaller one at the first

	for (int x = x0; x < x1; x++){
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1.0f - t) + (y1 * t);

		if (steep)
			image.set(y, x, color);
		else
			image.set(x, y, color);
		// transpose back if transposed

	}
}


void BresenhamLine03(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color){
	// second improvement
	bool steep = false;

	if (abs(x0 - x1) < abs(y0 - y1)){
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	// select a longer path

	if (x0 > x1){
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	// keep the smaller one at the first


}


int main(){
	TGAImage image(100, 100, TGAImage::RGB);
	BresenhamLine02(1, 1, 20, 1, image, red);
	image.write_tga_file("../bb2.tga");
	return 0;
}