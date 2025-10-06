#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
using namespace std;
#define N 3

struct state{
    vector<vector<int>> mat;
    int row;
    int col;
    int state_num;
    state *parent;

    state(vector<vector<int>> matrix, int x, int y, int st, state * p= nullptr ){
        mat = matrix;
        row = x;
        col = y;
        state_num = st;
        parent = p;
    }
};

bool isValid(int x, int y){
    return ( x >= 0 && x <N && y >=0 && y<N);
}

bool GoalMatrix(vector<vector<int>> & mat){
    vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    return mat == goal;
}

row_list[] = {-1,1,0,0};
col_list[] = {0,0,-1,1};

void print(vector<vector<int>> &mat){
    for(auto& i :mat){
        for(auto& num :i){
            cout<< num << " ";
        }
        cout<<endl;
    }
}

int heruistic_calculator(vector<vector<int>> mat ){
    vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    int h =0;
    for(int i=0; i<N ; i++){
        for(int j=0; j<N; j++){
            if(mat[i][j] != goal[i][j]){
                h += 1;
            }
        }
    }
    return h;
}

void Hill_Climbing(vector<vector<int>> & mat, int row, int col){
    if (isGoalMatrix(present->mat)) {
            cout << "Goal matrix achieved at step " << present->state_no << endl;
            printpuzzle(present->mat);
            return;
    }
}

int main(){
    vector<vector<int>> puzzle = {{1,2,3},{0,4,5},{6,7,8}};
    int row = 1, col = 0;  

    cout << "Starting Puzzle:" << endl;
    print(puzzle);

    Hill_Climbing(puzzle, row, col);
    return 0;
}