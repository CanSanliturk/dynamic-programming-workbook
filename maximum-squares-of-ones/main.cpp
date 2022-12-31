#include <vector>
#include <iostream>

using namespace std;

int maximalSquare(vector<vector<int>>& matrix) {
        
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> rec(m, vector<int>(n, 0));

    for (auto i = 0; i < n; ++i)
        rec[0][i] = matrix[0][i] == 1;

    for (auto i = 0; i < m; ++i)
        rec[i][0] = matrix[i][0] == 1;
        

    for (auto i = 1; i < m; ++i) {
        for (auto j = 1; j < n; ++j) {
            if (matrix[i][j] == 0)
                continue;
                
            rec[i][j] = 1 + min(
                rec[i - 1][j - 1],
                min(
                    rec[i - 1][j],
                    rec[i][j - 1]
                )
            );
        }
    }
        
    int maxArea = 0;
    for (auto i = 0; i < m; ++i)
        for (auto j = 0; j < n; ++j)
            maxArea = max(maxArea, rec[i][j]);

    return maxArea * maxArea;
}

int main() {
    vector<vector<int>> matrix {
        { 1, 0, 1, 0, 0 },
        { 1, 0, 1, 1, 1 },
        { 1, 1, 1, 1, 1 },
        { 1, 0, 0, 1, 0 }
    };

    cout << "Expected is 4 and actual answer is " << maximalSquare(matrix) << endl;
}