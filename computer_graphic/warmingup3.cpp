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
    // ����ü �迭 10�� ���� �� �ʱ�ȭ
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
        // Ȯ�� ���
        for (int i = 0; i < 10; i++) {
            
            printPoint(points[9 - i]);
            std::cout << std::endl;
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

		std::cin >> command;
		std::cin.ignore();

        switch (command[0]) {
            case '+':
            {
                if (command.size() < 5) {
                    std::cout << "�߸��� ��ɾ��Դϴ�." << std::endl;
                    break;
                }
                int x = std::stoi(command.substr(2, command.find(' ', 2) - 2));
                int y = std::stoi(command.substr(command.find(' ', 2) + 1, command.find(' ', command.find(' ', 2) + 1) - command.find(' ', 2) - 1));
                int z = std::stoi(command.substr(command.find(' ', command.find(' ', 2) + 1) + 1));
                // �� ���� �߰�
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
                // �� ������ ����
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
                    std::cout << "�߸��� ��ɾ��Դϴ�." << std::endl;
                    break;
                }
                int x = std::stoi(command.substr(2, command.find(' ', 2) - 2));
                int y = std::stoi(command.substr(command.find(' ', 2) + 1, command.find(' ', command.find(' ', 2) + 1) - command.find(' ', 2) - 1));
                int z = std::stoi(command.substr(command.find(' ', command.find(' ', 2) + 1) + 1));
                // �� �Ʒ��� �߰�
                points[9].x = x;
                points[9].y = y;
                points[9].z = z;
                points[9].active = true;
			}
            break;
            case 'd':
            {
                // �� �Ʒ����� ���� (ĭ�� ��� ��)
                points[9].x = 0;
                points[9].y = 0;
                points[9].z = 0;
                points[9].active = false;
			}
            break;
            case 'a':
            {
                // ����� ���� ���� ���
                int count = 0;
                for (const Point& p : points) {
                    if (p.active) {
                        count++;
                    }
                }
                std::cout << "����� ���� ����: " << count << std::endl;
            }
            break;
            case 'b':
            {
                // ��� ���� ��ġ�� �� ĭ�� ���� (0��9, 1��0, 2��1, ... 9��8)
                Point first = points[0];
                for (int i = 0; i < 9; ++i) {
                    points[i] = points[i + 1];
                }
                points[9] = first;
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
