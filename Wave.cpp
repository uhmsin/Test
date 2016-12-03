//
//  Wave.cpp
//  King
//
//  Created by mac on 14-3-27.
//
//

#include "Wave.h"

using namespace cocos2d;

Wave* Wave::create(float spawnrate){
	Wave* wave = new Wave;
	if(wave && wave->init(spawnrate))
    {
		wave->autorelease();
		return wave;
	}
	CC_SAFE_DELETE(wave);
	return NULL;
}

bool Wave::init( float spawnrate){
	this->setSpawnRate(spawnrate);
	return true;
}