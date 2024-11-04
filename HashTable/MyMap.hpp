#ifndef MYMAP_H
#define MYMAP_H
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;


int DEFAULT_INITIAL_CAPACITY = 4;
float DEFAULT_MAX_LOAD_FACTOR = 0.75f;
unsigned MAXIMUM_CAPACITY = 1 << 30;

template<typename K, typename V>
class Entry
{
  public:
    Entry(const K& key, const V& value)
    {
      this->key = key;
      this->value = value;
    }

    string toString() const 
    {
      stringstream ss;
      ss << "[" << key << " " << value << "]";
    }

    K key;
    V value;
};

template<typename K, typename V>
class MyMap
{
  public:
  MyMap();
  MyMap(int initialCapacity);
  MyMap(int initialCapacity, float loadFactorThreshold);

  V put(const K& key, const V& Value);
  V& get(const K& key) const;
  int getSize() const;
  bool isEmpty() const;
  vector<K> getKeys() const;
  vector<V> getValues() const;
  string toString() const;
  bool containsKey(const K& key) const;
  bool containValue(const V& value) const;
  void remove(const K& key);
  void clear();

  private:
  int size;
  float loadFactorThreshold;
  int capacity;

  // Hash table is an array with each cell as a vector
  vector<Entry<K, V> >* table; // table is a pointer to the array

  int hash(int hashCode) const;
  unsigned hashCode(const K& key) const;
  int supplementalHash(int h) const;
  int trimToPowerOf2(int initialCapacity);
  void rehash();
  void removeEntries();
};

#endif