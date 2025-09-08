#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <cctype>

#define space 1
#define character 2

int countalphbet(const std::string str) {
	int count = 0;
    if (str[0] == ' ') {
        return -1;
    }
    else if (str.compare("/") == 0) {
		return -1;
    }

    for (int i = 0; i < str.size(); ++i) {
        if (isalpha(str[i])) {
            ++count;
        }
    }
    return count;
}

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
	int highlightindex = -1; // 강조할 단어 인덱스
    std::string newstring;
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
                for (int j = 0; j < words_copy[i].size(); ++j) {
                    if(words_copy[i][j][0] == ' '){
                        words_copy[i][j] = "/";
					}
                }
            }
        }
       
       // 문자 변환
       if (charchangemode) {
           for (int i = 0; i < count; ++i) {
               for (int j = 0; j < words[i].size(); ++j) {
                   for (int k = 0; k < words[i][j].size(); ++k) {
                       if (std::toupper(words_copy[i][j][k]) == std::toupper(oldchar)) {
						   
                           if (words_copy[i][j][k] <= 'z' && words_copy[i][j][k] >= 'a') {
                               words_copy[i][j][k] = std::tolower(newchar);
                           }
                           else {
                               words_copy[i][j][k] = std::toupper(newchar);
						   }
                       }
                   }
               }
           }
       }

       // 문장 순서 뒤집기
       if (wordordermode) {
           for (int i = 0; i < count; ++i) {
               std::reverse(words_copy[i].begin(), words_copy[i].end());
           }
       }

	   // 단어 뒤집기
       if (wordreversemode) {
           for (int i = 0; i < count; ++i) {
               for (int j = 0; j < words_copy[i].size(); ++j) {
                   std::reverse(words_copy[i][j].begin(), words_copy[i][j].end());
               }
           }
       }

       // 단어 정렬
       if (sortmode) {

           for (int i = 0; i < count; ++i) {
               if (sortmode == 1) {
                   std::sort(words_copy[i].begin(), words_copy[i].end(), [](const std::string& a, const std::string& b) {
                       return countalphbet(a) < countalphbet(b);
                       });
               }
               else if (sortmode == 2) {
                   std::sort(words_copy[i].begin(), words_copy[i].end(), [](const std::string& a, const std::string& b) {
                       return countalphbet(a) > countalphbet(b);
                       });
			   }
           }

       }

	   // 대문자 변환
       if (uppermode) {
           for (int i = 0; i < count; ++i) {
               for (int j = 0; j < words_copy[i].size(); ++j) {
                   for (int k = 0; k < words_copy[i][j].size(); ++k) {
					   char ch = std::toupper(words_copy[i][j][k]);
                       words_copy[i][j][k] = ch;
                   }
               }
           }
       }

        // 출력
		std::cout << "----------------------------------------" << std::endl;
			int captalcount = 0; // 대문자 개수 세기
        for (int i = 0; i < count; ++i) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // idle

            

			int wordcount = 0;
            for (int j = 0; j < words_copy[i].size(); ++j) {
				//std::cout << words[i][j];
				int savecolor = 15;
				int highlightcont = 0;
                if (highlightmode) {
					std::string newcopy = words_copy[i][j];
					// 대소문자 구분 없이 찾기
					std::transform(newcopy.begin(), newcopy.end(), newcopy.begin(), ::tolower);
					std::transform(newstring.begin(), newstring.end(), newstring.begin(), ::tolower);

					// 단어 뒤집혀도 찾기
                    if (wordreversemode) {
                        std::reverse(newstring.begin(), newstring.end());
                    }

					// 강조할 단어가 포함된 단어 찾기
                    if (newcopy.find(newstring) != std::string::npos) {
						highlightindex = newcopy.find(newstring);
                        highlightcont = 1;
                    }
                }
                
                if (words_copy[i][j][0] == ' ' || words_copy[i][j].compare("/") == 0 || words_copy[i][j].length() == 0) {

                    if (sortmode) {
                        continue;
                    }
                }
                else {
					++wordcount;
                }
                
                // 대문자로 시작하는 단어 나올 때
                if (!spacemode) {
                    if (words_copy[i][j][0] <= 'Z' && words_copy[i][j][0] >= 'A') {
                        captalcount++;
                        if (capitalmode) {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // red
                            savecolor = 12;
                        }
                    }
                    else if (words_copy[i][j][0] > '9' || words_copy[i][j][0] < '0') {
                        int cnt = 0;
                        int ch = false;
                        for (; cnt < words_copy[i][j].size(); ++cnt) {
                            if (words_copy[i][j][cnt] <= 'Z' && words_copy[i][j][cnt] >= 'A') {
                                ch = true;
                                break;
                            }
                            else if (words_copy[i][j][cnt] <= '9' && words_copy[i][j][cnt] >= '0') {
                                ch = false;
                                break;
                            }
                            else if (words_copy[i][j][cnt] <= 'z' && words_copy[i][j][cnt] >= 'a') {
                                ch = false;
                                break;
                            }
                            else {

                            }

                        }

                        if (words_copy[i][j][cnt] <= 'Z' && words_copy[i][j][cnt] >= 'A') {
                            captalcount++;
                            if (capitalmode) {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // red
                                savecolor = 12;
                            }
                        }
                    }
                }
                if (capitalmode && spacemode) {
                    int ccnt = 0;

					int cch = false;
                    for (; ccnt < words_copy[i].size(); ++ccnt) {
                        if (words_copy[i][ccnt][0] == ' ' || words_copy[i][ccnt].compare("/") == 0 || words_copy[i][ccnt].length() == 0) {
                            
                        }
                        else {
                            break;
						}

                    }
                    if (words_copy[i][ccnt][0] <= 'Z' && words_copy[i][ccnt][0] >= 'A') {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // red
                        savecolor = 12;
                    }
                    else if (words_copy[i][ccnt][0] > '9' || words_copy[i][ccnt][0] < '0') {
                        int cnt = 0;
                        int ch = false;
                        for (; cnt < words_copy[i][ccnt].size(); ++cnt) {
                            if (words_copy[i][ccnt][cnt] <= 'Z' && words_copy[i][ccnt][cnt] >= 'A') {
                                ch = true;
                                break;
                            }
                            else if (words_copy[i][ccnt][cnt] <= '9' && words_copy[i][ccnt][cnt] >= '0') {
                                ch = false;
                                break;
                            }
                            else if (words_copy[i][ccnt][cnt] <= 'z' && words_copy[i][ccnt][cnt] >= 'a') {
                                ch = false;
                                break;
                            }
                            else {

                            }

                        }

                        if (words_copy[i][0][cnt] <= 'Z' && words_copy[i][0][cnt] >= 'A') {
                            captalcount++;
                            if (capitalmode) {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // red
                                savecolor = 12;
                            }
                        }
                    }
                    else {
                        if (capitalmode) {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // red
                            savecolor = 15;
                        }
                    }

                }


                /*if (wordreversemode) {
                    if (words_copy[i][j][0] == ' ' || words_copy[i][j].compare("/") == 0 || words_copy[i][j].length() == 0) {

                    }
                    else {
						//char firstchar = words_copy[i][j][words_copy[i][j].length() - 1];
                        if (words_copy[i][j][words_copy[i][j].length() - 1] <= 'Z' && words_copy[i][j][words_copy[i][j].length() - 1] >= 'A') {
                            captalcount++;
                            if (capitalmode) {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // red
								savecolor = 12;
                            }
                        }
                    }
                }*/


                for (int k = 0; k < words_copy[i][j].size(); ++k) {
                    if (highlightmode && highlightcont) {
                        if (k >= highlightindex && k <= highlightindex + newstring.length() - 1) {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                        }
                    }
					
                    //if (uppermode) {
                        //char ch = std::toupper(words_copy[i][j][k]);
                        //std::cout << ch;
                    //}
                    //else {
                        std::cout << words_copy[i][j][k];
                    //}
                    if (linenummode && words_copy[i][j][k] <= '9' && words_copy[i][j][k] >= '0') {
						std::cout << std::endl;
                    }

                    if (highlightmode) {
                        
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), savecolor);
                        
                    }
                }

                highlightcont = 0;

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

                //::toupper(words[i][j][0]);
            }
                if (wordnummode && wordcount) {
                    if (spacemode) {
                        wordcount = 1;
                    }
					std::cout << "    ---------(" << wordcount << ")";
                }
			std::cout << std::endl;
        }
            // 대문자 개수 출력
            if (capitalmode) {
				std::cout << "대문자 개수: " << captalcount << std::endl;
            }

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
			++wordreversemode;
            wordreversemode %= 2;
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
                
                std::cout << "바꾸고 싶은 문자 입력: ";
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