
# PPM Transformation Project

This project provides various image processing functions for PPM (Portable Pixmap) files. 
## Functions

It includes the following functions:

* sepia(): converts an image to sepia tone.
* mirror(): horizontally mirrors an image.
* nup(): scales down an image by a factor of scale.
* bitmap(): converts a PPM image to PBM (Portable Bitmap) format.
* grayscale(): converts a PPM image to PGM (Portable Graymap) format.
* thumbnail(): scales down an image to the specified width and height.

## Usage

The program reads a PPM file and applies one or more image processing functions on it. The processed image can then be written to a new file.
## Command-line Arguments

The program accepts the following command-line arguments:
* -h, --help: shows the help message.
* -i <input_file>, --input <input_file>: specifies the input file.
* -o <output_file>, --output <output_file>: specifies the output file.
* -s <scale>, --scale <scale>: specifies the scale factor for the nup() function.
* -w <width>, --width <width>: specifies the width of the output image for the thumbnail() function.
* -t <height>, --height <height>: specifies the height of the output image for the thumbnail() function.


## Examples

* Convert an image to sepia tone and write it to a new file:

```sh
$ ./ppm_transform -i input.ppm -o output.ppm sepia
```

* Scale down an image by a factor of 2 and write it to a new file:

```sh
$ ./ppm_transform -i input.ppm -o output.ppm -s 2 nup
```

* Convert a PPM image to PGM format and write it to a new file:

```sh
$ ./ppm_transform -i input.ppm -o output.pgm grayscale
```

* Create a thumbnail image with a width of 100 and a height of 50:

```sh
$ ./ppm_transform -i input.ppm -o output.ppm -w 100 -t 50 thumbnail
```
