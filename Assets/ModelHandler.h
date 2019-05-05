/*
 * ModelHandler.h
 *
 *  Created on: 2019-05-01
 *      Author: Joseph Haske
 */

#ifndef MODELHANDLER_H_
#define MODELHANDLER_H_

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>

#include "../Math/Vec3D.h"

class ModelHandler {

	/**
	 * This structure stores the data for each material in the model.
	 */
	struct Material
	{
		std::string matName;
		GLfloat emission[4], ambient[4], diffuse[4], specular[4], shininess;
	};

	/**
	 * This structure stores the data for each vertex in the model.
	 */
	struct Vertices
	{
		Vec3D<GLfloat> coord;
	};

	/**
	 * This structure stores the data for each triangle in the model.
	 */
	struct Triangle
	{
		Vec3D<int> vert;
		Material* m;
	};

public:
	ModelHandler();
	virtual ~ModelHandler();

	void draw();
	void loadModel(std::string fileName);

private:
	Vertices v[300]; /**< Loads up to 300 vertices. */
	Triangle t[100]; /**< Supports models with up to 100 triangles. */
	Material m[10]; /**< Supports models with up to 10 materials. */
	Vec3D<GLfloat> scale; /**< A scaling vector */
	int numVertices; /**< Stores the number of vertices in this model. */
	int numTriangles; /**< Stores the number of triangles in this model. */
	int numMaterials; /**< Stores the number of materials in this model. */

	int removeTags(std::string &line, std::regex &numRegex, std::string *returnArray);
	void scaleModel();
	void printModel();
};

#endif /* MODELHANDLER_H_ */
