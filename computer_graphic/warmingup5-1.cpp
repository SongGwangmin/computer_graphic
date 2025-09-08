#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // std::max, std::min, std::swap�� ����ϱ� ���� �߰�
#include <conio.h>

// �ü���� �´� ȭ�� ����� ����� ����ϱ� ���� ����
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

// �簢��(����)�� ������ �����ϴ� ����ü
struct Shape {
    int x1, y1; // ���� ��� ��ǥ
    int x2, y2; // ���� �ϴ� ��ǥ
};

// ���� ������ ���� ũ��� ���� ����
int board_width = 30;
int board_height = 30;
Shape shape1, shape2;

// �Լ� ����
void normalizeShape(Shape& s);
void resetGame();
void drawBoard();
void processInput(char command);
void printInstructions();

int main() {
    // 1. ���� �ʱ�ȭ (��ǥ �Է�)
    resetGame();

    bool running = true;
    while (running) {
        // 2. ���� ���� �׸���
        clearScreen();
        drawBoard();
        printInstructions();

        // 3. ����� �Է� ó��
        std::cout << "\n��ɾ� �Է�: ";
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

    std::cout << "���α׷��� �����մϴ�." << std::endl;
    return 0;
}

// ����ڰ� �Է��� �� ��ǥ�� (�»��, ���ϴ�)���� ����ȭ�ϴ� �Լ�
void normalizeShape(Shape& s) {
    if (s.x1 > s.x2) std::swap(s.x1, s.x2);
    if (s.y1 > s.y2) std::swap(s.y1, s.y2);
}

// ������ �ʱ�ȭ�ϰų� �����ϴ� �Լ� (��ǥ ���Է�)
void resetGame() {
    clearScreen();
    std::cout << "--- ���� �׸��� ���α׷� (�ʱ� ����) ---\n";
    std::cout << "���� 1�� �� ������ ��ǥ (x1 y1 x2 y2)�� �Է��ϼ���: ";
    std::cin >> shape1.x1 >> shape1.y1 >> shape1.x2 >> shape1.y2;
    normalizeShape(shape1);

    std::cout << "���� 2�� �� ������ ��ǥ (x1 y1 x2 y2)�� �Է��ϼ���: ";
    std::cin >> shape2.x1 >> shape2.y1 >> shape2.x2 >> shape2.y2;
    normalizeShape(shape2);
}

// ���� ����� ������ ���¸� ȭ�鿡 �׸��� �Լ�
void drawBoard() {
    // 1. �׸��� �۾��� ���� 2���� ����(����) ���� �� '.'���� �ʱ�ȭ
    std::vector<std::vector<char>> buffer(board_height, std::vector<char>(board_width, '.'));

    // 2. ���� 1 �׸��� (����: O)
    // ȭ�� ������ ���� �ʺ�� ���̸� ���� ������� �ʰ�, �� ��ǥ�� ��ȸ�ϸ� ��ⷯ ���� ����
    for (int y_offset = 0; y_offset <= shape1.y2 - shape1.y1; ++y_offset) {
        for (int x_offset = 0; x_offset <= shape1.x2 - shape1.x1; ++x_offset) {
            int y = (shape1.y1 + y_offset) % board_height;
            int x = (shape1.x1 + x_offset) % board_width;
            // C++�� % �����ڴ� ���� ����� ���� �� �����Ƿ� ����� ����
            if (y < 0) y += board_height;
            if (x < 0) x += board_width;
            buffer[y][x] = 'O';
        }
    }

    // 3. ���� 2 �׸��� (����: X, �浹 ��: #)
    for (int y_offset = 0; y_offset <= shape2.y2 - shape2.y1; ++y_offset) {
        for (int x_offset = 0; x_offset <= shape2.x2 - shape2.x1; ++x_offset) {
            int y = (shape2.y1 + y_offset) % board_height;
            int x = (shape2.x1 + x_offset) % board_width;
            if (y < 0) y += board_height;
            if (x < 0) x += board_width;

            if (buffer[y][x] == 'O') {
                buffer[y][x] = '#'; // �浹
            }
            else {
                buffer[y][x] = 'X';
            }
        }
    }

    // 4. �ϼ��� ���۸� ȭ�鿡 ���
    std::cout << "���� ���� ũ��: " << board_width << "x" << board_height << std::endl;
    for (int i = 0; i < board_height; ++i) {
        for (int j = 0; j < board_width; ++j) {
            std::cout << buffer[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

// ����� �Է��� �޾� ���� ����(���� ��ǥ, ���� ũ�� ��)�� �����ϴ� �Լ�
void processInput(char command) {
    // ���� 1 ��ɾ�
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
    else if (command == 'A') { // x�� ���, y�� Ȯ��
        if (shape1.x2 > shape1.x1) shape1.x2--;
        if (shape1.y2 < board_height - 1) shape1.y2++;
    }
    // 'a'�� ���� 2�� �̵�Ű�� ���ǹǷ� ���� 1�� ��ɿ��� ����

    // ���� 2 ��ɾ�
    else if (command == 'd') { shape2.x1++; shape2.x2++; }
    else if (command == 'a') { shape2.x1--; shape2.x2--; }
    else if (command == 's') { shape2.y1++; shape2.y2++; }
    else if (command == 'w') { shape2.y1--; shape2.y2--; }
    else if (command == 'g') { // ���� 2 Ȯ��
        if (shape2.x2 < board_width - 1) shape2.x2++;
        if (shape2.y2 < board_height - 1) shape2.y2++;
    }
    else if (command == 't') { // ���� 2 ���
        if (shape2.x2 > shape2.x1) shape2.x2--;
        if (shape2.y2 > shape2.y1) shape2.y2--;
    }

    // ��Ÿ ��ɾ�
    else if (command == 'b') {
        clearScreen();
        int width1 = shape1.x2 - shape1.x1 + 1;
        int height1 = shape1.y2 - shape1.y1 + 1;
        std::cout << "���� 1(O)�� ����: " << width1 << " x " << height1 << " = " << width1 * height1 << std::endl;

        int width2 = shape2.x2 - shape2.x1 + 1;
        int height2 = shape2.y2 - shape2.y1 + 1;
        std::cout << "���� 2(X)�� ����: " << width2 << " x " << height2 << " = " << width2 * height2 << std::endl;

        std::cout << "\n����Ϸ��� Enter Ű�� ��������...";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }
    else if (command == 'c') { // ���� �ø���
        if (board_width < 40) board_width++; // �ִ� 10ĭ ���� (30+10)
        if (board_height < 40) board_height++;
    }
    else if (command == 'D') { // ���� ���̱� (d ��� D)
        if (board_width > 10) board_width--; // �ִ� 20ĭ ���� (30-20)
        if (board_height > 10) board_height--;

        // ���� ũ�Ⱑ �پ�� �� ������ �ۿ� ������ �ʵ��� ��ǥ ����
        if (shape1.x2 >= board_width) shape1.x2 = board_width - 1;
        if (shape1.y2 >= board_height) shape1.y2 = board_height - 1;
        normalizeShape(shape1);

        if (shape2.x2 >= board_width) shape2.x2 = board_width - 1;
        if (shape2.y2 >= board_height) shape2.y2 = board_height - 1;
        normalizeShape(shape2);
    }
}

// ����ڿ��� ��ɾ� ����� �����ִ� �Լ�
void printInstructions() {
    std::cout << "-------------------------------------------------------------------------\n";
    std::cout << "���� 1 (O):  �̵�(X,x,Y,y) | ��üȮ��/���(S/s) | x��(l/i) | y��(J/j)\n";
    std::cout << "���� 2 (X):  �̵�(a,d,w,s) | ��üȮ��/���(g/t)\n";
    std::cout << "��Ÿ:        ����(b) | ����Ȯ��/���(c/D) | ����(r) | ����(q)\n";
    std::cout << "-------------------------------------------------------------------------\n";
}