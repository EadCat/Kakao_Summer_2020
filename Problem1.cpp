#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

#define LEFTHAND 1
#define RIGHTHAND 2
#define X 3
#define Y 4

int classifier(int order, int axis) {
    if (axis == X) {
        if (order == 1) {
            return 0;
        }
        else if (order == 2) {
            return 1;
        }
        else if (order == 3) {
            return 2;
        }
        else if (order == 4) {
            return 0;
        }
        else if (order == 5) {
            return 1;
        }
        else if (order == 6) {
            return 2;
        }
        else if (order == 7) {
            return 0;
        }
        else if (order == 8) {
            return 1;
        }
        else if (order == 9) {
            return 2;
        }
        else if (order == 0) {
            return 1;
        }
    }
    else { // Y
        if (order == 1) {
            return 0;
        }
        else if (order == 2) {
            return 0;
        }
        else if (order == 3) {
            return 0;
        }
        else if (order == 4) {
            return 1;
        }
        else if (order == 5) {
            return 1;
        }
        else if (order == 6) {
            return 1;
        }
        else if (order == 7) {
            return 2;
        }
        else if (order == 8) {
            return 2;
        }
        else if (order == 9) {
            return 2;
        }
        else if (order == 0) {
            return 3;
        }
    }
}

int dist(int order, int x, int y) {
    int pos_x, pos_y;
    int result = 0;
    if (order == 1) {
        pos_y = 0; pos_x = 0;
    }
    else if (order == 2) {
        pos_y = 0; pos_x = 1;
    }
    else if (order == 3) {
        pos_y = 0; pos_x = 2;
    }
    else if (order == 4) {
        pos_y = 1; pos_x = 0;
    }
    else if (order == 5) {
        pos_y = 1; pos_x = 1;
    }
    else if (order == 6) {
        pos_y = 1; pos_x = 2;
    }
    else if (order == 7) {
        pos_y = 2; pos_x = 0;
    }
    else if (order == 8) {
        pos_y = 2; pos_x = 1;
    }
    else if (order == 9) {
        pos_y = 2; pos_x = 2;
    }
    else if (order == 0) {
        pos_y = 3; pos_x = 1;
    }

    result += (abs(x - pos_x) + abs(y - pos_y));
    return result;
}

string solution(vector<int> numbers, string hand) {
    string answer = "";
    int mode = 0;

    if (hand == "left")
        mode = LEFTHAND;
    else
        mode = RIGHTHAND;

    int left_x = 0, left_y = 3;
    int right_x = 2, right_y = 3;

    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] == 1 || numbers[i] == 4 || numbers[i] == 7) {
            left_x = classifier(numbers[i], X);
            left_y = classifier(numbers[i], Y);
            answer += 'L';
        }
        else if (numbers[i] == 3 || numbers[i] == 6 || numbers[i] == 9) {
            right_x = classifier(numbers[i], X);
            right_y = classifier(numbers[i], Y);
            answer += 'R';
        }
        else {
            if (dist(numbers[i], left_x, left_y) > dist(numbers[i], right_x, right_y)) { // right
                // left > right
                right_x = classifier(numbers[i], X);
                right_y = classifier(numbers[i], Y);
                answer += 'R';
            }
            else if (dist(numbers[i], left_x, left_y) == dist(numbers[i], right_x, right_y)) {
                if (mode == LEFTHAND) {
                    left_x = classifier(numbers[i], X);
                    left_y = classifier(numbers[i], Y);
                    answer += 'L';
                }
                else {
                    right_x = classifier(numbers[i], X);
                    right_y = classifier(numbers[i], Y);
                    answer += 'R';
                }
            }
            else { // left
                // left < right
                left_x = classifier(numbers[i], X);
                left_y = classifier(numbers[i], Y);
                answer += 'L';
            }
            
        }
    }

    return answer;
}