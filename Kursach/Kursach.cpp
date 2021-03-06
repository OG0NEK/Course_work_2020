﻿#include <iostream>
#include <string>
#include "Utils.h"
#include "Univer.h"
#include <Windows.h>
using namespace std;
void input_data();
void menu();
Univer *u;
int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");
	u = new Univer("MIREA");
	while (1)
		menu();
	return 0;
}
void menu() {
	string n;
menu_n: 
	if (u->N == 0) {
		cout << "!!!! Чтобы начать использовать программу, необходимо сначала загрузить студентов при помощи первого пункта меню !!!!" << endl;
	}
	cout << "Введите номер действия, которое хотите совершить: "<<endl;
	cout << "1. Ввести/добавить студентов" << endl;
	cout << "2. Удалить студента" << endl;
	cout << "3. Показать всех студентов в университете" << endl;
	cout << "4. Изменить информацию о студенте" << endl;
	cout << "5. Показать выборку" << endl;
	cout << "0. Выход" << endl;
	cout << "> ";
	getline(cin, n);
	if (!isValidInt(n) || (stoi(n) > 5 || stoi(n) < -1)) {
		cls;
		goto menu_n;
	}
	switch (stoi(n))
	{
	case 0: { 
		cls;
		delete u;
		exit(0);
	}
	case 1: { 
		cls;
		if (fileExists("db.bin")) {
		menu_n1: 
			cout << "1. Загрузить данные из файла (db.bin)" << endl;
			cout << "2. Ввести студентов с клавиатуры" << endl;
			cout << "> ";
			getline(cin, n);
			if (!isValidInt(n) || (stoi(n) > 2) || stoi(n) < 1) {
				cls;
				goto menu_n1;
			}
			cls;
			if (n == "1") 
				u->loadAll();
			else { 
				input_data();
			}
		}
		else { 
			cout << "Файл не найден" << endl;
			input_data();
		}
		break;
	}
	case 2: {
		if (u->N == 0) {
			cls;
			cout << NOSTUDS << endl;
			system("pause"); cls;
			break;
		}
		string zach;
	zenter:
		cout << "Введите номер зачетной книжки студента, которого хотите удалить из университета: [0=выход в меню] > ";
		getline(cin, zach);
		if (zach == "0") { cls; break; }
		if (!u->hasStudent(zach)) {
			cout << NOSTUDS << endl;
			goto zenter;
		}
		u->removeStudent(zach);
		u->saveAll();
		cls;
		break;
	}
	case 3:{ 
		cls;
		u->showStudents();
		system("pause");
		cls;
		break;
	}
	case 4: { 
		if (u->N == 0) {
			cls;
			cout << NOSTUDS << endl;
			system("pause"); cls;
			break;
		}
		string zn;
		cout << "Введите номер зачётной книжки > ";
	checkZn: 
		getline(cin, zn);
		if (zn == "0") {
			cls;
			break;
		}
		if (!u->hasStudent(zn)) {
			cout << "Не найдено студентов с таким номером зачетки, попробуйте снова [0=выход в меню] > ";
			goto checkZn;
		}
		cls;
		u->showStudentChangeDialog(zn);
		u->saveAll();
		break;
	}
	case 5: {
		break;
	}
	default:
		break;
	}
}
void input_data() {
	string scount;
students_count_input: 
	cout << "Введите кол-во студентов > ";
	getline(cin, scount);
	if (!isValidInt(scount)) {
		cls;
		cout << INVINP << endl;
		goto students_count_input;
	}
	for (int i = 1;i < stoi(scount) + 1;i++) {
	sstart: clean;
		cout << "------------------ Студент [№" << i << "]: ---------------------" << endl;
		cout << "ФИО, разделенные пробелами > ";
		string sname, fname, mname, group, zach_num, kaf, fac, bdate, y, gender;
		Date bday, jdate;
		cin >> sname;
		cin >> fname;
		cin >> mname;
		if (!checkSpec(sname, 0) || !checkSpec(fname, 0) || !checkSpec(mname, 0)) {
			cout << CHR_ERR << endl;
			system("pause");
			cls;
			goto sstart;
		}
		clean;
	gender_input: 
		cout << "Пол [Ж,М] > ";
		getline(cin, gender);
		if ((strCase(gender,0) != "ж") && (strCase(gender, 0) != "м")) {
			cout << INVINP << endl;
			goto gender_input;
		}
		gender = (strCase(gender, 0) == "м" ? "1" : "0");
	bdate_input: 
		cout << "Дата рождения {дд.мм.ГГГГ} > ";
		getline(cin, bdate);
		if (!bday.isValid(parseDotDate(bdate))) {
			cout << INVINP << endl;
			goto bdate_input;
		}
		bday = parseDotDate(bdate);
	jdate_input: 
		cout << "Год поступления {ГГГГ} > ";
		getline(cin, y);
		if (!isValidInt(y) || stoi(y) < 0 || stoi(y) > 9999 || stoi(y) <= bday.year) {
			cout << INVINP << endl;
			goto jdate_input;
		}
		jdate.year = stoi(y);
	gri:
		cout << "Группа > ";
		getline(cin, group);
		if (!checkSpec(group, 1)) {
			cout << CHR_ERR << endl;
			goto gri;
		}
	znum: 
		cout << "Номер зачётки > ";
		getline(cin, zach_num);
		if (!checkSpec(zach_num, 1) || u->hasStudent(zach_num)) {
			cout << "Введённый вами номер зачётной книжки уже существует или содержит недопустимые символы!" << endl;
			goto znum;
		}
		cout << "Кафедра > ";
		getline(cin, kaf); 
		kaf = trim(kaf);
		cout << "Факультет > ";
		getline(cin, fac); 
		fac = trim(fac);
		Zachetka* z = new Zachetka(zach_num);
		for (int s = 1;s <= 12;s++) {
			cls;
			cout << "------------------ Семестры, предметы, оценки ---------------------" << endl;
			cout << "Вы можете ввести 9 сессий и по 10 предметов для каждой из них:" << endl;
			cout << "	[" << to_string(s) << "] семестр. Предметы [0=нет сессии, 1=сессия без предметов]: " << endl;
			Semestr* sem = new Semestr();
			for (int j = 1;j <= 10;j++) {
				string stitle, mark;
			tcheck:
				cout << "		[" << j << "] Название предмета [0=конец ввода предметов] > ";
				getline(cin, stitle);
				if (stitle == "0")
					break;
				if (stitle == "1") {
					Subj* s = new Subj("0subj~~", -1);
					sem->addSubj(s);
					break;
				}
				if (sem->hasSubj(stitle) || stitle=="") {
					cout << "Предмет с таким названием уже существует или неверно введено название!" << endl;
					goto tcheck;
				}
			mark_input: 
				cout << "Оценка:  (1=пересдача, 2-5=оценка)" << endl;
				getline(cin, mark);
				if (!isValidInt(mark) || (stoi(mark) < 1 || stoi(mark) > 5)) {
					cout << INVINP << endl;
					goto mark_input;
				}
				Subj* s = new Subj(stitle, stoi(mark));
				sem->addSubj(s);
			}
			z->addSem(sem);
		}
		Student* is = new Student(sname, fname, mname, stoi(gender), bday, group, fac, kaf, jdate, z);
		u->addStudent(is);
		cls;
		u->saveAll();
	}
	cls;
}
