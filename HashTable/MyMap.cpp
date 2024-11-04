#include "MyMap.hpp"


template<typename K, typename V> 
MyMap<K , V>::MyMap()
{
  capacity = DEFAULT_INITIAL_CAPACITY;
  table = new vector<Entry <K , V> >[capacity];
  loadFactorThreshold = DEFAULT_MAX_LOAD_FACTOR;
  size = 0;
}
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
  if(initialCapacity > MAXIMUM_CAPACITY)
    capacity = MAXIMUM_CAPACITY;
   else
     capacity = trimToPowerOf2(initialCapacity);

     this->loadFactorThreshold = loadFactorThreshold;
     table = new vector< Entry<K , V> >[capacity];
     size = 0; 
}

template<typename K, typename V> 
V MyMap<K , V>::put(const K& key, const V& value)
{
 if(containsKey(key)) // Test if key is in the map
 {// The key is already in the map. Update the value for the key.
  int bucketIndex = hash(hashCode(key));
  for(Entry<K, V>& entry : table[bucketIndex])
  {
    if(entry.key == key) // Test if the key is already in the map
    {
      V oldValue = entry.value;
      //Replace old value with new value
      entry.value = value;
      //Return the old value for the key
      return oldValue;
    }
  }
 }

 // Check load factor
 if(size >= capacity*loadFactorThreshold)
 {
  if(capacity == MAXIMUM_CAPACITY)
   throw runtime_error("Exceeding maximum capacity");

   rehash();
 }

 int bucketIndex = hash(hashCode(key)); // Hash key to an index
 
 // Add a new entry (key, value) to hashTable[index]
 table[bucketIndex].push_back(Entry<K , V>(key, value));

 size++; // Increase size
 return value;
}

template<typename K, typename V> V&
MyMap<K , V>::get(const K& key) const
{
  int bucketIndex = hash(hashCode(key));
  for(Entry<K, V>& entry : table[bucketIndex])
  {
    if(entry.key == key)
      return entry.value; // Return the value for the key
  }
  throw runtime_error("Key not found");
}

template<typename K, typename V> 
bool MyMap<K , V>::isEmpty() const
{
  return size == 0;
}

template<typename K, typename V> 
vector<Entry< K, V> > MyMap<K , V>::getEntries() const
{
  vector<Entry<K, V> > v;
  for(int i = 0; i < capacity; i++)
  {
    for(Entry<K, V>& entry : table[i])
     v.push_back(entry);
  }

  return v;
}
template<typename K, typename V> 
bool MyMap<K , V>::containsKey(const K& key) const
{
  try
  {
    get(key);
    return true;
  }
  catch(runtime_error& exception)
  {
    return false;
  }
  
}

template<typename K, typename V> 
bool MyMap<K , V>::containsValue(const V& value) const 
{
  for(int i = 0; i < capacity; i++)
  {
    for(Entry<K, V> entry : table[i])
     if(entry.value == value)
       return true;
  }
  return false;
}

template<typename K, typename V> 
void MyMap<K , V>::remove(const K& key)
{
  int bucketIndex = hash(hashCode(key));
  
  // Remove the entry that matches the key from the a bucket
  if(table[bucketIndex].size() > 0)
  {
    for(auto p = table[bucketIndex].begin(); p != table[bucketIndex].end(); p++)
    {
      if(p->key == key)
      {
      table[bucketIndex].erase(p);
      size--; // Decrease size
      break;// No need to continue in the loop
      }
    }
  }
}

template<typename K, typename V> 
void MyMap<K , V>::clear()
{
  size = 0;
  removeEntries();
}

template<typename K, typename V> 
void MyMap<K , V>::removeEntries ()
{
  for(int i = 0; i < capacity; i++)
  {
    table[i].clear();
  }
}

template<typename K, typename V> 
vector<K> MyMap<K , V>::getKeys() const
{
  vector<K> keys;
  for(int i = 0; i < capacity; i++)
  {
    keys.push_back(table[i].key);
  }

  return keys;
}


template<typename K, typename V> 
vector<V> MyMap<K , V>::getValues() const
{
  vector<V> values;
  for(int i = 0; i < capacity; i++)
  {
    for(Entry<K, V> entry : table[i])
    {
      values.push_back(entry.value);
    }
  }
}

template<typename K, typename V> 
string MyMap<K , V>::toString() const
{
  stringstream ss;
  ss << "[";
  for(int i = 0; i < capacity; i++)
  {
    for(Entry<K, V>& entry : table[i])
     ss << entry.toString();
  }

  ss << "]";
  return ss.str();
}

template<typename K, typename V> 
unsigned MyMap<K , V>::hashCode (const K& key) const
{
  return std::hash<K>(key);
}

template<typename K, typename V> 
int MyMap<K , V>::hash(int hashCode) const
{
  return supplementalHash(hashCode) & (capacity-1);
}

template<typename K, typename V> 
int MyMap<K , V>::supplementalHash(int h) const
{
  h ^= (h >> 20) ^ (h >> 12);
  return h ^ (h >> 7) ^ (h >> 4);
}

template<typename K, typename V> 
int MyMap<K , V>::trimToPowerOf2 (int initialCapacity)
{
  int capacity = 1;
  while(capacity < initialCapacity)
  {
    capacity <<=1;
  }
  return capacity;
}

template<typename K, typename V> 
void MyMap<K , V>::rehash() 
{
  vector<Entry<K, V> set = getEntries(); 
  capacity <<=1; // Double capacity
  delete[] table;// Delete old hash table 
  table = new vector<Entry<K, V> >[capacity]; // Create a new hash table 
  size = 0; // Reset size to 0

  for(Entry<K, V>& entry : set)
  {
    put(entry.key, entry.value); // Store to new table
  }
}

template<typename K, typename V> 
int MyMap<K , V>::getSize() const
{
  return size;
}