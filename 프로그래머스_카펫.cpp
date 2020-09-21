#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    int size = brown + yellow;
    int x = 1, y = size;
    vector<int> answer;
    
    while(1){
        if(size % x == 0){
            y = size / x;
            if(x >= y && (x - 2) * (y - 2) == yellow)
                break;
        }
        
        x++;
    }
    
    answer.push_back(x);
    answer.push_back(y);
    
    return answer;
}
