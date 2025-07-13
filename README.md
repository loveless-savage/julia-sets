These projects are different explorations of Julia Sets, mathematical fractals generated in the complex plane:
https://en.wikipedia.org/wiki/Julia_set

I used various algorithms and coloring systems to analyze these Julia Sets. They are separated by folders:

-basic: draw only the member points in red, with a black background
-traceable: draw the Mandelbrot Set, the fractal map of Julia Sets, large enough to trace on paper through the screen
-dist: using a formula to estimate the distance of any given point to the nearest point in the given Julia Set, along with intermediate steps showing derivatives and whatnot, to color the Sets in a vibrant and stripey way
-4d: ray tracer showing a 3D slice of the 4-dimensional sum of all Julia Sets stacked together in two additional dimensions

Each folder has directories src/ and inc/, which hold the .cpp and .h files respectively. There is also an executable bash script in each folder, titled gojulia[DIR_NAME]. Running this executable recompiles the source, executes the resulting binary, and displays the outputted image. These executables can accept different parameters to omit certain steps of this process.

Converting integer buffers to .png files was handled by stb_image_write.h, written by Sean Barrett:
https://github.com/nothings/stb/blob/master/stb_image_write.h
