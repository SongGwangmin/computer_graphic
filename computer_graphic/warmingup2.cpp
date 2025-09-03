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
	int uppermode = 0; // 0: 원래, 1: 대문자
	int wordnummode = 0; // 0: 원래, 1: 단어 개수 출력
	int capitalmode = 0; // 0: 원래, 1: 대문자 강조
	int wordreversemode = 0; // 0: 원래, 1: 거꾸로 출력
	int wordordermode = 0; // 0: 원래, 1: 단어 순서 거꾸로
	int spacemode = 0; // 0: 원래, 1: 공백을 '/'로
	int charchangemode = 0; // 0: 원래, 1: 문자 바꾸기
	int linenummode = 0; // 0: 원래, 1: 숫자 뒤 문장 다음 줄
	int sortmode = 0; // 0: 원래, 1: 오름차순, 2: 내림차순
	int highlightmode = 0; // 0: 원래, 1: 특정 단어 강조 및 개수 출력


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

        // 공백과 문자를 구분하는 변수
        int div = 0;
		// 문자 분리
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
        // 처리
        // 벡터 복사    
		std::vector<std::string> words_copy[10];
        for (int i = 0; i < count; ++i) {
            words_copy[i] = words[i];
		}
        // 공백 변환
       if (spacemode) {
            for (int i = 0; i < count; ++i) {
                for (int j = 0; j < words[i].size(); ++j) {
                    if(words[i][j][0] == ' '){
						words[i][j] = "/";
					}
                }
            }
        }

        // 출력
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
        // 문자 출력

        // 메뉴 출력
		std::cout << "a: 모든 문장을 대문자로 / 원래대로" << std::endl;
		std::cout << "b: 각 줄의 단어 개수 출력" << std::endl;
		std::cout << "c: 대문자로 시작하는 단어 강조 / 원래대로" << std::endl;
		std::cout << "d: 한 줄 문장 거꾸로 출력 / 원래대로" << std::endl;
		std::cout << "e: 공백을 '/'로 바꾸기 / 원래대로" << std::endl;
		std::cout << "f: 단어 순서를 거꾸로 출력 / 원래대로" << std::endl;
		std::cout << "g: 특정 문자를 다른 문자로 바꾸기 / 원래대로" << std::endl;
		std::cout << "h: 숫자 뒤의 문장을 다음 줄로 이동 / 원래대로" << std::endl;
		std::cout << "i: 문장을 알파벳 개수 기준 정렬 (오름/내림/원래 순환)" << std::endl;
		std::cout << "j: 입력한 단어 강조 및 개수 출력" << std::endl;
		std::cout << "q: 프로그램 종료" << std::endl;

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
				std::cout << "바꾸고 싶은 문자와 새 문자 입력: ";
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
                std::cout << "바꾸고 싶은 문자와 새 문자 입력: ";
                std::cin >> newstring;
                std::cin.ignore();

            }
            

            ++highlightmode;
            highlightmode %= 2;
        }
            break;
        case 'q':
            std::cout << "프로그램을 종료합니다." << std::endl;
            return 0;
        default:
        {

        }
            break;
        }

	}


	return 0;
}