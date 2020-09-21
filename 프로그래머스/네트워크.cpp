#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> ancestor;

int get_ancestor(int n) {
    if(ancestor[n] == n)
        return n;
    else
        return ancestor[n] = get_ancestor(ancestor[n]);
}

void union_ancestor(int a, int b) {
    int aa = get_ancestor(a);
    int ab = get_ancestor(b);
    
    if(aa != ab){
        if(aa < ab) {
            ancestor[ab] = aa;
            get_ancestor(b);
        }
    
        else {
            ancestor[aa] = ab;
            get_ancestor(a);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    int i, j, k;
    int answer = 0;
    vector<int> counter(n, 0);
    
    for(i = 0; i < n; i++)
        ancestor.push_back(i);
    
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(computers[i][j])
                union_ancestor(i, j);
            else {
                for(k = 0; k < n; k++){
                    if(computers[i][k] && computers[k][j]){
                        union_ancestor(i, j);
                        break;
                    }
                }
            }
        }
    }
    
    for(i = 0; i < n; i++)
        counter[ancestor[i]]++;
    
    for(i = 0; i < n; i++) {
        if(counter[i] != 0)
            answer++;
    }
    
    return answer;
}
