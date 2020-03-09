#ifndef MARKOV_HPP_
#define MARKOV_HPP_

#include "hashMap.hpp"
#include <iostream>

using namespace std;

class markov {
  hashMap *ht;
  string fn; // file name for input
  string newfile; // name of output file
public:
  markov(string file,string newf,bool h1, bool c1);
  void readFile();
  void writeFile(int numTweets);
};

#endif /* MARKOV_HPP_ */
