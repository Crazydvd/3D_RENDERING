#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * Basic demo of rendering a triangle in OpenGL through the new programmable pipeline.
 * In a real life example, this code should include error checking and refactor into classes/functions.
 * In addition VAO's are missing.
 */

int main () {
    //Open SFML Window == Valid OpenGL Context
    sf::Window window(
        sf::VideoMode (800, 600),       //800 x 600 x 32 bits pp
        "OpenGL Window",                //title
        sf::Style::Default,             //Default, Fullscreen, Titlebar, etc
        sf::ContextSettings (
            24,                         //24 bits depth buffer, important for 3D!
            0,                          //no stencil buffer
            0,                          //no anti aliasing
            3,                          //requested major OpenGL version
            3                           //requested minor OpenGL version
        )
    );

    window.setVerticalSyncEnabled(true);

    //initialize glew to load all available opengl functions/extensions
    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK) {
        std::cout << "Could not initialize GLEW, byeeee!" << std::endl;
        return -1;
    }

    //define the source for the shader as a pointer to an array of char
    const GLchar* vertexShaderSource = R"(
        #version 330

        in vec3 vertex;
        in vec3 color;

        out vec3 fColor;

        void main ()
        {
            gl_Position = vec4(vertex,1);
            fColor = color;
        }
    )";

    //create a vertex shader
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    //load shader source onto GPU: we only have 1 bit of source to load, which is null terminated
    glShaderSource (vertexShaderID, 1, &vertexShaderSource, NULL);
    //compile shader ON GPU, without error checking for now for brevity
	glCompileShader (vertexShaderID);

	//define the source for the shader as a pointer to an array of char
    const GLchar* fragmentShaderSource = R"(
        #version 330

        in vec3 fColor;
        out vec4 sColor;

        void main ()
        {
            sColor = vec4(fColor, 1);
        }
    )";

	//create a fragment shader
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	//load shader source onto GPU: we only have 1 bit of source to load, which is null terminated
    glShaderSource (fragmentShaderID, 1, &fragmentShaderSource, NULL);
	//compile shader ON GPU, without error checking for now for brevity
	glCompileShader (fragmentShaderID);

	//Now that we have the minimum amount of correct shader types,
	//we need to link them into a shader program:

	//first create the program ID
	GLuint programID = glCreateProgram();
    //now attach the shaders to the program and link (again error checking is omitted for brevity)
    glAttachShader (programID, vertexShaderID);
    glAttachShader (programID, fragmentShaderID);
    glLinkProgram (programID);

    //declare the data to upload
    const GLfloat vertices[] = {
        //1 triangles, 3 vertices per triangle, 4 floats per vertex
        -0.5f, -0.5f, 0,
        0.5f, -0.5f, 0,
        -0.5f, 0.5f, 0
    };

    const GLfloat colors[] {
        //1 triangle, 3 vertices per triangle, 1 color per vertex, 4 "floats" per color RGBA
        1,0,0,
        0,1,0,
        0,0,1
    };

    glClearColor(0, 0, 0, 1);
    while (window.isOpen()) {

		glClear( GL_COLOR_BUFFER_BIT );

        //tell the GPU to use this program
        glUseProgram (programID);

        //get the indexes for the data to render
        GLint vertexIndex = glGetAttribLocation(programID, "vertex");
        GLint colorIndex = glGetAttribLocation(programID, "color");

		//make sure data is streamed to the shader for this index
		glEnableVertexAttribArray(vertexIndex);
		//tell OpenGL in which format to expect this data and stream it
		glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, vertices);

		//make sure data is streamed to the shader for this index
		glEnableVertexAttribArray(colorIndex);
		//tell OpenGL in which format to expect this data and stream it
		glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, colors);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray (vertexIndex);
        glDisableVertexAttribArray (colorIndex);

        //display it
        window.display();

		//empty the event queue
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height);
        }

    }

    return 0;
}


