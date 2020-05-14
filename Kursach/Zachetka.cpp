#include "Zachetka.h"
#include "Utils.h"
#include <string>
#include <iomanip>
#include "Subj.h"
#include <iostream>
using namespace std;
Zachetka::Zachetka(string num) {
	_num = num;
}

Zachetka::~Zachetka() {
	for (int i = 0;i < sc;i++) {
		delete _sems[i];
	}

}

void Zachetka::showAll() {
	for (int i = 0;i < sc;i++) {
		cout << setw(3) << " " <<(i+1) <<" семестр:"<<endl;
		for (int j = 0;j < _sems[i]->sc; j++) {
			if (_sems[i]->_subjects[j]->title == "0subj~~") {
			}

			else
				cout << setw(7) << " " << _sems[i]->_subjects[j]->title << ": " << (_sems[i]->_subjects[j]->mark == 1 ? "P" : to_string(_sems[i]->_subjects[j]->mark)) << endl;
		}

	}

}

string Zachetka::dump() {
	string result; 
	string m = "\3", 
		s = "\2",
		le = "\1";
	for (int i = 0;i < 12;i++) {
			for (int j = 0;j < _sems[i]->sc;j++) {
				result.append(_sems[i]->_subjects[j]->title + s + to_string(_sems[i]->_subjects[j]->mark) + m);
			}

			result.append(le);
	}

	return result;
}

int Zachetka::addSem(Semestr* s) {
	if (s->sc < 12) { 
		_sems[sc] = s;
		sc++; 
		return 1;
	}

	return 0;
}

float Zachetka::average()
{
	int sum=0, count=0;
	for (int i = 0; i < sc;i++) {
		if (_sems[i]->sc != 0) {
			if (_sems[i]->average() == -1) {
			}

			else {
				sum += _sems[i]->average();
				count++;
			}

		}

	}

	return count == 0 ? -1 : sum * 1.0 / count; 
}

