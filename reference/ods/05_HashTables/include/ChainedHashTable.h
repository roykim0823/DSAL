#ifndef CHAINEDHASHTABLE_H_
#define CHAINEDHASHTABLE_H_
#include <climits>
#include <vector>

namespace ods {

template<class T>
class ChainedHashTable {
protected:
	typedef std::vector<T> chain;
	typedef std::vector<chain> hashTable;
	hashTable table;
	long n;	// number of element
	int d;  // size of hash table (1<<d)
	int z;	// an odd random number for hash code
	static const int w = 32; //sizeof(int)*8;

	void allocTable(int m);
	void resize();
	int hash(T x) {
		// Multiplicative hashing (based on modular arithmetic)
		// hash(x) = ( (z*x) mod 2^w) div 2^(w-d) )
		return ((unsigned)(z * x)) >> (w-d);  	// z is odd number
	}

public:
	ChainedHashTable();
	virtual ~ChainedHashTable() {};
	bool add(T x);
	bool remove(T x);
	//bool find(T x);
	int find(T x);
	int size() {
		return n;
	}
	void clear();
};

// TODO(khyunjin):  A copy-constructor for arrays would be useful here
template<class T>
void ChainedHashTable<T>::resize() {
	hashTable newTable;
	newTable.resize(1<<d);
	// std::cout << "resize hashTable to " << (1<<d) << std::endl;

	// Re-hashing with larger hashTable
	for (size_t i=0; i<table.size(); i++) {
		for(size_t j=0; j < table[i].size(); j++) {
			T x = table[i][j];
			newTable[hash(x)].push_back(x);
		}
	}

	table = newTable;	// replace the hashTable
}

template<class T>
ChainedHashTable<T>::ChainedHashTable() {
	n = 0;
	d = 10; // 1K entries (default)
	z = rand() | 1;     // is a random odd integer
	table.resize(1 << d);
}

// Add takes a constant time without resizing
template<class T>
bool ChainedHashTable<T>::add(T x) {
	if (find(x)!=-1) return false;	// if it is already added, then return false
	if (n > ( 1<< (d+1) ) && d<30) {	// n is larger than hashTable size x 2
		d++;
		resize();
	}
	table[hash(x)].push_back(x);
	n++;
	return true;
}

// O(n * hash(x)) time
template<class T>
bool ChainedHashTable<T>::remove(T x) {
	int idx = hash(x);
	// iterate over the list
	for (size_t i = 0; i < table[idx].size(); i++) {
		T y = table[idx][i];
		if (x == y) {
			table[idx].erase(table[idx].begin()+i);	// remove i th element
			n--;
			if( n < (1<<(d-1) )  && d > 10) {
				d--;
				resize();
			}
			return true;
		}
	}
	return false;
}

template<class T>
int ChainedHashTable<T>::find(T x) {
	int idx = hash(x);
	for (size_t i = 0; i < table[idx].size(); i++)
		if (x == table[idx][i])
			return i;
	//return false;
	return -1;
}


template<class T>
void ChainedHashTable<T>::clear() {
	n = 0;
	d = 10;
	z = rand() | 1;     // is a random odd integer
	hashTable newTable;
	newTable.resize(1<<d);
	table = newTable;
}

}  // namespace HKSTL
#endif  // CHAINEDHASHTABLE_H_
