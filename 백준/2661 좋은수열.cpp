#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> SEQ;
int len;


bool good(int size){

	bool duple;

	for (int i = 1; i <= (size + 1)/ 2; i++)  {
		duple = false;
		for (int j = 0; j < i; j++) {
			if (SEQ[size - j] != SEQ[size - i - j]) {
				duple = duple | true;
				break;
			}
		}

		if (!duple)
			return false;
	}
	
	return true;
}

void print() {
	for (int i = 0; i < SEQ.size(); i++)
		cout << SEQ[i];
}


void make_seq(int seq_len) {
	if (seq_len == len){
		print();
		exit(0);
	}
	
	for (int i = 1; i <= 3; i++) {
		if (SEQ.empty() || (!SEQ.empty() && SEQ.back() != i)) {
			SEQ.push_back(i);

			if (good(SEQ.size() - 1))
				make_seq(seq_len + 1);
			SEQ.pop_back();
		}
	}
}

int main()
{
	cin >> len;
	make_seq(0);
}