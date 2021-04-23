#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

bool graph[100][100];


bool dfs(int i, vector<bool>& col, int nodes) {
    if (col[i]) {
        return 0;
    }
    col[i] = true;
    for (int j = 0; j < nodes; j++) {
        if (graph[i][j]) {
            dfs(j, col, nodes);
        }
    }
}


bool isTree(int nodes, vector<int>& vecNodes, int bridges) {
    vector<bool> col;
    bool tr = false;
    int begin = 0;
    for (auto i = 0; i < nodes; i++)
    {
        col.push_back(false);
    }
    for (begin; begin < vecNodes.size(); begin++)
    {
        for (auto el : vecNodes) {
            if (begin == el) {
                tr = true;
                break;
            }
        }
        if (tr == false)
            break;
        tr = false;
    }
    dfs(begin, col, nodes);

    for (int i = 0; i < nodes; ++i) {
        if (!col[i]) {
            return false;
        }
    }
    return true;
}


int main() {
    vector<int> vecNodes;
    string path = "myfile5.txt";
    string msg;
    fstream fs;
    int nodes = 0, bridges = 0;

    fs.open(path, fstream::in | fstream::out | fstream::app);
    if (!fs.is_open())
        cout << "FILE OPEN ERROR!\n";
    else
        cout << "File is open!\n";

    while (true) {
        msg = "";
        if (fs.eof()) break;
        fs >> msg;
        int temp = 0;
        for (size_t j = 0; j < msg.size(); j += 2)
        {
            if (msg[j] == '0')
                graph[nodes][temp] = false;
            if (msg[j] == '1') {
                graph[nodes][temp] = true;
                bridges++;
                vecNodes.push_back(temp);
            }
            temp++;
        }
        nodes++;
    }
    fs.close();

    if (bridges != nodes - 1) {
        cout << "\nNo tree!\n";
        return 0;
    }

    if (isTree(nodes, vecNodes, bridges)) cout << "\nIt is tree!\n";
    else cout << "\nNo tree!\n";

    return 0;
}