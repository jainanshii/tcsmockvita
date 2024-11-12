#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>> moves (int x, int y) {
    return {{x, y}, {y, -x}, {-y, x}, {-x, -y}};
}

int help(vector<vector<int>>& grid, pair<int, int> s, pair<int, int> d, pair<int, int> move) {
    int m = grid.size(), n = grid[0].size();
    
    
    if (s == d) return 0;

    
    queue<vector<int>> q;
    q.push({s.first, s.second, 0});
    
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    visited[s.first][s.second] = true;
    
    while (!q.empty()) {
        int r = q.front()[0];
        int c = q.front()[1];
        int distance = q.front()[2];
        q.pop();
        
        
        if (r == d.first && c == d.second) 
            return distance;
        
       
        for (auto [x, y] : moves(move.first, move.second)) {
            int newr = r + x;
            int newc = c + y;
            
            
            if (newr >= 0 && newr < m && newc >= 0 && newc < n && grid[newr][newc] == 0 && !visited[newr][newc]) {
                visited[newr][newc] = true;
                q.push({newr, newc, distance + 1});
            }
        }
    }
    
 
    return -1;
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }

    pair<int, int> source, dest, move_rule;
    cin >> source.first >> source.second;
    cin >> dest.first >> dest.second;
    cin >> move_rule.first >> move_rule.second;
    
    int result = help(grid, source, dest, move_rule);
    cout << result;

    return 0;
}
