/*
 * AssetHandler.cpp
 *
 *  Created on: May 4, 2019
 *      Author: user1
 */

#include "AssetHandler.h"

AssetHandler::AssetHandler() {
	// TODO Auto-generated constructor stub

}

AssetHandler::~AssetHandler() {
	// TODO Auto-generated destructor stub
}


void AssetHandler::loadAssets()
{
	std::string modelNames[] = {"./Models/Trees/generic.dae"};
	mh[0].loadModels(modelNames);
	//mh[1].loadModel("./Models/Trees/generic.dae");
}

void AssetHandler::drawAssets()
{
	mh[0].draw();
	//mh[1].draw();
}
