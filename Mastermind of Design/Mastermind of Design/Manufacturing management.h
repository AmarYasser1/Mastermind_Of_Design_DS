#pragma
#include "linkedList.h"
#include<string>
#include<ctime>
class Manufacturing_management {
	linkedList<string> ls;
public:
	static int count;

	Manufacturing_management();

	void add_product();

	void delete_product();

	void search_product();

	void production_all_product();
};