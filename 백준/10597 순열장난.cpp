#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>

#define MAX_SEQ_LEN 50
#define MAX_STR_LEN 91

using namespace std;

int STR_LEN, SEQ_LEN;

string str;
vector<int> num;
bool check[MAX_SEQ_LEN + 1];

int count(int len)
{
	if (len <= 9)
		return len;
	else
		return (len + 9) / 2;
}


void input() {
	cin >> str;
	STR_LEN = str.size();
	SEQ_LEN = count(str.size());
}

void dfs(int str_index) {

	if (str_index >= STR_LEN) {
		for (int i = 0; i < SEQ_LEN; i++)
			cout << num[i] << " ";

		exit(0);
	}

	string s = "";
	int toi = 0;
	
	for (int i = str_index; i <= str_index + 1; i++) {
		s += str[i];
		toi = stoi(s);

		
		if (toi > SEQ_LEN)
			continue;
		if (check[stoi(s)])
			continue;

		num.push_back(toi);
		check[toi] = true;

		dfs(i + 1);

		check[toi] = false;
		num.pop_back();
	}
}

int main()
{
	input();
	dfs(0);
}