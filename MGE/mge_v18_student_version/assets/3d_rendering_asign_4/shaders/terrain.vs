//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D heightMapTexture;

uniform float maxHeight;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated
out vec3 worldNormal; //interpolated worldNormal
out vec3 position; //interpolated fragPosition

void main( void )
{
	texCoord = uv;
	
	vec3 frag_color = vec3(texture(heightMapTexture, texCoord));
	float value = frag_color.r;
	//value -= 0.5f; //subtract half of 1 (max value) so we can go down as well
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex + vec3(0, maxHeight, 0) * value, 1.0f);
	position = vec3(modelMatrix * vec4(vertex + vec3(0, maxHeight, 0) * value, 1));
	worldNormal = vec3(modelMatrix * vec4(normal, 0));
}
