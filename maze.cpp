#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;


// the method sir gave us
void solveMaze(vector<vector<char>>& maze, int height, int width, pair<int, int> source, pair<int, int> goal)
{
    // Initialise an empty queue
    queue<pair<int, int>> q;

    // Initialise distance and parent arrays
    vector<vector<int>> distance(height, vector<int>(width, INT_MAX)); // int_max makes it inf
    vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, {-2, -2}));

    q.push(source);
    distance[source.first][source.second] = 0;

    vector<pair<int, int>> directions = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}}; // down, left, up, right in thers of columns and rows


    while (!q.empty() == true)
    {
        pair<int, int> curr = q.front();
        q.pop();

        // If the goal is reached, we can exit the loop early
        if (curr == goal)
        {
            break;
        }



        // Foreach neighbor (down, left, up, right), doing the next part of the way for everything
        for (const auto& direction : directions)
        {
            int newRow = curr.first + direction.first;
            int newCol = curr.second + direction.second;

            // Check if the neighbor is a valid(not a walll of the maze) and not in que already
            if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width && maze[newRow][newCol] != 'x' && distance[newRow][newCol] == INT_MAX)
            {
                distance[newRow][newCol] = distance[curr.first][curr.second] + 1;
                parent[newRow][newCol] = curr;
                q.push({newRow, newCol});
            }
        }
    }





    // If queue is empty and goal is not visited, we tried everywhere
    if (distance[goal.first][goal.second] == INT_MAX)
    {
        cout << "No Path" << endl;
    }
    else
    {
        // Backtrack to find the path from goal to start
        vector<pair<int, int>> output;
        pair<int, int> curr = goal;
        while (curr != source)
        {
            output.insert(output.begin(), curr); // Add current to the front of the output
            curr = parent[curr.first][curr.second];
        }
        output.insert(output.begin(), source); // Add start to the front of the output





        //showing the path on the maze
        for (const auto& step : output)
        {
            if (maze[step.first][step.second] != 'G' && maze[step.first][step.second] != 'S')
            {
                maze[step.first][step.second] = '*';
            }
        }

        // Print the maze, doing in function cause of varibles
        cout << endl;
        for (const auto& row : maze)
        {
            for (char cell : row)
            {
                cout << cell;
            }
            cout << endl;
        }
    }


}

int main()
{
    //input
    int height, width;
    cin >> height >> width;
    cin.ignore();

    vector<vector<char>> maze(height, vector<char>(width));
    pair<int, int> source, goal;

    for (int i = 0; i < height; ++i)
    {
        string row;
        getline(cin, row);
        for (int j = 0; j < width; ++j)
        {
            maze[i][j] = row[j];
            if (maze[i][j] == 'S') source = {i, j};
            if (maze[i][j] == 'G') goal = {i, j};
        }
    }



    //solving
    solveMaze(maze, height, width, source, goal);
    return 0;
}
