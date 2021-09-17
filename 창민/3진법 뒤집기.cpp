#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(int n) {
    int answer = 0;
    vector<int> three;
    int square = 0;

    while (n != 0) {
        three.push_back(n % 3);
        n /= 3;
    }
    for (int i = three.size() - 1; i >= 0; i--) {
        answer += three[i] * pow(3, square++);
    }

    return answer;
}