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
	int highlightindex = -1; // ������ �ܾ� �ε���
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
                for (int j = 0; j < words_copy[i].size(); ++j) {
                    if(words_copy[i][j][0] == ' '){
                        words_copy[i][j] = "/";
					}
                }
            }
        }
       
       // ���� ��ȯ
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

       // ���� ���� ������
       if (wordordermode) {
           for (int i = 0; i < count; ++i) {
               std::reverse(words_copy[i].begin(), words_copy[i].end());
           }
       }

	   // �ܾ� ������
       if (wordreversemode) {
           for (int i = 0; i < count; ++i) {
               for (int j = 0; j < words_copy[i].size(); ++j) {
                   std::reverse(words_copy[i][j].begin(), words_copy[i][j].end());
               }
           }
       }

       // �ܾ� ����
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

	   // �빮�� ��ȯ
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

        // ���
		std::cout << "----------------------------------------" << std::endl;
			int captalcount = 0; // �빮�� ���� ����
        for (int i = 0; i < count; ++i) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // idle

            

			int wordcount = 0;
            for (int j = 0; j < words_copy[i].size(); ++j) {
				//std::cout << words[i][j];
				int savecolor = 15;
				int highlightcont = 0;
                if (highlightmode) {
					std::string newcopy = words_copy[i][j];
					// ��ҹ��� ���� ���� ã��
					std::transform(newcopy.begin(), newcopy.end(), newcopy.begin(), ::tolower);
					std::transform(newstring.begin(), newstring.end(), newstring.begin(), ::tolower);

					// �ܾ� �������� ã��
                    if (wordreversemode) {
                        std::reverse(newstring.begin(), newstring.end());
                    }

					// ������ �ܾ ���Ե� �ܾ� ã��
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
                
                // �빮�ڷ� �����ϴ� �ܾ� ���� ��
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
            // �빮�� ���� ���
            if (capitalmode) {
				std::cout << "�빮�� ����: " << captalcount << std::endl;
            }

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
			++wordreversemode;
            wordreversemode %= 2;
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
                
                std::cout << "�ٲٰ� ���� ���� �Է�: ";
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