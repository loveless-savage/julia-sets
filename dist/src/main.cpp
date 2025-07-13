/* writes a PNG file given julia set parameters
 * stride = width * #colors
*/


#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

using namespace std;

#define W 800
#define H 800

// linear transformation
float l_trans(float val, float min1, float max1, float min2, float max2){
	val -= min1;
	val /= max1-min1;
	val *= max2-min2;
	val += min2;
	return val;
}

// traditional julia test
bool jt(complex<float> z, complex<float> c, int itnum){
	for(char n = 0; n < itnum; n++){
		if(abs(z)>2.0){
			return false;
		}
		z *= z;
		z += c;
	}
	return true;
}

// distance test (julia)
float jtdist(complex<float> z, complex<float> c, int itnum, int retval){
	complex<float> cdr = 1;
	for(char n = 0; n < itnum; n++){
		if(abs(z)>2.0) break;
		cdr *= z;
		cdr *= 2;
		//cdr += 1;

		z *= z;
		z += c;
	}

	float r = abs(z);
	float dr = abs(cdr);

	switch (retval){
	case 2:
		return log(r) * r/dr;
		break;
	case 1:
		return dr;
		break;
	default:
		return r;
		break;
	}
}

// distance test (mandelbrot)
float jtdistm(complex<float> z, complex<float> c, int itnum, int retval){
	complex<float> cdr = 1;
	for(char n = 0; n < itnum; n++){
		if(abs(z)>2.0) break;
		cdr *= z;
		cdr *= 2;
		cdr += 1;

		z *= z;
		z += c;
	}

	float r = abs(z);
	float dr = abs(cdr);

	switch (retval){
	case 2:
		return log(r) * r/dr;
		break;
	case 1:
		return dr;
		break;
	default:
		return r;
		break;
	}
}

// distance test (4D)
float jtdist4d(complex<float> z, complex<float> c, int itnum, int retval){
	complex<float> cdrz = 1;
	complex<float> cdrc = 1;
	for(char n = 0; n < itnum; n++){
		if(abs(z)>2.0) break;
		cdrz *= z;
		cdrz *= 2;
		cdrz += 1;

		cdrc *= z;
		cdrc *= 2;

		z *= z;
		z += c;
	}

	float r = abs(z);
	float dr = abs(cdrc);

	switch (retval){
	case 2:
		return log(r) * r/dr;
		break;
	case 1:
		return dr;
		break;
	default:
		return r;
		break;
	}
}


// nice color spectrum mapping given distance
float spectrumSkew(float depth, int rgb){
	float skew = 255+255*cosf(M_PI*sinf(depth + rgb*M_PI/3));
	if(skew>255.0){
		return 255;
	}else{
		return skew;
	}
};


complex<float> z,c;
float distr, distd, distl;


int main(int argc, char** argv){
	if (argc < 3){
		fprintf(stderr, "ohp, you need 2 numbers. Give a & b for c = a + bi\n");
		return EXIT_FAILURE;
	}

	// collect constant iterator from execution input
	c = atof(argv[1]) + atof(argv[2])*I;

	// prep buffers
	//unsigned char ptsr[W*H*3] = {0};
	//unsigned char *readheadr = ptsr;
	//unsigned char ptsd[W*H*3] = {0};
	//unsigned char *readheadd = ptsd;
	unsigned char ptsl[W*H*3] = {0};
	unsigned char *readheadl = ptsl;

	for(size_t y=0; y<H; y++){
		for(size_t x=0; x<W; x++){

			// collect initial z from coordinate
			z = l_trans((float)y,0.0,(float)H,-2.0,2.0) * I;
			z += l_trans((float)x,0.0,(float)W,-2.0,2.0);

			// calculate
			//distr = jtdist(z,c,30,0);
			//distd = jtdist(z,c,30,1);
			distl = jtdist(z,c,30,2);

			// write colors to buffers
			*readheadl++ = spectrumSkew(1*distl, 0);
			*readheadl++ = spectrumSkew(1*distl, 1);
			*readheadl++ = spectrumSkew(1*distl, 2);
/*
			*readheadr++ = spectrumSkew(1*distr, 0);
			*readheadr++ = spectrumSkew(1*distr, 1);
			*readheadr++ = spectrumSkew(1*distr, 2);

			*readheadd++ = spectrumSkew(1*distd, 0);
			*readheadd++ = spectrumSkew(1*distd, 1);
			*readheadd++ = spectrumSkew(1*distd, 2);

			if(jt(z,c,30)){
				*readhead++ = 255;
				*readhead++ = 0;
				*readhead++ = 0;
			}else{readhead+=3;}
*/
		}
	}

	// write buffers to pngs
	//stbi_write_png("juliadistr.png", W, H, 3, ptsr, W*3); 
	//stbi_write_png("juliadistd.png", W, H, 3, ptsd, W*3); 
	stbi_write_png("juliadistl.png", W, H, 3, ptsl, W*3); 
}
