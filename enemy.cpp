#include "enemy.h"
#include "system.h"
#include "bullet.h"

static double lastTime = 0;

void Enemy::step() {
    this->position.x+=0.02f;

	double currentTime = glfwGetTime();


	int random=((int)rand())%30;
	if(random== 0 && (currentTime - lastTime) > 1.0f){
		Bullet* bullet=new Bullet("bullet.trg");
		bullet->rotation.z = glm::radians(180.0f);
		bullet->direction=-1.0f;
		bullet->position.x=this->position.x;
        bullet->position.y=this->position.y - 0.5f;
		bullet->position.z = this->position.z - 0.1f;
		bullet->scale=glm::vec3(0.5f,0.35f,0.1f);
		System::scene->addObject(bullet);
		
		lastTime = currentTime;
	}
	
	

	if(this->position.x>1.5f) {
		this->position.x=-1.9f;
	}

}
