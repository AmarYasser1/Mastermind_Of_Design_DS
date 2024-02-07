#pragma
#include "QUEUE.h"

template<typename T>
struct queueNode {
	QUEUE<T> queue;
	queueNode* next;

	queueNode() :next(nullptr) {}
};

template<typename T>
class linkedList {
	queueNode<T>* head;
	queueNode<T>* tail;
	int length;

public:
	linkedList();
	~linkedList();

	bool isEmpty();
	int size();

	void delete_tail_node();

	void RESIZE();

	void push(const T& value , bool newNode = false);
	void push(stackNode<T>* node);

	void pop();

	queueNode<T>* find(int idx);

	queueNode<T>* front();

	void print();

	void debug_verify_data_integrity();
};

template<typename T>
linkedList<T>::linkedList() : head(nullptr), tail(nullptr), length(0) {}
template<typename T>
linkedList<T>::~linkedList() {
	while (head) {
		queueNode<T>* temp = head;
		head = head->next;
		delete temp;
	}
}

template<typename T>
bool linkedList<T>::isEmpty() { return (!head && !tail && !length) || !size(); }
template<typename T>
int linkedList<T>::size() { return tail && tail->queue.isEmpty() ? length - 1 : length; }

template<typename T>
void linkedList<T>::delete_tail_node() {
	assert(!isEmpty());

	queueNode<T>* cur = head;

	while (cur->next != tail && cur->next)
		cur = cur->next;

	if (!cur->next) {
		queueNode<T>* temp = head;

		head = tail = nullptr;
		delete temp;
		--length;
		return;
	}

	queueNode<T>* temp = tail;
	tail = cur;
	tail->next = nullptr;
	delete temp;
	--length;
}

template<typename T>
void linkedList<T>::RESIZE() {

	// Shift one product only for each sub-linked list
	if (head != tail) {
		queueNode<T>* Prv = head;
		queueNode<T>* Next = head->next;

		while (Prv->queue.isFull() && Next && Prv != tail)
			Prv = Prv->next, Next = Next->next;

		while (!Prv->queue.isFull() && Next && Prv != tail) { // disconnect one product to connect with prev
			Prv->queue.push(Next->queue.disconnectNode());
			Prv  = Prv->next;
			Next = Next->next;
		}
	}


	if (tail->queue.isEmpty())
		delete_tail_node();

	debug_verify_data_integrity();
}

template<typename T>
void linkedList<T>::push(const T& value , bool newNode) {

	if (isEmpty()) {
		queueNode<T>* temp = new queueNode<T>();
		temp->queue.push(value);

		head = tail = temp;
		tail->next = nullptr;
		length = 0;
		++length;
		return;
	}

	RESIZE();

	if (!tail->queue.isFull()) {
		tail->queue.push(value , newNode);
	}
	else {
		queueNode<T>* temp = new queueNode<T>();
		temp->queue.push(value, newNode);

		tail->next = temp;
		tail = temp;
		tail->next = nullptr;
		++length;
	}

	debug_verify_data_integrity();
}

template<typename T>
void linkedList<T>::push(stackNode<T>* node) {
	
	if (isEmpty()) {
		queueNode<T>* temp = new queueNode<T>();
		temp->queue.push(node);

		tail = head = temp;
		tail->next = nullptr;
		length = 0;
		++length;
		return;
	}

	RESIZE();

	if (!tail->queue.isFull()) {
		tail->queue.push(node);
	}
	else {
		queueNode<T>* temp = new queueNode<T>();
		temp->queue.push(node);

		tail->next = temp;
		tail = temp;
		tail->next = nullptr;
		++length;
	}

	debug_verify_data_integrity();
}

template<typename T>
void linkedList<T>::pop() {
	RESIZE();
	assert(!isEmpty());

	if (head)
		head->queue.pop();

	debug_verify_data_integrity();
}

template<typename T>
queueNode<T>* linkedList<T>::find(int idx) {
	RESIZE();
	assert(!isEmpty());
	assert(idx >= 1 && idx <= length);

	queueNode<T>* temp = head;
	while (--idx)
		temp = temp->next;

	return temp;
}

template<typename T>
queueNode<T>* linkedList<T>::front() {
	RESIZE();
	assert(!isEmpty());

	return head;
}

template<typename T>
void linkedList<T>::print() {
	assert(!isEmpty());
	RESIZE();

	queueNode<T>* cur = head;
	while (cur) {
		cur->queue.print();
		cur = cur->next;
	}
}

template<typename T>
void linkedList<T>::debug_verify_data_integrity() {
	if (!length) {
		assert(head == nullptr);
		assert(tail == nullptr);
	}
	else {
		assert(head != nullptr);
		assert(tail != nullptr);

		if (length == 1)
			assert(head == tail);
		else
			assert(head != tail);

		assert(tail->next == nullptr);
	}
}