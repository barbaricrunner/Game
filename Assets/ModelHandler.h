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

#include "./ModelLoader.h"

class ModelHandler {

	public:
	ModelHandler();
	virtual ~ModelHandler();

	void draw();
	void loadModels(std::string fileName[1]);

private:
	Model models[1];
	Vec3D<GLfloat> scale; /**< A scaling vector */

	int removeTags(std::string &line, std::regex &numRegex, std::string *returnArray);
	void scaleModel();
	void printModel();
	void removeExponents(std::string &line);
};

#endif /* MODELHANDLER_H_ */
