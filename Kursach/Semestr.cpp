#include "Utils.h"
#include "Semestr.h"
Semestr::Semestr() {
	sc = 0;
}
int Semestr::addSubj(Subj* s) {
	if (sc == 10)
		return 0;
	if (!hasSubj(s->title)) {
		_subjects[sc] = s;
		sc++;
		return 1;
	}
	return 0;
}
float Semestr::average()
{
	int sum = 0, count = 0;
	if (sc!=0) 
		for (int i = 0;i < sc;i++) {
			if (abs(_subjects[i]->mark) == 1) { 
				sum += 0; 
			}
			else {
				sum += _subjects[i]->mark; 
			}
			count++;
		}
	return count == 0 ? -1 : sum * 1.0 / count; 
}
int Semestr::hasSubj(string title) {
	for (int i = 0; i < sc;i++) {
		if (trim(strCase(_subjects[i]->title, 0)) == trim(strCase(title, 0)))
			return 1;
	}
	return 0;
}
Subj* Semestr::getByTitle(string title)
{
	for (int i = 0;i < sc;i++) {
		if (trim(_subjects[i]->title) == trim(title))
			return _subjects[i];
	}
	return nullptr;
}
