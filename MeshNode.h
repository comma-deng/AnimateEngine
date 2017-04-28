#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glew.h>
#include<iostream>
#include<vector>
#include"Shader.h"

using namespace std;
using namespace glm;



class MeshNode{
public:

	MeshNode(vector<vec3> &points,vec3 shift,quat rotation,Shader *shader,GLenum mode)
	{
		this->shader = shader;
		this->mode = mode;
		this->shift = shift;
		this->rotation = rotation;
		
		this->numVertices = points.size();
		this->rotation = rotation;
		glGenVertexArrays(1,&VAO);
		glBindVertexArray(VAO);

		
		glGenBuffers(1,&VBO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER,numVertices*sizeof(vec3),points.data(),GL_STATIC_DRAW);

		//�����������ң��ڼ���������������������ͣ�ÿ��������֮��ľ��룬��һ�������ƫ����
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(vec3),(GLvoid *)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	void setShift(vec3 shift)
	{
		this->shift = shift;
	}

	vec3 getShift()
	{
		return this->shift;
	}

	void setRotation(quat rotation)
	{
		this->rotation = rotation;
	}

	quat getRotation()
	{
		return this->rotation;
	}



private:
	GLuint VAO;
	GLuint VBO;

	/*
	�����parent����ת��λ�ơ�
	tramsformation��Ҫ����shader�ı任���󣬲��������parent�ģ������������������ϵ�ı任����
	����ʱ������parent��rotation��shift����Ⱦǰ�Ӹ��ڵ㿪ʼ���£�ȫ��������������Ⱦ��
	*/
	quat rotation;
	vec3 shift;
	mat4 transformation;

	Shader *shader;
	GLenum mode;
	int numVertices;

	MeshNode *parent;

	friend class Mesh;

};


