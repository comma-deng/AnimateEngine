#define GLEW_STATIC
#include<iostream>
#include <glew.h>
#include<glfw3.h>
#include"Shader.h"
#include"MeshNode.h"
#include"Mesh.h"
#include"math.h"
#include <glm/gtc/matrix_transform.hpp>
#include "PixelManager.h"

const float PI = 3.1415926f;

using namespace std;

PixelManager pixelmanager;

bool isStart = true;

mat4 startMat;

double startX,startY;

unsigned int obj_ID = 1;
unsigned int mesh_ID = 0;

Mesh* obj_list[255];

void quad(vector<vec3>& vertices,vector<vec3>& points,int a,int b,int c,int d)
{
	points.push_back(vertices[a]);
	points.push_back(vertices[b]);
	points.push_back(vertices[c]);

	points.push_back(vertices[a]);
	points.push_back(vertices[c]);
	points.push_back(vertices[d]);
}

/*
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	
	double xpos,ypos;
	
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		
		glfwGetCursorPos(window,&xpos,&ypos);	
		pixelInfo info = pixelmanager.pickingPixel(xpos,ypos);
		cout<< (int)info.obj_ID <<" "<<(int)info.mesh_ID<<endl;
	}

	
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	MeshNode* cur = &(obj_list[obj_ID]->subMeshes[mesh_ID]);
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if(obj_ID == 0) return;

	if (state == GLFW_PRESS)
	{
		if(isStart)
		{
			startMat = cur->getMat();
			startX = xpos;
			startY = ypos;
			isStart = false;
			return;
		}
		mat4 newMat ;
		//rotate(newMat,(float)(3.14*(xpos-startX)/1000),vec3(0.0,1.0,0.0));
		GLfloat distance = (xpos-startX)/100;
		newMat = translate(newMat,vec3(distance,0.0,0.0));
		cur->setMat(newMat);
		cout<<distance<<endl;
	}	

	else if(state == GLFW_RELEASE)
	{
		isStart = true;
	}
}
*/

/*
int main()
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1000,800,"cooma's window",nullptr,nullptr);
	if(window == nullptr) 
	{
		std::cout<<"fail to create glfw window!"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if(glewInit()!=GLEW_OK)
	{
		std::cout<<"failed to initialize glew!";
		return -1;

	}
	int width,height;
	glfwGetFramebufferSize(window,&width,&height);
	glViewport(0,0,width,height);

	glfwSetMouseButtonCallback(window,mouse_button_callback);
	glfwSetCursorPosCallback(window,mouse_callback);
	
	vector<vec3> box_vertices;
	box_vertices.push_back(vec3(-0.5,-0.5,0.5));
	box_vertices.push_back(vec3(-0.5,0.5,0.5));
	box_vertices.push_back(vec3(0.5,0.5,0.5));
	box_vertices.push_back(vec3(0.5,-0.5,0.5));

	box_vertices.push_back(vec3(-0.5,-0.5,-0.5));
	box_vertices.push_back(vec3(-0.5,0.5,-0.5));
	box_vertices.push_back(vec3(0.5,0.5,-0.5));
	box_vertices.push_back(vec3(0.5,-0.5,-0.5));
	

	vector<vec3> box_points;
	
	quad(box_vertices,box_points,1,0,3,2);
	quad(box_vertices,box_points,2,3,7,6);
	quad(box_vertices,box_points,3,0,4,7);
	quad(box_vertices,box_points,6,5,1,2);
	quad(box_vertices,box_points,4,5,6,7);
	quad(box_vertices,box_points,5,4,0,1);
	

	Shader simpleShader("vShader.glsl","fShader.glsl");
	Shader InfoShader("vShader.glsl","InfofShader.glsl");

	pixelmanager.Init(width,height);

	vec3 position(0.1,0.0,0.0);
	quat rotation =  angleAxis(1.0f,vec3(0,0,0));

	MeshNode head(box_points,position,rotation,&simpleShader,GL_TRIANGLES);

	vector<MeshNode> meshList;
	meshList.push_back(head);

	Mesh x(meshList,window,&InfoShader);

	x.registerThis(obj_list);
	x.render();

    glfwTerminate();
    return 0; 
} 
*/

int main()
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1000,800,"cooma's window",nullptr,nullptr);
	if(window == nullptr) 
	{
		std::cout<<"fail to create glfw window!"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if(glewInit()!=GLEW_OK)
	{
		std::cout<<"failed to initialize glew!";
		return -1;

	}
	int width,height;
	glfwGetFramebufferSize(window,&width,&height);
	glViewport(0,0,width,height);

	
	Shader simpleShader("vShader.glsl","fShader.glsl");

	quat rotation = angleAxis(PI/2,vec3(0,0,1));
	vec3 pos(0,0,0);
	vector<vec3> points;
	points.push_back(vec3(0.5,0,0));
	points.push_back(vec3(0,-0.5,0));
	points.push_back(vec3(0,0.5,0));
	MeshNode node(points,pos,rotation,&simpleShader,GL_TRIANGLES);

	node.update();

	glfwPollEvents();

	glfwSwapBuffers(window);

	glClearColor(0.5,0.2,0.1,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_DEPTH_TEST);
	
	Mesh::test(node,window);
	


}