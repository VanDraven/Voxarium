/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ioJPG.cpp created in 11 2008.
 * Mail : biri@univ-mlv.fr
 *
 * This file is part of the OpenKraken-image.
 *
 * The OpenKraken-image is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKraken-image is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/


/*
 * Internal Includes
 */
#include "ioJPG.hpp"
#include "ImageException.hpp"

/*
 * External Includes
 */
#include <sstream>
#include <fstream>
#include <jpeglib.h>
#include <setjmp.h>

using namespace std;

/*
 * Namespace
 */
namespace kn{
	/*
		* Functions definitions
		*/
	int loadJPG(Image<unsigned char>& res,const std::string& filename) {
		//std::cerr<<"IN loadImageJPG"<<std::endl;
		unsigned char* thebuffer;
		size_t w_size,h_size;
		unsigned int nb_component;
		std::ifstream is;
		std::stringstream serr;
		/* This struct contains the JPEG decompression parameters and pointers to
			* working space (which is allocated as needed by the JPEG library).
			*/
		struct jpeg_decompress_struct cinfo;
		/* We use our private extension JPEG error handler.
			* Note that this struct must live as long as the main JPEG parameter
			* struct, to avoid dangling-pointer problems.
			*/
		struct jpeg_error_mgr jerr;
		/* More stuff */
		FILE * infile;			/* source file */
		JSAMPARRAY buffer;	/* Output row buffer */
		int row_stride;			/* physical row width in output buffer */
		int typtmp;

		// STEP 0 : WE CHECK THAT THE IMAGE IS NOT ALREADY ALLOCATED AND OPEN THE FILE
		if (res.size()>0) {
			throw ImageException("Image already allocated. Cannot store JPG image in that image.","loadImageJPG");
		}

		//std::cerr<<"Charge fichier "<<filename<<std::endl;
		infile = fopen(filename.c_str(),"rb");
		if (infile == NULL) {
			throw ImageException("Error could not read file "+filename,"loadImageJPG");
		}
		//std::cerr<<"Fin charge fichier"<<std::endl;

		// STEP 1 : READING HEADER
		cinfo.err = jpeg_std_error(&jerr);
		/* Initialize the JPEG decompression object. */
		jpeg_create_decompress(&cinfo);
		/* Specify data source (eg, a file) */
		jpeg_stdio_src(&cinfo, infile);
		/* Read file parameters with jpeg_read_header() */
		//std::cerr<<"Read header of file"<<std::endl;
		//std::cerr<<"STRUCTURE : "<<std::endl;
		//std::cerr<<"Source mgr : "<<cinfo.src<<std::endl;
		//std::cerr<<"Image size : "<<cinfo.image_width<<"/"<<cinfo.image_height<<std::endl;
		//std::cerr<<"FILE : "<<infile<<std::endl;

		/*int resultt =*/ jpeg_read_header(&cinfo, TRUE);
		//std::cerr<<"Fin Read header of file"<<std::endl;

		h_size = cinfo.image_height;
		w_size = cinfo.image_width;
		nb_component = cinfo.num_components;
		typtmp = cinfo.jpeg_color_space;
		//std::cerr<<"IN switch"<<std::endl;
		switch(typtmp) {
			case JCS_GRAYSCALE :
				if (nb_component != 1)
					throw ImageException("Nb of component does not match type of JPG file (L)","loadImageJPG");
				typtmp = L_JPG;
				break;
			case JCS_RGB :
			case JCS_YCbCr :
				if (nb_component != 3)
					throw ImageException("Nb of component does not match type of JPG file (RGB)","loadImageJPG");
				typtmp = RGB_JPG;
				break;
			case JCS_CMYK :
				if (nb_component != 4)
					throw ImageException("Nb of component does not match type of JPG file (RGBA)","loadImageJPG");
				typtmp = RGBA_JPG;
				break;
			case JCS_YCCK :
				throw ImageException("We do not handle YCCK jpg file format","loadImageJPG");
			case JCS_UNKNOWN :
			default :
				throw ImageException("jpg file format unknown","loadImageJPG");
		}
		/* Set parameters for decompression (nothing to do) */

		// STEP 2 : READ IMAGE (Decompression)
		/* Start decompressor */
		(void) jpeg_start_decompress(&cinfo);
		/* Testing */
		if ((cinfo.output_width != (unsigned int)w_size) ||
				(cinfo.output_height != (unsigned int)h_size) ||
				((unsigned int)cinfo.out_color_components != nb_component)) {
			throw ImageException("JPG Loader error : Difference between header and jpg data in file","loadImageJPG");
		}
		/* Buffer allocation */
		thebuffer = new unsigned char[w_size*h_size*nb_component];
		if (thebuffer == NULL)
			throw ImageException("JPG Loader error : Unable to get memory !","loadImageJPG");

		/* We may need to do some setup of our own at this point before reading
		* the data.  After jpeg_start_decompress() we have the correct scaled
		* output image dimensions available, as well as the output colormap
		* if we asked for color quantization.
		* In this example, we need to make an output work buffer of the right size.
		*/
		/* JSAMPLEs per row in output buffer */
		row_stride = w_size * nb_component;
		/* Make a one-row-high sample array that will go away when done with image */
		buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

		/* while (scan lines remain to be read) */
		/*           jpeg_read_scanlines(...); */
		/* Here we use the library's state variable cinfo.output_scanline as the
		* loop counter, so that we don't have to keep track ourselves.
		*/
		unsigned char *ptr = thebuffer;//+(cinfo.output_height-1)*row_stride;
		while (cinfo.output_scanline < cinfo.output_height) {
			/* jpeg_read_scanlines expects an array of pointers to scanlines.
			* Here the array is only one element long, but you could ask for
			* more than one scanline at a time if that's more convenient.
			*/
			(void) jpeg_read_scanlines(&cinfo, buffer, 1);
/*				std::cerr<<iii++<<" : ";
			for(int j=0;j<4;j++) {
				for(int k=0;k<3;k++) {std::cerr<<(int)(buffer[0][3*j+k])<<" ";}
				std::cerr<<" / ";
			}
			std::cerr<<std::endl;*/
			/* Assume put_scanline_someplace wants a pointer and sample count. */
			memcpy(ptr,buffer[0],row_stride);
			ptr += row_stride;
		}

		/* Finish decompression */
		(void) jpeg_finish_decompress(&cinfo);
		/* Release JPEG decompression object */
		/* This is an important step since it will release a good deal of memory. */
		jpeg_destroy_decompress(&cinfo);

		// TODO Conversion for YUV type file
		//CompImage tool;
		//image_buffer = tool.convertYUVtoRVB(image_buffer,image_width,image_height);
// 			std::cerr<<"TESTING FINAL buffer : ";
// 			for(int i=0;i<4*4;i++) {
// 				if (i%4 == 0) std::cerr<<std::endl;
// 				for(int j=0;j<3;j++) std::cerr<<(int)thebuffer[i*3+j]<<" ";
// 				std::cerr<<std::endl;
// 			}
// 			std::cerr<<std::endl;

		try {
			res.buildImageFromBuffer(w_size,h_size,nb_component,thebuffer);
			if (thebuffer != NULL) delete[](thebuffer);
		}
		catch (ImageException &e) {
			// Should absolutely not happens
			if (thebuffer != NULL) delete[](thebuffer);
			throw ImageException("Exception when building image from buffer : "+e.errorString(),"loadFileJPG");
		}


		fclose(infile);
		return typtmp;

	}

	bool saveJPG(const Image<unsigned char>& res,const std::string& filename,int quality) {
		struct jpeg_compress_struct cinfo;
		struct jpeg_error_mgr jerr;
		FILE * outfile;		/* target file */
		JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
		int row_stride;		/* physical row width in image buffer */

		cinfo.err = jpeg_std_error(&jerr);
		jpeg_create_compress(&cinfo);

		// STEP 1 : Open the file
		if ((outfile = fopen(filename.c_str(), "wb")) == NULL) {
			throw ImageException("Error could not write file "+filename,"saveJPG");
		}
		jpeg_stdio_dest(&cinfo, outfile);

		// STEP 2 : Writing header structure
		cinfo.image_width = res.width(); 	/* image width and height, in pixels */
		cinfo.image_height = res.height();
		cinfo.input_components = res.nbChannel(); /* # of color components per pixel */
		switch(res.nbChannel()) {
			case 0 :
				throw ImageException("Image not allocated or empty","saveJPG");
				break;
			case 1 :
				cinfo.in_color_space = JCS_GRAYSCALE; 	/* colorspace of input image */
				break;
			case 3 :
				cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
				break;
			case 4 :
				cinfo.in_color_space = JCS_CMYK; 	/* colorspace of input image */
				break;
			default :
				throw ImageException("Unable to store a jpeg with channels != 1,3 or 4","saveJPG");
				break;
		}

		/* Now use the library's routine to set default compression parameters.
		* (You must set at least cinfo.in_color_space before calling this,
		* since the defaults depend on the source color space.)
		*/
		jpeg_set_defaults(&cinfo);
		/* Now you can set any non-default parameters you wish to.
		* Here we just illustrate the use of quality (quantization table) scaling:
		*/
		jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

		/* TRUE ensures that we will write a complete interchange-JPEG file.
		* Pass TRUE unless you are very sure of what you're doing.
		*/
		jpeg_start_compress(&cinfo, TRUE);

		/* Here we use the library's state variable cinfo.next_scanline as the
		* loop counter, so that we don't have to keep track ourselves.
		* To keep things simple, we pass one scanline per call; you can pass
		* more if you wish, though.
		*/
		row_stride = res.size()/res.height(); /* JSAMPLEs per row in image_buffer */
		//std::cerr<<"Taille stride : "<<row_stride<<std::endl;

		while (cinfo.next_scanline < cinfo.image_height) {
			/* jpeg_write_scanlines expects an array of pointers to scanlines.
			* Here the array is only one element long, but you could pass
			* more than one scanline at a time if that's more convenient.
			*/
			//std::cerr<<"Number of ligne : "<<cinfo.next_scanline<<std::endl;
			row_pointer[0] = res.begin()+(cinfo.next_scanline * row_stride);
			(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
		}

		jpeg_finish_compress(&cinfo);
		/* After finish_compress, we can close the output file. */
		fclose(outfile);


		/* This is an important step since it will release a good deal of memory. */
		jpeg_destroy_compress(&cinfo);
		return true;
	}



	/*
	 * End of Namespace
	 */
}
