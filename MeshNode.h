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

		//参数从左至右：第几个分量，组件数量，类型，每两个分量之间的距离，第一个组件的偏移量
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

	//根据记录的关键帧信息更新骨骼状态
	//if(parent == nullptr)路径已测试。无误。
	void updateTransformation()
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
			   p′=qp
			   q是四元数。p和p′是向量。
			*/
			absolute_rotation = rotation_parent * rotation;
		}

		mat4 position_matrix;
		position_matrix = translate(position_matrix,absolute_position);
		mat4 inverse_position_matrix;
		inverse_position_matrix = translate(inverse_position_matrix,-absolute_position);
		mat4 rotation_matrix = mat4_cast(absolute_rotation);

		transformation = position_matrix * rotation_matrix * inverse_position_matrix;
	}

private:
	GLuint VAO;
	GLuint VBO;

	/*
	相对于parent的旋转和位置。
	tramsformation是要传入shader的变换矩阵，不是相对于parent的，而是相对于世界坐标系的变换矩阵。
	计算时可以用parent的rotation和position。渲染前从根节点开始更新，全部更新完了再渲染。
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


