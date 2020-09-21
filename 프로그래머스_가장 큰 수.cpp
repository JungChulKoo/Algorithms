#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

bool cmp(string a, string b) {
	return a + b > b + a;
}

string solution(vector<int> numbers) {
	int i;
	string temp;
	string answer = "";
	vector<string> numbers_in_str;

	for (i = 0; i < numbers.size(); i++)
		numbers_in_str.push_back(to_string(numbers[i]));
	if(numbers_in_str.size() > 1)
		sort(numbers_in_str.begin(), numbers_in_str.end(), cmp);

	for (i = 0; i < numbers_in_str.size(); i++) {
		if (numbers_in_str[i] != "0")
			break;
	}

	if (i == numbers_in_str.size())
		answer += '0';
	else {
		for (i = 0; i < numbers_in_str.size(); i++)
			answer += numbers_in_str[i];
	}

	return answer;
}
