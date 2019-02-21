//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 ambientLightColor;
uniform vec3 diffuseColor;

in float diffuseIntensity;
in vec3 worldNormal;
in vec3 position;

out vec4 fragment_color;

void main( void ) 
{
	vec3 pointlightPosition = vec3(-1, 1, 1);
	vec3 pointlightDirection = position - pointlightPosition;
	vec3 LightVector = pointlightDirection;
	
	float diffuseIntensity = max(dot(-normalize(LightVector), normalize(worldNormal)), 0);
	
	vec3 lightColor = vec3(1, 1, 1);
	
	vec3 ambientTerm = ambientLightColor * diffuseColor;
	vec3 diffuseTerm = diffuseIntensity * lightColor * diffuseColor;

	fragment_color = vec4 (ambientTerm + diffuseTerm, 1);
}
