#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>
#include <windows.h>

#define maxmapsize 40
#define minmapsize 10 // 맵 줄어들면 도형도 줄어들어야함

using namespace std;

struct Shape {
    int x1, y1; // 좌측 상단 좌표
    int x2, y2; // 우측 하단 좌표
};

void normalizeShape(Shape& s) {
	if (s.x1 > s.x2) std::swap(s.x1, s.x2);
	if (s.y1 > s.y2) std::swap(s.y1, s.y2);
}

int main() {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	char map[maxmapsize][maxmapsize]{};

	int nowmapsize = 30;
	int ztoggle = 0; // z 누를때마다 0,1 바뀜

	for (int i = 0; i < maxmapsize; ++i) {
		for (int j = 0; j < maxmapsize; ++j) {
			map[i][j] = '.';
		}
	}

	for (int i = 0; i < nowmapsize;  ++i) {
		for (int j = 0; j < nowmapsize; ++j) {
			cout << map[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl << endl;
	Shape p1rect, p2rect;

	cout << "도형 1의 두 꼭짓점 좌표 (x1 y1 x2 y2)를 입력하세요: ";
	cin >> p1rect.x1 >> p1rect.y1 >> p1rect.x2 >> p1rect.y2;
	cout << "도형 2의 두 꼭짓점 좌표 (x1 y1 x2 y2)를 입력하세요: ";
	cin >> p2rect.x1 >> p2rect.y1 >> p2rect.x2 >> p2rect.y2;

	// 좌표 검사
	normalizeShape(p1rect);
	normalizeShape(p2rect);
	//


	//loop
	while (1) {
		system("cls");
		//init map
		for (int i = 0; i < maxmapsize; ++i) {
			for (int j = 0; j < maxmapsize; ++j) {
				map[i][j] = '.';
			}
		}

		//fill map to 1
		for (int i = p1rect.x1; i <= p1rect.x2; ++i) {
			for (int j = p1rect.y1; j <= p1rect.y2; ++j) {
				map[(j + nowmapsize)% nowmapsize][(i + nowmapsize) % nowmapsize] = '1';
			}
		}
		//fill map to 2
		for (int i = p2rect.x1; i <= p2rect.x2; ++i) {
			for (int j = p2rect.y1; j <= p2rect.y2; ++j) {
				if (map[(j + nowmapsize) % nowmapsize][(i + nowmapsize) % nowmapsize] == '1') {
                    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
					map[(j + nowmapsize) % nowmapsize][(i + nowmapsize) % nowmapsize] = '3';
                    
				}
				else {
					map[(j + nowmapsize) % nowmapsize][(i + nowmapsize) % nowmapsize] = '2';
				}
			}
		}



		//print map
		for (int i = 0; i < nowmapsize; ++i) {
			for (int j = 0; j < nowmapsize; ++j) {
                if (map[i][j] == '3') {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                }
				cout << map[i][j] << ' ';
                if (map[i][j] == '3') {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
			}
			cout << endl;
		}

		std::cout << "-------------------------------------------------------------------------\n";
		std::cout << "도형 1 (O):  이동(x,X,y,Y) | 전체확대/축소(s/S) | x축(i/I) | y축(j/J) | xy축 확대축소/축소확대(a/A)\n";
		std::cout << "도형 2 (X):  이동(f,F,b,B) | 전체확대/축소(t/T) | x축(n/N) | y축(m/M) | xy축 확대축소/축소확대(v/V)\n";
		std::cout << "기타:        면적(z) | 보드확대/축소(c/D) | 리셋(r) | 종료(q)\n";
		std::cout << "-------------------------------------------------------------------------\n";
        if (ztoggle) {
            std::cout << "p1 면적: " << p1rect.x2 - p1rect.x1 + 1 << " x " << p1rect.y2 - p1rect.y1 + 1
                << " = " << (p1rect.x2 - p1rect.x1 + 1) * (p1rect.y2 - p1rect.y1 + 1) << endl;
            std::cout << "p2 면적: " << p2rect.x2 - p2rect.x1 + 1 << " x " << p2rect.y2 - p2rect.y1 + 1
                << " = " << (p2rect.x2 - p2rect.x1 + 1) * (p2rect.y2 - p2rect.y1 + 1) << endl;
        }
		char command;
		cin >> command;
		cin.ignore();
		//command list


        switch (command) {
            // 도형 1 이동
        case 'x': {
            std::cout << "도형1: 오른쪽 이동\n";
            p1rect.x1++;
            p1rect.x2++;

            if (p1rect.x1 >= nowmapsize) {
                p1rect.x1 -= nowmapsize;
                p1rect.x2 -= nowmapsize;
            }
            break;
        }
        case 'X': {
            std::cout << "도형1: 왼쪽 이동\n";
            p1rect.x1--;
            p1rect.x2--;

            if (p1rect.x2 < 0) {
                p1rect.x1 += nowmapsize;
                p1rect.x2 += nowmapsize;
            }
            break;
        }
        case 'y': {
            std::cout << "도형1: 위쪽 이동\n";
            p1rect.y1--;
            p1rect.y2--;
            if (p1rect.y2 < 0) {
                p1rect.y1 += nowmapsize;
                p1rect.y2 += nowmapsize;
            }

            break;
        }
        case 'Y': {
            std::cout << "도형1: 아래쪽 이동\n";
            p1rect.y1++;
            p1rect.y2++;
            if (p1rect.y1 >= nowmapsize) {
                p1rect.y1 -= nowmapsize;
                p1rect.y2 -= nowmapsize;
            }

            break;
        }

                // 도형 1 변환
        case 's': {
            std::cout << "도형1: 전체 확대\n";
            if (p1rect.x2 - p1rect.x1 < nowmapsize && p1rect.y2 - p1rect.y1 < nowmapsize) {
				p1rect.x2++;
				p1rect.y2++;
            }

            break;
        }
        case 'S': {
            std::cout << "도형1: 전체 축소\n";

            if (p1rect.x2 - p1rect.x1 > 1 && p1rect.y2 - p1rect.y1 > 1) {
				p1rect.x2--;
				p1rect.y2--;

            }
            break;
        }
        case 'i': {
            std::cout << "도형1: x축 확대\n";
			if (p1rect.x2 - p1rect.x1 < nowmapsize) {
                p1rect.x2++;
			}
            break;
        }
        case 'I': {
            std::cout << "도형1: x축 축소\n";
            if (p1rect.x2 - p1rect.x1 > 1) {
				p1rect.x2--;
			}
            break;
        }
        case 'j': {
            std::cout << "도형1: y축 확대\n";
            if (p1rect.y2 - p1rect.y1 < nowmapsize) {
				p1rect.y2++;
			}

            break;
        }
        case 'J': {
            std::cout << "도형1: y축 축소\n";
			if (p1rect.y2 - p1rect.y1 > 1) {
				p1rect.y2--;
			}
            break;
        }
        case 'a': {
            std::cout << "도형1: xy축 확대축소\n";

			if (p1rect.x2 - p1rect.x1 < nowmapsize && p1rect.y2 - p1rect.y1 > 1) {
                p1rect.x2++;
				p1rect.y2--;
			}

            break;
        }
        case 'A': {
            std::cout << "도형1: xy축 축소확대\n";
            if (p1rect.x2 - p1rect.x1 > 1 && p1rect.y2 - p1rect.y1 < nowmapsize) {
				p1rect.x2--;
				p1rect.y2++;
			}
            break;
        }

                // 도형 2 이동
                // 도형 2 이동
        case 'f': {
            std::cout << "도형2: 오른쪽 이동\n";
            p2rect.x1++;
            p2rect.x2++;

            if (p2rect.x1 >= nowmapsize) {
                p2rect.x1 -= nowmapsize;
                p2rect.x2 -= nowmapsize;
            }
            break;
        }
        case 'F': {
            std::cout << "도형2: 왼쪽 이동\n";
            p2rect.x1--;
            p2rect.x2--;

            if (p2rect.x2 < 0) {
                p2rect.x1 += nowmapsize;
                p2rect.x2 += nowmapsize;
            }
            break;
        }
        case 'b': {
            std::cout << "도형2: 위쪽 이동\n";
            p2rect.y1--;
            p2rect.y2--;
            if (p2rect.y2 < 0) {
                p2rect.y1 += nowmapsize;
                p2rect.y2 += nowmapsize;
            }
            break;
        }
        case 'B': {
            std::cout << "도형2: 아래쪽 이동\n";
            p2rect.y1++;
            p2rect.y2++;
            if (p2rect.y1 >= nowmapsize) {
                p2rect.y1 -= nowmapsize;
                p2rect.y2 -= nowmapsize;
            }
            break;
        }

                // 도형 2 변환
        case 't': {
            std::cout << "도형2: 전체 확대\n";
            if (p2rect.x2 - p2rect.x1 < nowmapsize && p2rect.y2 - p2rect.y1 < nowmapsize) {
                p2rect.x2++;
                p2rect.y2++;
            }
            break;
        }
        case 'T': {
            std::cout << "도형2: 전체 축소\n";
            if (p2rect.x2 - p2rect.x1 > 1 && p2rect.y2 - p2rect.y1 > 1) {
                p2rect.x2--;
                p2rect.y2--;
            }
            break;
        }
        case 'n': {
            std::cout << "도형2: x축 확대\n";
            if (p2rect.x2 - p2rect.x1 < nowmapsize) {
                p2rect.x2++;
            }
            break;
        }
        case 'N': {
            std::cout << "도형2: x축 축소\n";
            if (p2rect.x2 - p2rect.x1 > 1) {
                p2rect.x2--;
            }
            break;
        }
        case 'm': {
            std::cout << "도형2: y축 확대\n";
            if (p2rect.y2 - p2rect.y1 < nowmapsize) {
                p2rect.y2++;
            }
            break;
        }
        case 'M': {
            std::cout << "도형2: y축 축소\n";
            if (p2rect.y2 - p2rect.y1 > 1) {
                p2rect.y2--;
            }
            break;
        }
        case 'v': {
            std::cout << "도형2: xy축 확대축소\n";
            if (p2rect.x2 - p2rect.x1 < nowmapsize && p2rect.y2 - p2rect.y1 > 1) {
                p2rect.x2++;
                p2rect.y2--;
            }
            break;
        }
        case 'V': {
            std::cout << "도형2: xy축 축소확대\n";
            if (p2rect.x2 - p2rect.x1 > 1 && p2rect.y2 - p2rect.y1 < nowmapsize) {
                p2rect.x2--;
                p2rect.y2++;
            }
            break;
        }

                // 기타 기능
        case 'c': {
            std::cout << "보드 확대\n";
            if (nowmapsize < maxmapsize) {
                nowmapsize++;
			}
            break;
        }
        case 'D': {
            std::cout << "보드 축소\n";
            if (nowmapsize > minmapsize) {
                nowmapsize--;

                if (p1rect.x2 - p1rect.x1 >= nowmapsize) {
					p1rect.x2 = p1rect.x1 + nowmapsize - 1;
                }
                if (p1rect.y2 - p1rect.y1 >= nowmapsize) {
                    p1rect.y2 = p1rect.y1 + nowmapsize - 1;
                }

                if (p2rect.x2 - p2rect.x1 >= nowmapsize) {
                    p2rect.x2 = p2rect.x1 + nowmapsize - 1;
                }
                if (p2rect.y2 - p2rect.y1 >= nowmapsize) {
                    p2rect.y2 = p2rect.y1 + nowmapsize - 1;
                }
            }
            break;
        }
        case 'r': {
            std::cout << "리셋\n";
            break;
        }
        case 'q': {
            std::cout << "종료합니다.\n";
            break;
        }
        case 'z': {
            std::cout << "면적 계산\n";
			ztoggle = 1 - ztoggle;
            break;
        }

                // 기본 처리
        default: {
            std::cout << "잘못된 입력입니다.\n";
            break;
        }
        }

	}

	return 0;
}