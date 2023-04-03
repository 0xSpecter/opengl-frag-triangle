// includes-----------------------------------------------------------------------------

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// functions----------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// shader code-------------------------------------------------------------------------

// vertex shader code
const char* vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

// fragment shader code
const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.7f, 0.5f, 1.0f);\n"
    "}\n\0";

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

    // loades glad and checks if success
    if (!gladLoadGL()) { // can be exchanged with: gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)
        std::cout << "bitch you done fuck it all up! with glad spice" << std::endl;
        return -1;
    }

    // creates viewport and window resize callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // shaders---------------------------------------------------------------------------

    // shader compile error check vars
    GLint success;
    GLchar infolog[512];

    // vertex shaders and checks if succses
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }
    // vertex shaders and checks if succses

    // fragment shaders and checks if succses
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }

    // linking shaders and checks if success
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
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
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // buffers---------------------------------------------------------------------------

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);  

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // configure vertex attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    // window loop-------------------------------------------------------------------------

    while (!glfwWindowShouldClose(window)) {

        // input
        processInput(window);

        // render
        glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

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
