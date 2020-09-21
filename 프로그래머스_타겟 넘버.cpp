#include <string>
#include <vector>

using namespace std;

int counter = 0;

void dfs(int point, vector<int> numbers, int index, int target)
{
    if(index < numbers.size()){
        int number = numbers.at(index);
        
        dfs(point - number, numbers, index + 1, target);
        dfs(point + number, numbers, index + 1, target);
    }
    
    else
    {
        if(point == target)
            counter++;
    }
}

int solution(vector<int> numbers, int target) {
    
    dfs(0, numbers, 0, target);
    return counter;
}
