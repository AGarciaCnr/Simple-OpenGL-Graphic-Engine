#include <iostream>
#include "common.h"
#include <vector>
#include "mesh.h"
#include "render.h"
#include "object.h"
#include "scene.h"
#include "inputManager.h"
#include "spaceShip.h"
#include "system.h"
#include "enemy.h"
#include "cube.h"
#include "background.h"


bool renderfps(double framerate) { 
	static double currentTime = 0; 
	static double lastTime=0;
	
	currentTime = glfwGetTime();
	if(currentTime - lastTime >= 1.0 / framerate) 
	{
		lastTime = currentTime;
		return true;
	}
	return false;
}


int main(int argc, char** argv) {

	int glfwState=glfwInit();
	if (!glfwState)
		std::cout << "ERROR iniciando glfw\n";

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Prueba 1 GLFW", glfwGetPrimaryMonitor(), nullptr);
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	
	int glewState=glewInit();
	
	if (glewState!=GLEW_OK)
		std::cout << "ERROR iniciando glew\n";

	InputManager::init(window);

	Object* background = new Background("background.trg");
	background->position = glm::vec3(4.0f, 3.0f, -2.0f);
	background->scale = glm::vec3(12.0f, 12.0f, 1.0f);
	
	Object* background2 = new Background("background.trg");
	background2->position = glm::vec3(-2.0f, 3.0f, -2.0f);
	background2->scale = glm::vec3(12.0f, 12.0f, 1.0f);
	
	Object* triangle = new SpaceShip("triangle.trg");
	triangle->scale=glm::vec3(0.1f,0.1f,0.1f);
	triangle->position.y=-0.45f;
	
	/*
	Object* enemy=new Enemy("triangle.trg");
	enemy->scale=glm::vec3(0.1f,0.1f,0.1f);
	enemy->position.y=0.45f;
	enemy->rotation.z=glm::radians(180.0f);
	*/

	Object* enemy = new Enemy("triangle.trg");
	enemy->scale = glm::vec3(0.1f, 0.1f, 0.1f);
	enemy->position.y = 0.45f;
	enemy->rotation.z = glm::radians(180.0f);
	

	
	Render* render=new Render();
	Scene* scene=new Scene();
	System::scene=scene;
	scene->setCamera(new Camera(glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,0.0f,0.0f),perspective));

	scene->addObject(background);
	render->setupObject(background);
	
	scene->addObject(background2);
	render->setupObject(background2);
	
	scene->addObject(enemy);
	render->setupObject(enemy);
		
	scene->addObject(triangle);
	render->setupObject(triangle);

	/*
	scene->addObject(triangle);
	scene->addObject(enemy);
	
	render->setupObject(enemy);
	render->setupObject(triangle);
	*/
	//Object* cube=new Cube("cube.trg");
	//cube->scale=glm::vec3(0.5f,0.5f,0.5f);
	//cube->position.z=3.0f;

	//render->setupObject(cube);
	//scene->addObject(cube);

	while(!glfwWindowShouldClose(window)) {	
		if(renderfps(60.0f)) {
			scene->step(0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
			render->drawScene(scene);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	//delete triangle;
	return 0;
}
