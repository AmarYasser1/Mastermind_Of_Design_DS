#pragma
#include<iostream>
#include<cassert>
using namespace std;
template<typename T>
class Stack {
	size_t size{ };
	T* arr{ nullptr };
	int Top;
public:
	Stack(size_t size = 3);
	~Stack();

	bool isEmpty();
	bool isFull();

	void push(const T& value);
	T& pop();
	T& top();

	void resize();
	int getSize();
	int max_size();
	void clear();

	void print();
};

template<typename T>
Stack<T>::Stack<T>(size_t size) : size(size), Top(-1), arr(new T[size]) {} 
template<typename T>
Stack<T>::~Stack<T>() { delete[]arr; }
template<typename T>
bool Stack<T>::isEmpty() { return Top == -1; }
template<typename T>
bool Stack<T>::isFull() { return Top == size - 1; }
template<typename T>
void Stack<T>::push(const T& value) {
	//assert(!isFull());
	if (isFull())
		resize();

	arr[++Top] = value;
}
template<typename T>
T& Stack<T>::pop() {
	assert(!isEmpty());
	
	return arr[Top--];
}
template<typename T>
T& Stack<T>::top() {
	assert(!isEmpty());

	return arr[Top];
}
template<typename T>
void Stack<T>::resize() {
	int newSize = 2 * size;
	size_t new_size = std::max(2, newSize);
	T* temp = new T[new_size];

	copy(arr, arr + size, temp);

	delete[] arr;
	arr = temp;
	size = new_size;
}
template<typename T>
int Stack<T>::getSize() { return Top + 1; }
template<typename T>
int Stack<T>::max_size() { return size; }
template<typename T>
void Stack<T>::clear() { Top = -1; }
template<typename T>
void Stack<T>::print() {
	assert(!isEmpty());

	for (auto i = Top; i >= 0; --i)
		cout << '*' << arr[i] << endl;

	cout << endl;
}