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

	int uppermode = 0; // 0: ����, 1: �빮��


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



        // ���
		std::cout << "----------------------------------------" << std::endl;
        for (int i = 0; i < count; ++i) {
            for (int j = 0; j < words[i].size(); ++j) {
				//std::cout << words[i][j];
                for (int k = 0; k < words[i][j].size(); ++k) {
					std::cout << words[i][j][k];
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

        }
            break;
        case 'b':
        {

        }
            break;
        case 'c':
        {

        }
            break;
        case 'd':
        {
            
        }
            break;
        case 'e':
        {

        }
            break;
        case 'f':
        {

        }
            break;
        case 'g':
        {

        }
            break;
        case 'h':
        {

        }
            break;
        case 'i':
        {

        }
            break;
        case 'j':
        {

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