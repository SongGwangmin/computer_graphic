#include <iostream>
#include <random>

typedef struct twoint {
	int oneint;
	int twoint;
} twoint;

int subdeterminant(int matrix[3][3]) {
	return matrix[0][0] * ((matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1]))
		- matrix[0][1] * ((matrix[1][0] * matrix[2][2]) - (matrix[1][2] * matrix[2][0]))
		+ matrix[0][2] * ((matrix[1][0] * matrix[2][1]) - (matrix[1][1] * matrix[2][0]));
}

twoint determinant(int matrix[2][4][4]) {
	int det[2]{};
	for (int i = 0; i < 2; i++) {

		int submatrix[3][3]{};
		int dontuse{};
		for (dontuse = 0; dontuse < 4; ++dontuse) {
			int slide{};
			for (int j = 1; j < 4; j++) { // 0행 고정으로 전개
				for (int k = 0; k < 4; k++) {
					if (k == dontuse) {
						continue;
					}
					submatrix[slide / 3][slide % 3] = matrix[i][j][k];
					slide++;
				}
			}
			int input = matrix[i][0][dontuse] * subdeterminant(submatrix);

			if (dontuse % 2) {
				input = -input;
			}

			det[i] += input;
		}
	}


	twoint result{};
	return result;
}

int main() {
	std::default_random_engine dre;

	std::random_device rd;

	dre.seed(rd());

	

	std::uniform_int_distribution<int> uid(1, 9);

	int matrix[2][4][4]{};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				matrix[i][j][k] = uid(dre);
			}
		}
	}
	int etoggle{};
	int ftoggle{};

	int max{};
	int min{};

	while (1) {
		char command{};

		max = 0;
		min = 10;

		int tmatrix[2][4][4]{};
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					tmatrix[i][j][k] = matrix[i][j][k];
					if (tmatrix[i][j][k] > max) { max = tmatrix[i][j][k]; }
					if (tmatrix[i][j][k] < min) {
						min = tmatrix[i][j][k];
					}
				}
			}
		}

		if (etoggle) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						tmatrix[i][j][k] += max;
					}
				}
			}
		}

		if (ftoggle) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						tmatrix[i][j][k] -= min;
					}
				}
			}
		}

		std::cout << "m. 곱셈, a. 덧셈, d. 뺄셈, r. 행렬식\nt. 전치 행렬, e. 최소값 빼기, f. 최대값 더하기\n(1 ~ 9). 입력받은 숫자의 배수만 출력, s. 행렬 재설정, q. 프로그램 종료 \nCommand: ";

		std::cin >> command;

		switch (command) {
		case 'm':
		{
			int result[4][4]{};

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k{}; k < 4; ++k) {
						result[i][j] += tmatrix[0][i][k] * tmatrix[1][k][j];
					}
				}
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					std::cout << result[i][j] << ' ';
				}
				std::cout << '\n';
			}
		}
			break;
		case 'a':
		{
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					std::cout << tmatrix[0][j][k] + tmatrix[1][j][k] << ' ';
				}
				std::cout << '\n';
			}

		}
			break;
		case 'd':
		{

			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					std::cout << tmatrix[0][j][k] - tmatrix[1][j][k] << ' ';
				}
				std::cout << '\n';
			}
		}
			break;

		default:
			break;
		}

		std::cin.ignore();
		std::cout << "press any key" << std::endl;
		std::cin.get();
		std::cin.ignore();
		system("cls");
	}
	
	return 0;
}