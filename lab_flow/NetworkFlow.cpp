/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

using namespace std;

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
    vector<Vertex> v_vertex = g_.getVertices();
    vector<Edge> v_edge = g_.getEdges();
    for(auto & vertex : v_vertex){
      residual_.insertVertex(vertex);
      flow_.insertVertex(vertex);
    }
    for(auto & edge : v_edge){
      residual_.insertEdge(edge.source, edge.dest);
      residual_.setEdgeWeight(edge.source, edge.dest, edge.getWeight());
      residual_.insertEdge(edge.dest, edge.source);
      residual_.setEdgeWeight(edge.dest, edge.source, 0);
      flow_.insertEdge(edge.source, edge.dest);
      flow_.setEdgeWeight(edge.source, edge.dest, 0);
    }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int res = 0x7fffffff;
  vector<int> v_edge;
  for(unsigned i = 0; i < path.size() - 1; i ++){
    v_edge.push_back(residual_.getEdgeWeight(path[i], path[i + 1]));
  }
  for(auto & edge : v_edge){
    if(edge < res){
      res = edge;
    }
  }
  return res;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector <Vertex> path;
  int cap = 0;
  int res = 0;

  while(findAugmentingPath(source_, sink_, path)){
    vector<Edge> v = residual_.getEdges();

    cap = pathCapacity(path);
    res += cap;
    for(unsigned i = 0; i < path.size() - 1; i ++){
      residual_.setEdgeWeight(path[i], path[i + 1], residual_.getEdgeWeight(path[i], path[i + 1]) - cap);
      residual_.setEdgeWeight(path[i + 1], path[i], residual_.getEdgeWeight(path[i + 1], path[i]) + cap);
      if(flow_.edgeExists(path[i], path[i + 1])){
        flow_.setEdgeWeight(path[i], path[i + 1], flow_.getEdgeWeight(path[i], path[i + 1]) + cap);
      }else{
        flow_.setEdgeWeight(path[i + 1], path[i], flow_.getEdgeWeight(path[i + 1], path[i]) - cap);
      }
    }

  }
  maxFlow_ = res;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

