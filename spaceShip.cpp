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
    }

    if (InputManager::keys['D'])
    {
        position.x += 0.01f;
    }

    if (InputManager::keys['T'] && (shoot == true))
    {
        Object* bullet = new Bullet("bullet.trg");
        bullet->position.x = this->position.x;
        bullet->position.y = this->position.y + 0.1f;
        bullet->scale = glm::vec3(0.03f, 0.03f, 0.03f);
        System::scene->addObject(bullet);

        shoot = false;
    }

    if (!InputManager::keys['T'])
        shoot = true;
}

