#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <utility>
#include <iostream>
using namespace std;

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;

  map <string, pair<int, string>> unvisited; // not labeled set
  for(auto & it : vertexMap){
  	unvisited.insert(make_pair(it.first, make_pair(0x7fffffff, "This is start!")));
  }
  unvisited.erase(start);
  map <string, int> visited;
  visited.insert(make_pair(start, 0));
  string cur = start;
  map <string, string> path_helper;
  path_helper.insert(make_pair(cur, "This is start!"));

  for(auto it : edgeList){
  	typename unordered_map<string, list<edgeListIter>>::iterator it1 = adjList.find(it.get().dest().key());
  	if(it1 == adjList.end()){
  		adjList.insert(make_pair(it.get().dest().key(), list<edgeListIter>()));
  		//cout << "Add Adjlist " << it.get().dest().key() << endl;
  	}
  	insertEdge(it.get().dest(), it.get().source());
  	//cout << "insert edges " << it.get().dest().key()  << " -> "<< it.get().source().key()<<endl;
  }



  while(cur != end){
  	for(auto & it2 : visited){
  		//cout << it2.first << " ";

	  	for(auto & it : adjList.at(it2.first)){
	  		map <string, pair<int, string>>::iterator un_it = unvisited.find((it->get()).dest().key());
	  		if(un_it != unvisited.end()){
	  			double edge_weight = (it->get()).weight();
	  			edge_weight += visited.at(it2.first);
	  			double cur_distance = unvisited.at((it->get()).dest().key()).first;
	 
	  			if(edge_weight < cur_distance){
	  				unvisited.at((it->get()).dest().key()).first = edge_weight;
	  				unvisited.at((it->get()).dest().key()).second = it2.first;
	  			}
	  		}
	  	}
  	}
  	//cout << endl;
  	pair<string, pair<int, string>> new_cur = make_pair("haha", make_pair(0x7fffffff, "haha"));
  	for(auto &it : unvisited){
  		//cout << it.first << " " <<it.second.first << endl;
  		if(it.second.first < new_cur.second.first){
  			new_cur = it;
  			cur = it.second.second;
  		}
  	}
  	unvisited.erase(new_cur.first);
  	visited.insert(make_pair(new_cur.first, new_cur.second.first));
  	path_helper.insert(make_pair(new_cur.first, cur));
  	//cout << endl << "new node intersted " << new_cur.first << " with pre " << cur << endl;
  	cur = new_cur.first;
  }

  path.push_front(cur);
  while(path_helper[cur] != "This is start!"){
  	cur = path_helper[cur];
  	path.push_front(cur);
  }
  /*
  cout << endl;
  for(auto &it : path){
  	cout << it <<"->";
  }
  cout << endl;
	*/
  return path;
}

