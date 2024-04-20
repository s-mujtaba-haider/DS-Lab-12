#include<iostream>
using namespace std;
template <class V>
class HashItem {
public:
	V value;
	int key;
	string name;
	HashItem(int key, V value,string name)
	{
		this->value = value;
		this->key = key;
		this->name = name;
	}
};
template <typename V>
class HashMap {
protected:
	HashItem<V>** arr;
	int capacity;
	int size;
	HashItem<V>* dummy;
protected:
	virtual int hashCode(int key)
	{
		return key % capacity;
	}
public:
	HashMap(){
		capacity = 20;
		size = 0;
		arr = new HashItem<V>*[capacity];
		for (int i = 0; i < capacity; i++)
			arr[i] = NULL;
		dummy = new HashItem<V>(-1, -1," ");
	}
	void insertNode(int key, V value,string name)
	{
		HashItem<V>* temp = new HashItem<V>(key, value, name);
		int hashIndex = hashCode(key);
		while (arr[hashIndex] != NULL
			&& arr[hashIndex]->key != key
			&& arr[hashIndex]->key != -1) {
			hashIndex++;
			hashIndex %= capacity;
		}
		if (arr[hashIndex] == NULL
			|| arr[hashIndex]->key == -1)
			size++;
		arr[hashIndex] = temp;
	}
	V deleteNode(int key) {
		int hashIndex = hashCode(key);
		while (arr[hashIndex] != NULL) {
			if (arr[hashIndex]->key == key) {
				HashItem<V>* temp = arr[hashIndex];
				arr[hashIndex] = dummy;
				size--;
				return temp->value;
			}
			hashIndex++;
			hashIndex %= capacity;
		}
		return -1;
	}
	V get(int key){
		int hashIndex = hashCode(key);
		int counter = 0;
		while (arr[hashIndex] != NULL) {

			if (counter++ > capacity)
				return NULL;
			if (arr[hashIndex]->key == key)
				return arr[hashIndex]->value;
			hashIndex++;
			hashIndex %= capacity;
		}
		return -1;
	}
	int sizeofMap()
	{
		return size;
	}
	void isEmpty()
	{
		if (size == 0) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	void display(){
		cout << "Key\tValue\t  Name" << endl;
		for (int i = 0; i < capacity; i++) {
			if (arr[i] != NULL && arr[i]->key != -1)
				cout << " " << arr[i]->key << "   ->   "
				<< arr[i]->value << "  ->  " << arr[i]->name << endl;
		}
		cout << endl;
	}
};
void printArray(int arr[], int n){
	cout << "Key\tValue" << endl;
	for (int i = 0; i < n; i++) {
		cout << " " << i << "  ->   " << arr[i] << endl;
	}
}
void hashing(int table[], int tsize, int arr[], int N){

	for (int i = 0; i < N; i++) {
		int hv = arr[i] % tsize;
		if (table[hv] == -1)
			table[hv] = arr[i];
		else {
			for (int j = 0; j < tsize; j++) {
				int t = (hv + j * j) % tsize;
				if (table[t] == -1) {
					table[t] = arr[i];
					break;
				}
			}
		}
	}
	printArray(table, N);
}
int main()
{
	cout << "Linear Probing" << endl << endl;
	HashMap<int>* h = new HashMap<int>;
	h->insertNode(1, 3, "Mujtaba");
	h->insertNode(2, 6, "Ali");
	h->insertNode(3, 8, "Kamran");
	h->insertNode(4, 9, "Jazib");
	h->insertNode(5, 2, "Salman");
	h->insertNode(7, 4, "Khurram");
	h->display();
	cout << "Size of Map : " << h->sizeofMap() << endl << endl;
	int a = 3;
	cout << "Delete " << a << " Node : Value at Node " << a << " is " << h->deleteNode(a) << endl << endl;
	h->display();
	int k = 8;
	cout << "Delete " << k << " Node : Value at Node " << k << " is " << h->deleteNode(k) << endl << endl;
	h->display();
	cout << "Size of Map : " << h->sizeofMap() << endl << endl;
	cout << "Is Empty : ";
	h->isEmpty();
	cout << endl;
	int i = 4;
	cout << "Find value at Node " << i << " : Value at Node " << i << " is " << h->get(i) << endl << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "Quadratic Probing" << endl << endl;;
	int arr[] = { 50, 700, 76, 85, 92, 73, 101 };
	int N = 7;
	int L = 7;
	int hash_table[7];
	for (int i = 0; i < L; i++) {
		hash_table[i] = -1;
	}
	hashing(hash_table, L, arr, N);
	cout << endl;
	return 0;
}
