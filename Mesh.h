#pragma once 
#include "MeshNode.h"
#include "Pixelmanager.h"
#include "Shader.h"
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


extern PixelManager pixelmanager;

class Mesh{

private:
	GLFWwindow* window;
	Shader* infoShader;

	unsigned int ID;

	static unsigned int totalNum;
	

public:
	vector<MeshNode> subMeshes;


	Mesh(vector<MeshNode> subMeshes,GLFWwindow* window,Shader *infoShader)
	{
		ID = totalNum;
		++totalNum;

		this->subMeshes = subMeshes;
		this->window = window;
		this->infoShader = infoShader;
	}

	void registerThis(Mesh * list[])
	{
		list[ID] = this;
	}

	void render()
	{
		while(!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			renderInfo();
			renderScene();
			glfwSwapBuffers(window);
		}
		
		glfwTerminate();    
	}

	void renderScene(){
		glClearColor(0.5,0.2,0.1,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer so why bother with clearing?
        glEnable(GL_DEPTH_TEST);
		for(int i=0;i<subMeshes.size();i++)
		{
			MeshNode &cur =  subMeshes[i];
			cur.shader->Use();
			GLuint modelLoc = glGetUniformLocation(cur.shader->program,"model"); 
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(cur.transformation));
			glBindVertexArray(cur.VAO);
			glDrawArrays(cur.mode,0,cur.numVertices);
			glBindVertexArray(0);
		}
	}

	//ע�⣬���ڵķ�ʽ��һ������ȱ�ݣ�meshnode��Ŀ���ܳ���255.
	void renderInfo(){

		infoShader->Use();
		pixelmanager.enableWrite();

		glClearColor(0.0,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer so why bother with clearing?
        glEnable(GL_DEPTH_TEST);
		for(int i=0;i<subMeshes.size();i++)
		{
			MeshNode &cur = subMeshes[i];

			GLuint modelLoc = glGetUniformLocation(infoShader->program,"model"); 
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(cur.transformation));

			GLuint objIndexPos = glGetUniformLocation(infoShader->program,"objIndexDivideBy255"); 
			glUniform1f(objIndexPos,GLfloat(ID)/255);

			GLuint meshIndexPos = glGetUniformLocation(infoShader->program,"meshIndexDivideBy255"); 
			glUniform1f(meshIndexPos,GLfloat(i)/255);


			glBindVertexArray(cur.VAO);
			glDrawArrays(cur.mode,0,cur.numVertices);
			glBindVertexArray(0);
		}
		pixelmanager.disableWrite();
	}
};

unsigned int Mesh::totalNum = 1;


