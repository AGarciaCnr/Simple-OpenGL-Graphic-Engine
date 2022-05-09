#pragma once
#include "object.h"

class Background : public Object {
	
public:
	Background() :Object() {};
	Background(std::string fileName) :Object(fileName) { typeObject = BACKGROUND_OBJ; };
	virtual void step() override;
};

