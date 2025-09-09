#include <iostream>
#include <algorithm> // std::swap을 사용하기 위함
#include <random>    // 난수 생성을 위함
#include <ctime>     // 난수 시드 초기화를 위함
#include <conio.h>
#include <windows.h>


// 배열의 내용을 출력하는 함수 (전체 900개를 다 출력하면 너무 길어서 앞 20개만 출력)
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
    // 1. 900개의 char 배열을 선언합니다.
    const int ARRAY_SIZE = 900;
    char charArray[ARRAY_SIZE];
    // 2. 배열의 모든 요소를 '0'으로 초기화합니다.
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        charArray[i] = '0';
    }
	charArray[0] = '*'; // 첫 번째 요소는 '*'로 설정

    // 3. 1번 인덱스부터 4개를 'x'로 변경합니다. (인덱스 1, 2, 3, 4)
    for (int i = 1; i <= 4; ++i) {
        charArray[i] = 'x';
    }
    // 4. 1번 인덱스부터 899번 인덱스까지 난수를 이용해 스왑합니다.
    // 최신 C++ 방식의 난수 생성기 사용
    std::random_device rd;  // 하드웨어에서 직접 난수 시드를 가져옵니다.
    std::mt19937 gen(rd()); // 메르센 트위스터 엔진을 시드로 초기화합니다.

    // 1부터 899까지의 균등 분포 정수 난수를 생성할 준비
    std::uniform_int_distribution<int> distrib(1, 899);

    // 피셔-예이츠 셔플 알고리즘을 적용하여 1~899번 인덱스를 섞습니다.
    for (int i = 899; i > 1; --i) {
        // i와 바꾸기 위한 랜덤 인덱스를 1부터 i 사이에서 선택합니다.
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
                // i와 바꾸기 위한 랜덤 인덱스를 1부터 i 사이에서 선택합니다.
                int j = distrib(gen) % i + 1;
                std::swap(charArray[i], charArray[j]);
            }
        }
    }
    return 0;
}