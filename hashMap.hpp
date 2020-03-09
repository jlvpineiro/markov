#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_

#include "hashNode.hpp"

#include <string>

using namespace std;

class hashMap {
  friend class markov;
  hashNode **map; //a single dimensional dynamically allocated array of pointers to hashNodes
  string first; // for first keyword for printing to a file
  int numKeys;
  int mapSize;
  bool h1; 
  bool c1; 
  int collisionct1; 
  int collisionct2; 
public:
  hashMap(bool hash1, bool coll1); 
  void addKeyValue(string k, string v); 
  int getIndex(string k); 
  int calcHash(string k); 
  int calcHash2(string k); 
  void getClosestPrime(); 
  void reHash(); 
  int collHash1(int h, int i, string k); 
  int collHash2(int h, int i, string k); 
  int findKey(string k); 
  string randFirst(); 
  void printMap(); 
};

#endif /* HASHMAP_HPP_ */
