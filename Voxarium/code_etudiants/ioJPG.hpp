/***************************************************************************\
 * Copyright (C) by University Paris-Est - MISS team
 * ioJPG.hpp created in 10 2008.
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
 * Anti-doublon
 */
#ifndef __OPENKN_IMAGE__IMAGELOADERJPG_HPP__
#define __OPENKN_IMAGE__IMAGELOADERJPG_HPP__

/*
 * External Includes
 */
#include <string>

/*
 * Internal Includes
 */
#include "Image.hpp"

/*
 * Namespace
 */
namespace kn {
	/** \addtogroup Macros */
	/*@{*/
	/** \defgroup JPG_image_type JPG Image Type (5 kinds) */
	/*@{*/
	enum JPG_file_type {NONE_JPG=0, RGB_JPG=1, RGBA_JPG=2, L_JPG=3,CMYK_JPG=4};
	/*@}*/
	/*@}*/

	/** \brief Load function for JPG image.
		* This is a generic JPG loading function. It handles jpeg format file.<br>
		* This class uses the library libjpg so we do not care about format file
		* \param res Image recieving data from JPG file
		* \param filename Name of the file to load
		* \return The type of the JPG file (see kn::JPG_file_type)
		* \todo Must this function check that the extension of the name file is correct ? (.jpg/.JPG/.jpeg)
		* \todo Handle CMYK or YUV jpg file
		*/
	int loadJPG(Image<unsigned char>& res,const std::string& filename);

	/** \brief Save function for JPG image.
		* This is a generic JPG saving function. It handles jpeg format file.<br>
		* This function uses the library libjpg so we do not care about format file
		* \param res Image sending data to JPG file
		* \param filename Name of the file to saves
		* \param quality quality of the compressed image (lossy data compression)
		* \return Boolean indicating succes of export operation
		*/
	bool saveJPG(const Image<unsigned char>& res,const std::string& filename,int quality=100);

	/*
	 * End of Namespace
	 */
}

/*
 * End of Anti-doublon
 */
#endif
