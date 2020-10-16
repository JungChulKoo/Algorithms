#include <string>
#include <vector>

#define MAX_LENGTH 100
#define IN_WATER -1

using namespace std;

long long way[MAX_LENGTH + 1][MAX_LENGTH + 1];

int solution(int m, int n, vector<vector<int>> puddles) {
	int i, j;
	long long answer = 0;

	for (i = 0; i < puddles.size(); i++)
		way[puddles[i][0]][puddles[i][1]] = IN_WATER;

	way[1][1] = 1;

	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (way[i][j] != IN_WATER) {
				if (way[i][j - 1] != IN_WATER) {
					way[i][j] += way[i][j - 1];
                    			way[i][j] %= 1000000007;
				}
           
				if (way[i - 1][j] != IN_WATER) {
                    			way[i][j] += way[i - 1][j];
                    			way[i][j] %= 1000000007;
				}
			}
		}
	}
	
	answer = way[m][n];
	return answer;
}
