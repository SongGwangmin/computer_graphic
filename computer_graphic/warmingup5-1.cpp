#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // std::max, std::min, std::swap을 사용하기 위해 추가
#include <conio.h>

// 운영체제에 맞는 화면 지우기 명령을 사용하기 위한 설정
#ifdef _WIN32
#include <windows.h>
void clearScreen() {
    system("cls");
}
#else
#include <unistd.h>
void clearScreen() {
    system("clear");
}
#endif

// 사각형(도형)의 정보를 저장하는 구조체
struct Shape {
    int x1, y1; // 좌측 상단 좌표
    int x2, y2; // 우측 하단 좌표
};

// 전역 변수로 보드 크기와 도형 관리
int board_width = 30;
int board_height = 30;
Shape shape1, shape2;

// 함수 선언
void normalizeShape(Shape& s);
void resetGame();
void drawBoard();
void processInput(char command);
void printInstructions();

int main() {
    // 1. 게임 초기화 (좌표 입력)
    resetGame();

    bool running = true;
    while (running) {
        // 2. 현재 상태 그리기
        clearScreen();
        drawBoard();
        printInstructions();

        // 3. 사용자 입력 처리
        std::cout << "\n명령어 입력: ";
        char command;
        //std::cin >> command;
		command = _getch();
        if (command == 'q') {
            running = false;
        }
        else if (command == 'r') {
            resetGame();
        }
        else {
            processInput(command);
        }
    }

    std::cout << "프로그램을 종료합니다." << std::endl;
    return 0;
}

// 사용자가 입력한 두 좌표를 (좌상단, 우하단)으로 정규화하는 함수
void normalizeShape(Shape& s) {
    if (s.x1 > s.x2) std::swap(s.x1, s.x2);
    if (s.y1 > s.y2) std::swap(s.y1, s.y2);
}

// 게임을 초기화하거나 리셋하는 함수 (좌표 재입력)
void resetGame() {
    clearScreen();
    std::cout << "--- 도형 그리기 프로그램 (초기 설정) ---\n";
    std::cout << "도형 1의 두 꼭짓점 좌표 (x1 y1 x2 y2)를 입력하세요: ";
    std::cin >> shape1.x1 >> shape1.y1 >> shape1.x2 >> shape1.y2;
    normalizeShape(shape1);

    std::cout << "도형 2의 두 꼭짓점 좌표 (x1 y1 x2 y2)를 입력하세요: ";
    std::cin >> shape2.x1 >> shape2.y1 >> shape2.x2 >> shape2.y2;
    normalizeShape(shape2);
}

// 현재 보드와 도형의 상태를 화면에 그리는 함수
void drawBoard() {
    // 1. 그리기 작업을 위한 2차원 벡터(버퍼) 생성 및 '.'으로 초기화
    std::vector<std::vector<char>> buffer(board_height, std::vector<char>(board_width, '.'));

    // 2. 도형 1 그리기 (문자: O)
    // 화면 래핑을 위해 너비와 높이를 직접 계산하지 않고, 각 좌표를 순회하며 모듈러 연산 적용
    for (int y_offset = 0; y_offset <= shape1.y2 - shape1.y1; ++y_offset) {
        for (int x_offset = 0; x_offset <= shape1.x2 - shape1.x1; ++x_offset) {
            int y = (shape1.y1 + y_offset) % board_height;
            int x = (shape1.x1 + x_offset) % board_width;
            // C++의 % 연산자는 음수 결과가 나올 수 있으므로 양수로 보정
            if (y < 0) y += board_height;
            if (x < 0) x += board_width;
            buffer[y][x] = 'O';
        }
    }

    // 3. 도형 2 그리기 (문자: X, 충돌 시: #)
    for (int y_offset = 0; y_offset <= shape2.y2 - shape2.y1; ++y_offset) {
        for (int x_offset = 0; x_offset <= shape2.x2 - shape2.x1; ++x_offset) {
            int y = (shape2.y1 + y_offset) % board_height;
            int x = (shape2.x1 + x_offset) % board_width;
            if (y < 0) y += board_height;
            if (x < 0) x += board_width;

            if (buffer[y][x] == 'O') {
                buffer[y][x] = '#'; // 충돌
            }
            else {
                buffer[y][x] = 'X';
            }
        }
    }

    // 4. 완성된 버퍼를 화면에 출력
    std::cout << "현재 보드 크기: " << board_width << "x" << board_height << std::endl;
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            std::cout << buffer[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

// 사용자 입력을 받아 게임 상태(도형 좌표, 보드 크기 등)를 변경하는 함수
void processInput(char command) {
    // 도형 1 명령어
    if (command == 'x') { shape1.x1++; shape1.x2++; }
    else if (command == 'X') { shape1.x1--; shape1.x2--; }
    else if (command == 'y') { shape1.y1++; shape1.y2++; }
    else if (command == 'Y') { shape1.y1--; shape1.y2--; }
    else if (command == 'S') {
        if (shape1.x2 < board_width - 1) shape1.x2++;
        if (shape1.y2 < board_height - 1) shape1.y2++;
    }
    else if (command == 's') {
        if (shape1.x2 > shape1.x1) shape1.x2--;
        if (shape1.y2 > shape1.y1) shape1.y2--;
    }
    else if (command == 'l') { if (shape1.x2 < board_width - 1) shape1.x2++; }
    else if (command == 'i') { if (shape1.x2 > shape1.x1) shape1.x2--; }
    else if (command == 'J') { if (shape1.y2 < board_height - 1) shape1.y2++; }
    else if (command == 'j') { if (shape1.y2 > shape1.y1) shape1.y2--; }
    else if (command == 'A') { // x축 축소, y축 확대
        if (shape1.x2 > shape1.x1) shape1.x2--;
        if (shape1.y2 < board_height - 1) shape1.y2++;
    }
    // 'a'는 도형 2의 이동키로 사용되므로 도형 1의 기능에서 제외

    // 도형 2 명령어
    else if (command == 'd') { shape2.x1++; shape2.x2++; }
    else if (command == 'a') { shape2.x1--; shape2.x2--; }
    else if (command == 's') { shape2.y1++; shape2.y2++; }
    else if (command == 'w') { shape2.y1--; shape2.y2--; }
    else if (command == 'g') { // 도형 2 확대
        if (shape2.x2 < board_width - 1) shape2.x2++;
        if (shape2.y2 < board_height - 1) shape2.y2++;
    }
    else if (command == 't') { // 도형 2 축소
        if (shape2.x2 > shape2.x1) shape2.x2--;
        if (shape2.y2 > shape2.y1) shape2.y2--;
    }

    // 기타 명령어
    else if (command == 'b') {
        clearScreen();
        int width1 = shape1.x2 - shape1.x1 + 1;
        int height1 = shape1.y2 - shape1.y1 + 1;
        std::cout << "도형 1(O)의 면적: " << width1 << " x " << height1 << " = " << width1 * height1 << std::endl;

        int width2 = shape2.x2 - shape2.x1 + 1;
        int height2 = shape2.y2 - shape2.y1 + 1;
        std::cout << "도형 2(X)의 면적: " << width2 << " x " << height2 << " = " << width2 * height2 << std::endl;

        std::cout << "\n계속하려면 Enter 키를 누르세요...";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }
    else if (command == 'c') { // 보드 늘리기
        if (board_width < 40) board_width++; // 최대 10칸 증가 (30+10)
        if (board_height < 40) board_height++;
    }
    else if (command == 'D') { // 보드 줄이기 (d 대신 D)
        if (board_width > 10) board_width--; // 최대 20칸 감소 (30-20)
        if (board_height > 10) board_height--;

        // 보드 크기가 줄어들 때 도형이 밖에 나가지 않도록 좌표 조정
        if (shape1.x2 >= board_width) shape1.x2 = board_width - 1;
        if (shape1.y2 >= board_height) shape1.y2 = board_height - 1;
        normalizeShape(shape1);

        if (shape2.x2 >= board_width) shape2.x2 = board_width - 1;
        if (shape2.y2 >= board_height) shape2.y2 = board_height - 1;
        normalizeShape(shape2);
    }
}

// 사용자에게 명령어 목록을 보여주는 함수
void printInstructions() {
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "도형 1 (O):  이동(X,x,Y,y) | 전체확대/축소(S/s) | x축(l/i) | y축(J/j)\n";
    std::cout << "도형 2 (X):  이동(a,d,w,s) | 전체확대/축소(g/t)\n";
    std::cout << "기타:        면적(b) | 보드확대/축소(c/D) | 리셋(r) | 종료(q)\n";
    std::cout << "-------------------------------------------------------------------------\n";
}