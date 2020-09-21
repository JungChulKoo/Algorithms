#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> sequence;
vector<string> candidates;


bool is_prime(int n) {
	if (n < 2)
		return false;
	else if
		(n <= 3)
		return true;

	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0)
			return false;
	}

	return true;
}

void make_number(string numbers, int start, int end) {
	if (start > end) 
		return;

	int i = 0;
	int toi;

	for (i = start; i <= end; i++) {
		swap(numbers[start], numbers[i]);
		toi = stoi(numbers);

		if (is_prime(toi))
			sequence.push_back(toi);

		make_number(numbers, start + 1, end);
		swap(numbers[start], numbers[i]);
	}
}


void select_number(string numbers, string zero_or_one, int idx) {
	if (zero_or_one.size() >= numbers.size()) {
		string s = "";

		for (int i = 0; i < zero_or_one.size(); i++) {
			if (zero_or_one[i] == '1') {
				s += numbers[i];
			}
		}

		if (s != "")
			candidates.push_back(s);

		return;
	}

	for (int i = 0; i <= 1; i++) {
		zero_or_one += i + '0';
		select_number(numbers, zero_or_one, idx + 1);
		zero_or_one.erase(zero_or_one.size() - 1);
	}
}

int solution(string numbers) {
	int i, j;
	int count = 0;

	for (i = 0; i <= numbers.size(); i++)
		select_number(numbers, "", 0);

	for (i = 0; i < candidates.size(); i++)
		make_number(candidates[i], 0, candidates[i].size() - 1);

	sort(sequence.begin(), sequence.end());
	count = sequence.size();

	if (sequence.size() >= 1) {
		for (i = 0; i < sequence.size() - 1; i++) {
			if (sequence[i] == sequence[i + 1])
				count--;
		}
	}

	return count;
}
