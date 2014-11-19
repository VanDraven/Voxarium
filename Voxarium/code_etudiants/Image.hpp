/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team   
 * Image.hpp created in 09 2008.
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
#ifndef __OPENKN_IMAGE__IMAGE_HPP__
#define __OPENKN_IMAGE__IMAGE_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4996)
#endif

/*
 * External Includes
 */
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

/*
 * Internal Includes
 */
#include "ImageException.hpp"

/*
 * Namespace
 */
namespace kn{
	
		/*
		 * Class definition
		 */

		/** \brief Container for images
		 *	This class represent any generic image for any size, and basic type and any nb channel.
		 *	The data of the image is represented as a unidimensionnal array of the basic typename.
		 *	Moreover, we store the position of any row allowing a fast acces to any pixel of the image.
		 *	The first row is the top row and each row is stored from left to right.
		 */
		template<typename T>
		class Image {

			/*
			 * Constructor & destructors
			 */
		public:
			/** \brief Constructor to build a 0 size image
			 */
			Image();

			/** \brief Constructor to build an allocated empty image or an image from a raw data buffer
			 *	\param width width of the image
			 *	\param height height of the image
			 *	\param nbChannel depth of the image
			 *	\param buffer optional data buffer WHICH IS NOT COPYIED
			 */
			Image(const size_t width, const size_t height, const size_t nbChannel, T* buffer=0);

			/** \brief Copy Constructor
			 * \param i Image to clone
			 */
			Image(const Image<T> & i);

			/** \brief dealoccates image data
			 */
			virtual ~Image();

			/** \brief Friend function for PPM file format loader
			 * \param res image receiving data
			 * \param filename filename containing data
			 * \return nb_channel of image (depending on format P1,P2,P3,P4,P5 or P6)
			 */
			friend int kn::loadPPM(Image<unsigned char>& res,const std::string& filename);
			/** \brief Friend function for TGA file format loader
			 * \param res image receiving data
			 * \param filename filename containing data
			 * \return The type of the TGA file (see kn::TGA_file_type)
			 */
			friend int kn::loadTGA(Image<unsigned char>& res,const std::string& filename);
			/** \brief Friend function for JPG file format loader
			 * \param res image receiving data
			 * \param filename filename containing data
			 * \return The type of the JPG file (see kn::JPG_file_type)
			 */
			friend int kn::loadJPG(Image<unsigned char>& res,const std::string& filename);
			/** \brief Friend function for HDR file format loader
			 * \param res image receiving data
			 * \param filename filename containing data
			 * \return 1 if succeeds
			 */
			friend int kn::loadHDR(Image<float>& res,const std::string& filename);
			/** \brief Friend function for PNG file format loader
			 * \param res image receiving data
			 * \param filename filename containing data
			 * \return The type of PNG file (see kn::PNG_file_type)
			 */
			friend int kn::loadPNG(Image<unsigned char>& res,const std::string& filename);

		protected :
			/** \brief raw data of the image
			 */
			T * data;

			/** \brief pointers on each row of the image on the raw date
			 */
			T ** rows;

			/** \brief allocate and initialize the rows array
			 */
			void initRows();

			/** \brief pointer on the begining of raw data
			 */
			T * begin_;

			/** \brief pointer on the end of raw data
			 */
			T * end_;

		public :
			/** \brief getting the raw data of the image
			 * \return raw data of the image
			 */
			inline virtual T  * begin() const {return begin_;}

			/** \brief getting the end of raw data of the image
			 * \return end of raw data of the image
			 */
			inline virtual T  * end() const {return end_;}
			
		protected :
			/** \brief width of the image
			 */
			size_t imageWidth;

			/** \brief height of the image
			 */
			size_t imageHeight;

			/** \brief nb channel of the image
			 */
			size_t imageNbChannel;

			/** \brief Total size of the image (w*h*d)
			 */
			size_t imageSize;
		public:
			/** \brief getting the width of the image
			 * \return the width of the image
			 */
			inline virtual size_t width() const {return imageWidth; }

			/** \brief getting the height of the image
			 * \return the height of the image
			 */
			inline virtual size_t height() const {return imageHeight; }

			/** \brief getting the number of channel of the image
			 * \return the number of channel of the image
			 */
			inline virtual size_t nbChannel() const {return imageNbChannel; }

			/** \brief getting the total size of the image
			 * \return the total of the image
			 */
			inline virtual size_t size() const {return imageSize; }
			
			/** \brief get pointer on the asked pixel
			 *	\param x width position of the pixel
			 *	\param y height position of the pixel
			 *	\return a buffer with the pixel
			 */
			inline virtual T * operator()(const unsigned int x, const unsigned int y) const {
				return (rows[y]+x*nbChannel());
			}

			/** \brief get pointer on the asked pixel (with bounds checking).
			 * This function is the same than the operator() but checks if indices are valid.
			 * \param x width position of the pixel
			 * \param y height position of the pixel
			 * \return a buffer with the pixel
			 */
			inline virtual T * at(const unsigned int x, const unsigned int y) const {
				if (x>=width() || y>=height() ) {
					std::ostringstream o("Operator("); o << x << "," << y << ") " ;
					throw ImageException(o.str(), "Invalid range");
				}
				return (*this)(x,y);//(rows[y]+x*nbChannel());
			}

			/** \brief get component value of the asked pixel
			 *	\param x width position of the pixel
			 *	\param y height position of the pixel
			 *	\param d component number
			 *	\return a value of the component
			 */
			inline virtual T & operator()(const unsigned int x, const unsigned int y, const unsigned int d) {
				return (*this)(x,y)[d];
			}

			/** \brief get component value of the asked pixel (with bounds checking).
			 *	\param x width position of the pixel
			 *	\param y height position of the pixel
			 *	\param d component number
			 *	\return a value of the component
			 */
			inline virtual T & at(const unsigned int x, const unsigned int y, const unsigned int d) {
				if (d>=imageNbChannel || x>=width() || y>=height()) {
					std::ostringstream o("Operator("); o << x << "," << y << "," <<d <<") " ;
					throw ImageException(o.str(), "Invalid range");
				}
				return ((*this)(x,y)[d]);
			}

			/** \brief get component value of the asked pixel
			 * \param x width position of the pixel
			 * \param y height position of the pixel
			 * \param d component number
			 * \return a value of the component
			 */
			inline virtual const T & operator()(const unsigned int x, const unsigned int y, const unsigned int d)const {
				return (*this)(x,y)[d];
			}

			/** \brief get component value of the asked pixel (with bounds checking)
			 * This function behaves the same than the operator() but checks if indices are valid respect to
			 * the size of
			 * \param x width position of the pixel
			 * \param y height position of the pixel
			 * \param d component number
			 * \return a value of the component
			 */
			inline virtual const T & at(const unsigned int x, const unsigned int y, const unsigned int d)const {
				if (d>=imageNbChannel || x>=width() || y>=height()) {
					std::ostringstream o("Operator("); o << x << "," << y << "," <<d <<") " ;
					throw ImageException(o.str(), "Invalid range");
				}
				return (*this)(x,y)[d];
			}
			
			/** \brief get component value of the asked pixel (with bounds checking)
			 * This function behaves the same than the operator() but checks if indices are valid respect to
			 * the size of
			 * \param x width position of the pixel
			 * \param y height position of the pixel
			 * \param color : array containing the resulting color, should have a nbchannel size.
			 */
			void atBilinear(const double x, const double y, T *color)const;

			/** \brief check whether a pixel position is a valid position in the image or not.
			 * \param x width position of the pixel
			 * \param y height position of the pixel
			 * \return true if (x,y) is a valid position in the image, else return false
			 */
			inline bool contains(const int x, const int y)const
			    {return (x>=0 && x<(int)imageWidth && y>=0 && y<(int)imageHeight);}

			/** \brief copy on this image the content of another if they have the same resolution and number of channel; if the calling image have width = height = 0, this function create the adequat memory, else throws an exception.
			 * \param i : source image
			 * \throw ImageException : incompatible image size
			 * \return a reference to the destination image
			 */
			virtual Image<T> & operator=(const Image &i) ;

			/** \brief fill all the pixels component to the parameter value
			 *  \param value : value used to fill the image
			 */
			inline void fill(const T &value) {
			  std::fill(begin_,end_,value);
			}

			/** \brief flip the image vertically
			 */
		 	inline void flip() {
			   for(unsigned int i=0; i<imageHeight/2; i++)
			     std::swap_ranges(rows[i],rows[i+1],rows[imageHeight-i-1]);
			}

			/** \brief flop the image horizontally
			 */
		        inline void flop() {
			  for(unsigned int i=0; i<imageHeight; i++)
			    for(unsigned int j=0; j<imageWidth/2; j++)
			      for(unsigned int c=0; c<imageNbChannel;c++)
				std::swap(rows[i][imageNbChannel*j+c],rows[i][imageNbChannel*(imageWidth-j-1)+c]);
			}

			/** \brief rotate the image by PI/2 (clockwise)
			 */
		        inline void rotate() {
		          T* buffer = new T[size()*sizeof(T)];
		          T* b = buffer;
		            for(int j=imageWidth-1, d=(imageWidth-1)*imageNbChannel; j>=0; j--,d-=imageNbChannel)
		              for(unsigned int i=0; i<imageHeight; i++)
			        for(unsigned int c=0; c<imageNbChannel;c++,b++)
				  *b = rows[i][d+c];
			  imageSize = 0;
			  buildImageFromBuffer(imageHeight, imageWidth, imageNbChannel, buffer, false);
			}

			/** \brief rotate the image by -PI/2  (counterclockwise) 
			 */
		        inline void rotateInverse() {
		          T* buffer = new T[size()*sizeof(T)];
		          T* b = buffer;
		            for(unsigned int j=0, d=0; j<imageWidth; j++,d+=imageNbChannel)
		              for(int i=imageHeight-1; i>=0; i--)
			        for(unsigned int c=0; c<imageNbChannel;c++,b++)
				  *b = rows[i][d+c];
			  	imageSize = 0;
			  	buildImageFromBuffer(imageHeight, imageWidth, imageNbChannel, buffer, false);
			}

			
			/** \brief Get a sub part of the image. 
			  * The sub part need to be contained in the image,, else function throws an exception.
			    \param x the x-coordinate of the top left corner of sub part
			    \param y the y-coordinate of the top left corner of sub part
			    \param sub the image which will store the sub part the dimensions of sub are the one of the sub part
			 */
		        void getSubImage(unsigned int x, unsigned int y, Image<T>& sub)const;

			/** \brief Set a sub part of the image. 
			  * The sub part need to be contained in the image,, else function throws an exception.
			    \param x the x-coordinate of the top left corner of sub part
			    \param y the y-coordinate of the top left corner of sub part
			    \param sub the image which contains the sub part the dimensions of sub are the one of the sub part
			 */
		        void setSubImage(unsigned int x, unsigned int y, const Image<T>& sub);


			/*
			 * Building and erasing images
			 */
		private:
			/** \brief This function is used ONLY ON 0 SIZED Images to build an image from a buffer which can optionnaly be NOT copied
			 * \param width width of the image
			 * \param height height of the image
			 * \param nbChannel depth of the image
			 * \param buffer data buffer
			 * \param copy flag to control wether the buffer is copied or not
			 */
			void buildImageFromBuffer(const size_t width, const size_t height, const size_t nbChannel, T* buffer, const bool copy=true);

			/** \brief This function is used ONLY ON 0 SIZED Images to build an image from another Image which can optionnaly be NOT copied
			 * \param i the source image
			 * \param copy flag to control wether the buffer is copied or not
			 */
			void buildImageFromImage(const Image<T> & i, const bool copy=true);

		private:
			/** \brief This function is used internaly ONLY ON 0 SIZED Images to build an empty image
			 * \param width width of the image
			 * \param height height of the image
			 * \param nbChannel depth of the image
			 */
			void buildEmptyImage(const size_t width, const size_t height, const size_t nbChannel);

			/** \brief This function allows to empty/erase the data of an image
			 */
			void erase();

		};

		/*
		 * Templates definitions
		 */

		/*
		 * Functions definitions
		 */
		template<typename T>
		Image<T>::Image() {
			imageWidth = 0;
			imageHeight = 0;
			imageNbChannel = 0;
			imageSize = 0;
			
			rows = 0;
			data = 0;
			begin_ = 0;
			end_ = 0;
			//std::cerr<<"CONSTRUCT VIDE"<<std::endl;
		}

		template<typename T>
		Image<T>::Image(const size_t w, const size_t h, const size_t d,	 T* buffer) {
			imageSize = 0;
			imageWidth = 0;
			imageHeight = 0;
			imageNbChannel = 0;
			imageSize = 0;
			
			rows=0;
			data=0;
			begin_ = 0;
			end_ = 0;

			if (buffer) {
				buildImageFromBuffer(w,h,d,buffer);
			}
			else {
				buildEmptyImage(w,h,d);
			}
		}

		template<typename T>
		Image<T>::Image(const Image<T> & i) {
			imageSize = 0;
			imageSize = 0;
			imageWidth = 0;
			imageHeight = 0;
			imageNbChannel = 0;
			imageSize = 0;
			
			rows=0;
			data=0;
			begin_ = 0;
			end_ = 0;

			buildImageFromImage(i,true);
		}

		template<typename T>
		Image<T>::~Image() {
			erase();
		}

		template<typename T>
		void Image<T>::initRows() {
			unsigned int i;
			if(rows) {
				delete[] rows;
				rows = 0;
			}
			rows = new T*[imageHeight];
			for (i =0; i <imageHeight; i++) {
				rows[i] = (data+(i*imageWidth*imageNbChannel));
			}
		}
		
		template<typename T>
		void Image<T>::buildImageFromBuffer(const size_t width, const size_t height,
						    const size_t nbChannel, T* buffer, const bool copy) {
			if (size()) {
				throw ImageException("buildImageFromImage","Image already allocated");
			}
			imageWidth = width;
			imageHeight = height;
			if (imageNbChannel == 0) imageNbChannel = nbChannel;
			imageSize = imageWidth*imageHeight*imageNbChannel;
			if (copy) {
				if(data){
					delete[] data;
					data = 0;
				}
				data = new T[size()*sizeof(T)];
				std::copy(buffer,buffer+size(),data);
			}
			else {
				if(data){
					delete[] data;
				}
				data = buffer;
			}
			initRows();

			begin_ = data;
			end_ = data+imageSize;
		}
		
		template<typename T>
		void Image<T>::buildImageFromImage(const Image<T> & i, const bool copy) {
			buildImageFromBuffer(i.imageWidth,i.imageHeight,i.imageNbChannel,i.begin_,copy);
		}

		template<typename T>
		void Image<T>::buildEmptyImage(const size_t width, const size_t height, const size_t nbChannel) {
			if(imageSize) {
				throw ImageException("buildEmptyImage","Image already allocated");			   
			}			
			imageWidth = width;
			imageHeight = height;
			imageNbChannel = nbChannel;
			imageSize = width * height * nbChannel;
            if(data){
                delete[] data;
                data = 0;
            }
			data = new T[imageSize * sizeof(T)];
			initRows();

			begin_ = data;
			end_ = data+imageSize;
		}
		
		
		template<typename T>
		void Image<T>::erase() {
			imageWidth = 0;
			imageHeight = 0;
			imageNbChannel = 0;
			imageSize = 0;
			if(data) delete[] data;
			if(rows) delete[] rows;
			data = 0;
			rows = 0;
			begin_ = 0;
			end_ = 0;
		}


		template<typename T>
		Image<T> & Image<T>::operator=(const Image &i) {
			// precaution
			if(&i == this) return *this;

			// 0 size image
			if(this->imageWidth  == 0 && this->imageHeight ==0){
			    buildImageFromImage(i);
			    return *this;
			}

			// standard copy
			if(this->imageWidth  == i.imageWidth  && 
			   this->imageHeight == i.imageHeight &&
			   this->imageNbChannel  == i.imageNbChannel)
			std::copy(i.begin_,i.end_,this->begin_);
			else throw ImageException("operator=","incompatible image size");

			return *this;
		}
		
		template<typename T>
		void Image<T>::getSubImage(unsigned int x, unsigned int y, Image<T>& sub)const{
			if(sub.imageNbChannel != imageNbChannel)
				throw ImageException("incompatible nb channel","Image<T>::getSubImage");
			if(sub.imageWidth+x > imageWidth || sub.imageHeight+y > imageHeight)
				throw ImageException("incompatible dimensions","Image<T>::getSubImage");
			unsigned int dx = x*imageNbChannel;
			unsigned int s = sub.imageWidth*imageNbChannel;
			for(unsigned int j = 0; j < sub.imageHeight; j++)
				std::copy(rows[j+y]+dx,rows[j+y]+dx+s, sub.rows[j]);
		}
		
		
		template<typename T>
		void  Image<T>::setSubImage(unsigned int x, unsigned int y, const Image<T>& sub){
			if(sub.imageNbChannel != imageNbChannel)
				throw ImageException("incompatible nb channel","Image<T>::setSubImage");
			if(sub.imageWidth+x > imageWidth || sub.imageHeight+y > imageHeight)
				throw ImageException("incompatible dimensions","Image<T>::setSubImage");
			unsigned int dx = x*imageNbChannel;
			unsigned int s = sub.imageWidth*imageNbChannel;
			for(unsigned int j = 0; j < sub.imageHeight; j++)
				std::copy(sub.rows[j],sub.rows[j]+s,rows[j+y]+dx);
		}
		
		

		template<typename T>
		void Image<T>::atBilinear(const double x, const double y, T *color)const{
			// 4 concerned pixels
			double x1 = floor(x);
			double y1 = floor(y);
			int    x2    = (int)x1+1;
			int    y2    = (int)y1+1;

			// default : border is black
			std::vector<T> black(imageNbChannel);
			std::fill(black.begin(),black.end(),T(0));
			
			// 4 colors
			T *color1  = &(black[0]);
			T *color2  = &(black[0]);
			T *color3  = &(black[0]);
			T *color4  = &(black[0]);
			
			// color1
			if(contains((int)x1,(int)y1)) color1 = (*this)((int)x1,(int)y1);

			// color2
			if(contains((int)x1,y2)) color2 = (*this)((int)x1,y2);

			// color3
			if(contains(x2,y2)) color3 = (*this)(x2,y2);

			// color4
			if(contains(x2,(int)y1)) color4 = (*this)(x2,(int)y1);
			  
			for(unsigned int c=0; c<imageNbChannel; ++c)
			    color[c] = (T)(((x-x1)*color4[c] + (1.0-(x-x1))*color1[c]) * (1.0-(y-y1)) +
			                   ((x-x1)*color3[c] + (1.0-(x-x1))*color2[c]) * (y-y1));
		}
		
		
		

		/*
		 * End of Namespace
		 */
	}

/*
 * End of Anti-doublon
 */
#endif
