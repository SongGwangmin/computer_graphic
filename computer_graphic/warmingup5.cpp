#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>
#include <windows.h>

#define maxmapsize 40
#define minmapsize 10 // �� �پ��� ������ �پ������

using namespace std;

struct Shape {
    int x1, y1; // ���� ��� ��ǥ
    int x2, y2; // ���� �ϴ� ��ǥ
};

void normalizeShape(Shape& s) {
	if (s.x1 > s.x2) std::swap(s.x1, s.x2);
	if (s.y1 > s.y2) std::swap(s.y1, s.y2);
}

int main() {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	char map[maxmapsize][maxmapsize]{};

	int nowmapsize = 30;
	int ztoggle = 0; // z ���������� 0,1 �ٲ�

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

	cout << "���� 1�� �� ������ ��ǥ (x1 y1 x2 y2)�� �Է��ϼ���: ";
	cin >> p1rect.x1 >> p1rect.y1 >> p1rect.x2 >> p1rect.y2;
	cout << "���� 2�� �� ������ ��ǥ (x1 y1 x2 y2)�� �Է��ϼ���: ";
	cin >> p2rect.x1 >> p2rect.y1 >> p2rect.x2 >> p2rect.y2;

	// ��ǥ �˻�
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
		std::cout << "���� 1 (O):  �̵�(x,X,y,Y) | ��üȮ��/���(s/S) | x��(i/I) | y��(j/J) | xy�� Ȯ�����/���Ȯ��(a/A)\n";
		std::cout << "���� 2 (X):  �̵�(f,F,b,B) | ��üȮ��/���(t/T) | x��(n/N) | y��(m/M) | xy�� Ȯ�����/���Ȯ��(v/V)\n";
		std::cout << "��Ÿ:        ����(z) | ����Ȯ��/���(c/D) | ����(r) | ����(q)\n";
		std::cout << "-------------------------------------------------------------------------\n";
        if (ztoggle) {
            std::cout << "p1 ����: " << p1rect.x2 - p1rect.x1 + 1 << " x " << p1rect.y2 - p1rect.y1 + 1
                << " = " << (p1rect.x2 - p1rect.x1 + 1) * (p1rect.y2 - p1rect.y1 + 1) << endl;
            std::cout << "p2 ����: " << p2rect.x2 - p2rect.x1 + 1 << " x " << p2rect.y2 - p2rect.y1 + 1
                << " = " << (p2rect.x2 - p2rect.x1 + 1) * (p2rect.y2 - p2rect.y1 + 1) << endl;
        }
		char command;
		cin >> command;
		cin.ignore();
		//command list


        switch (command) {
            // ���� 1 �̵�
        case 'x': {
            std::cout << "����1: ������ �̵�\n";
            p1rect.x1++;
            p1rect.x2++;

            if (p1rect.x1 >= nowmapsize) {
                p1rect.x1 -= nowmapsize;
                p1rect.x2 -= nowmapsize;
            }
            break;
        }
        case 'X': {
            std::cout << "����1: ���� �̵�\n";
            p1rect.x1--;
            p1rect.x2--;

            if (p1rect.x2 < 0) {
                p1rect.x1 += nowmapsize;
                p1rect.x2 += nowmapsize;
            }
            break;
        }
        case 'y': {
            std::cout << "����1: ���� �̵�\n";
            p1rect.y1--;
            p1rect.y2--;
            if (p1rect.y2 < 0) {
                p1rect.y1 += nowmapsize;
                p1rect.y2 += nowmapsize;
            }

            break;
        }
        case 'Y': {
            std::cout << "����1: �Ʒ��� �̵�\n";
            p1rect.y1++;
            p1rect.y2++;
            if (p1rect.y1 >= nowmapsize) {
                p1rect.y1 -= nowmapsize;
                p1rect.y2 -= nowmapsize;
            }

            break;
        }

                // ���� 1 ��ȯ
        case 's': {
            std::cout << "����1: ��ü Ȯ��\n";
            if (p1rect.x2 - p1rect.x1 < nowmapsize && p1rect.y2 - p1rect.y1 < nowmapsize) {
				p1rect.x2++;
				p1rect.y2++;
            }

            break;
        }
        case 'S': {
            std::cout << "����1: ��ü ���\n";

            if (p1rect.x2 - p1rect.x1 > 1 && p1rect.y2 - p1rect.y1 > 1) {
				p1rect.x2--;
				p1rect.y2--;

            }
            break;
        }
        case 'i': {
            std::cout << "����1: x�� Ȯ��\n";
			if (p1rect.x2 - p1rect.x1 < nowmapsize) {
                p1rect.x2++;
			}
            break;
        }
        case 'I': {
            std::cout << "����1: x�� ���\n";
            if (p1rect.x2 - p1rect.x1 > 1) {
				p1rect.x2--;
			}
            break;
        }
        case 'j': {
            std::cout << "����1: y�� Ȯ��\n";
            if (p1rect.y2 - p1rect.y1 < nowmapsize) {
				p1rect.y2++;
			}

            break;
        }
        case 'J': {
            std::cout << "����1: y�� ���\n";
			if (p1rect.y2 - p1rect.y1 > 1) {
				p1rect.y2--;
			}
            break;
        }
        case 'a': {
            std::cout << "����1: xy�� Ȯ�����\n";

			if (p1rect.x2 - p1rect.x1 < nowmapsize && p1rect.y2 - p1rect.y1 > 1) {
                p1rect.x2++;
				p1rect.y2--;
			}

            break;
        }
        case 'A': {
            std::cout << "����1: xy�� ���Ȯ��\n";
            if (p1rect.x2 - p1rect.x1 > 1 && p1rect.y2 - p1rect.y1 < nowmapsize) {
				p1rect.x2--;
				p1rect.y2++;
			}
            break;
        }

                // ���� 2 �̵�
                // ���� 2 �̵�
        case 'f': {
            std::cout << "����2: ������ �̵�\n";
            p2rect.x1++;
            p2rect.x2++;

            if (p2rect.x1 >= nowmapsize) {
                p2rect.x1 -= nowmapsize;
                p2rect.x2 -= nowmapsize;
            }
            break;
        }
        case 'F': {
            std::cout << "����2: ���� �̵�\n";
            p2rect.x1--;
            p2rect.x2--;

            if (p2rect.x2 < 0) {
                p2rect.x1 += nowmapsize;
                p2rect.x2 += nowmapsize;
            }
            break;
        }
        case 'b': {
            std::cout << "����2: ���� �̵�\n";
            p2rect.y1--;
            p2rect.y2--;
            if (p2rect.y2 < 0) {
                p2rect.y1 += nowmapsize;
                p2rect.y2 += nowmapsize;
            }
            break;
        }
        case 'B': {
            std::cout << "����2: �Ʒ��� �̵�\n";
            p2rect.y1++;
            p2rect.y2++;
            if (p2rect.y1 >= nowmapsize) {
                p2rect.y1 -= nowmapsize;
                p2rect.y2 -= nowmapsize;
            }
            break;
        }

                // ���� 2 ��ȯ
        case 't': {
            std::cout << "����2: ��ü Ȯ��\n";
            if (p2rect.x2 - p2rect.x1 < nowmapsize && p2rect.y2 - p2rect.y1 < nowmapsize) {
                p2rect.x2++;
                p2rect.y2++;
            }
            break;
        }
        case 'T': {
            std::cout << "����2: ��ü ���\n";
            if (p2rect.x2 - p2rect.x1 > 1 && p2rect.y2 - p2rect.y1 > 1) {
                p2rect.x2--;
                p2rect.y2--;
            }
            break;
        }
        case 'n': {
            std::cout << "����2: x�� Ȯ��\n";
            if (p2rect.x2 - p2rect.x1 < nowmapsize) {
                p2rect.x2++;
            }
            break;
        }
        case 'N': {
            std::cout << "����2: x�� ���\n";
            if (p2rect.x2 - p2rect.x1 > 1) {
                p2rect.x2--;
            }
            break;
        }
        case 'm': {
            std::cout << "����2: y�� Ȯ��\n";
            if (p2rect.y2 - p2rect.y1 < nowmapsize) {
                p2rect.y2++;
            }
            break;
        }
        case 'M': {
            std::cout << "����2: y�� ���\n";
            if (p2rect.y2 - p2rect.y1 > 1) {
                p2rect.y2--;
            }
            break;
        }
        case 'v': {
            std::cout << "����2: xy�� Ȯ�����\n";
            if (p2rect.x2 - p2rect.x1 < nowmapsize && p2rect.y2 - p2rect.y1 > 1) {
                p2rect.x2++;
                p2rect.y2--;
            }
            break;
        }
        case 'V': {
            std::cout << "����2: xy�� ���Ȯ��\n";
            if (p2rect.x2 - p2rect.x1 > 1 && p2rect.y2 - p2rect.y1 < nowmapsize) {
                p2rect.x2--;
                p2rect.y2++;
            }
            break;
        }

                // ��Ÿ ���
        case 'c': {
            std::cout << "���� Ȯ��\n";
            if (nowmapsize < maxmapsize) {
                nowmapsize++;
			}
            break;
        }
        case 'D': {
            std::cout << "���� ���\n";
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
            std::cout << "����\n";
            break;
        }
        case 'q': {
            std::cout << "�����մϴ�.\n";
            break;
        }
        case 'z': {
            std::cout << "���� ���\n";
			ztoggle = 1 - ztoggle;
            break;
        }

                // �⺻ ó��
        default: {
            std::cout << "�߸��� �Է��Դϴ�.\n";
            break;
        }
        }

	}

	return 0;
}