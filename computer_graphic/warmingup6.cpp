#include <iostream>
#include <algorithm> // std::swap�� ����ϱ� ����
#include <random>    // ���� ������ ����
#include <ctime>     // ���� �õ� �ʱ�ȭ�� ����
#include <conio.h>
#include <windows.h>


// �迭�� ������ ����ϴ� �Լ� (��ü 900���� �� ����ϸ� �ʹ� �� �� 20���� ���)
void printArray(const char arr[], int size) {
    int limit = 900;
    for (int i = 0; i < limit; ++i) {
        if (arr[i] == 'x') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        }

        if (arr[i] == '*') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        }

        std::cout << arr[i] << ' ';
        if ((i + 1) % 30 == 0) {
            std::cout << std::endl;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }
    std::cout << std::endl;
}

int main() {
    // 1. 900���� char �迭�� �����մϴ�.
    const int ARRAY_SIZE = 900;
    char charArray[ARRAY_SIZE];
    // 2. �迭�� ��� ��Ҹ� '0'���� �ʱ�ȭ�մϴ�.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        charArray[i] = '0';
    }
	charArray[0] = '*'; // ù ��° ��Ҵ� '*'�� ����

    // 3. 1�� �ε������� 4���� 'x'�� �����մϴ�. (�ε��� 1, 2, 3, 4)
    for (int i = 1; i <= 4; ++i) {
        charArray[i] = 'x';
    }
    // 4. 1�� �ε������� 899�� �ε������� ������ �̿��� �����մϴ�.
    // �ֽ� C++ ����� ���� ������ ���
    std::random_device rd;  // �ϵ����� ���� ���� �õ带 �����ɴϴ�.
    std::mt19937 gen(rd()); // �޸��� Ʈ������ ������ �õ�� �ʱ�ȭ�մϴ�.

    // 1���� 899������ �յ� ���� ���� ������ ������ �غ�
    std::uniform_int_distribution<int> distrib(1, 899);

    // �Ǽ�-������ ���� �˰����� �����Ͽ� 1~899�� �ε����� �����ϴ�.
    for (int i = 899; i > 1; --i) {
        // i�� �ٲٱ� ���� ���� �ε����� 1���� i ���̿��� �����մϴ�.
        int j = distrib(gen) % i + 1;
        std::swap(charArray[i], charArray[j]);
    }

	char map[30][30]{};

    for(int i = 0; i < 30; ++i) {
        for(int j = 0; j < 30; ++j) {
            map[i][j] = charArray[i * 30 + j];
        }
	}

	int xpos = 0;
	int ypos = 0;

    int matrix[30][30] = { 0 };

    while (1) {
		system("cls");

        //printArray(charArray, ARRAY_SIZE);
        for (int i = 0; i < 900; ++i) {
            if (map[i / 30][i % 30] == 'x') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                std::cout << map[i / 30][i % 30] << ' ';
            }
            else if (xpos == i % 30 && ypos == i / 30) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                std::cout << '*' << ' ';
            }
            else {
                if (matrix[i / 30][i % 30] != 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                }
                std::cout << matrix[i / 30][i % 30];
                if (!(matrix[i / 30][i % 30] / 10)) {
					std::cout << ' ';
                }
            }

            
            if ((i + 1) % 30 == 0) {
                std::cout << std::endl;
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        std::cout << std::endl;
		std::cout << "Use WASD to move the '*'. Press 'q' to quit. press 'enter' to reset" << std::endl;
        
		char command = _getch();

        if (command == 'q') {
            break;
        }
        else if (command == 'w') {
            
            if (ypos > 0) {
                if (map[ypos - 1][xpos] != 'x') {
					++matrix[ypos][xpos];
                    ypos--;
                }
            }
        }
        else if (command == 's') {
            
            if (ypos < 29) {
                if (map[ypos + 1][xpos] != 'x') {
                    ++matrix[ypos][xpos];
                    ypos++;
                }
            }
        }
        else if (command == 'a') {
            
            if (xpos > 0) {

                if (map[ypos][xpos - 1] != 'x') {
                    ++matrix[ypos][xpos];
                    xpos--;
                }
            }
        }
        else if (command == 'd') {
            
            if (xpos < 29) {
                if (map[ypos][xpos + 1] != 'x') {
                    ++matrix[ypos][xpos];
                    xpos++;
                }
            }
        }
        else if (command == '\r') { // Enter key
            xpos = 0;
            ypos = 0;
            for (int i = 0; i < 30; ++i) {
                for (int j = 0; j < 30; ++j) {
                    matrix[i][j] = 0;
                }
			}
            for (int i = 899; i > 1; --i) {
                // i�� �ٲٱ� ���� ���� �ε����� 1���� i ���̿��� �����մϴ�.
                int j = distrib(gen) % i + 1;
                std::swap(charArray[i], charArray[j]);
            }
        }
    }
    return 0;
}