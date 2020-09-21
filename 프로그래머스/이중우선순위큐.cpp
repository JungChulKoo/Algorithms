#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> solution(vector<string> operations) {
    int i;
    multiset<int, less<int>> DEPQ;
    vector<int> answer;
    
    for(i = 0 ; i < operations.size(); i++){
        if(operations[i] == "D 1"){
            if(!DEPQ.empty())
                DEPQ.erase(*DEPQ.rbegin());
        }
        
        else if(operations[i] == "D -1"){
            if(!DEPQ.empty())
                DEPQ.erase(*DEPQ.begin());
        }
        
        else
            DEPQ.insert(stoi(operations[i].substr(2, operations[i].size())));
    }
    
    if(DEPQ.empty()){
        answer.push_back(0);
        answer.push_back(0);
    }
    
    else{
        answer.push_back(*DEPQ.rbegin());
        answer.push_back(*DEPQ.begin());
    }
    
    return answer;
}
