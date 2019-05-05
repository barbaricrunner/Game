/*
 * Model.h
 *
 *  Created on: May 5, 2019
 *      Author: Joseph Haske
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <GLFW/glfw3.h>
#include <iostream>

#include "../Math/Vec3D.h"
#include "../Math/Vec4D.h"

class Model {

	const static int MAX_VERTICES = 2000; /**< The maximum number of vertices supported. */
	const static int MAX_TRIANGLES = 1500; /**< The maximum number of triangles supported. */
	const static int MAX_MATERIALS = 10; /**< The maximum number of materials supported. */

	/**
	 * This structure stores the data for each material in the model.
	 */
	struct Material
	{
		std::string matName;
		Vec4D<GLfloat> emission;
		Vec4D<GLfloat> ambient;
		Vec4D<GLfloat> diffuse;
		Vec4D<GLfloat> specular;
		GLfloat shininess;
	};

	/**
	 * This structure stores the data for each vertex in the model.
	 */
	struct Vertex
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
	Model();
	virtual ~Model();

	void addVertex(Vec3D<GLfloat> vec);
	void addTriangle(Vec3D<int> vec);
	void addMaterial(std::string n);
	void matSetEmission(Vec4D<GLfloat> e);
	void matSetAmbient(Vec4D<GLfloat> a);
	void matSetDiffuse(Vec4D<GLfloat> d);
	void matSetSpecular(Vec4D<GLfloat> s);
	void setTriangleMaterial(std::string name);

	void getMaterial(std::string name, Material *&mat);

	void printModel();
	void drawModel();

private:
	Vertex *v; /**< Stores the model's vertices. */
	Triangle *t; /**< Stores the model's triangles. */
	Material *m; /**< Stores the model's materials. */

	int numVertices; /**< Stores the number of vertices in this model. */
	int numTriangles; /**< Stores the number of triangles in this model. */
	int numMaterials; /**< Stores the number of materials in this model. */
};

#endif /* MODEL_H_ */
