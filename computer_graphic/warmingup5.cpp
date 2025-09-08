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
	char map[maxmapsize][maxmapsize]{};

	int nowmapsize = 30;

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
				map[j % nowmapsize][i % nowmapsize] = '1';
			}
		}
		//fill map to 2
		for (int i = p2rect.x1; i <= p2rect.x2; ++i) {
			for (int j = p2rect.y1; j <= p2rect.y2; ++j) {
				if (map[j % nowmapsize][i % nowmapsize] == '1') {
					map[j % nowmapsize][i % nowmapsize] = '3';
				}
				else {
					map[j % nowmapsize][i % nowmapsize] = '2';
				}
			}
		}



		//print map
		for (int i = 0; i < nowmapsize; ++i) {
			for (int j = 0; j < nowmapsize; ++j) {
				cout << map[i][j] << ' ';
			}
			cout << endl;
		}

		//command list
	}

	return 0;
}