#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

struct Point {
    int x;
    int y;
    int z;
    int index;
    bool active;
};

int delpoint(Point* list, int x, int y, int z) {
	int index = 0;

    while (index < 10) {
        if (list[index].active == true) {
            break;
        }
        index++;
    }

    if (index == 10) {
        return -1;
    }
    else {
		list[index].active = false;
    }
}

int delpointdown(Point* list, int x, int y, int z) {
    int index = 9;

    while (index > -1) {
        if (list[index].active == true) {
            break;
        }
        index--;
    }

    if (index == -1) {
        return -1;
    }
    else {
        list[index].active = false;
    }
}

void printPoint(const Point& p) {
    std::cout << p.index << ": ";
    if (p.active) {
		std::cout << p.x << ' ' << p.y << ' ' << p.z;
    }
}

int downinsert(Point* list, int x, int y, int z) {
    int index = 9;

    while (index > -1) {
        if (list[index].active == true) {
            break;
        }
		index--;
    }

    if (index == 9) {
		return -1;
    }
    
    else {
		list[index + 1].x = x;
		list[index + 1].y = y;
		list[index + 1].z = z;
		list[index + 1].active = true;

        return index + 1;
    }

}

int upinsert(Point* list, int x, int y, int z) {
    int index = 0;
    while (index < 10) {
        if (list[index].active == false) {
            break;
        }
        index++;
    }

    if (index == 10) {
        return -1;
    }
    else {
        for (int i = 0; i < index; ++i) {
			list[index - i].x = list[index - i - 1].x;
			list[index - i].y = list[index - i - 1].y;
            list[index - i].z = list[index - i - 1].z;
			list[index - i].active = true;

        }
		list[0].x = x;
		list[0].y = y;
		list[0].z = z;
        list[0].active = true;
		return index;
    }
}

int main() {
    // 구조체 배열 10개 생성 및 초기화
    Point points[10] = {
    };

	int atoggle = 0;

	int i = 0;

    for (Point& p : points) {
		p.x = 0;
		p.y = 0;
		p.z = 0;
        p.index = i;
		p.active = true;
		i++;
    }

    while (true) {
        // 확인 출력

		int pcount = 0;

        for (int i = 0; i < 10; i++) {
            
            printPoint(points[9 - i]);
            std::cout << std::endl;

            if (points[i].active == true) {
				++pcount;
            }
        }
        if (atoggle) {
            std::cout << "현재 점의 개수: " << pcount << std::endl;
        }
        // command
        std::cout << "===== 명령어 목록 =====" << std::endl;
        std::cout << "+ x y z : 리스트의 맨 위에 점 (x, y, z) 추가" << std::endl;
        std::cout << "-       : 리스트의 맨 위에서 점 삭제" << std::endl;
        std::cout << "e x y z : 리스트의 맨 아래에 점 (x, y, z) 추가" << std::endl;
        std::cout << "d       : 리스트의 맨 아래에서 점 삭제 (칸이 비게 됨)" << std::endl;
        std::cout << "a       : 리스트에 저장된 점의 개수 출력" << std::endl;
        std::cout << "b       : 모든 점의 위치를 한 칸씩 감소 (0→9, 1→0, 2→1, ... 9→8)" << std::endl;
        std::cout << "c       : 리스트를 비움 (비운 후 다시 입력하면 0번부터 저장)" << std::endl;
        std::cout << "f       : 원점과의 거리 기준 정렬 (오름차순)" << std::endl;
        std::cout << "q       : 프로그램 종료" << std::endl;
        std::cout << "========================" << std::endl;

        

		std::string command{};
        std::string argument[3];

		std::getline(std::cin, command);

		std::istringstream iss(command);
		std::vector<std::string> tokens;
		std::string token;

        while (iss >> token) {
            tokens.push_back(token);
        }
        
       /* for (auto& i : tokens) {
			std::cout << i << std::endl;
        }*/
        

        switch (tokens[0][0]) {
            case '+':
            {
                if (tokens.size() < 4) {
					std::cout << "argumnent가 부족합니다." << std::endl;
					break;
                }
				
                int x, y, z;
                
                try {
					x = std::stoi(tokens[1]);
                }
				catch (const std::invalid_argument&) {
                    std::cout << "잘못된 명령어입니다." << std::endl;
                    break;
				}

                try {
				    y = std::stoi(tokens[2]);

                }
                catch (const std::invalid_argument&) {
                    std::cout << "잘못된 명령어입니다." << std::endl;
                    break;
				}

                try {
                    z = std::stoi(tokens[3]);

                }
                catch (const std::invalid_argument&) {
                    std::cout << "잘못된 명령어입니다." << std::endl;
                    break;
                }

                // 맨 위에 추가
				int result = downinsert(points, x, y, z);
                if (result == -1) {
					result = upinsert(points, x, y, z);
                    if (result == -1) {
                        std::cout << "더 이상 추가할 수 없습니다." << std::endl;
                    }
                }
			}
            break;
            case '-':
            {
                int result = delpointdown(points, 0, 0, 0);
                if (result == -1) {
                    std::cout << "삭제할 점이 없습니다." << std::endl;
                }
            }
            break;
            case 'e':
            {
                if (tokens.size() < 4) {
                    std::cout << "argumnent가 부족합니다." << std::endl;
                    break;
                }

                int x, y, z;

                try {
                    x = std::stoi(tokens[1]);
                }
                catch (const std::invalid_argument&) {
                    std::cout << "잘못된 명령어입니다." << std::endl;
                    break;
                }

                try {
                    y = std::stoi(tokens[2]);

                }
                catch (const std::invalid_argument&) {
                    std::cout << "잘못된 명령어입니다." << std::endl;
                    break;
                }

                try {
                    z = std::stoi(tokens[3]);

                }
                catch (const std::invalid_argument&) {
                    std::cout << "잘못된 명령어입니다." << std::endl;
                    break;
                }
                
                int result = upinsert(points, x, y, z);
                if (result == -1) {
                    std::cout << "더 이상 추가할 수 없습니다." << std::endl;
                }
			}
            break;
            case 'd':
            {
                int result = delpoint(points, 0, 0, 0);
                if (result == -1) {
                    std::cout << "삭제할 점이 없습니다." << std::endl;
                }
			}
            break;
            case 'a':
            {
                ++atoggle;
				atoggle %= 2;

            }
            break;
            case 'b':
            {
				Point temp[10];

                for (int i = 0; i < 10; ++i) {
					temp[i] = points[i];
                }


                for (int i = 0; i < 10; ++i) {
					points[i].x = temp[(i + 1) % 10].x;
                    points[i].y = temp[(i + 1) % 10].y;
					points[i].z = temp[(i + 1) % 10].z;
					points[i].active = temp[(i + 1) % 10].active;

                }
				
            }
			break;
            case 'c':
            {
                // 리스트를 비움 (비운 후 다시 입력하면 0번부터 저장)
                for (Point& p : points) {
                    p.x = 0;
                    p.y = 0;
                    p.z = 0;
                    p.active = false;
                }
			}
            break;
            case 'f':
            {
                // 원점과의 거리 기준 정렬 (오름차순)
                std::sort(points, points + 10, [](const Point& a, const Point& b) {
                    if (!a.active && b.active) return false;
                    if (a.active && !b.active) return true;
                    if (!a.active && !b.active) return false; // 둘 다 비활성화된 경우 순서 유지
                    int distA = a.x * a.x + a.y * a.y + a.z * a.z;
                    int distB = b.x * b.x + b.y * b.y + b.z * b.z;
                    return distA < distB;
                    });
            }
            break;
            case 'q':
            {
                return 0;
            }
            break;
            default:
            {
             
            }
            break;
        }
    }

    return 0;
}
