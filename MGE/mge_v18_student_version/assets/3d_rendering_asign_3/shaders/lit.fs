//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform mat4 viewMatrix;

uniform vec3 ambientLightColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform vec3 lightPosition;
uniform vec3 lightForward;
uniform vec3 lightColor;
uniform int lightType;

uniform float coneAngle;
uniform float fallOffAngle;

uniform int shininess;

in float diffuseIntensity;
in vec3 worldNormal;
in vec3 position;

out vec4 fragment_color;

void main(void) 
{
	vec3 LightVector;
	float Angledegrees;
	
	float intensity = 1;
	
	if (lightType == 0) //ambient
	{
		vec3 ambientTerm = ambientLightColor * diffuseColor;
		fragment_color = vec4(ambientTerm, 1);
		return;
	}
	else
	if (lightType == 1) //directional
	{
		LightVector = normalize(lightForward);
	}
	else
	if (lightType == 2) //point
	{
		LightVector = position - lightPosition;
	}
	else
	if (lightType == 3) //spot
	{
		LightVector = position - lightPosition;
		vec3 normalizedLight = normalize(LightVector);
		vec3 forward = normalize(lightForward);
		
		float dotProduct = dot(forward, normalizedLight);
		float angle = acos(dotProduct);
		Angledegrees = degrees(angle);
		
		if (Angledegrees > fallOffAngle)
		{
			intensity -= (Angledegrees - fallOffAngle) / (coneAngle - fallOffAngle);
		}
	}	
	
	float diffuseIntensity = max(dot(-normalize(LightVector), normalize(worldNormal)), 0);
	
	float distance = length(LightVector);
	float squareDistance = distance * distance;
	float c1 = 1;
	float c2 = 1;
	float c3 = 0;
	float attenuation = (c1 + c2 * distance + c3 * squareDistance);
	diffuseIntensity /= attenuation;
	
	mat4 cameramatrix = inverse(viewMatrix);
	vec3 cameraPosition = vec3(cameramatrix[3]);
	vec3 cameraVector = cameraPosition - position;
	
	vec3 lightDirection = normalize(LightVector);
	vec3 reflectedRay = reflect(lightDirection, normalize(worldNormal));
	
	float projection = dot(reflectedRay, normalize(cameraVector));
	float maximum = max(projection, 0);
	
	vec3 ambientTerm = ambientLightColor * diffuseColor;
	vec3 diffuseTerm = diffuseIntensity * lightColor * diffuseColor;
	vec3 specularTerm = pow(maximum, shininess) * lightColor * specularColor;
	specularTerm /= attenuation;

	fragment_color = vec4 ((ambientTerm + diffuseTerm + specularTerm) * intensity, 1);
}
