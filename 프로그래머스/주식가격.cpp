#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> tracker;

vector<int> solution(vector<int> prices) {
	int time;
	vector<int> answer(prices.size());
	vector<int> stack;

	for (time = 0; time < prices.size(); time++) {
		while (!stack.empty() && prices[time] < prices[stack.back()]) {
			answer[stack.back()] = time - stack.back();
			stack.pop_back();
		}

		stack.push_back(time);
	}

	while (!stack.empty()) {
		answer[stack.back()] = time - stack.back() - 1;
		stack.pop_back();
	}

	return answer;
}
