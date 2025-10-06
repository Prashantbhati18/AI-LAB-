#include<iostream>
#include<vector>
#include<set>
#include<stack>
#include<algorithm>
using namespace std;
#define N 3

struct State {
    vector<vector<int>> mat;
    int row, col;
    int state_num;
    State* parent;

    State(vector<vector<int>> b, int i, int j, int d, State* p = nullptr) {
        mat = b;
        row = i;
        col = j;
        state_num = d;
        parent = p;
    }
};

bool isGoalState(vector<vector<int>>& mat) {
    vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    return mat == goal;
}

bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int row_list[] = {0, 0, -1, 1};
int col_list[] = {-1, 1, 0, 0};

void print(vector<vector<int>>& mat) {
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------" << endl;
}

void DFS(vector<vector<int>>& mat, int row, int col) {
    stack<State*> st;
    set<vector<vector<int>>> visited;

    State* start = new State(mat, row, col, 0, nullptr);
    st.push(start);
    visited.insert(mat);

    while(!st.empty()) {
        State* current = st.top();
        st.pop();

        if(isGoalState(current->mat)) {
            cout << "Goal state_num reached at: " << current->state_num << endl;
            print(current->mat);
            return; // stop immediately after goal
        }

        // Explore neighbors
        for(int i=0; i<4; i++) {
            int new_row = current->row + row_list[i];
            int new_col = current->col + col_list[i];

            if(isValid(new_row, new_col)) {
                vector<vector<int>> temp = current->mat;
                swap(temp[current->row][current->col], temp[new_row][new_col]);

                if(visited.find(temp) == visited.end()) {
                    visited.insert(temp);
                    State* child = new State(temp, new_row, new_col, current->state_num + 1, current);
                    st.push(child);
                }
            }
        }
    }

    cout << "No solution found !!" << endl;
}

int main() {
    vector<vector<int>> starting_puzzle = {{1,3,2},{0,4,6},{7,5,8}};
    int row = 1, col = 0;  

    cout << "Starting state_num:" << endl;
    print(starting_puzzle);

    DFS(starting_puzzle, row, col);
    return 0;
}