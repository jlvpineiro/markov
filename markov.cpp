#include "markov.hpp"
#include "hashMap.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

markov::markov(string f1,string f2,bool h1, bool c1) {
  ht = new hashMap(h1,c1);
  newfile = f2;
  fn = f1;
  readFile();
  //writeFile();
}

void markov::readFile() {
  ifstream infile(fn.c_str(),ios::in); // open file
  string key = "";
  string value= "";
  infile>> key;
  ht->first = key;
  while (infile >> value) {
    // loop getting single characters
    if (ispunct(value[value.length()-1])) {
      string value2 = value.substr(value.length()-1,1);//value[value.length()-1];
      value.pop_back();
      cout << key <<": " << value << endl;
      ht->addKeyValue(key,value);
      key = value;
      value = value2;
    }
    cout << key <<": " << value << endl;
    ht->addKeyValue(key,value);
    key = value;
    value = "";
  }
  ht->addKeyValue(key,value);
  cout << endl;
  infile.close();
}

void markov::writeFile(int numTweets) {
  ofstream outfile(newfile.c_str(),ios::out);
  for (int i=0; i<numTweets; i++) {
    string firstWord = ht->randFirst();
    outfile << firstWord;
    //outfile << ht->first << " ";
    int ct = firstWord.length();
    string key = "";
    string value = ht->map[ht->getIndex(firstWord)]->getRandValue();
    int len = 0;
    while (ct + value.length()+1 < 280) { // && value != "") {
      cout << ct << endl;
      key = value;
      if (key.length() > 1 || !ispunct(key[0])) {
        outfile << " ";
        ct++;
      }
      outfile << key;
      cout << value << " ";
      //if (len == 11) {
        //outfile << "\n";
        //len = 0;}
      //else len++;
      ct += value.length();
      cout << value.length() << endl;
      value = ht->map[ht->getIndex(key)]->getRandValue();
    }
    outfile << "\n\n\n";
  }
  outfile.close();
}
