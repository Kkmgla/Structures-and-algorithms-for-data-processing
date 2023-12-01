#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <queue>

using namespace std;
class Graph {
private:
    int vertices;
    vector<char> names;
    vector<vector<int>> adjacencyMatrix;

public:

    int addNode(char name) {
        for (char ch : names)
        {
            if (ch == name)
            {
                return -1;
            }
        }
        names.push_back(name);
        vertices++;
        for (auto& row : adjacencyMatrix) {
            row.push_back(-1);
        }
        adjacencyMatrix.push_back(std::vector<int>(vertices, -1));
        return 0;
    }

    int addConjugation(char departure, char destination, int weight, bool symmetry) {
        bool dep = false, dest = false;
        int i = 0, j = 0;
        for (char ch : names)
        {
            if (ch == departure)
            {
                dep = true;
                break;
            }
            i++;
        }
        for (char ch : names)
        {
            if (ch == destination)
            {
                dest = true;
                break;
            }
            j++;
        }
        if (!dep || !dest) {
            return -1;
        }
        if (symmetry)
        {
            adjacencyMatrix[i][j] = weight;
            adjacencyMatrix[j][i] = weight;
        }
        else
        {
            adjacencyMatrix[i][j] = weight;
        }
        return 0;
    }

    int printMatrix() {
        if (vertices == 0) return -1;
        cout << "Adjacency matrix:" << endl;
        for (int i = 0; i < vertices; i++) cout << "\t" << " " << names[i];
        cout << endl;
        for (int i = 0; i < vertices; i++) {
            cout << names[i] << "\t";
            for (int j = 0; j < vertices; j++) {
                if (adjacencyMatrix[i][j] == -1) cout << -1 << "\t";
                else cout << " " << adjacencyMatrix[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl << endl;
        return 0;
    }

    int printAllPaths(bool AllOrNot) {
        if (vertices == 0)
        {
            return -1;
        }
        cout << "All Paths (DFS):" << endl;
        for (int i = 0; i < vertices; ++i) {
            vector<bool> visited(vertices, false);//������ � �����������
            vector<int> path;
            dfsPrintPaths(AllOrNot, i, visited, path);
        }
        cout << endl;
        return 0;
    }

    void dfsPrintPaths(bool AllOrNot,int start, vector<bool>& visited, vector<int>& path) {
        visited[start] = true;
        path.push_back(start);
        if (AllOrNot)
        {
            for (int i = 0; i < vertices; ++i) {
                if (!visited[i]) {
                    dfsPrintPaths(AllOrNot, i, visited, path);
                }
            }
        }
        else
        {
            for (int i = 0; i < vertices; ++i) {
                if (adjacencyMatrix[start][i] != -1 && !visited[i]) {
                    dfsPrintPaths(AllOrNot, i, visited, path);
                }
            }
        }
        if (path.size() > 1) {
            cout << "Path: ";
            for (int i : path) {
                cout << names[i] << " ";
            }
            cout << endl;
        }

        path.pop_back();
        visited[start] = false;
    }
    
    void findShortestPaths(char start, char end) {
        int startIdx = getIndex(start);
        int endIdx = getIndex(end);

        if (startIdx == -1 || endIdx == -1) {
            cout << "Start or end edge not found." << endl;
            return;
        }

        vector<int> dist(vertices, INT_MAX);  // dist ������ ���������� �� ��������� ������� �� ���� ���������, � ���������������� ��������������.
        vector<int> parent(vertices, -1);     // parent ������������ ��� �������� ���������� � ���������������� � ���������� �����.
        priority_queue<pair<int, int>,        /* pair<int, int>: ��� ��� ���������, ������� ����� ��������� � ������������ �������.
                                                 ������ ������� - ��� �������� ���������� (����������), � ������ ������� - ������ �������.
        vector<pair<int, int>>: ��� ��������� (������) ��� �������� ��������� ������ ������������ �������.
        greater<pair<int, int>>: ��� ����������, ������� ���������� ������� ��������� � ������������ �������.
        ����� � ��������� greater, ������� ������������� ������� �� ��������(top -> 1 4 7.*/
        vector<pair<int, int>>,
        greater<pair<int, int>>> pq;          // pq - ������������ ������� ��� ��������� ������ � ������� ����������� �� ������� ����������.

        dist[startIdx] = 0;      // ���������� �� ��������� ������� �� ����� ���� ��������������� � 0, � ���� { 0, startIdx } ����������� � ������������ �������.
        pq.push({ 0, startIdx });

        while (!pq.empty()) {
            int u = pq.top().second;/*pq.top(): ���������� ������� � ���������� ��������� ���������� � ������������ ������� pq.
                                      pq.top().second: ��������� ������ ������� �� ����, ������� ������������ ����� ������ ������� � ���������� �����������.
                                      pq - ��� ������������ �������, ������� ������ ���� {����������, ������ �������}.
                                      �� ����, pq.top().second ��������� ������ ������� � ���������� ����������� �� ������������ �������.*/
            pq.pop();

          /*����������� ������� u � ���������� ������� ����������� �� ������������ �������.
            ��� ������ ������� ������� v �����������, ����� �� ��������� ���������� �� �� ����� ������� ������� u.
            ���� ����� ���������� ������ ��������, �� ��� �����������, � ���������� � ��������������� ����������� � ������� parent.
            ����� ������� v ����������� � ������������ ������� ��� ����������� ������������.*/
            for (int v = 0; v < vertices; ++v) {
                if (adjacencyMatrix[u][v] != -1) {
                    int weight = adjacencyMatrix[u][v];
                    if (dist[v] > dist[u] + weight) {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                        pq.push({ dist[v], v });
                    }
                }
            }
        }

        // ����� ���������� �����
        cout << "Shortest Paths from " << start << " to " << end << ":" << endl;
        printShortestPaths(startIdx, endIdx, parent);
        cout << endl;
    }
    // ��������������� ������� ��� ��������� ������� ������� �� � �����
    int getIndex(char name) {
        for (int i = 0; i < vertices; ++i) {
            if (names[i] == name) {
                return i;
            }
        }
        return -1;
    }

    // ��������������� ������� ��� ������ ���������� �����
    void printShortestPaths(int start, int end, const vector<int>& parent) {
        if (end == -1) {
            cout << "No path exists." << endl;
            return;
        }

        stack<int> path;
        /*i = parent[i] - �� ������ �������� �������� i ����������� �� ������ ��������������� ������� ������� (����������� �� ������� parent).
        ��� ���������� � �������� �����������, ��� ��� �� ��������� �� �������� ������� � ���������.*/
        for (int i = end; i != -1; i = parent[i]) {
            path.push(i);
        }

        while (!path.empty()) {
            cout << names[path.top()] << " ";
            path.pop();
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Graph graph;
    while (true) {
        cout << "1. Add Node"
            << "\n2. Add Conjugation"
            << "\n3. Display Graph"
            << "\n4. Display All Paths (DFS)/All Availible Paths"
            << "\n5. Find Shortest Paths (Solution Tree)"
            << "\n6. Test default graph" << endl;

        char opt;
        char tmp;
        cout << "Enter your choice: ";
        cin >> opt;

        switch (opt) {
            case '1': {
                cout << "Enter your edge name: ";
                cin >> tmp;
                int result = graph.addNode(tmp);
                if (result == 0)
                    cout << "Edge added" << endl;
                else if (result == -1)
                    cout << "Edge already existed" << endl;
                break;
            }
            case '2': {
                char start, end;
                int weight;
                bool symm;
                cout << "Enter start and end vertices, weight and symmetry: ";
                cin >> start >> end >> weight >> symm;
                if (weight < 0)
                {
                    cout << "Weight does not can be lesser than 0" << endl;
                    break;
                }
                int result = graph.addConjugation(start, end, weight, symm);
                if (result == 0)
                    cout << "Conjugation added" << endl;
                else if (result == -1)
                    cout << "Edge(s) you wrote did not found" << endl;
                break;
            }
            case '3': {
                int result = graph.printMatrix();
                if (result == 0)
                    cout << "Matrix successfully printed" << endl;
                else if (result == -1)
                    cout << "Matrix does not exist yet" << endl;
                break;
            }
            case '4': {
                bool tmp;
                cout << "1 - All paths\n" << "0 - All avalieble paths\n";
                cin >> tmp;
                int result = graph.printAllPaths(tmp);
                if (result == 0)
                    cout << "Paths was printed" << endl;
                else if (result == -1)
                    cout << "There is no paths yet" << endl;
                break;
            }
            case '5': {
                char start, end;
                cout << "Enter start and end vertices: ";
                cin >> start >> end;
                graph.findShortestPaths(start, end);
                break;
            }
            case '6': {
                graph.addNode('1');
                graph.addNode('2');
                graph.addNode('3');
                graph.addNode('4');
                graph.addNode('5');
                graph.addConjugation('1', '2', 1, 1);
                graph.addConjugation('1', '3', 2, 1);
                graph.addConjugation('1', '5', 10, 1);
                graph.addConjugation('2', '5', 6, 1);
                graph.addConjugation('2', '4', 3, 1);
                graph.addConjugation('3', '5', 7, 1);
                graph.addConjugation('3', '4', 4, 1);
                graph.addConjugation('4', '5', 11, 1);
                graph.printMatrix();
                graph.printAllPaths(1);
                graph.printAllPaths(0);
                graph.findShortestPaths('1', '4');
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    return 0;
}