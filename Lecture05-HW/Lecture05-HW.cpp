//1. 삼각형으로 별을 그리시오
//2. 마우스 좌클릭 후에 드래그해서 드래그한만큼 별을 이동해주세요
//3. 우클릭하고 우측으로 드래그한만큼 확대 좌측으로 드래그한만큼 축소를 해주세요.
//   (별의 중점을 기준으로 확대/축소가 돼야합니다.)


#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// 마우스 이동을 위한 변수들
float moveFactorX = 0.0f;
float moveFactorY = 0.0f;

// 확대/축소를 위한 변수들
float scaleFactor = 1.0f;

// 마우스 이동 콜백 함수에서 사용할 변수들
bool isDragging = false; // 좌클릭 드래그 상태
bool isRightDragging = false; // 우클릭 드래그 상태
double lastX = 0.0; // 마우스 이동 기준 X 위치
double lastY = 0.0; // 마우스 이동 기준 Y 위치
double rightLastX = 0.0; // 우클릭 드래그 기준 X 위치
double rightLastY = 0.0; // 우클릭 드래그 기준 Y 위치

// 에러 콜백 함수
void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

// 마우스 버튼 콜백 함수
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    // 좌클릭 버튼 처리
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            isDragging = true;
            glfwGetCursorPos(window, &lastX, &lastY); // 마우스 위치 기록
        }
        else if (action == GLFW_RELEASE)
        {
            isDragging = false;
        }
    }
    // 우클릭 버튼 처리
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            isRightDragging = true;
            glfwGetCursorPos(window, &rightLastX, &rightLastY); // 마우스 위치 기록
        }
        else if (action == GLFW_RELEASE)
        {
            isRightDragging = false;
        }
    }
}

// 마우스 이동 콜백 함수
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    // 좌클릭 드래그 처리
    if (isDragging)
    {
        double deltaX = xpos - lastX;
        double deltaY = ypos - lastY;
        moveFactorX += static_cast<float>(deltaX) / 500.0f; // X 이동
        moveFactorY -= static_cast<float>(deltaY) / 500.0f; // Y 이동 (마우스 Y 좌표가 아래로 갈수록 화면은 위쪽으로 이동하므로 Y 이동값은 반전되어야 함)
        lastX = xpos;
        lastY = ypos;
    }
    // 우클릭 드래그 처리
    if (isRightDragging)
    {
        double deltaX = xpos - rightLastX;
        scaleFactor += static_cast<float>(deltaX) / 500.0f; // 확대/축소
        rightLastX = xpos;
        rightLastY = ypos;
    }
}

// 렌더링 함수
int render()
{
    // 별을 그리는 부분
    glBegin(GL_TRIANGLES);
    // 삼각형 1
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(-0.3f * scaleFactor + moveFactorX, 0.3f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.2f * scaleFactor + moveFactorX, -0.5f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.1f * scaleFactor + moveFactorX, 0.1f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glEnd();

    // 삼각형 2
    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.3f * scaleFactor + moveFactorX, 0.3f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(-0.2f * scaleFactor + moveFactorX, -0.5f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(-0.1f * scaleFactor + moveFactorX, 0.1f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glEnd();

    // 삼각형 3
    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.0f * scaleFactor + moveFactorX, 0.58f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(0.1f * scaleFactor + moveFactorX, 0.1f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(-0.1f * scaleFactor + moveFactorX, 0.1f * scaleFactor + moveFactorY); // X, Y 이동 및 확대/축소를 적용한 위치
    glEnd();

    return 0;
}

int main(void)
{
    // GLFW 초기화
    if (!glfwInit())
        return -1;

    // 윈도우 생성
    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // OpenGL 컨텍스트를 현재 윈도우로 설정
    glfwMakeContextCurrent(window);

    // GLFW 콜백 함수 설정
    glfwSetErrorCallback(errorCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    // 렌더링 루프
    while (!glfwWindowShouldClose(window))
    {
        // 이벤트 처리
        glfwPollEvents();

        // 화면 지우기
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 렌더링
        render();

        // 화면 전환
        glfwSwapBuffers(window);
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
