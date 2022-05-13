#include "render.h"

Render::Render() {
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
}

void Render::setupObject(Object* obj) {
	bufferObject_t bo;
	glGenVertexArrays(1, &bo.abo);
	glBindVertexArray(bo.abo);
	
	glGenBuffers(1,&bo.vbo);
	glGenBuffers(1,&bo.ibo);

	glBindBuffer(GL_ARRAY_BUFFER,bo.vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_t)*obj->mesh->vertexList->size(),
		obj->mesh->vertexList->data(),GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,bo.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*obj->mesh->faceList->size(),
		obj->mesh->faceList->data(),GL_STATIC_DRAW);

	boList[obj->id]=bo;	
}


void Render::drawMesh(Mesh* mesh,glm::mat4 model) {
	int numFaces=(int)mesh->faceList->size()/3;
	for(int i=0;i<numFaces;i++) {
		glBegin(GL_TRIANGLES);
		glm::vec4 newPos;	
		for(int idV=i*3; idV<(i*3+3); idV++) {   
			vertex_t v=mesh->vertexList->data()[mesh->faceList->data()[idV]];
			newPos=proj*view*model*v.posicion;
			glColor3f(v.color.r,v.color.g,v.color.b);
			glVertex3f(newPos.x,newPos.y,newPos.z);
		}
		glEnd();
	}
}


void Render::drawObject(Object* obj) {
	obj->computeMatrix();
	drawMesh(obj->mesh,obj->getMatrix());	
}




void Render::drawObjectGL4(Object* obj, glm::vec3 camPos) {
	obj->computeMatrix();
	
	bufferObject_t bo=boList[obj->id];
	
	glBindVertexArray(bo.abo);
	glBindBuffer(GL_ARRAY_BUFFER, bo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.ibo);


	glUseProgram(obj->shader->programID);
	unsigned int vpos = 0;
	glEnableVertexAttribArray(vpos);
	glVertexAttribPointer(vpos,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,posicion));

	unsigned int vcolor = 1;
	glEnableVertexAttribArray(vcolor);
	glVertexAttribPointer(vcolor,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,color));

	unsigned int vnorm = 2;
	glEnableVertexAttribArray(vnorm);
	glVertexAttribPointer(vnorm,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,normal));

	unsigned int vtext = 3;
	glEnableVertexAttribArray(vtext);
	glVertexAttribPointer(vtext, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, texCoord));
	
	glm::vec4 lightPos(0.0f,0.0f,6.0f,1.0f);
	glm::vec4 cameraPos(camPos, 1.0f);

	glUniformMatrix4fv(0,1,GL_FALSE,&(proj*view*obj->getMatrix())[0][0]);

	glm::mat4 matT = glm::translate(glm::mat4(1.0f), obj->position);
	matT = glm::rotate(matT, obj->rotation.x, glm::vec3(1.0f, 0, 0));
	matT = glm::rotate(matT, obj->rotation.y, glm::vec3(0, 1.0f, 0));
	matT = glm::rotate(matT, obj->rotation.z, glm::vec3(0, 0, 1.0f));

	glUniformMatrix4fv(1,1,GL_FALSE,&(matT)[0][0]);	
	glUniform4fv(2,1,&lightPos[0]);
	glUniform4fv(3, 1, &cameraPos[0]);

	int textureUnit = 0;
	glUniform1i(4, textureUnit);

	if (obj->typeObject == BACKGROUND_OBJ) {
		Background* background = dynamic_cast<Background*>(obj);
		glm::vec2 scroll = background->scroll;
		glUniform2fv(5, 1, &scroll[0]);
	}
	else {
		glm::vec2 scroll = glm::vec2(0, 0);
		glUniform2fv(5, 1, &scroll[0]);
	}
	
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	obj->mesh->tex->bind(textureUnit);

	glDrawElements(GL_TRIANGLES, obj->mesh->faceList->size(), GL_UNSIGNED_INT,nullptr);
}


void Render::drawScene(Scene* scene) {
	Camera* cam=scene->getCamera();
	std::map<int,Object*> *addedObjList=scene->addedObjList;
	
	for(auto it=addedObjList->begin();
            it!=addedObjList->end();
            it++) {
        setupObject(it->second);
    }
    
	cam->computeMatrix();
	view=cam->getMatrix();
	proj=cam->getProjectionMatrix();
	std::map<float,Object*, std::greater<float>>* objList=scene->orderedObjList;	
	
	for(auto it=objList->begin();
			it!=objList->end();
			it++) {
		drawObjectGL4(it->second, scene->getCamera()->getPosition());
	}
}