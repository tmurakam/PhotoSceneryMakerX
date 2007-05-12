/*
 * Photo Scenery Maker
 *
 * Copyright (C) 2003 Takuya Murakami
 *
 * latlon.cpp : Latitude/Longitude calculation
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
#include <vcl.h>
#pragma hdrstop

#include <math.h>
#include "latlon.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void Angle::SetStr(AnsiString s)
{
	char buf[100];
        strncpy(buf, s.c_str(), sizeof(buf));

	char *p;
        double dd, mm, ss;

        dd = mm = ss = 0.0;

	p = strtok(buf, ":");
	if (p) {
		dd = atof(p);

		p = strtok(NULL, ":");
		if (p) {
			mm = atof(p);
			p = strtok(NULL, ":");
			if (p) {
				ss = atof(p);
			}
		}
	}

	if (dd >= 0) {
		deg = dd + mm / 60.0 + ss / 3600.0;
	} else {
		deg = -dd + mm / 60.0 + ss / 3600.0;
		deg = -deg;
	}
		
}

AnsiString Angle::GetStr(void)
{
	int dd, mm;
        double ss, t;
	int sign = 1;

	t = deg;
	if (t < 0) {
		t = -t;
		sign = -1;
	}
        dd = (int)t;
	t = (t - dd) * 60.0;
        mm = (int)t;
        t = (t - mm) * 60.0;
        ss = t;

        AnsiString s;
	if (isHighPres) {
		s.sprintf("%d:%02d:%2.20f", dd * sign, mm, ss);
	} else {
		s.sprintf("%d:%02d:%2.2f", dd * sign, mm, ss);
	}
        return s;
}

//---------------------------------------------------------------------------
#define EQ2NPL          (40007.0 * 1000 / 4)    /* distance from equator to north pole */
#define LAT2M(x)        ((x) / 90.0 * EQ2NPL)     /* latitude[degree] to distance[meter] */
#define	DEG2RAD(d)	((d) * M_PI / 180.0)
#define M2LAT(x)	((x) * 90.0 / EQ2NPL)

void LatLon::CalcDistance(const LatLon &tgt, double *dx, double *dy)
{
	*dy = LAT2M(tgt.lat.deg - lat.deg);
	*dx = LAT2M(tgt.lon.deg - lon.deg) *
        	cos(DEG2RAD((tgt.lat.deg + lat.deg) / 2.0));
}

void LatLon::CalcLatLon(const LatLon &base, double dx, double dy)
{
	lat.deg = base.lat.deg + M2LAT(dy);
	lon.deg = base.lon.deg + M2LAT(dx) /
		cos(DEG2RAD(base.lat.deg + lat.deg) / 2.0);
}

