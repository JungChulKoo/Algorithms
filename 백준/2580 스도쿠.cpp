#include <iostream>
#include <algorithm>
#include <vector>
#define BOARD_LENGTH 9
#define SQUARE_LENGTH 3

using namespace std;

int board[BOARD_LENGTH][BOARD_LENGTH];

vector<pair<int, int>> empty_location;
void place_number(int x, int y, int value) {
	board[x][y] = value;
}

void remove_number(int x, int y) {
	board[x][y] = 0;
}

int is_possible(int x, int y, int value) {
	
	int i, j;

	for (i = 0; i < BOARD_LENGTH; i++) {
		if (board[x][i] == value)
			return false;
		if (board[i][y] == value)
			return false;
	}


	for (i = (x / SQUARE_LENGTH) * SQUARE_LENGTH; i < (x / SQUARE_LENGTH) * SQUARE_LENGTH + 3; i++) {
		for (j = (y / SQUARE_LENGTH) * SQUARE_LENGTH; j < (y / SQUARE_LENGTH) * SQUARE_LENGTH + 3; j++) {
			if (board[i][j] == value)
				return false;
		}
	}

	return true;
}

void print()
{
	for (int i = 0; i < BOARD_LENGTH; i++) {
		for (int j = 0; j < BOARD_LENGTH; j++) {
			cout << board[i][j];
			if (j < BOARD_LENGTH)
				cout << " ";
		}
		cout << endl;
	}
}


void dfs(int seq_num) {

	if (seq_num >= empty_location.size()) {
		print();
		exit(0);
	}

	for (int i = 1; i <= BOARD_LENGTH; i++) {

		if (is_possible(empty_location[seq_num].first, empty_location[seq_num].second, i)) {
			place_number(empty_location[seq_num].first, empty_location[seq_num].second, i);
			dfs(seq_num + 1);
			remove_number(empty_location[seq_num].first, empty_location[seq_num].second);
		}

		else
			continue;
	}

}




int main()
{
	int i, j;
	
	for (i = 0; i < BOARD_LENGTH; i++) {
		for (j = 0; j < BOARD_LENGTH; j++)
			cin >> board[i][j];
	}

	for (i = 0; i < BOARD_LENGTH; i++) {
		for (j = 0; j < BOARD_LENGTH; j++) {
			if (board[i][j] == 0)
				empty_location.push_back(make_pair(i, j));
		}
	}

	sort(empty_location.begin(), empty_location.end());
	dfs(0);
}