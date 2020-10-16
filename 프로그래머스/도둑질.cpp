#include <string>
#include <vector>
#include <algorithm>

int * sum[2];
using namespace std;

int solution(vector<int> money) {

	sum[0] = new int[money.size()], sum[1] = new int[money.size()];
	sum[0][0] = money[0], sum[0][1] = money[0];
	sum[1][0] = 0, sum[1][1] = money[1];

	for (int i = 0; i < 2; i++) {
		for (int j = 2; j < money.size(); j++)
			sum[i][j] = max(sum[i][j - 2] + money[j], sum[i][j - 1]);
	}

	return max(sum[0][money.size() - 2], sum[1][money.size() - 1]);
}