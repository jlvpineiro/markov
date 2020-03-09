#ifndef HASHNODE_HPP_
#define HASHNODE_HPP_

#include <string> 

using namespace std;

class hashNode {
  friend class hashMap;
  string keyword; 
  string *values; 
  int valuesSize; // the size of the values array 
  int currSize;   // the number of words in the values array so far
public:
  hashNode(); //constructor-initializes keyword to “” , valuesSize to 0, and 
              // currSize to 0 and values to NULL
  hashNode(string s); 
  hashNode(string s, string v); 
  void addValue(string v); 
  void dblArray(); 
  string getRandValue(); 
};

#endif /* HASHNODE_HPP_ */
