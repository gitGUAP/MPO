#pragma once
#include <string>

template <typename V> class HashNode {
public:
  HashNode(const std::string &key, const V &value) : key(key), value(value) {}

  std::string getKey() const { return key; }
  V getValue() const { return value; }
  void setValue(V val) { HashNode::value = val; }

private:
  std::string key;
  V value;
};
