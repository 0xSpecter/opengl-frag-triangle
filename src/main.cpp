// includes-----------------------------------------------------------------------------

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <cmath>

// functions----------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// shader code-------------------------------------------------------------------------

// vertex shader code
const char* vertexShaderSource = 
    "#version 330 core\n"

    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"

    "out vec3 ourColor;\n"

    "void main() {\n"
    "    gl_Position = vec4(aPos, 1.0);\n"
    "    ourColor = aColor;\n"
    "}\n";

// fragment shader code
const char* fragmentShaderSource = 
    "#version 330 core\n"

    "out vec4 FragColor;\n"

    "in vec3 ourColor;\n"
    
    "void main() {\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n";

// main--------------------------------------------------------------------------------

int main() {

    // inits---------------------------------------------------------------------------

    //hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create window---------------------------------------------------------------------

    // creates window and checks if success
    GLFWwindow* window = glfwCreateWindow(800, 600, "yeha baby", NULL, NULL);
    if (window == NULL) {
        std::cout << "bitch you done fuck it all up! with window spice" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // creates viewport and window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // loades glad and checks if success
    if (!gladLoadGL()) { // can be exchanged with: gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)
        std::cout << "bitch you done fuck it all up! with glad spice" << std::endl;
        return -1;
    }

    // shaders---------------------------------------------------------------------------

    // shader compile error check vars
    GLint success;
    GLchar infolog[512];

    // vertex shaders and checks if succses
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    // fragment shaders and checks if succses
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    // linking shaders and checks if success
    // green fragment program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infolog << std::endl;
    }

    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    // set up vertex data-----------------------------------------------------------------

    //data for triangle
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };    
    
    // buffers---------------------------------------------------------------------------

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);  

    // configure triangles
    
    // first triangle setup
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);   

    // window loop-------------------------------------------------------------------------

    // draws in wireframe mode; comment out
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    while (!glfwWindowShouldClose(window)) {

        // input
        processInput(window);

        // render
        glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // program
        glUseProgram(shaderProgram);

        // draw
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    // cleanup------------------------------------------------------------------------------

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

// functions----------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}