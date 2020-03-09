/* Jared Pineiro
* 3/9/2020
* This file contains function definitions for the hashNode class
*/
#include "hashNode.hpp"

#include <stdlib.h>
#include <string>

using namespace std;

hashNode::hashNode() {
  keyword = "";
  values = NULL;
  valuesSize = 0;
  currSize = 0;
}

hashNode::hashNode(string s) {
  keyword = s;
  valuesSize = 15;
  values = new string[valuesSize];
  currSize = 0;
}

hashNode::hashNode(string s, string v) {
  keyword = s;
  valuesSize = 15;
  values = new string[valuesSize];
  values[0] = v;
  currSize = 1;
}

void hashNode::addValue(string v) {
  values[currSize] = v;
  currSize++;
  if (currSize >= valuesSize) {
    dblArray();
  }
}

void hashNode::dblArray() {
  string* newValues = new string[valuesSize*2];
  for (int i = 0; i < valuesSize; i++) {
    newValues[i] = values[i];
  }
  delete [] values;
  valuesSize *= 2;
  values = newValues;
}

string hashNode::getRandValue() {
  if (currSize > 0) {
    int idx = rand() % currSize;
    return values[idx];
  }
  else {
    return "";
  }
} 
