#version 330 core

uniform float objIndexDivideBy255;  

uniform float meshIndexDivideBy255;  

out vec4  Indices;//�������������

void main()
{
	Indices = vec4(objIndexDivideBy255,meshIndexDivideBy255,0.0,0.0);
}

