/* Jared Pineiro
* 3/9/2020
* This file contains function definitions for the hashMap class
*/
#include "hashMap.hpp"
#include "hashNode.hpp"

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

int nextPrime(int n);
int prevPrime(int n);
bool isPrime(int n);

hashMap::hashMap(bool hash1, bool coll1) {
  mapSize = 23;
  numKeys = 0;
  collisionct1 = 0;
  collisionct2 = 0;
  h1 = hash1;
  c1 = coll1;
  map = new hashNode*[mapSize];
  first = "";
  for (int i = 0; i < mapSize; i++) {
    map[i] = NULL;
  }
}

void hashMap::addKeyValue(string k, string v) {
  int idx = getIndex(k);
  int i = 0;
  bool collide = false;
  while (map[idx] != NULL && map[idx]->keyword != k) {

    collide = true;
    collisionct2++;
    i++;
    if (c1) {
      idx = collHash1(idx,i,k);
    }
    else {
      idx = collHash2(idx,i,k);
    }
  }

  if (collide) {
    collisionct1++;
    collisionct2--; //removes extra collisionct2 increment
  }

  //if there's no node, add new key
  if (map[idx] == NULL) {
    map[idx] = new hashNode(k,v);
    numKeys++;
    if (numKeys == 1) {
      first = k;
    }
  }
  //if the node has the same keyword, add value to keyword
  else if (map[idx]->keyword == k) {
    map[idx]->addValue(v);
  }

  //checks if hashMap is 70% full and rehashes if so
  if ((float) numKeys / mapSize >= 0.7) {
    reHash();
  }
  //cout << collisionct1 << ", " << collisionct2 << endl;
}

int hashMap::getIndex(string k) {
  if (h1) {
    return calcHash(k);
  }
  else {
    return calcHash2(k);
  }
}

int hashMap::calcHash(string k) {
  //this hash function performs a polynomial equation on each letter in the string
  //each letter is treated as the ascii value and multiplied by a prime exponential
  int p = 59; //prime number approximately greater than alphabet size
  unsigned long long hashVal = 0;
  unsigned long long p_pow = 1;
  for (int i=0; i < k.length(); i++) {
    if ((int)k[i] < 0) {
      hashVal += i * p_pow; //rejects negative ascii values
    }
    else {
      hashVal += ((int)k[i]) * p_pow;
    }
    p_pow *= p;
  }
  return hashVal % mapSize;
}

int hashMap::calcHash2(string k) {
  //simply sums up all non-negative ascii values in string
  int hashVal = 0;
  for (int i=0; i < k.length(); i++) {
    if ((int)k[i] < 0) {
      continue;
    }
    hashVal += (int) k[i];
  }
  return hashVal % mapSize;
}

void hashMap::getClosestPrime() {
  mapSize = nextPrime(mapSize*2);
}

void hashMap::reHash() {
  int oldMapSize = mapSize;
  hashNode **oldMap = map;
  getClosestPrime();

  map = new hashNode*[mapSize];

  for (int i = 0; i < mapSize; i++) {
    map[i] = NULL;
  }

  for (int j=0; j < oldMapSize; j++) {
    //adds all non-NULL items from old map to new map, rehashing indices
    if (oldMap[j] != NULL) {
      string k = oldMap[j]->keyword;
      int idx = getIndex(k);
      int i = 0;
      while (map[idx] != NULL) {
        i++;
        if (c1) {
          idx = collHash1(idx,i,k);
        }
        else {
          idx = collHash2(idx,i,k);
        }
      } map[idx] = oldMap[j];
    }
  }
  delete[] oldMap;
}

int hashMap::collHash1(int h, int i, string k) {
  //double hashing collision handler
  int m = prevPrime(mapSize);
  int h0 = getIndex(k);
  int kVal = getIndex(map[h]->keyword);
  int h2 = 1 + (kVal % m);

  return (h0 + i*h2) % mapSize;
}

int hashMap::collHash2(int h, int i, string k) {
  //linear probing collision handler (adds 1, then 2, then 3, etc.)
  return (h + i) % mapSize;
}

int hashMap::findKey(string k) {
  int idx = getIndex(k);
  int i = 0;
  while (map[idx] != NULL && map[idx]->keyword != k) {
    i++;
    if (c1) {
      idx = collHash1(idx,i,k);
    }
    else {
      idx = collHash2(idx,i,k);
    }
  }

  if (map[idx] == NULL) {
    return -1;
  }
  else {
    return idx;
  }
}

string hashMap::randFirst() {
  if (numKeys > 0) {
    int i = rand() % mapSize;
    int orig_ind = i;
    while (map[i] == NULL || islower(map[i]->keyword[0])) {
      i++;
      if (i >= mapSize) {
        i=0;
      }
      if (i == orig_ind) {
        return "";
      }
    }
    return map[i]->keyword;
  }
  else {
    return "";
  }
}



void hashMap::printMap() {
  for (int i=0; i<mapSize; i++) {
    if (map[i] != NULL) {
      cout << map[i]->keyword << ": {";
      for (int j=0; j<map[i]->valuesSize-1; j++) {
        cout << map[i]->values[j] << ", ";
      }
      cout << map[i]->values[map[i]->valuesSize-1] << "}" << endl;
    }
  }
}

int nextPrime(int n) {
  if (n <= 1) {
    return 2;
  }
  else {
    n++;
    while (!isPrime(n)) {
      n++;
    }
  }
  return n;
}

int prevPrime(int n) {
  if (n <= 3) {
    return 2;
  }
  else {
    n--;
    while (!isPrime(n)) {
      n--;
    }
  }
  return n;
}

bool isPrime(int n) {
  for (int i=2; i <= n/2; i++) {
    if (n % i == 0){
      return false;
    }
  }
  return true;
}
