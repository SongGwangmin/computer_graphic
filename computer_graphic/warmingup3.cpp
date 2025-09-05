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
    // ����ü �迭 10�� ���� �� �ʱ�ȭ
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
        // Ȯ�� ���

		int pcount = 0;

        for (int i = 0; i < 10; i++) {
            
            printPoint(points[9 - i]);
            std::cout << std::endl;

            if (points[i].active == true) {
				++pcount;
            }
        }
        if (atoggle) {
            std::cout << "���� ���� ����: " << pcount << std::endl;
        }
        // command
        std::cout << "===== ��ɾ� ��� =====" << std::endl;
        std::cout << "+ x y z : ����Ʈ�� �� ���� �� (x, y, z) �߰�" << std::endl;
        std::cout << "-       : ����Ʈ�� �� ������ �� ����" << std::endl;
        std::cout << "e x y z : ����Ʈ�� �� �Ʒ��� �� (x, y, z) �߰�" << std::endl;
        std::cout << "d       : ����Ʈ�� �� �Ʒ����� �� ���� (ĭ�� ��� ��)" << std::endl;
        std::cout << "a       : ����Ʈ�� ����� ���� ���� ���" << std::endl;
        std::cout << "b       : ��� ���� ��ġ�� �� ĭ�� ���� (0��9, 1��0, 2��1, ... 9��8)" << std::endl;
        std::cout << "c       : ����Ʈ�� ��� (��� �� �ٽ� �Է��ϸ� 0������ ����)" << std::endl;
        std::cout << "f       : �������� �Ÿ� ���� ���� (��������)" << std::endl;
        std::cout << "q       : ���α׷� ����" << std::endl;
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
					std::cout << "argumnent�� �����մϴ�." << std::endl;
					break;
                }
				
                int x, y, z;
                
                try {
					x = std::stoi(tokens[1]);
                }
				catch (const std::invalid_argument&) {
                    std::cout << "�߸��� ��ɾ��Դϴ�." << std::endl;
                    break;
				}

                try {
				    y = std::stoi(tokens[2]);

                }
                catch (const std::invalid_argument&) {
                    std::cout << "�߸��� ��ɾ��Դϴ�." << std::endl;
                    break;
				}

                try {
                    z = std::stoi(tokens[3]);

                }
                catch (const std::invalid_argument&) {
                    std::cout << "�߸��� ��ɾ��Դϴ�." << std::endl;
                    break;
                }

                // �� ���� �߰�
				int result = downinsert(points, x, y, z);
                if (result == -1) {
					result = upinsert(points, x, y, z);
                    if (result == -1) {
                        std::cout << "�� �̻� �߰��� �� �����ϴ�." << std::endl;
                    }
                }
			}
            break;
            case '-':
            {
                int result = delpointdown(points, 0, 0, 0);
                if (result == -1) {
                    std::cout << "������ ���� �����ϴ�." << std::endl;
                }
            }
            break;
            case 'e':
            {
                if (tokens.size() < 4) {
                    std::cout << "argumnent�� �����մϴ�." << std::endl;
                    break;
                }

                int x, y, z;

                try {
                    x = std::stoi(tokens[1]);
                }
                catch (const std::invalid_argument&) {
                    std::cout << "�߸��� ��ɾ��Դϴ�." << std::endl;
                    break;
                }

                try {
                    y = std::stoi(tokens[2]);

                }
                catch (const std::invalid_argument&) {
                    std::cout << "�߸��� ��ɾ��Դϴ�." << std::endl;
                    break;
                }

                try {
                    z = std::stoi(tokens[3]);

                }
                catch (const std::invalid_argument&) {
                    std::cout << "�߸��� ��ɾ��Դϴ�." << std::endl;
                    break;
                }
                
                int result = upinsert(points, x, y, z);
                if (result == -1) {
                    std::cout << "�� �̻� �߰��� �� �����ϴ�." << std::endl;
                }
			}
            break;
            case 'd':
            {
                int result = delpoint(points, 0, 0, 0);
                if (result == -1) {
                    std::cout << "������ ���� �����ϴ�." << std::endl;
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
                // ����Ʈ�� ��� (��� �� �ٽ� �Է��ϸ� 0������ ����)
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
                // �������� �Ÿ� ���� ���� (��������)
                std::sort(points, points + 10, [](const Point& a, const Point& b) {
                    if (!a.active && b.active) return false;
                    if (a.active && !b.active) return true;
                    if (!a.active && !b.active) return false; // �� �� ��Ȱ��ȭ�� ��� ���� ����
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
