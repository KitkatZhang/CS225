#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
using namespace std;
/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  int degree_count = 0;
  for(auto & it : vertexMap){
    if(it.second == v.key()){
      degree_count += adjList[it.first].size();
    }
    for(auto & Ver_iter : adjList[it.first]){
      if(Ver_iter->dest() == it.first){
        degree_count += 1;
      }
    }
  }
  return degree_count;
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.insert({key,v});
  adjList[key] = list<edgeListIter>();
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  for(auto & it : adjList){
    for(auto it1 : it.second){
      if(it1->get().dest().key() == key){
        (it.second).remove(it1);
        edgeList.erase(it1);
      }
      if(it1->get().source().key() == key){
        (it.second).remove(it1);
        edgeList.erase(it1);
      }
    }
  }


  auto Ver_iter = vertexMap.find(key);
  if(Ver_iter != vertexMap.end()){
    vertexMap.erase(key);
    adjList.erase(key);
  }



}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  E_byRef e_ref = e;
  edgeList.push_front(e);
  edgeListIter Edge_iter = edgeList.begin();

  auto Ver_iter = vertexMap.find(v1.key());
  if(Ver_iter == vertexMap.end()){
    insertVertex(v1.key());
  }
  Ver_iter = vertexMap.find(v2.key());
  if(Ver_iter == vertexMap.end()){
    insertVertex(v2.key());
  }

  adjList[v1.key()].push_front(Edge_iter);

  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  
  // TODO: Part 2
  for(typename list<edgeListIter>::iterator Edge_iter = adjList[key1].begin(); Edge_iter != adjList[key1].end(); Edge_iter ++){
    if(((*Edge_iter)->get()).dest().key() == key2){
      edgeList.erase(*Edge_iter);
      adjList[key1].erase(Edge_iter);
    }
  }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  string key1 = it->source();
  string key2 = it->dest();
  removeEdge(key1, key2);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<edgeListIter> edges;
  std::list<std::reference_wrapper<E>> edges_;
  edges = adjList.at(key);
  for(auto & iter : edges){
    edges_.push_back(*iter);
  }
  for(auto & adj_iter : adjList){
    if(adj_iter.first != key){
      for(auto & list_iter : adjList.at(adj_iter.first)){
        if((list_iter->get()).dest().key() == key){
          edges_.push_back((*list_iter));
        }
      }
    }
  }
  return edges_;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  for(auto & list_iter : adjList.at(key1)){
    if((list_iter->get()).dest().key() == key2){
      return true;
    }
  }
  for(auto & list_iter : adjList.at(key2)){
    if((list_iter->get()).dest().key() == key2 && list_iter->get().directed() == false){
      return true;
    }
  }
  return false;
}
