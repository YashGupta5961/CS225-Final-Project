/**
 * @file reddit.cpp
 * CS 225: Data Structures
 */

#pragma once

#include <stack>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

#include "graph.h"
#include "edge.h"

using std::unordered_set;
using std::stack;

class Reddit{
    
    public:
    Reddit(string filename);
    vector<Vertex> BFS(Vertex src, Vertex goal);
    vector<Vertex> IDS(string src, string goal, int depth);
    vector<vector<Vertex>> SCCs();
    vector<vector<Vertex>> StronglyCC();
    int maxDepth(Vertex src);
    const Graph & getGraph() const;
    const Graph & getTranspose() const;

    // void BFS(Graph & g_);
    // void BFSHelper(Graph & g_, Vertex v);
    // bool Reddit::IDS(string node, string goal, int depth);
    void StronglyCCUtil(Vertex u, unordered_map<Vertex, int> disc, unordered_map<Vertex, int> low, stack<Vertex> *st, unordered_map<Vertex, bool> stackMember);

    private:
    // Graph redditg_;
    // Vertex startvertex_;
    Graph g_;
    vector<vector<Vertex>> result;

    

};   
