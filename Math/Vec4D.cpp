/*
 * Vec4D.cpp
 *
 *  Created on: May 5, 2019
 *      Author: Joseph Haske
 */

#include "Vec4D.h"

/**
 * This constructor allows for each vector element to be defined. magSqrd is calculated by default.
 *
 * @param win Input for the w-axis.
 * @param xin Input for the x-axis.
 * @param yin Input for the y-axis.
 * @param zin Input for the z-axis.
 */
template <class num>
Vec4D<num>::Vec4D(num win, num xin, num yin, num zin) {
	w = win;
	x = xin;
	y = yin;
	z = zin;
	magSqrd = magSquared();
}

/**
 * This constructor assumes w, x, y, z, and magSqrd are zero.
 */
template <class num>
Vec4D<num>::Vec4D(){
	w = x = y = z = magSqrd = 0.0f;
}

/**
 * The destructor still needs to be developed
 */
template <class num>
Vec4D<num>::~Vec4D() {
	// TODO Auto-generated destructor stub
}

/**
 * Takes an input Vec4D and adds it to the current one, storing the result in place of this vector.
 *
 * @param v The vector to be added.
 */
template <class num>
void Vec4D<num>::add(Vec4D v)
{
	w += v.w;
	x += v.x;
	y += v.y;
	z += v.z;
}

/**
 * Takes an input Vec4D and subtracts it from the current one, storing the result in place of this vector.
 *
 * @param v The vector to be subtracted.
 */
template <class num>
void Vec4D<num>::sub(Vec4D v)
{
	w -= v.w;
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

/**
 * Takes an input Vec4D and scales the current one in each direction, storing the result in place of this vector.
 *
 * @param v The vector to be multiplied by.
 */
template <class num>
void Vec4D<num>::scale(Vec4D v)
{
	w *= v.w;
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

/**
 * Projects this vector onto the input Vec4D.
 *
 * @param v The vector to be projected on.
 * @return Creates a new Vec4D and returns the result of the projection.
 */
template <class num>
Vec4D<num> Vec4D<num>::projOnto(Vec4D v)
{
	num temp = dotProd(v)/v.magSqrd;
	return Vec4D(temp*v.w, temp*v.x, temp*v.y, temp*v.z);
}

//Instantiate relevant templates
template class Vec4D<GLfloat>;
template class Vec4D<int>;
