#pragma once
#include "HashNode.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

template <typename V> class HashMap {
public:
  HashMap(int N) {
    MAP_SIZE = N;
    map = new HashNode<V> *[N];
    exprt = new int[N];
    for (int i = 0; i < N; i++) {
      map[i] = nullptr;
      exprt[i] = 0;
    }
    // Generate prime numbers for h2
    // 2, 3, 5, 7, 11, 13, 17, 19...N
    primes_h2.push_back(2);
    for (int i = 3; i < N; i++) {
      bool prime = true;
      for (int j = 0; j < primes_h2.size() && primes_h2[j] * primes_h2[j] <= i;
           j++) {
        if (i % primes_h2[j] == 0) {
          prime = false;
          break;
        }
      }
      if (prime)
        primes_h2.push_back(i);
    }
  };
  ~HashMap() {
    for (int i = 0; i < N; i++)
      delete map[i];
    delete map;
    delete exprt;
  };
  unsigned int h1(string &key) {
    unsigned int h1 = 0;
    const int p = 37;
    unsigned int p_pow = 1;
    // h(S) = S[0] + S[1] * P + S[2] * P ^ 2 + S[3] * P ^ 3 + ... + S[N] * P^N
    for (size_t i = 0; i < key.length(); i++) {
      h1 += (key[i] - '0' + 1) * p_pow;
      p_pow *= p;
    }
    return h1;
  }
  unsigned int h2(string &key) {
    unsigned int h2 = 0;
    for (size_t i = 0; i < key.length(); i++)
      h2 += key[i] * key[i];
    // Take a random item
    return primes_h2[h2 % primes_h2.size()];
  }
  void put(string key, V value) {
    unsigned int h1 = HashMap::h1(key);
    unsigned int h2 = HashMap::h2(key);
    for (size_t i = 0; i < MAP_SIZE; i++) {
      exprt[h1 % N] += 1;
      if (map[h1 % N] == nullptr) {
        map[h1 % N] = new HashNode<V>(key, value);
        return;
      } else {
        if (map[h1 % N]->getKey() == key)
          map[h1 % N]->setValue(value);
        h1 = (h1 + h2) % N;
      }
    }
    cout << "OVERFLOW" << endl;
  }
  vector<HashNode<V> *> del(string &key) {
    unsigned int h1 = HashMap::h1(key);
    unsigned int h2 = HashMap::h2(key);
    vector<HashNode<V> *> collision;
    for (size_t i = 0; i < MAP_SIZE; i++) {
      if (map[h1 % N]->getKey() == key) {
        delete map[h1 % N];
        map[h1 % N] = nullptr;
        return collision;
      } else {
        collision.push_back(map[h1 % N]);
        h1 = (h1 + h2) % N;
      }
    }
  }
  void excel(string &name) {
    ofstream fout(name);
    for (size_t i = 0; i < MAP_SIZE; i++)
      fout << exprt[i] << endl;
    fout.close();
  }
  void print() {
    cout << endl;
    for (size_t i = 0; i < MAP_SIZE; i++)
      if (map[i] != nullptr)
        cout << i << ": " << map[i]->getKey() << " - " << map[i]->getValue()
             << endl;
  }

private:
  HashNode<V> **map;
  int *exprt;
  int MAP_SIZE;
  vector<int> primes_h2;
};
