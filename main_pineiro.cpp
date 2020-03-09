#include "markov.hpp"
#include "hashMap.hpp"
#include "hashNode.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

int main() {

  //seed random number generator
  srand(time(NULL));

  string infile = "nk";
  int numTweets = 1;

  //hash 1, coll1
  markov *m = new markov(infile,"tweets.txt",true,true);

  m->writeFile(8);

  return 0;
}
