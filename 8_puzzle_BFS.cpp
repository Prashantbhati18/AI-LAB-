#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
#define N 3

struct state {
    vector<vector<int>> mat;
    int row;
    int col;
    int state_no;
    state* parent;

    state(vector<vector<int>> p, int x, int y, int num, state* par = nullptr) {
        mat = p;
        row = x;
        col = y;
        state_no = num;
        parent = par;
    }
};

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

bool isGoalMatrix(vector<vector<int>>& mat) {
    vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    return mat == goal;
}

void printpuzzle(vector<vector<int>>& matrix) {
    for (auto& r : matrix) {
        for (auto& i : r) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << "------" << endl;
}

int row_list[] = {0, 0, -1, 1};
int col_list[] = {-1, 1, 0, 0};

void BFS_puzzle(vector<vector<int>>& mat, int row, int col) {
    queue<state*> q;
    set<vector<vector<int>>> closed;

    state* first = new state(mat, row, col, 0, nullptr);
    q.push(first);
    closed.insert(mat);

    while (!q.empty()) {
        state* present = q.front();
        q.pop();

        if (isGoalMatrix(present->mat)) {
            cout << "Goal matrix achieved at step " << present->state_no << endl;
            printpuzzle(present->mat);
            return;
        }

        // Exploring the other children
        for (int i = 0; i < 4; i++) {
            int new_row = present->row + row_list[i];
            int new_col = present->col + col_list[i];

            if (isValid(new_row, new_col)) {
                vector<vector<int>> temp = present->mat;
                swap(temp[present->row][present->col], temp[new_row][new_col]);

                if (closed.find(temp) == closed.end()) {
                    closed.insert(temp);
                    state* child = new state(temp, new_row, new_col, present->state_no + 1, present);
                    q.push(child);
                }
            }
        }
    }
    cout << "No such goal found !!" << endl;
}

int main() {
    vector<vector<int>> puzzle = {{1,2,3},{4,5,6},{8,7,0}};
    int row = 1, col = 0;  

    cout << "Starting Puzzle:" << endl;
    printpuzzle(puzzle);

    BFS_puzzle(puzzle, row, col);
    return 0;
}
