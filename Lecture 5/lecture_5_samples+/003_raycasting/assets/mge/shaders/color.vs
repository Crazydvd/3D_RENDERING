//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 	mvpMatrix;
out float i;

void main( void ){
	gl_Position = mvpMatrix * vec4(vertex, 1.f);
	i = max(0,dot (normal, vec3(1,1,1)));
}
