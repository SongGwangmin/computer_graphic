#include <iostream>
#include <string>
struct Point {
    int x;
    int y;
    int z;
    int index;
    bool active;
};

void printPoint(const Point& p) {
    std::cout << p.index << ": ";
    if (p.active) {
		std::cout << p.x << ' ' << p.y << ' ' << p.z;
    }
}

int main() {
    // 구조체 배열 10개 생성 및 초기화
    Point points[10] = {
    };

	int i = 0;

    for (Point& p : points) {
		p.x = 0;
		p.y = 0;
		p.z = 0;
        p.index = i;
		p.active = false;
		i++;
    }

    while (true) {
        // 확인 출력
        for (int i = 0; i < 10; i++) {
            
            printPoint(points[9 - i]);
            std::cout << std::endl;
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

		std::cin >> command;
		std::cin.ignore();

        switch (command[0]) {
            case '+':
            {
                if (command.size() < 5) {
                    std::cout << "잘못된 명령어입니다." << std::endl;
                    break;
                }
                int x = std::stoi(command.substr(2, command.find(' ', 2) - 2));
                int y = std::stoi(command.substr(command.find(' ', 2) + 1, command.find(' ', command.find(' ', 2) + 1) - command.find(' ', 2) - 1));
                int z = std::stoi(command.substr(command.find(' ', command.find(' ', 2) + 1) + 1));
                // 맨 위에 추가
                for (int i = 9; i > 0; --i) {
                    points[i] = points[i - 1];
                }
                points[0].x = x;
                points[0].y = y;
                points[0].z = z;
                points[0].active = true;
			}
            break;
            case '-':
            {
                // 맨 위에서 삭제
                for (int i = 0; i < 9; ++i) {
                    points[i] = points[i + 1];
                }
                points[9].x = 0;
                points[9].y = 0;
                points[9].z = 0;
                points[9].active = false;
            }
            break;
            case 'e':
            {
                if (command.size() < 5) {
                    std::cout << "잘못된 명령어입니다." << std::endl;
                    break;
                }
                int x = std::stoi(command.substr(2, command.find(' ', 2) - 2));
                int y = std::stoi(command.substr(command.find(' ', 2) + 1, command.find(' ', command.find(' ', 2) + 1) - command.find(' ', 2) - 1));
                int z = std::stoi(command.substr(command.find(' ', command.find(' ', 2) + 1) + 1));
                // 맨 아래에 추가
                points[9].x = x;
                points[9].y = y;
                points[9].z = z;
                points[9].active = true;
			}
            break;
            case 'd':
            {
                // 맨 아래에서 삭제 (칸이 비게 됨)
                points[9].x = 0;
                points[9].y = 0;
                points[9].z = 0;
                points[9].active = false;
			}
            break;
            case 'a':
            {
                // 저장된 점의 개수 출력
                int count = 0;
                for (const Point& p : points) {
                    if (p.active) {
                        count++;
                    }
                }
                std::cout << "저장된 점의 개수: " << count << std::endl;
            }
            break;
            case 'b':
            {
                // 모든 점의 위치를 한 칸씩 감소 (0→9, 1→0, 2→1, ... 9→8)
                Point first = points[0];
                for (int i = 0; i < 9; ++i) {
                    points[i] = points[i + 1];
                }
                points[9] = first;
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
