#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
	bool loaded = false;
	int answer = 0, sum_of_weight = 0;
	queue<int> waiting;
	queue<pair<int, int>> in_bridge;

	for (int i = 0; i < truck_weights.size(); i++)
		waiting.push(truck_weights[i]);

	while (!(waiting.empty() && in_bridge.empty())) {
		loaded = false;

		if (!in_bridge.empty()) {
			if (answer - in_bridge.front().second >= bridge_length) {
				sum_of_weight -= in_bridge.front().first;
				in_bridge.pop();
			}
		}

		if (!waiting.empty()) {
			if (sum_of_weight + waiting.front() <= weight) {
				in_bridge.push(make_pair(waiting.front(), answer));
				waiting.pop();
				loaded = true;
			}
		}

		answer++;
		if (loaded)
			sum_of_weight += in_bridge.back().first;
	}

	return answer;
}
