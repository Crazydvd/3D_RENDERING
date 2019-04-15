//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 mvpMatrix;
uniform float time;
uniform float maxValue;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec2 texCoord; //make sure the texture coord is interpolated

float modulo(float number, float divider);
float pingPong(float value, float length);

void main( void )
{	
	float value = abs(sin(time - vertex.x - vertex.y - vertex.z));
	value = pingPong(value, maxValue);

	gl_Position = mvpMatrix * vec4(vertex + vertex * value, 1.0f);
	texCoord = uv;
}

float modulo(float number, float divider)
{
	float result = number;
	while (result > divider)
	{
		result -= divider;
	}
	
	return result;
}

float pingPong(float value, float length)
{
	if (value > length) //check if we are over our limit
	{
		float a = modulo(value, length); //grab the remainder
		int b = int(value / length); //check how many times we are over our limit
		int c = b % 2; //see if it's an even number
		if (c == 0) //even
		{
			return a;
		}
		else //not even
		{
			return length - a;
		}
	}
	else
	{
		return value;
	}
}