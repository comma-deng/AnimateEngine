#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#include <glew.h>
#include<iostream>
#include<vector>
#include"Shader.h"

using namespace std;
using namespace glm;



class MeshNode{
public:

	MeshNode(vector<vec3> &points,vec3 position,quat rotation,Shader *shader,GLenum mode)
	{
		this->shader = shader;
		this->mode = mode;
		this->position = position;
		this->rotation = rotation;
		
		this->numVertices = points.size();
		this->rotation = rotation;

		this->parent = nullptr;

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


	void setShift(vec3 position)
	{
		this->position = position;
	}

	vec3 getShift()
	{
		return this->position;
	}

	void setRotation(quat rotation)
	{
		this->rotation = rotation;
	}

	quat getRotation()
	{
		return this->rotation;
	}

	void setParent(MeshNode *parent)
	{
		this->parent = parent;
	}

	//���ݼ�¼�Ĺؼ�֡��Ϣ���¹���״̬
	void update()
	{
		quat absolute_rotation;
		vec3 absolute_position;

		if(parent == nullptr)
		{
			absolute_rotation = rotation;
			absolute_position = position;
		}

		else
		{
			quat rotation_parent = parent->rotation;
			vec3 position_parent = parent->position;

			vec3 absolute_position = position_parent + position;

			/*
			   p��=qp
			   q����Ԫ����p��p����������
			*/
			absolute_rotation = rotation_parent * rotation;
		}

		mat4 position_matrix;
		position_matrix = translate(position_matrix,absolute_position);

		mat4 rotation_matrix = mat4_cast(absolute_rotation);

		transformation = position_matrix * rotation_matrix;
	}

private:
	GLuint VAO;
	GLuint VBO;

	/*
	�����parent����ת��λ�á�
	tramsformation��Ҫ����shader�ı任���󣬲��������parent�ģ������������������ϵ�ı任����
	����ʱ������parent��rotation��position����Ⱦǰ�Ӹ��ڵ㿪ʼ���£�ȫ��������������Ⱦ��
	*/
	quat rotation;
	vec3 position;
	mat4 transformation;

	Shader *shader;
	GLenum mode;
	int numVertices;

	MeshNode *parent;
	vector<MeshNode *> childrenList;

	friend class Mesh;

};


