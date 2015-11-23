#include "graph.hpp"
#include <queue>

void Graph::add_edge(const Edge &e)
{
    Vertex v = e.either();
    Vertex w = e.other(v);
    Vertex x = std::max(v,w);
    if (x + 1 > V){
	V = x + 1;
	adj.resize(V + 1);
    }
    adj[v].push_back(w);
    adj[w].push_back(v);
    edges.push_back(e);
    E++;
}

void Digraph::add_edge(const Edge &e)
{
    Vertex v = e.from();
    Vertex w = e.to();
    Vertex x = std::max(v,w);
    if (x + 1 > V){
	V = x + 1;
	adj.resize(V + 1);
    }
    adj[v].push_back(w);
    edges.push_back(e);
    E++;
}

std::vector<Vertex> Digraph::tsort()
{
    std::vector<long int> sorted(0);
    std::vector<long int> indegree(V);
    
    for (int i=0; i<V; ++i) {
        indegree[i] = 0;
    }
    for (int i=0; i<V; ++i) {
	for (int j=0; j<V; ++j) {
	    if (std::find(adj[j].begin(), adj[j].end(), i) != adj[j].end()) {  
		indegree[i]++;
	    }
        }  
    }
    
    std::queue<Vertex> q;
    for (int i=0; i<V; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
	if(std::find(sorted.begin(), sorted.end(), v) == sorted.end()) {
	    sorted.push_back(v);
	}
        
        for (int i = 0; i < adj[v].size(); i++){
	    for (std::list<long>::iterator it=adj[v].begin(); it != adj[v].end(); ++it){
		if (--indegree[*it] == 0) q.push(*it);
	    }
        }
    }
   //if (V != sorted.size())
     //   throw;  //here it throws an exception
    return sorted;
}