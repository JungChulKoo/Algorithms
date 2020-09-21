#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> copy;
    vector<int> answer;
    
    for(int i = 0 ; i < commands.size(); i++) {
        copy.assign(array.begin(), array.end());
        nth_element(copy.begin() + commands[i][0] - 1,
                    copy.begin() + commands[i][0] + commands[i][2] - 2,
                    copy.begin() + commands[i][1]);
        
        answer.push_back(copy[commands[i][0] + commands[i][2] - 2]);
    }
    
    return answer;
}
