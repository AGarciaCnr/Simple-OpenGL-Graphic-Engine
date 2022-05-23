#pragma once
#include "object.h"
#include <ctime>

class Enemy: public Object{

	
public:


	Enemy():Object(){};
	Enemy(std::string fileName):Object(fileName){typeObject=ENEMY_OBJ;};
	virtual void step() override;
};

