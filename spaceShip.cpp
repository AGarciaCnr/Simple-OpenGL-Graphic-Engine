#include "spaceShip.h"
#include "inputManager.h"
#include "scene.h"
#include "system.h"
#include "bullet.h"


bool shoot = true;

void SpaceShip::step() {
	
    if (InputManager::keys['A'])
    {
        position.x -= 0.01f;
        if (this->rotation.y == glm::radians(0.0f)) {
            this->rotation.y = glm::radians(180.0f);
            position.x += 0.25f;
        }    
    }

    if (InputManager::keys['D'])
    {
        position.x += 0.01f;
        if (this->rotation.y == glm::radians(180.0f)) {
            this->rotation.y = glm::radians(0.0f);
            position.x -= 0.25f;
        }
    }

    if (this->position.x > 1.0f) {
		this->position.x = 1.0f;
    }

	if (this->position.x < -1.0f) {
		this->position.x = -1.0f;
	}

    if (InputManager::keys[' '] && (shoot == true))
    {
        Object* bullet = new Bullet("bullet.trg");
        bullet->position.x = this->position.x;
        bullet->position.y = this->position.y + 0.1f;
        bullet->scale = glm::vec3(0.3f, 0.3f, 0.3f);
        System::scene->addObject(bullet);

        shoot = false;
    }

    if (!InputManager::keys[' '])
        shoot = true;
}

