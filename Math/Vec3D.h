/*
 * Vec3D.h
 *
 *  Created on: May 4, 2019
 *      Author: Joseph Haske
 */

#ifndef VEC3D_H_
#define VEC3D_H_

#include <GLFW/glfw3.h>

template <class num> class Vec3D
{
private:
	num x, y, z, magSqrd;

public:
	Vec3D(num xin, num yin, num zin);
	Vec3D();
	virtual ~Vec3D();

	void add(Vec3D v);
	void sub(Vec3D v);
	Vec3D<num> projOnto(Vec3D v);

	num dotProd(Vec3D v) {return (x * v.x) + (y * v.y) + (z * v.z);}
	Vec3D<num> crossProd(Vec3D v){return Vec3D<num>((y*v.z)-(z*v.y),(z*v.x)-(x-v.z),(x-v.y)-(y-v.x));}
	num magSquared() {return (x * x) + (y * y) + (z * z);}
	num getX() {return x;}
	num getY() {return y;}
	num getZ() {return z;}
};

#endif /* VEC3D_H_ */
