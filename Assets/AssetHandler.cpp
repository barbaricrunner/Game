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
	std::string modelNames[] = {"./Models/Trees/generic.dae", "./Models/ground.dae"};
	mh.loadModels(modelNames);
}

void AssetHandler::drawAssets()
{
	mh.draw();
}
