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

typedef struct rect {

	int x1, y1, x2, y2;
}rec;

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
	rec p1rect, p2rect;

	cin >> p1rect.x1 >> p1rect.y1 >> p1rect.x2 >> p1rect.y2;
	cin >> p2rect.x1 >> p2rect.y1 >> p2rect.x2 >> p2rect.y2;

	// 좌표 검사

	//
	char p1map[maxmapsize][maxmapsize]{};
	char p2map[maxmapsize][maxmapsize]{};

	for (int i = 0; i < maxmapsize; ++i) {
		for (int j = 0; j < maxmapsize; ++j) {
			if (j >= p1rect.x1 && j <= p1rect.x2 && i >= p1rect.y1 && i <= p1rect.y2) {
				p1map[i][j] = '1';
			}
			else {
				p1map[i][j] = '.';
			}
		}
	}

	for (int i = 0; i < maxmapsize; ++i) {
		for (int j = 0; j < maxmapsize; ++j) {
			if (j >= p2rect.x1 && j <= p2rect.x2 && i >= p2rect.y1 && i <= p2rect.y2) {
				p2map[i][j] = '2';
			}
			else {
				p2map[i][j] = '.';
			}
		}
	}


	for (int i = 0; i < nowmapsize; ++i) {
		for (int j = 0; j < nowmapsize; ++j) {
			if (p1map[i][j] == '1') {
				if (p2map[i][j] == '2') {
					cout << "3 ";
				}
				else {
					cout << p1map[i][j] << ' ';
				}
			}
			else {
				if (p2map[i][j] == '2') {
					cout << p2map[i][j] << ' ';
				}
				else {
					cout << ". ";
						
				}
			}
		}
		cout << endl;
	}



	return 0;
}