#include "StudentArray.h"
#include <iostream>
#include <string>
using namespace std;
StudentArray::StudentArray() {
	length = 0; 
}

Student& StudentArray::operator[] (const int index)
{	
	if (index<0 || index >= length)
		throw out_of_range("Индекс находится за пределами списка");
	else {
		pCurrent = pStart;
		for (int i = 0; i < index; i++)
		{
			pCurrent = pCurrent->next_item;
		}

		return *pCurrent->val;
	}

}

StudentArray::~StudentArray() {
	for (int i = 0; i < length; i++)
	{
		pTemp = pStart->next_item;
		delete pStart->val;
		delete pStart;
		pStart = pTemp;
	}

}

void StudentArray::addItem(Student* value)
{
	pCurrent = new ListItem; 
	pCurrent->val = value; 
	if (!length) 
	{
		pStart = pCurrent;
		pCurrent->previous_item = pCurrent;
		pCurrent->next_item = pCurrent;
		pTemp = pCurrent;
	}

	else 
	{
		pCurrent->previous_item = pTemp;
		pCurrent->next_item = pTemp->next_item;
		pTemp->next_item = pCurrent;
		pTemp = pCurrent;
	}

	length++; 
}

void StudentArray::removeItem(string zach) {
	pCurrent = pStart;
	for (int i = 0; i <= length; i++)
	{
		if (pCurrent->val->_zach->_num == zach) 
		{
			if (i == 0) {
				pStart = pCurrent->next_item;
				pCurrent->next_item->previous_item = nullptr;
			}

			else {
				pCurrent->previous_item->next_item = pCurrent->next_item;
				pCurrent->next_item->previous_item = pCurrent->previous_item;
			}

			delete pCurrent->val;
			delete pCurrent;
			length--;
			return;
		}

		else
			pCurrent = pCurrent->next_item;
	}

}

