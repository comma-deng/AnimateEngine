#pragma once
#include "glew.h"
#include <iostream>
#include "Utils.h"
using namespace std;


struct pixelInfo
{
	unsigned char obj_ID;
	unsigned char mesh_ID;
	unsigned char none;
};

class PixelManager
{
public:
	PixelManager(){}

	bool Init(unsigned int width,unsigned int height){
		glGenFramebuffers(1,&FBO);
		glBindFramebuffer(GL_FRAMEBUFFER,FBO);

		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		/*
			void glTexImage2D( 	GLenum target,
  			GLint level,
  			GLint internalFormat,  //��������ڲ����ݸ�ʽ�������������ʵ�洢�����ݡ�
  			GLsizei width,
  			GLsizei height,
  			GLint border,
  			GLenum format,
  			GLenum type,
  			const GLvoid * data);
		*/

		 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		/*
			target��������������֡�������͵�Ŀ�꣨���ơ���ȡ�����߶��У���
			attachment�����������ӵĸ��������͡��������Ǹ��ӵ���һ����ɫ��������Ҫע�⣬�����Ǹ�0�ǰ�ʾ���ǿ��Ը���1��������ɫ�ĸ��������ǻ��ں���Ľ̳���̸����
			textarget����ϣ�����ӵ��������͡�
			texture�����ӵ�ʵ������
			level��Mipmap level����������Ϊ0��
		*/
		glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, texture, 0);
		
		glGenTextures(1,&depth_texture);
		glBindTexture(GL_TEXTURE_2D,depth_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	
		glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_COMPONENT,GL_TEXTURE_2D,depth_texture,0);
		
		glReadBuffer(GL_NONE);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) 
		{
			cout<<"FB error, status: "<<errorInfo(status)<<endl;
			return false;
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}

	void enableWrite()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
	}

	void disableWrite()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	pixelInfo pickingPixel(unsigned int x,unsigned int y)
	{
		pixelInfo info;
		glBindFramebuffer(GL_READ_FRAMEBUFFER,FBO);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &info);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
		return info;
	}

private:
	GLuint FBO;
	GLuint texture;
	GLuint depth_texture;
};
