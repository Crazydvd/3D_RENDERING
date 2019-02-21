//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 ambientLightColor;
uniform vec3 diffuseColor;

/**/
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform int lightType;

/**/

in float diffuseIntensity;
in vec3 worldNormal;
in vec3 position;

out vec4 fragment_color;

void main( void ) 
{
	vec3 LightVector;
	
	if (lightType == 0) //ambient
	{
		vec3 ambientTerm = ambientLightColor * diffuseColor;
		fragment_color = vec4(ambientTerm, 1);
		return;
	}
	if (lightType == 1) //directional
	{
		LightVector = lightPosition;
	}
	if (lightType == 2) //point
	{
		LightVector = position - lightPosition;
	}
	if (lightType == 3) //spot
	{
		LightVector = position - lightPosition;
	}	
	
	float diffuseIntensity = max(dot(-normalize(LightVector), normalize(worldNormal)), 0);
	
	float distance = length(LightVector);
	float squareDistance = distance * distance;
	float c1 = 1;
	float c2 = 1;
	float c3 = 0;
	diffuseIntensity /= (c1 + c2 * distance + c3 * squareDistance);
	
	vec3 ambientTerm = ambientLightColor * diffuseColor;
	vec3 diffuseTerm = diffuseIntensity * lightColor * diffuseColor;

	fragment_color = vec4 (ambientTerm + diffuseTerm, 1);
}
