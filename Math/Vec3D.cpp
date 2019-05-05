/*
 * Vec3D.cpp
 *
 *  Created on: May 4, 2019
 *      Author: Joseph Haske
 */

#include "Vec3D.h"

/**
 * This constructor allows for each vector element to be defined. magSqrd is calculated by default.
 *
 * @param xin Input for the x-axis.
 * @param yin Input for the y-axis.
 * @param zin Input for the z-axis.
 */
template <class num>
Vec3D<num>::Vec3D(num xin, num yin, num zin) {
	x = xin;
	y = yin;
	z = zin;
	magSqrd = magSquared();
}

/**
 * This constructor assumes x, y, z, and magSqrd are zero.
 */
template <class num>
Vec3D<num>::Vec3D(){
	x = y = z = magSqrd = 0.0f;
}

/**
 * The destructor still needs to be developed
 */
template <class num>
Vec3D<num>::~Vec3D() {
	// TODO Auto-generated destructor stub
}

/**
 * Takes an input Vec3D and adds it to the current one, storing the result in place of this vector.
 *
 * @param v The vector to be added.
 */
template <class num>
void Vec3D<num>::add(Vec3D v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

/**
 * Takes an input Vec3D and subtracts it from the current one, storing the result in place of this vector.
 *
 * @param v The vector to be subtracted.
 */
template <class num>
void Vec3D<num>::sub(Vec3D v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

/**
 * Takes an input Vec3D and scales the current one in each direction, storing the result in place of this vector.
 *
 * @param v The vector to be multiplied by.
 */
template <class num>
void Vec3D<num>::scale(Vec3D v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

/**
 * Projects this vector onto the input Vec3D.
 *
 * @param v The vector to be projected on.
 * @return Creates a new Vec3D and returns the result of the projection.
 */
template <class num>
Vec3D<num> Vec3D<num>::projOnto(Vec3D v)
{
	num temp = dotProd(v)/v.magSqrd;
	return Vec3D(temp*v.x, temp*v.y, temp*v.z);
}

//Instantiate relevant templates
template class Vec3D<GLfloat>;
template class Vec3D<int>;
