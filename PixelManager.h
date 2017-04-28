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
  			GLint internalFormat,  //纹理对象内部数据格式，即计算机中真实存储的数据。
  			GLsizei width,
  			GLsizei height,
  			GLint border,
  			GLenum format,
  			GLenum type,
  			const GLvoid * data);
		*/

		 glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		/*
			target：我们所创建的帧缓冲类型的目标（绘制、读取或两者都有）。
			attachment：我们所附加的附件的类型。现在我们附加的是一个颜色附件。需要注意，最后的那个0是暗示我们可以附加1个以上颜色的附件。我们会在后面的教程中谈到。
			textarget：你希望附加的纹理类型。
			texture：附加的实际纹理。
			level：Mipmap level。我们设置为0。
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
