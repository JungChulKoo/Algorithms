#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	int day, count, job;
	vector<int> answer;
	queue<pair<int, int>> Q;

	for (int i = 0; i < progresses.size(); i++)
		Q.push(make_pair(progresses[i], speeds[i]));

	day = 0;

	while (!Q.empty()) {
		count = 0;
		job = Q.front().first + day * Q.front().second;

		while (job < 100) {
			job += Q.front().second;
			day++;
		}
        
        cout << day << endl;
		while (!Q.empty() && Q.front().first + day * Q.front().second >= 100) {
			Q.pop();
			count++;
		}
		
		if(count > 0)
			answer.push_back(count);
	}

	return answer;
}
