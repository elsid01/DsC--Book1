#include "MyMap.hpp"

template<typename K, typename V> 
MyMap<K , V>::MyMap(int initialCapacity)
{
  capacity = initialCapacity;
  table = new vector<Entry<K, V> > [capacity];
  loadFactorThreshold = DEFAULT_MAX_LOAD_FACTOR;
  size = 0;
}

template<typename K, typename V> 
MyMap<K , V>::MyMap(int initialCapacity, float loadFactorThreshold)
{
  
}