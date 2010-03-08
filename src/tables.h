// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//-----------------------------------------------------------------------------
/// \file
/// \brief Lookup tables

#ifndef __TABLES__
#define __TABLES__

#ifdef LINUX
#include <math.h>
#endif

#include "m_fixed.h"

#define FINEANGLES 8192
#define FINEMASK (FINEANGLES - 1)
#define FINEANGLE_C(x) ((((x)*(FINEANGLES/8))/(360/8)) & FINEMASK) // ((x*(ANGLE_45/45))>>ANGLETOFINESHIFT) & FINEMASK
#define ANGLETOFINESHIFT 19 // 0x100000000 to 0x2000

// Effective size is 10240.
extern fixed_t finesine[5*FINEANGLES/4];

// Re-use data, is just PI/2 phase shift.
extern fixed_t *finecosine;

// Effective size is 4096.
extern fixed_t finetangent[FINEANGLES/2];

#define ANG1   0x00B60B61 //0.B6~
#define ANG2   0x016C16C1 //.6C1~
#define ANG10  0x071C71C7 //.1C7~
#define ANG15  0x0AAAAAAB //A.AA~
#define ANG20  0x0E38E38E //.38E~
#define ANG30  0x15555555 //.555~
#define ANG60  0x2AAAAAAB //A.AA~
#define ANG64h 0x2DDDDDDE //D.DD~
#define ANG105 0x4AAAAAAB //A.AA~
#define ANG210 0x95555555 //.555~
#define ANG255 0xB5555555 //.555~
#define ANG340 0xF1C71C72 //1.C7~
#define ANG350 0xF8E38E39 //8.E3~

#define ANGLE_11hh 0x08000000
#define ANGLE_22h  0x10000000
#define ANGLE_45   0x20000000
#define ANGLE_67h  0x30000000
#define ANGLE_90   0x40000000
#define ANGLE_122h 0x50000000
#define ANGLE_135  0x60000000
#define ANGLE_157h 0x70000000
#define ANGLE_180  0x80000000
#define ANGLE_202h 0x90000000
#define ANGLE_225  0xA0000000
#define ANGLE_247h 0xB0000000
#define ANGLE_270  0xC0000000
#define ANGLE_292h 0xD0000000
#define ANGLE_315  0xE0000000
#define ANGLE_337h 0xF0000000
#define ANGLE_MAX  0xFFFFFFFF

#if defined (_MSC_VER)
typedef unsigned __int32 angle_t;
#else
typedef UINT32 angle_t;
#endif

// To get a global angle from Cartesian coordinates, the coordinates are
// flipped until they are in the first octant of the coordinate system, then
// the y (<=x) is scaled and divided by x to get a tangent (slope) value
// which is looked up in the tantoangle[] table.
#define SLOPERANGE 2048
#define SLOPEBITS 11
#define DBITS (FRACBITS - SLOPEBITS)

// The +1 size is to handle the case when x == y without additional checking.
extern angle_t tantoangle[SLOPERANGE+1];

// Utility function, called by R_PointToAngle.
unsigned SlopeDiv(unsigned num, unsigned den);

// angle_t to fixed_t f(ANGLE_45) = 45*FRACUNIT
FUNCMATH fixed_t AngleFixed(angle_t af);
// fixed_t to angle_t f(45*FRACUNIT) = ANGLE_45
FUNCMATH angle_t FixedAngle(fixed_t fa);
// and with a factor, with +factor for (fa/factor) and -factor for (fa*factor)
FUNCMATH angle_t FixedAngleC(fixed_t fa, fixed_t factor);

// The table values in tables.c are calculated with this many fractional bits.
#define FINE_FRACBITS 16

// These macros should be used in case FRACBITS < FINE_FRACBITS.
#define FINESINE(n) (finesine[n]>>(FINE_FRACBITS-FRACBITS))
#define FINECOSINE(n) (finecosine[n]>>(FINE_FRACBITS-FRACBITS))
#define FINETANGENT(n) (finetangent[n]>>(FINE_FRACBITS-FRACBITS))

#endif
