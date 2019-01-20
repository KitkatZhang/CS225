#include "../cs225/catch/catch.hpp"

#include "../Graph.h"
#include "../DirectedEdge.h"
#include "../Vertex.h"

TEST_CASE("Graphs with `DirectedEdge`s have directed edges", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  g.insertVertex("a");
  g.insertVertex("b");
  g.insertEdge("a", "b");
  
  REQUIRE( g.incidentEdges("a").front().get().directed() == true );
}

TEST_CASE("Graphs::isAdjacent with `DirectedEdge`s finds the directed edge", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  Vertex a = g.insertVertex("a");
  Vertex b = g.insertVertex("b");
  g.insertEdge("a", "b");
  
  REQUIRE( g.isAdjacent(a, b) == true );
}

TEST_CASE("Graphs::isAdjacent with `DirectedEdge`s does not find the directed edge", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  Vertex a = g.insertVertex("a");
  Vertex b = g.insertVertex("b");
  g.insertEdge("a", "b");
  
  REQUIRE( g.isAdjacent(b, a) == false );
}

TEST_CASE("Graphs::isAdjacent with `DirectedEdge`s does not finds the directed edge_2", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  Vertex a = g.insertVertex("a");
  Vertex b = g.insertVertex("b");
  g.insertEdge("a", "b");
  g.removeEdge("a", "b");
  
  REQUIRE( g.isAdjacent(a, b) == false );
}


TEST_CASE("Remove Vertex test_1", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  Vertex a = g.insertVertex("a");
  Vertex b = g.insertVertex("b");
  g.removeVertex("a");
  
  REQUIRE(g.size() == 1);
}

TEST_CASE("Remove Vertex test_2", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  Vertex a = g.insertVertex("a");
  Vertex b = g.insertVertex("b");
  g.insertEdge("a", "b");
  g.insertEdge("b", "a");
  g.removeVertex("a");

  
  REQUIRE(g.size() == 1);
  REQUIRE(g.edges() == 0);
}

TEST_CASE("Remove Vertex test_3", "[weight=1]") {
  Graph<Vertex, DirectedEdge> g;
  Vertex a = g.insertVertex("a");
  Vertex b = g.insertVertex("b");
  g.insertVertex("c");
  g.insertVertex("d");
  g.insertVertex("e");
  g.insertVertex("f");
  g.insertVertex("g");
  g.insertVertex("h");

  g.insertEdge("a", "b");
  g.insertEdge("b", "a");
  g.insertEdge("a", "h");
  g.insertEdge("b", "g");
  g.insertEdge("a", "f");
  g.insertEdge("b", "f");
  g.insertEdge("f", "b");
  g.insertEdge("f", "c");
  g.removeVertex("f");

  
  REQUIRE(g.size() == 7);
  REQUIRE(g.edges() == 4);
}