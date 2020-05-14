#pragma once
#include "Subj.h"
class Semestr
{
	friend class Student;
	friend class Zachetka;
	friend class Univer;
	Subj* _subjects[10]; 
public:
	int sc=0; 
	Semestr();
	int hasSubj(string);
	Subj* getByTitle(string);
	int addSubj(Subj*);
	float average();
}
;

