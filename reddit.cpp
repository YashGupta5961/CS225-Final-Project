#include "reddit.h"
#include "graph.h"
#include "edge.h"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <deque>

using namespace std;


Reddit::Reddit() //Project graph constructor
{
    g_ = Graph(); // create empty, weighted, and directed graph
    std::ifstream f("cleaned.csv"); //input file stream - file pointer
    
    if(!f.is_open()) std::cout << "File not found!" << std::endl; // error message

    std::string str;
    getline(f, str); //skips first line of csv - coloumn headers

    std::string src; // temp string to parse source subreddit
    std::string des; // temp string to parse target subreddit
    std::string sent; // temp string to parse link sentiment - edge weight
    std::string count; // temp string to parse #links averaged - edge label

    while(!f.eof()) // read lines till end of file is reached
    {
        std::getline(f, src, ','); // reads till first comma, inserts data in 'src'
        std::getline(f, des, ','); // reads till second comma, inserts data in 'des' 
        std::getline(f, sent, ','); // reads till third comma, inserts data in 'sent'
        std::getline(f, count, '\n'); // reads till end of line, inserts data in 'count'

        if(!g_.vertexExists(src)) g_.insertVertex(src); // if source subreddit doesnt exist, insert to graph
        if(!g_.vertexExists(des)) g_.insertVertex(des); // if target subreddit doesnt exist, insert to graph
        if(!g_.edgeExists(src, des)) // if edge connecting src & des doesnt exist:
        {
            bool attempt = g_.insertEdge(src, des); // insert edge
            int w = std::stof(sent) * std::stoi(count); // calculate edge weight
            g_.setEdgeWeight(src, des, w); // set edge weight
            g_.setEdgeLabel(src, des, count); // set edge label
        }
    }

    f.close(); // close .csv file
}



void Reddit::BFS(Graph & g_){
    //std::unordered_map<Vertex, bool> vlabel;
    //std::unordered_map<Edge, std::string> elabel;
    int connectedcomp = 0;
    for(Vertex v : g_.getVertices()){
        vlabel[v] = false;
    }
    for(Edge e: g_.getEdges()){
        elabel[e] = "UNEXPLORED";
    }
    for(Vertex v : g_.getVertices()){
        if(vlabel[v] = false){
            BFSHelper(g_, v);
            connectedcomp++;
        }
    }

}
void Reddit::BFSHelper(Graph & g_, Vertex v){
    std::queue<Vertex> vertices;
    vlabel[v] = true;
    vertices.push(v);
    bool cycle = false;
    //Vertex popped;

    while(!vertices.empty()){
        v = vertices.front();
        vertices.pop();
        for(Vertex w : g_.getAdjacent(v)){
            if(vlabel[w] == false){
                elabel[g_.getEdge(v, w)] = "DISCOVERY";
                vlabel[w] = true;
                vertices.push(w);
            }
            else if(vlabel[w] == true){
                elabel[g_.getEdge(v, w)] = "CROSS";
                cycle = true;
            }
        }
    }
}