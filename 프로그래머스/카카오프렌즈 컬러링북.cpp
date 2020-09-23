#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int index_point(pair<int, int> p, vector<pair<int, int>>& v) {
	int i = 0;

	while (i < v.size() && v[i] != p)
		i++;

	return i;
}

bool range_check(int x, int y, vector<vector<long long>>& v) {
	if (x >= 0 && x < v.size() &&
		y >= 0 && y < v[0].size())
		return true;
	else
		return false;
}

void dfs(int s_index, int x, int y, bool diff, vector<vector<long long>>& pic, vector<int>& cnt, queue<pair<int, int>>& q) {
	if (diff) {
		q.push(make_pair(x, y));
		return;
	}

	if (pic[x][y] != -1) {
		long long col = pic[x][y];
		int pl[4][2] = { { -1, 0 }, {0, -1}, {1, 0}, {0, 1} };

		pic[x][y] = -1;
		cnt[s_index]++;

		for (int i = 0; i <= 3; i++) {
			if (range_check(x + pl[i][0], y + pl[i][1], pic)) {
				if (pic[x + pl[i][0]][y + pl[i][1]] == col)
					dfs(s_index, x + pl[i][0], y + pl[i][1], false, pic, cnt, q);
				else
					dfs(s_index, x + pl[i][0], y + pl[i][1], true, pic, cnt, q);
			}
		}
	}
}


vector<int> solution(int m, int n, vector<vector<int>> picture) {
	int i, j;
	int number_of_area = 0, max_size_of_one_area = 0;
	pair<int, int> p;
	vector<int> answer(2), cnt(10201);
	vector<pair<int, int>> sp;
	queue<pair<int, int>> q;

	vector<vector<long long>> pic(picture.size(), vector<long long>(picture[0].size(), 0));

	for (i = 0; i < picture.size(); i++) {
		for (j = 0; j < picture[i].size(); j++)
			pic[i][j] = picture[i][j];
	}

	q.push(make_pair(0, 0));
	sp.push_back(make_pair(0, 0));

	dfs(0, 0, 0, false, pic, cnt, q);

	while (!q.empty()) {
		p = q.front();
		q.pop();

		if (pic[p.first][p.second] != -1) {
			if (index_point(p, sp) == sp.size())
				sp.push_back(p);

			dfs(index_point(p, sp), p.first, p.second, false, pic, cnt, q);
		}
	}

	i = distance(cnt.begin(), max_element(cnt.begin(), cnt.end()));
	
	if (picture[sp[i].first][sp[i].second] == 0)
		cnt[i] = 0;

	for (i = 0; i < sp.size(); i++) {
		if (picture[sp[i].first][sp[i].second] != 0)
			number_of_area++;
	}

	max_size_of_one_area = *(max_element(cnt.begin(), cnt.end()));
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
	return answer;
}
