#include "bullet.h"
#include "system.h"

void Bullet::step()
{
    this->position.y+=direction*0.01f;
	
	//testColisiones
	
    std::vector<Object*> *objects=System::scene->getCollisions(SPACESHIP_OBJ, this);
	
	if (objects->size() > 0)
	{
		System::scene->deleteObject(this);
	}
	else if ((this->position.y > 2.0f) || (this->position.y < -3.0f))
	{
		System::scene->deleteObject(this);
	}
}