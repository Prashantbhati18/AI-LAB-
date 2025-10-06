#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;   // coordinates
    int g, h, f;
    Node* parent;
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(int x, int y, int rows, int cols, vector<vector<int>>& grid) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0);
}

int heuristic(int x1, int y1, int x2, int y2) {
    // Manhattan distance
    return abs(x1 - x2) + abs(y1 - y2);
}

void printPath(Node* endNode) {

    vector<pair<int,int>> path;

    while (endNode != nullptr) {
        path.push_back({endNode->x, endNode->y});
        endNode = endNode->parent;
    }
    reverse(path.begin(), path.end());

    cout << "Path found:\n";
    for (auto p : path) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
}

void aStar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {

    int rows = grid.size();
    int cols = grid[0].size();
    
    priority_queue<Node*, vector<Node*>, Compare> openList;
    vector<vector<bool>> closedList(rows, vector<bool>(cols, false));

    Node* startNode = new Node{start.first, start.second, 0, 0, 0, nullptr};
    startNode->h = heuristic(start.first, start.second, goal.first, goal.second);
    startNode->f = startNode->g + startNode->h;
    openList.push(startNode);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == goal.first && current->y == goal.second) {
            printPath(current);
            return;
        }

        closedList[current->x][current->y] = true;

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            if (!isValid(nx, ny, rows, cols, grid) || closedList[nx][ny]) continue;

            Node* neighbor = new Node{nx, ny, current->g + 1, 0, 0, current};
            neighbor->h = heuristic(nx, ny, goal.first, goal.second);
            neighbor->f = neighbor->g + neighbor->h;

            openList.push(neighbor);
        }
    }

    cout << "No path found!" << endl;
}

int main() {
    // 0 = free space, 1 = obstacle (river)
    vector<vector<int>> grid = { 
            { 0, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
            { 1, 1, 0, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 0, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 0, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 } };

    pair<int,int> start = {0,0};
    pair<int,int> goal  = {5,9};

    cout << "Starting A* Search..." << endl;
    aStar(grid, start, goal);

    return 0;
}