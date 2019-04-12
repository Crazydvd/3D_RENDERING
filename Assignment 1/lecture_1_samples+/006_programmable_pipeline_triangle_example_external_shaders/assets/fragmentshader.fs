#version 330

in vec2 fuv;

in vec3 fColor;
out vec4 sColor;

uniform int horizontalMultiplier;
uniform int verticalMultiplier;
uniform vec4 color1;
uniform vec4 color2;
uniform vec2 mousePosition;
uniform vec4 lightColor;
uniform float lightSize;


void main (void) 
{
	float colorNum = (int(fuv.x * horizontalMultiplier) + int(fuv.y * verticalMultiplier)) % 2;
	sColor = (colorNum == 0)? color1 : color2;
	
	float distance = length(vec4(mousePosition.x, mousePosition.y, 0, 0) - gl_FragCoord);
	
	float intensity = lightSize / distance;
	intensity = (intensity > 1)? 1 : intensity;
	vec4 light = lightColor * intensity;
	sColor *= intensity;
	
	sColor += light;
}