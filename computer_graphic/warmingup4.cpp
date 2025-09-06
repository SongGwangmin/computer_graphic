#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>
#include <windows.h>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 24);

int main() {
	char cardlist[25];

	int turn = 0;

	for (int i = 0; i < 25; ++i) {
		cardlist[i] = 'a' + (i / 2);
	}

	cardlist[24] = '@';

	char board[5][5]{};


	for (int i = 0; i < 25; ++i) {
		std::cout << cardlist[i] << ' ';

		if((i + 1) % 5 == 0) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	
	//카드 섞기
	for (int i = 0; i < 10000; ++i) {
		int a = dist(gen);
		int b = dist(gen);
		char temp = cardlist[a];
		cardlist[a] = cardlist[b];
		cardlist[b] = temp;
	}

	for(int i = 0; i < 25; ++i) {
		board[i / 5][i % 5] = '*';
	}
	char command1x[2], command1y[2];

	while (1) {
		system("cls");
		std::cout << "   a  b  c  d  e " << std::endl;


		for (int i = 0; i < 25; ++i) {
			if (i % 5 == 0) {
				std::cout << std::endl;
				std::cout << i / 5 + 1 << "  ";
			}

			if (board[i / 5][i % 5] != '*') {

				if (cardlist[i] == '@') {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				}
				else {
					char color = toupper(cardlist[i]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (color - 'A') + 1);
				}

				std::cout << cardlist[i] << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else {
				std::cout << board[i / 5][i % 5] << "  ";
			}
			
		}


		if (turn == 2) {
			for (int i = 0; i < 25; ++i) {
				if (board[i / 5][i % 5] == '1') {
					board[i / 5][i % 5] = '*';
				}
			}
			Sleep(1000);
			turn = 0;
			continue;
		}
		
		// 커맨드 입력
		std::cout << std::endl << "좌표 입력 (예: a 1): ";

		std::string command{};
		std::string argument[3];

		std::getline(std::cin, command);

		std::istringstream iss(command);
		std::vector<std::string> tokens;
		std::string token;



		while (iss >> token) {
			tokens.push_back(token);
		}

		if (tokens.size() == 2) {
			command1x[turn] = tokens[0][0];
			command1y[turn] = tokens[1][0];

			if (command1x[turn] < 'a' || command1x[turn] > 'e' || command1y[turn] < '1' || command1y[turn] > '5') {
				std::cout << "잘못된 좌표입니다. 다시 입력해주세요." << std::endl;
				Sleep(1000);
				continue;
			}

			if (board[command1y[turn] - '1'][command1x[turn] - 'a'] != '*') {
				std::cout << "이미 뒤집힌 카드입니다. 다시 입력해주세요." << std::endl;
				Sleep(1000);
				continue;
			}

			board[command1y[turn] - '1'][command1x[turn] - 'a'] = '1';

			if (turn == 1) {
				if (cardlist[(command1y[0] - '1') * 5 + (command1x[0] - 'a')] == cardlist[(command1y[1] - '1') * 5 + (command1x[1] - 'a')]) {
					std::cout << "같은 카드입니다!" << std::endl;
					board[command1y[0] - '1'][command1x[0] - 'a'] = '2';
					board[command1y[1] - '1'][command1x[1] - 'a'] = '2';
					cardlist[(command1y[0] - '1') * 5 + (command1x[0] - 'a')] = toupper(cardlist[(command1y[0] - '1') * 5 + (command1x[0] - 'a')]);
					cardlist[(command1y[1] - '1') * 5 + (command1x[1] - 'a')] = toupper(cardlist[(command1y[1] - '1') * 5 + (command1x[1] - 'a')]);
				}
				else if (cardlist[(command1y[1] - '1') * 5 + (command1x[1] - 'a')] == '@' || cardlist[(command1y[0] - '1') * 5 + (command1x[0] - 'a')] == '@') {
					std::cout << "같은 카드입니다!" << std::endl;
					board[command1y[0] - '1'][command1x[0] - 'a'] = '2';
					board[command1y[1] - '1'][command1x[1] - 'a'] = '2';
					cardlist[(command1y[0] - '1') * 5 + (command1x[0] - 'a')] = toupper(cardlist[(command1y[0] - '1') * 5 + (command1x[0] - 'a')]);
					cardlist[(command1y[1] - '1') * 5 + (command1x[1] - 'a')] = toupper(cardlist[(command1y[1] - '1') * 5 + (command1x[1] - 'a')]);
				}
				else {
					std::cout << "다른 카드입니다!" << std::endl;
				}
			}

			++turn;
		}
		else if (tokens.size() == 1) {
			if (tokens[0][0] == 'h') {
				system("cls");
				std::cout << "   a  b  c  d  e " << std::endl;

				for (int i = 0; i < 25; ++i) {
					if (i % 5 == 0) {
						std::cout << std::endl;
						std::cout << i / 5 + 1 << "  ";
					}

					if (cardlist[i] == '@') {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
					}
					else {
						char color = toupper(cardlist[i]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (color - 'A') + 1);
					}
						
					std::cout << cardlist[i] << "  ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

				}

				Sleep(3000);
			}
			else if(tokens[0][0] == 'q') {
				break;
			}
			else if (tokens[0][0] == 'r') {
				turn = 0;
				for (int i = 0; i < 25; ++i) {
					board[i / 5][i % 5] = '*';
				}
				for (int i = 0; i < 10000; ++i) {
					int a = dist(gen);
					int b = dist(gen);
					char temp = cardlist[a];
					cardlist[a] = cardlist[b];
					cardlist[b] = temp;
				}
				for (int i = 0; i < 25; ++i) {
					if (isupper(cardlist[i])) {
						cardlist[i] = tolower(cardlist[i]);
					}
				}
			}
			else {
				std::cout << "잘못된 명령어입니다. 다시 입력해주세요." << std::endl;
				Sleep(1000);
				continue;
			}
		}
		else {
			std::cout << "잘못된 명령어입니다. 다시 입력해주세요." << std::endl;
			Sleep(1000);
			continue;
		}

		/*command1x[turn] = tokens[0][0];
		command1y[turn] = tokens[1][0];

		if (command1x[turn] < 'a' || command1x[turn] > 'e' || command1y[turn] < '1' || command1y[turn] > '5') {
			std::cout << "잘못된 좌표입니다. 다시 입력해주세요." << std::endl;
			Sleep(1000);
			continue;
		}

		if (board[command1y[turn] - '1'][command1x[turn] - 'a'] != '*') {
			std::cout << "이미 뒤집힌 카드입니다. 다시 입력해주세요." << std::endl;
			Sleep(1000);
			continue;
		}

		board[command1y[turn] - '1'][command1x[turn] - 'a'] = '1';

		if (turn == 1) {
			if (cardlist[(command1y[0] - '1') * 5 + (command1x[0] - 'a')] == cardlist[(command1y[1] - '1') * 5 + (command1x[1] - 'a')]) {
				std::cout << "같은 카드입니다!" << std::endl; 
				board[command1y[0] - '1'][command1x[0] - 'a'] = '2';
				board[command1y[1] - '1'][command1x[1] - 'a'] = '2';
			}
			else {
				std::cout << "다른 카드입니다!" << std::endl;
			}
		}

		++turn;*/
	}

	return 0;
}