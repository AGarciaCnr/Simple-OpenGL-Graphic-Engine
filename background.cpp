#include "background.h"
#include "system.h"

void Background::step() {
	scroll += glm::vec2(0.0f, 0.001f);
}