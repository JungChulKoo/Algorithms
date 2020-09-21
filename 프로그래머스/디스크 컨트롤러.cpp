#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
	using namespace std;
	struct compare_job {
		bool operator()(vector <int> a, vector <int> b)
		{
			return a[1] > b[1];
		}
	};

	int solution(vector<vector<int>> jobs) {

		int progress = 0;
		int ji = 0; 
		int p_point = 0; 
		int t_job = 0; 
		vector<int> job; 
		priority_queue<vector<int>, vector<vector<int>>, compare_job> PQ; 
		
		int answer = 0;

		sort(jobs.begin(), jobs.end());

		for (ji = 0; ji < jobs.size(); ji++){
			t_job += jobs.at(ji)[1]; //
		}

		ji = 0;

		while (1) {

			if (ji < jobs.size()) {
				if (jobs.at(ji)[0] <= p_point)
				{
					PQ.push(jobs.at(ji++));
					continue;
				}
			} 

			if (progress) {  
				progress--;
				t_job--; // 

				if (!progress) // 
				{
					answer += p_point - job[0]; 

					if (!PQ.empty()) { 
						job = PQ.top(); 
						progress = job[1]; 
						PQ.pop(); 

					}

				}
			}

			else  
			{
				if (!PQ.empty()) { 
					job = PQ.top(); 
					progress = job[1]; 
					PQ.pop(); 
				}
			}

			if (t_job <= 0)
			{
				answer /= jobs.size(); 
				return answer;
			}

			p_point++;
			
		}

		
	}
