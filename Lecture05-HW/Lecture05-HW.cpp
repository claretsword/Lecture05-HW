#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>

float moveFactorX = 0.0f;
float moveFactorY = 0.0f;
float scaleFactor = 1.0f;

// 이동을 위한 변수들
bool isDragging = false;
double lastX = 0.0;
double lastY = 0.0;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

// 마우스 이벤트 콜백 함수
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            isDragging = true;
            glfwGetCursorPos(window, &lastX, &lastY);
        }
        else if (action == GLFW_RELEASE)
        {
            isDragging = false;
        }
    }
}

// 마우스 이동 콜백 함수
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (isDragging)
    {
        double deltaX = xpos - lastX;
        double deltaY = ypos - lastY;
        moveFactorX += static_cast<float>(deltaX) / 500.0f; // X 이동
        moveFactorY -= static_cast<float>(deltaY) / 500.0f; // Y 이동 (반대 방향으로 수정)
        lastX = xpos;
        lastY = ypos;
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        moveFactorY += 0.01f; // 위로 이동
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scaleFactor += 0.1f;
    }
}

int render()
{
    glBegin(GL_TRIANGLES);
    // 삼각형 1
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(-0.3f + moveFactorX, 0.3f + moveFactorY); // Y 이동 추가
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.2f + moveFactorX, -0.5f + moveFactorY); // Y 이동 추가
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.1f + moveFactorX, 0.1f + moveFactorY); // Y 이동 추가
    glEnd();

    glBegin(GL_TRIANGLES);
    // 삼각형 2
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.3f + moveFactorX, 0.3f + moveFactorY); // Y 이동 추가
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(-0.2f + moveFactorX, -0.5f + moveFactorY); // Y 이동 추가
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(-0.1f + moveFactorX, 0.1f + moveFactorY); // Y 이동 추가
    glEnd();

    glBegin(GL_TRIANGLES);
    // 삼각형 3
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.0f + moveFactorX, 0.58f + moveFactorY); // Y 이동 추가
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.1f + moveFactorX, 0.1f + moveFactorY); // Y 이동 추가
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(-0.1f + moveFactorX, 0.1f + moveFactorY); // Y 이동 추가
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
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
