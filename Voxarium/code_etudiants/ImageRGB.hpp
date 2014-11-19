/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * ImageRGB.hpp created in 09 2008.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.	 If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_IMAGE__IMAGERGB_HPP__
#define __OPENKN_IMAGE__IMAGERGB_HPP__

/*
 * External Includes
 */
#include <iostream>
#include <string>


/*
 * Internal Includes
 */
#include "Image.hpp"

/*
 * Namespace
 */
namespace kn{
		/*
		 * Class definition
		 */
		 
		/** \brief Class for RGB image 
		 *
		 */
		template<typename T>
		class ImageRGB : public Image<T> {

			/*
			 * Constructor & destructors
			 */
		public:
			/** \brief Constructor to build a 0 size image
			 */
			ImageRGB();
			/** \brief Constructor to build an allocated empty image RGB or an image from a raw data buffer
			 *	\param w width of the image
			 *	\param h height of the image
			 *	\param buffer optional data buffer WHICH IS NOT COPYIED
			 */
			ImageRGB(const size_t w, const size_t h, T * buffer=NULL);
			/** \brief Copy Constructor
			 *	\param e Error to clone
			 */
			ImageRGB(const ImageRGB & e);
			/** \brief dealoccates image data
			 */
			virtual ~ImageRGB();

		};
		
		/*
		 * Templates definitions
		 */

		/*
		 * Functions definitions
		 */
		template<typename T>
		ImageRGB<T>::ImageRGB(void) : Image<T>() {
			this->imageNbChannel = 3;
		}

		template<typename T>
		ImageRGB<T>::ImageRGB(const size_t w,const size_t h,T* buffer) : Image<T>(w,h,3,buffer) {
		}

		template<typename T>
		ImageRGB<T>::ImageRGB(const ImageRGB<T> & e) : Image<T>(e) {
		}

		template<typename T>
		ImageRGB<T>::~ImageRGB(void) {
		}

		/*
		 * Type definition
		 */	   
		typedef ImageRGB<float> ImageRGBf;
		typedef ImageRGB<double> ImageRGBd;
		typedef ImageRGB<unsigned char> ImageRGB8u;
		typedef ImageRGB<unsigned short int> ImageRGB16u;
		typedef ImageRGB<unsigned int> ImageRGB32u;
		typedef ImageRGB<unsigned long int> ImageRGB64u;
		typedef ImageRGB<char> ImageRGB8s;
		typedef ImageRGB<short int> ImageRGB16s;
		typedef ImageRGB<int> ImageRGB32s;
		typedef ImageRGB<long int> ImageRGB64s;
		

		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
