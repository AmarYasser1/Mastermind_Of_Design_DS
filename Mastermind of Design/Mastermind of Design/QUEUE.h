#pragma
#include "Stack.h"
#include <utility>
template<typename T>
struct stackNode {
	int id = 0;
	string name = "";
	Stack<T> stack;
	stackNode<T>* next;

	stackNode() : next(nullptr) {}
	stackNode(const stackNode<T>& other) : stack(other.stack), next(nullptr) {}
};

template<typename T>
class QUEUE {
	stackNode<T>* front;
	stackNode<T>* rear;
	size_t SIZE;
	size_t added_element;

public:
	QUEUE(size_t size = 3);
	~QUEUE();

	int size();
	int max_size();
	bool isEmpty();
	bool isFull();
	pair<bool, int> checkEmptyStack();

	void resize();

	void push(const T& value, bool makeNewNode = false);
	void push(stackNode<T>* node);

	T& pop_element();
	void pop();

	void delete_node(int idx);

	stackNode<T>* Front();

	stackNode<T>* find(int idx);

	void debug_verify_data_integrity();

	void print();

	stackNode<T>* disconnectNode();
};


template<typename T>
QUEUE<T>::QUEUE(size_t size) : front(nullptr), rear(nullptr), SIZE(size), added_element(0) {}
template<typename T>
QUEUE<T>::~QUEUE() {
	while (front) {
		stackNode<T>* temp = front;
		front = front->next;
		delete temp;
	}
}

template<typename T>
int QUEUE<T>::size() { return added_element; }
template<typename T>
int QUEUE<T>::max_size() { return SIZE; }
template<typename T>
bool QUEUE<T>::isEmpty() { return !front && !rear && !added_element; }
template<typename T>
bool QUEUE<T>::isFull() { return added_element == SIZE; }

template<typename T>
pair<bool ,int> QUEUE<T>::checkEmptyStack() {
	pair<bool, int> check;
	check = make_pair(front->stack.isEmpty() , front->id);

	// To remove this empty if exist
	resize();

	return check; 
}

template<typename T>
void QUEUE<T>::resize() {

	if (!front) {
		rear = front;
		return;
	}

	if (front->stack.isEmpty()) {
		stackNode<T>* temp = front;

		front = front->next;
		delete temp;

		--added_element;
	}

	if (!front)
		rear = front;

	debug_verify_data_integrity();
}

template<typename T>
void QUEUE<T>::push(const T& value, bool makeNewNode) {
	assert(!isFull());

	// The first node
	if (isEmpty()) {
		stackNode<T>* temp = new stackNode<T>();
		temp->stack.push(value);

		rear = front = temp;
		rear->next = nullptr;

		++added_element;
	}
	else {

		if (!rear->stack.isFull() && !makeNewNode) {
			rear->stack.push(value);
		}
		else {
			stackNode<T>* temp = new stackNode<T>();
			temp->stack.push(value);

			rear->next = temp;
			rear = temp;
			rear->next = nullptr;

			++added_element;
		}
	}

	debug_verify_data_integrity();
}
template<typename T>
void QUEUE<T>::push(stackNode<T>* node) {
	assert(!isFull());

	if (isEmpty()) {
		rear = front = node;
		rear->next = nullptr;
		++added_element;

		return;
	}

	rear->next = node;
	rear = node;
	rear->next = nullptr;

	++added_element;

	debug_verify_data_integrity();
}

template<typename T>
T& QUEUE<T>::pop_element() {
	assert(!isEmpty());
	debug_verify_data_integrity();

	T value = front->stack.pop();

	// Resize
	resize();

	return value;
}
template<typename T>
void QUEUE<T>::pop() {
	assert(!isEmpty());
	debug_verify_data_integrity();

	stackNode<T>* temp = front;
	front = front->next;
	delete temp;
	--added_element;

	// Resize
	resize();
}

template<typename T>
void QUEUE<T>::delete_node(int idx) {
	assert(!isEmpty());
	assert(idx >= 1 && idx <= added_element);


	if (idx == 1) {
		stackNode<T>* temp = front;

		if (added_element == 1) {
			front = rear = nullptr;
		}
		else if (added_element > 1) {
			front = front->next;
		}

		delete temp;
		--added_element;
		return;
	}

	stackNode<T>* prv = front;
	stackNode<T>* cur = front->next;

	idx -= 1;

	while (--idx) {
		prv = cur;
		cur = cur->next;
	}

	prv->next = cur->next;
	bool is_rear = cur == rear;

	if (is_rear)
		rear = prv;

	delete cur;
	--added_element;

	resize();

	debug_verify_data_integrity();
}

template<typename T>
stackNode<T>* QUEUE<T>::Front() {
	assert(!isEmpty());

	return front;
}

template<typename T>
stackNode<T>* QUEUE<T>::find(int idx) {
	assert(!isEmpty());
	assert(idx >= 1 && idx <= added_element);

	stackNode<T>* temp = front;
	while (--idx)
		temp = temp->next;

	return temp;
}

template<typename T>
void QUEUE<T>::debug_verify_data_integrity() {
	// To check if exist any flaw in this code
	if (!added_element) {
		assert(front == nullptr);
		assert(rear  == nullptr);
	}
	else {
		assert(front != nullptr);
		assert(rear  != nullptr);

		if (added_element == 1) {
			assert(front == rear);
		}
		else {
			assert(front != rear);
		}

		assert(rear->next == nullptr);
	}
}

template<typename T>
void QUEUE<T>::print() {

	stackNode<T>* cur = front;
	while (cur) {
		cur->stack.print();
		cur = cur->next;
	}

	cout << endl;
}

template<typename T>
stackNode<T>* QUEUE<T>::disconnectNode() {
	assert(!isEmpty());

	stackNode<T>* temp = front;
	front = front->next;
	temp->next = nullptr;
	--added_element;

	// optimization
	resize();

	return temp;
}