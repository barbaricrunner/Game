/*
 * ModelHandler.cpp
 *
 *  Created on: 2019-05-01
 *      Author: Joseph Haske
 */

#include "ModelHandler.h"

ModelHandler::ModelHandler() {
	scale = Vec3D<GLfloat>(1.0f, 1.0f, 1.0f);
}

ModelHandler::~ModelHandler() {
	// TODO Auto-generated destructor stub
}

/**
 * Draws the current model.
 */
void ModelHandler::draw()
{
	//TODO: Draw each model.
	for(int i=0; i<1; i++)
		models[i].drawModel();
}

/**
 * Loads the model in from a Blender output Collada file.
 *
 * @param fileName A string representing the file name.
 */
void ModelHandler::loadModels(std::string *fileName)
{
	for(int i=0; i<1; i++)
	{
		ModelLoader ml;
		ml.loadModel(fileName[i], models[i]);
	}
}//end loadModel(std::string) method


/**
 * Scales the model from the blender input matrix.
 */
void ModelHandler::scaleModel()
{
	/*for(int i = 0; i < numVertices; i++)
	{
		v[i].coord.scale(scale);
	}*/
}
