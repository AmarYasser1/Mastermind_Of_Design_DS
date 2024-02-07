#include "Manufacturing management.h"
Manufacturing_management::Manufacturing_management() { }
int Manufacturing_management::count = 1;

void Manufacturing_management::add_product() {
	system("cls");
	string Name;
	
	cout << "What is the name of the product ? ";
	cin >> Name;

	stackNode<string>* st = new stackNode<string> ();
	cout << "Enter the step operations of the product : \t\t [ to finish enter (ok) ]";
	for (auto i = 0; i < 37; ++i)
		cout << '\b';

	string s;
	st->name = Name;

	do {
		
		cin >> s;

		if (s != "OK" && s != "ok")
		   st->stack.push(s);

	} while (s != "OK" && s != "ok");

	st->id = count;
	ls.push(st);
	++count;
}

void Manufacturing_management::delete_product() {
	system("cls");

	if (ls.isEmpty()) {
		cout << "-> Not exist any product for deleted ." << endl;
		return;
	}

	int container, idx;
	cout << "Enter the container of this product : ";
	cin >> container;

	if (container > ls.size() || container < 0) {
		cout << "-> Invalid container ." << endl;
		return;
	}

	cout << "Enter the idx of the product : ";
	cin >> idx;

	if (idx > ls.find(container)->queue.size() || idx < 0) {
		cout << "-> Invalid idx ." << endl;
		return;
	}

	int id = ls.find(container)->queue.find(idx)->id;

	ls.find(container)->queue.delete_node(idx);

	cout << "==> The product [" << id << "] deleted successfully ." << endl;
}

void Manufacturing_management::search_product() {
	system("cls");

	if (ls.isEmpty()) {
		cout << "-> Not exist any products ." << endl;
		return;
	}

	int container, idx;
	cout << "Enter the container of this product : ";
	cin >> container;

	if (container > ls.size() || container < 0) {
		cout << "-> Invalid container ." << endl;
		return;
	}

	cout << "Enter the idx of the product : ";
	cin >> idx;

	if (idx > ls.find(container)->queue.size() || idx < 0) {
		cout << "-> Invalid idx ." << endl;
		return;
	}

	cout << "\n- The name of the product  : " << ls.find(container)->queue.find(idx)->name << endl;
	cout << "- The id of the product : " << ls.find(container)->queue.find(idx)->id << endl;
	cout << "The step operations" << endl;
	cout << "*******************" << endl;
	ls.find(container)->queue.find(idx)->stack.print();
}

void Manufacturing_management::production_all_product() {
	system("cls");

	if (ls.isEmpty()) {
		cout << "-> Not exist any product for production ." << endl;
		return;
	}

	// Lambada function
	auto delay = [&](int milliseconds)-> void {
		clock_t start_time = clock();

		while ((clock() - start_time) / CLOCKS_PER_SEC * 1000 < milliseconds);
	};

	while (!ls.isEmpty()) {
		ls.front()->queue.Front()->stack.pop();
		
		pair<bool, int> check = ls.front()->queue.checkEmptyStack();
		if (check.first) {
			delay(300);
			cout << "Product [" << check.second << "] is completed" << endl;
		}

	}

	delay(300);
	cout << "*|| All products are producted ||*" << endl;
}