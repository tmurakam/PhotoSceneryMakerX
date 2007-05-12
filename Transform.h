/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * Transform.h : Transform coordinates
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */
//---------------------------------------------------------------------------

#ifndef TransformH
#define TransformH

#include <IniFiles.hpp>

#include "latlon.h"

//---------------------------------------------------------------------------
class Vector {
public:
	int x, y;
};

// Control point for coordinates correction
class ControlPoint {
public:
	LatLon	p;
	Vector	v;
};

class XYparam {
public:
	double	x;
	double	y;
};

class BitmapBoundary {
public:
	bool	useWhole;
	int	top;
	int	left;
	int	right;
	int	bottom;

	BitmapBoundary(void) { useWhole = true; top = left = right = bottom = 0; }
};

//
// Transformation class
//
class Transform {
private:
	int	width;			// bitmap width
	int	height;			// bitmap height
	BitmapBoundary boundary;

	LatLon	base;			// Upper-Left(North-West) Latitude/Longitude
	XYparam	res;			// Resolution (degree/pixel)
	XYparam optres;		       	// Optimal Resolution (degree/pixel)	
	XYparam	mag;			// Magnify rate

private:
	void CalcResolution(void);
	void writeResolution(XYparam r)	{ res = r; CalcResolution(); }

public:
	bool CalcParameters(ControlPoint *cp);
	LatLon CalcLatLon(int x, int y);
	int CalcX(double lon);
	int CalcY(double lat);
	void CalcOptSize(int width, int height, int *correct_w, int *correct_h);

        // TPicture *TransImage(TPicture *pict);

	__property int Width = { read=width, write=width };
	__property int Height = { read=height, write=height };
	__property BitmapBoundary Boundary = { read=boundary, write=boundary };
	__property LatLon Base = { read=base, write=base};
	__property XYparam Resolution = { read=res, write=writeResolution};
	__property XYparam Optres = { read=optres };
};

#endif
