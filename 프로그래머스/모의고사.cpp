#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> f = {1, 2, 3, 4, 5};
vector<int> s = {2, 1, 2, 3, 2, 4, 2, 5};
vector<int> t = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};

vector<int> counter = {0, 0, 0};

vector<int> solution(vector<int> answers) {
    int i;
    vector<int> answer;
    
    for(i = 0; i < answers.size(); i++) {
        if(answers[i] == f[i % f.size()])
            counter.at(0) = counter.at(0) + 1;
        if(answers[i] == s[i % s.size()])
            counter.at(1) = counter.at(1) + 1;
        if(answers[i] == t[i % t.size()])
            counter[2] = counter[2] + 1;
    }
    if(counter[0] == *max_element(counter.begin(), counter.end()))
        answer.push_back(1);
    if(counter[1] == *max_element(counter.begin(), counter.end()))
        answer.push_back(2);
    if(counter[2] == *max_element(counter.begin(), counter.end()))
        answer.push_back(3);
    
    return answer;
}
