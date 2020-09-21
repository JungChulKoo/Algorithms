#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int i, size = scoville.size();
    int answer = 0;
    int m1, m2, r;
    priority_queue <int, vector<int>, greater<int>> PQ;
    
    for(i = 0; i < size; i++)
        PQ.push(scoville.at(i));
    
    while(K > PQ.top()){
        
        if(PQ.empty())
            return -1;
        
        m1 = PQ.top();
        PQ.pop();
        
        if(PQ.empty())
            return -1;
        
        m2 = PQ.top();
        PQ.pop();
        
        r = m1 + 2 * m2;
        PQ.push(r);
        
        answer++;
    }
    return answer;
}
