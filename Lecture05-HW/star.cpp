#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

float moveFactorX = 0.0f;
float moveFactorY = 0.0f;
float scaleFactor = 1.0f;
double lastX = 0.0, lastY = 0.0;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &lastX, &lastY);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &lastX, &lastY);
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        float dx = xpos - lastX;
        float dy = ypos - lastY;
        moveFactorX += dx / 500.0f;
        moveFactorY -= dy / 500.0f;
        lastX = xpos;
        lastY = ypos;
    }
    state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (state == GLFW_PRESS)
    {
        float dx = xpos - lastX;
        float dy = ypos - lastY;
        scaleFactor += dx / 500.0f;
        lastX = xpos;
        lastY = ypos;
    }
}

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int render()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f + moveFactorX, 0.5f + moveFactorY);
    glVertex2f(0.0f + moveFactorX, -0.3f + moveFactorY);
    glVertex2f(-0.2f + moveFactorX, -0.5f + moveFactorY);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f + moveFactorX, 0.5f + moveFactorY);
    glVertex2f(0.0f + moveFactorX, -0.3f + moveFactorY);
    glVertex2f(0.2f + moveFactorX, -0.5f + moveFactorY);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f + moveFactorX, -0.25f + moveFactorY);
    glVertex2f(-0.36f + moveFactorX, 0.1f + moveFactorY);
    glVertex2f(0.36f + moveFactorX, 0.1f + moveFactorY);
    glEnd();

    return 0;
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 배경을 마젠타 색상으로 설정 (R:1.0, G:0.0, B:1.0)
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
