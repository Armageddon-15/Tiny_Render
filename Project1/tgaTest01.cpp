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

bool isSteep(int& x0, int& y0, int& x1, int& y1){
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

	return steep;
}

template<typename T>
inline T lerp(T &a, T &b, float &alpha) {
	// return a if alpha is 0
	return a * (1 - alpha) + b * alpha;
}


void BresenhamLine02(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color){
	// first improvement
	bool steep = isSteep(x0, y0, x1, y1);

	for (int x = x0; x < x1; x++){
		float t = (x - x0) / (float)(x1 - x0);
		int y = lerp(y0, y1, t);

		if (steep)
			image.set(y, x, color);
		else
			image.set(x, y, color);
		// transpose back if transposed

	}
}


void BresenhamLine03(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color){
	// second improvement
	// speed up
	bool steep = isSteep(x0, y0, x1, y1);

	int dx = x1 - x0;
	int dy = y1 - y0;

	float derror = abs(dy / (float)dx); // const
	float error = 0;

	int y = y0;
	for (int x = x0; x < x1; x++){
		if (steep)
			image.set(y, x, color); 
		else
			image.set(x, y, color);

		error += derror;
		if(error > 0.5f){
			y += y1 > y0 ? 1 : -1;
			error -= 1.0f;
		}
	}
}

void BresenhamLine04(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color){
	// third improvement
	// speed up
	bool steep = isSteep(x0, y0, x1, y1);

	int dx = x1 - x0;
	int dy = y1 - y0;

	int derror = abs(dy) * 2; // const
	int error = 0;

	int y = y0;
	if (steep) {
		for (int x = x0; x < x1; x++){
			image.set(y, x, color); 
			error += derror;
			if(error > dx){
				y += y1 > y0 ? 1 : -1;
				error -= dx * 2;
			}
		}
	} else {
		for (int x = x0; x < x1; x++){
			image.set(x, y, color);
			error += derror;
			if(error > dx){
				y += y1 > y0 ? 1 : -1;
				error -= dx * 2;
			}
		}
	}
}


int main(){
	TGAImage image(100, 100, TGAImage::RGB);
	BresenhamLine04(1, 1, 76, 94, image, red);
	BresenhamLine03(2, 84, 76, 3, image, white);
	image.write_tga_file("../bb2.tga");
	return 0;
}