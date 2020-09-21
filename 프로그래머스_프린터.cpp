#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> priorities, int location) {
    bool finished = false;
    int answer = 0;
    pair<int, int> job;
    vector<pair<int, int>> Q;
    
    for(int i = 0; i < priorities.size(); i++)
        Q.push_back(make_pair(priorities[i], i));
    reverse(Q.begin(), Q.end());
    
    while(!finished){
        job = Q.back();
        Q.pop_back();
        if(job.first < max_element(Q.begin(), Q.end())->first){
            Q.insert(Q.begin(), job);
        }
        
        else {
            if(job == make_pair(priorities[location], location))
                finished = true;
            answer++;
        }
        
        
    }
    
    return answer;
}
