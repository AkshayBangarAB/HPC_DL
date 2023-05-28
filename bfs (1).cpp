#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void bfs(vector<vector<int>>& graph, int start,
vector<bool>& visited) {
	queue<int> q;
	q.push(start);
	visited[start] = true;
	cout<< start << endl;
	#pragma omp parallel
	{
		#pragma omp single
		{
			while(!q.empty()){
				int vertex = q.front();
				q.pop();
				#pragma omp task firstprivate(vertex)
				{
					for (int neighbor: graph[vertex]) {
						if (!visited[neighbor]){
							q.push(neighbor);
							visited[neighbor] = true;
							cout<< neighbor << endl;
							bfs(graph, neighbor, visited);
						}
					}
				}
			}
		}
	}
}
void parallel_bfs(vector<vector<int>>& graph, int start){
	vector<bool> visited(graph.size(), false);
	bfs(graph, start, visited);
}
int main() {
    // Create a sample graph
    vector<vector<int>> graph = {
        {1, 2},     // Node 0 is connected to nodes 1 and 2
        {0, 2, 3},  // Node 1 is connected to nodes 0, 2, and 3
        {0, 1, 3},  // Node 2 is connected to nodes 0, 1, and 3
        {1, 2}      // Node 3 is connected to nodes 1 and 2
    };

    int startNode = 0;  // Starting node for the depth-first search

    parallel_bfs(graph, startNode);

    return 0;
}