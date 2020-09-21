#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
bool searched = true;
int answer = 51;
vector<int> visited;
void dfs(string begin, string target, vector<string> words, int changed) {
	if (begin == target) {
		if (changed < answer)
			answer = changed;
		return;
	}

	else
		searched = false;


	int i, j, difference;

	for (j = 0; j < words.size(); j++) {
		difference = 0;
		for (i = 0; i < begin.length(); i++) {
			if (begin[i] != words[j][i])
				difference++;
		}

		if (difference == 1) {
			if (!visited[j]) {
				visited[j] = true;
				dfs(words[j], target, words, changed + 1);
				visited[j] = false;
			}
		}
	}
}

int solution(string begin, string target, vector<string> words) {
	visited.assign(words.size(), false);
	dfs(begin, target, words, 0);
	
	if (answer < 51)
		return answer;
	else
		return 0;
}
