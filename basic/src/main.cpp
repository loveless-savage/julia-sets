/* writes a PNG file given julia set parameters
 * stride = width * #colors
*/


#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#define W 800
#define H 800

float l_trans(float val, float min1, float max1, float min2, float max2){
	val -= min1;
	val /= max1-min1;
	val *= max2-min2;
	val += min2;
	return val;
}

bool jt(float complex z, float complex c, int itnum){
	for(char n = 0; n < itnum; n++){
		if(cabsf(z)>2.0){
			return false;
		}
		z *= z;
		z += c;
	}
	return true;
}

float complex z,c;


int main(int argc, char** argv){
	if (argc < 3){
		fprintf(stderr, "ohp, you need 2 numbers. Give a & b for c = a + bi\n");
		return EXIT_FAILURE;
	}

	c = atof(argv[1]) + atof(argv[2])*I;

	unsigned char pts[W*H*3] = {0};
	unsigned char *readhead = pts;
	for(size_t x=0; x<W; x++){
			for(size_t y=0; y<H; y++){

				z = l_trans((float)x,0.0,(float)W,-2.0,2.0) * I;
				z += l_trans((float)y,0.0,(float)H,-2.0,2.0);

				if(jt(z,c,30)){
					*readhead++ = 255;
					*readhead++ = 0;
					*readhead++ = 0;
				}else{readhead+=3;}
			}
	}

	stbi_write_png("juliabasic.png", W, H, 3, pts, W*3); 
}
