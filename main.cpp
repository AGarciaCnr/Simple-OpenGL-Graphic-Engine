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

#define MODE 1

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

	if (MODE) {
		
		int glfwState = glfwInit();
		if (!glfwState)
			std::cout << "ERROR iniciando glfw\n";

		GLFWwindow* window = glfwCreateWindow(1920, 1080, "Prueba 1 GLFW", glfwGetPrimaryMonitor(), nullptr);
		glfwMakeContextCurrent(window);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


		int glewState = glewInit();

		if (glewState != GLEW_OK)
			std::cout << "ERROR iniciando glew\n";

		InputManager::init(window);

		Render* render = new Render();
		Scene* scene = new Scene();
		System::scene = scene;

		scene->setCamera(new Camera(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), perspective));

		Object* background = new Background("background.trg");
		background->position = glm::vec3(4.0f, 3.0f, -2.0f);
		background->scale = glm::vec3(16.0f, 12.0f, 1.0f);

		Object* triangle = new SpaceShip("kirby.trg");
		triangle->scale = glm::vec3(0.25f, 0.15f, 0.3f);
		triangle->position.y = -0.75f;
		triangle->position.z = -0.1f;
		triangle->rotation.z = glm::radians(180.0f);

		Object* enemy = new Enemy("bullet.trg");
		enemy->scale = glm::vec3(0.1f, 0.1f, 0.1f);
		enemy->position.y = 2.5f;
		enemy->position.z = -1.0f;
		enemy->rotation.z = glm::radians(180.0f);

		scene->addObject(background);
		render->setupObject(background);

		scene->addObject(enemy);
		render->setupObject(enemy);

		scene->addObject(triangle);
		render->setupObject(triangle);

		while (!glfwWindowShouldClose(window)) {
			if (renderfps(60.0f))
			{
				scene->step(0.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				render->drawScene(scene);
				glfwSwapBuffers(window);
				glfwPollEvents();
			}

			if (InputManager::keys['P'])
				return 0;

		}
	}
	else {
		
		int glfwState = glfwInit();
		if (!glfwState)
			std::cout << "ERROR iniciando glfw\n";

		GLFWwindow* window = glfwCreateWindow(1080, 1080, "Prueba 1 GLFW", glfwGetPrimaryMonitor(), nullptr);
		glfwMakeContextCurrent(window);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


		int glewState = glewInit();

		if (glewState != GLEW_OK)
			std::cout << "ERROR iniciando glew\n";

		InputManager::init(window);

		Render* render = new Render();
		Scene* scene = new Scene();
		System::scene = scene;

		scene->setCamera(new Camera(glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f),perspective));

		Object* cube=new Cube("cube.trg");
		cube->scale=glm::vec3(0.5f,0.5f,0.5f);
		cube->position.z=3.0f;

		render->setupObject(cube);
		scene->addObject(cube);

		while (!glfwWindowShouldClose(window)) {
			if (renderfps(60.0f))
			{
				scene->step(0.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
				render->drawScene(scene);
				glfwSwapBuffers(window);
				glfwPollEvents();
			}

			if (InputManager::keys['P'])
				return 0;
		}
	}
	
	//delete triangle;
	return 0;
}
