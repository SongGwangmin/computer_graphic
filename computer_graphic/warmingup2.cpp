#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cctype>

#define space 1
#define character 2

int main() {
	std::string line[10];

	std::vector<std::string> words[10];

	std::ifstream fout;
    char oldchar{}, newchar{};
	int uppermode = 0; // 0: ����, 1: �빮��
	int wordnummode = 0; // 0: ����, 1: �ܾ� ���� ���
	int capitalmode = 0; // 0: ����, 1: �빮�� ����
	int wordreversemode = 0; // 0: ����, 1: �Ųٷ� ���
	int wordordermode = 0; // 0: ����, 1: �ܾ� ���� �Ųٷ�
	int spacemode = 0; // 0: ����, 1: ������ '/'��
	int charchangemode = 0; // 0: ����, 1: ���� �ٲٱ�
	int linenummode = 0; // 0: ����, 1: ���� �� ���� ���� ��
	int sortmode = 0; // 0: ����, 1: ��������, 2: ��������
	int highlightmode = 0; // 0: ����, 1: Ư�� �ܾ� ���� �� ���� ���


	fout.open("data.txt");

	if (fout) {
		//std::cout << "File opened successfully.\n";
	}
	else {
		//std::cout << "Error opening file.\n";
		return -1;
	}

	int count = 0;

	while(getline(fout, line[count])){
		++count;
		
	}

	for (int i = 0; i < count; ++i) {
		std::cout << line[i] << '\n';
	}


	fout.close();

	while (1) {
		char command{};

        // ����� ���ڸ� �����ϴ� ����
        int div = 0;
		// ���� �и�
        for (int i = 0; i < 10; ++i) {
			words[i].clear();
            if(line[0][0] == ' ') div = space;
			else div = character;

			std::string strcat = "";
			//std::cout << line[i][line[i].size() - 1] << std::endl;

            for (int j = 0; j < line[i].size(); ++j) {
                if (div == space) {
                    if(line[i][j] == ' ') {
                        strcat.push_back(line[i][j]);
					}
                    else {
                        words[i].push_back(strcat);
						strcat = "";
						div = character;
                        strcat.push_back(line[i][j]);
                    }
                }
                else {
                    if (line[i][j] != ' ') {
                        strcat.push_back(line[i][j]);
                    }
                    else {
                        words[i].push_back(strcat);
						strcat = "";
						div = space;
                        strcat.push_back(line[i][j]);
                    }
                }
			}
            words[i].push_back(strcat);
        }
        // ó��
        // ���� ����    
		std::vector<std::string> words_copy[10];
        for (int i = 0; i < count; ++i) {
            words_copy[i] = words[i];
		}
        // ���� ��ȯ
       if (spacemode) {
            for (int i = 0; i < count; ++i) {
                for (int j = 0; j < words[i].size(); ++j) {
                    if(words[i][j][0] == ' '){
						words[i][j] = "/";
					}
                }
            }
        }

        // ���
		std::cout << "----------------------------------------" << std::endl;
        for (int i = 0; i < count; ++i) {
            for (int j = 0; j < words[i].size(); ++j) {
				//std::cout << words[i][j];
                for (int k = 0; k < words[i][j].size(); ++k) {
					std::cout << words_copy[i][j][k];
                }

                //::toupper(words[i][j][0]);
            }
			std::cout << std::endl;
        }
        // ���� ���

        // �޴� ���
		std::cout << "a: ��� ������ �빮�ڷ� / �������" << std::endl;
		std::cout << "b: �� ���� �ܾ� ���� ���" << std::endl;
		std::cout << "c: �빮�ڷ� �����ϴ� �ܾ� ���� / �������" << std::endl;
		std::cout << "d: �� �� ���� �Ųٷ� ��� / �������" << std::endl;
		std::cout << "e: ������ '/'�� �ٲٱ� / �������" << std::endl;
		std::cout << "f: �ܾ� ������ �Ųٷ� ��� / �������" << std::endl;
		std::cout << "g: Ư�� ���ڸ� �ٸ� ���ڷ� �ٲٱ� / �������" << std::endl;
		std::cout << "h: ���� ���� ������ ���� �ٷ� �̵� / �������" << std::endl;
		std::cout << "i: ������ ���ĺ� ���� ���� ���� (����/����/���� ��ȯ)" << std::endl;
		std::cout << "j: �Է��� �ܾ� ���� �� ���� ���" << std::endl;
		std::cout << "q: ���α׷� ����" << std::endl;

		std::cin >> command;
		std::cin.ignore();
        switch (command) {
        case 'a':
        {
			++uppermode;
			uppermode %= 2;
        }
            break;
        case 'b':
        {
			++wordnummode;
			wordnummode %= 2;

        }
            break;
        case 'c':
        {
			++capitalmode;
			capitalmode %= 2;


        }
            break;
        case 'd':
        {
			++wordreversemode;
			wordreversemode %= 2;
            ++wordordermode;
			wordordermode %= 2;
            
        }
            break;
        case 'e':
        {
			++spacemode;
			spacemode %= 2;
        }
            break;
        case 'f':
        {
			++wordordermode;
			wordordermode %= 2;
        }
            break;
        case 'g':
        {

            if (charchangemode == 0) {
				//char oldchar, newchar;
				std::cout << "�ٲٰ� ���� ���ڿ� �� ���� �Է�: ";
				std::cin >> oldchar >> newchar;
				std::cin.ignore();

            }

            ++charchangemode;
            charchangemode %= 2;
        }
            break;
        case 'h':
        {
			++linenummode;
			linenummode %= 2;

        }
            break;
        case 'i':
        {
			++sortmode;
			sortmode %= 3;
        }
            break;
        case 'j':
        {

            if (highlightmode == 0) {
                std::string newstring;
                std::cout << "�ٲٰ� ���� ���ڿ� �� ���� �Է�: ";
                std::cin >> newstring;
                std::cin.ignore();

            }
            

            ++highlightmode;
            highlightmode %= 2;
        }
            break;
        case 'q':
            std::cout << "���α׷��� �����մϴ�." << std::endl;
            return 0;
        default:
        {

        }
            break;
        }

	}


	return 0;
}