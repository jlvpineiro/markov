#include "markov.hpp"
#include "hashMap.hpp"
#include "hashNode.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, char** argv) {

  //seed random number generator
  srand(time(NULL));

  string infile;
  string outfile;
  int numTweets;

  switch (argc) {
    case 4:
      infile = argv[1];
      outfile = argv[2];
      numTweets = atoi(argv[3]);
      break;
    case 3:
      infile = argv[1];
      outfile = argv[2];
      numTweets = 8;
      break;
    case 2:
      infile = argv[1];
      outfile = "tweets.txt";
      numTweets = 8;
      break;
    default:
      infile = "sample.txt";
      outfile = "tweets.txt";
      numTweets = 8;
  }

  //hash 1, coll1
  markov *m = new markov(infile,outfile,true,true);

  m->writeFile(numTweets);

  return 0;
}
