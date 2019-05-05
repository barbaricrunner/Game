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
	num x; /**< The x component of the vector.*/
	num y; /**< The y component of the vector.*/
	num z; /**< The z component of the vector.*/
	num magSqrd; /**< The magnitude squared of the vector. This prevents having to calculate it multiple times.*/

public:
	Vec3D(num xin, num yin, num zin);
	Vec3D();
	virtual ~Vec3D();

	void add(Vec3D v);
	void sub(Vec3D v);
	Vec3D<num> projOnto(Vec3D v);

	/**
	 * Calculates the dot product of this vector and the input vector.
	 * @param v The input vector.
	 * @return Returns the calculated dot product.
	 */
	num dotProd(Vec3D v) {return (x * v.x) + (y * v.y) + (z * v.z);}
	/**
	 * Calculates the cross product of this vector and the input vector.
	 * @param v The input vector.
	 * @return Returns the calculated cross product as a Vec3D.
	 */
	Vec3D<num> crossProd(Vec3D v){return Vec3D<num>((y*v.z)-(z*v.y),(z*v.x)-(x-v.z),(x-v.y)-(y-v.x));}
	/**
	 * Calculates the magnitude of this vector, squared.
	 * @return Returns the calculated magnitude squared.
	 */
	num magSquared() {return (x * x) + (y * y) + (z * z);}
	/**
	 * Getter for the x component of the vector.
	 * @return Returns z.
	 */
	num getX() {return x;}
	/**
	 * Getter for the y component of the vector.
	 * @return Returns y.
	 */
	num getY() {return y;}
	/**
	 * Getter for the z component of the vector.
	 * @return Returns z.
	 */
	num getZ() {return z;}
};

#endif /* VEC3D_H_ */
