/*
 * Vec3D.cpp
 *
 *  Created on: May 4, 2019
 *      Author: user1
 */

#include "Vec3D.h"

template <class num>
Vec3D<num>::Vec3D(num xin, num yin, num zin) {
	x = xin;
	y = yin;
	z = zin;
	magSqrd = magSquared();
}

template <class num>
Vec3D<num>::Vec3D(){
	x = y = z = magSqrd = 0.0f;
}

template <class num>
Vec3D<num>::~Vec3D() {
	// TODO Auto-generated destructor stub
}

template <class num>
void Vec3D<num>::add(Vec3D v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
template <class num>
void Vec3D<num>::sub(Vec3D v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

template <class num>
Vec3D<num> Vec3D<num>::projOnto(Vec3D v)
{
	num temp = dotProd(v)/v.magSqrd;
	return Vec3D(temp*v.x, temp*v.y, temp*v.z);
}

//Instantiate relevant templates
template class Vec3D<GLfloat>;
template class Vec3D<int>;
