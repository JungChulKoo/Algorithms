#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> check;
bool finished = false; 

void dfs(vector<vector<string>> tickets, string s_point, vector<string>& answer) {
	
	if (answer.size() == tickets.size() + 1) {
		finished = true;
		return;
	}
	
	int i = 0;
	vector<int> candidates;

	while (i < tickets.size()) {
		if (tickets[i][0] == s_point && !check[i])
			candidates.push_back(i);
		i++;
	}

	for (i = 0; i < candidates.size(); i++) {
		check[candidates[i]] = true;
		answer.push_back(tickets[candidates[i]][1]);

		dfs(tickets, tickets[candidates[i]][1], answer);
		if(finished)
            return;
		answer.pop_back();
		check[candidates[i]] = false;
	}
}

vector<string> solution(vector<vector<string>> tickets) {
	vector<string> answer;
	sort(tickets.begin(), tickets.end());
	check.assign(tickets.size(), false);

	answer.push_back("ICN");
	dfs(tickets, "ICN", answer);
	
	return answer;
}
