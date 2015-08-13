/*

Least Recently used  algorithm
*/


/*

Least Recently Used (LRU) is a family of caching algorithms, which discards the
least recently used items first. This algorithm requires keeping track of when
the item was used, which is expensive if one wants to make sure the algorithm
always discards the least recently used item.

*/



/*

Data structures used

The key data structure of the algorithm is the combination 
of Hash Map and Doubly-Linked List. We initialize a Hash Map 
in a pre-defined size to store pairs, and use Doubly-Linked 
List to index the pairs in the order of data age.

*/




/* 

Declare an array of LRUCacheEntry objects 
and store them in a vector

Declare a hashmap with key as Key and value as a LRUCacheEntry object.
*/


 

using namespace std;
using namespace stdext;

template<class K, class T>
struct LRUCacheEntry
{
	K key;
	T data;
	LRUCacheEntry* prev;
	LRUCacheEntry* next;
};

template<class K, class T>
class LRUCache
{
private:
	hash_map< K, LRUCacheEntry<K,T>* >	_mapping;
	vector< LRUCacheEntry<K,T>* >		_freeEntries;
	LRUCacheEntry<K,T> *			head;
	LRUCacheEntry<K,T> *			tail;
	LRUCacheEntry<K,T> *			entries;
public:
	LRUCache(size_t size){
		entries = new LRUCacheEntry<K,T>[size];
		for (int i=0; i<size; i++)
			_freeEntries.push_back(entries+i);
		head = new LRUCacheEntry<K,T>;
		tail = new LRUCacheEntry<K,T>;
		head->prev = NULL;
		head->next = tail;
		tail->next = NULL;
		tail->prev = head;
	}
	~LRUCache()
	{
		delete head;
		delete tail;
		delete [] entries;
	}


/* 

Put operation

1. Check the hashmap whether the key already exists. If it already exists, retrieve the 
   LRUCacheObject, modify the data and put it at the head of the doubly linked list.
2. If it does not exist, then check the vector size.
	-If vector size is empty, then this means we have used all the LRUCache objects.
	 Get the tail of the linkedlist, change the key and data and put it to the head of the linkedlist.
	 Add the new key entry to the hash table.
	-If the vector size is not empty, then remove a node from the vector. Change the key and the value 
	 of the node and insert it to the head of the linked list. Add the new key entry to the hash table.

*/
	void put(K key, T data)
	{
		LRUCacheEntry<K,T>* node = _mapping[key];
		if(node)
		{
			// refresh the link list
			detach(node);
			node->data = data;
			attach(node);
		}
		else{
			if ( _freeEntries.empty() )
			{
				node = tail->prev;
				detach(node);
				_mapping.erase(node->key);
				node->data = data;
				node->key = key;
				_mapping[key] = node;
				attach(node);
			}
			else{
				node = _freeEntries.back();
				_freeEntries.pop_back();
				node->key = key;
				node->data = data;
				_mapping[key] = node;
				attach(node);
			}
		}
	}




/*

Search the hash table for the node that corresponds to the key.
If there is a match, then return the data.
else return NULL

*/


	T get(K key)
	{
		LRUCacheEntry<K,T>* node = _mapping[key];
		if(node)
		{
			detach(node);
			attach(node);
			return node->data;
		}
		else return NULL;
	}

private:
	void detach(LRUCacheEntry<K,T>* node)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	void attach(LRUCacheEntry<K,T>* node)
	{
		node->next = head->next;
		node->prev = head;
		head->next = node;
		node->next->prev = node;
	}
};
