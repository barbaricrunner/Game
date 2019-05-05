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
	mh[0].loadModel("./Models/ground.dae");
	mh[1].loadModel("./Models/Trees/generic.dae");
}

void AssetHandler::drawAssets()
{
	mh[0].draw();
	mh[1].draw();
}
