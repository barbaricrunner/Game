/*
 * Vec4D.h
 *
 *  Created on: May 5, 2019
 *      Author: Joseph Haske
 */

#ifndef VEC4D_H_
#define VEC4D_H_

#include <GLFW/glfw3.h>

template <class num> class Vec4D {
private:
	num w; /**< The w component of the vector.*/
	num x; /**< The x component of the vector.*/
	num y; /**< The y component of the vector.*/
	num z; /**< The z component of the vector.*/
	num magSqrd; /**< The magnitude squared of the vector. This prevents having to calculate it multiple times.*/

public:
	Vec4D(num win, num xin, num yin, num zin);
	Vec4D();
	virtual ~Vec4D();

	void add(Vec4D v);
	void sub(Vec4D v);
	void scale(Vec4D v);
	Vec4D<num> projOnto(Vec4D v);

	/**
	 * Calculates the dot product of this vector and the input vector.
	 * @param v The input vector.
	 * @return Returns the calculated dot product.
	 */
	num dotProd(Vec4D v) {return (w * v.w) + (x * v.x) + (y * v.y) + (z * v.z);}
	/**
	 * Calculates the magnitude of this vector, squared.
	 * @return Returns the calculated magnitude squared.
	 */
	num magSquared() {return (w * w) + (x * x) + (y * y) + (z * z);}
	/**
	 * Getter for the w component of the vector.
	 * @return Returns w.
	 */
	num getW() {return w;}
	/**
	 * Getter for the x component of the vector.
	 * @return Returns x.
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

#endif /* VEC4D_H_ */
