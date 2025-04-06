#include "students.h"
#include <iostream>

using namespace std;

void Students::Add(string name, string group, vector<int> grades)
{
	double medium = 0;
	for (int i = 0; i < grades.size(); i++) {
		medium = medium + grades[i];
	}
	medium = medium / grades.size();
	Student* newStudent = new Student();
	newStudent->name = name;
	newStudent->group = group;
	newStudent->grades = grades;
	newStudent->mdgrade = medium;

	Student* curr = firstStudent;
	if (curr == NULL) {
		firstStudent = newStudent;
		newStudent->prev = NULL;
		newStudent->next = NULL;
	}
	else {
		firstStudent = newStudent;
		newStudent->next = curr;
		newStudent->prev = NULL;
		curr->prev = newStudent;
	}
	count++;
}

bool Students::Del(string name)
{
	bool deleted = false;
	Student* curr = firstStudent;
	string grad;
	Student* parent = NULL;
	Student* currnext = NULL;
	bool find = false;
	int i;
	bool ok = false;

	if (curr != NULL) {
		while (curr->name != name && curr->next != NULL)
		{
			parent = curr;
			curr = curr->next;
		}
		if (curr->name == name) {
			find = true;
		}
		else if (curr->next == NULL) {
			cout << "В списке нет ученика с такой фамилией." << endl;
		}
		if (find)
		{
			while (!ok)
			{
				grad = "";
				cout << "Вы желаете удалить этого студента?(1=Да/2=Нет/3=Продолжить поиск): " << endl << endl;
				for (int i = 0; i < curr->grades.size(); i++) {
					grad = grad + " " + to_string(curr->grades[i]);
				}
				cout << "ФИО: " << curr->name << endl << "Группа: " << curr->group << endl << "Средний балл: " << curr->mdgrade << endl << "Оценки: " << grad << endl << endl;
				cout << "Ввод: ";
				cin >> i;
				switch (i) {
				case 1:
					ok = true;
					break;
				case 2:
					ok = true;
					find = false;
					break;
				case 3:
					ok = false;
					find = false;
					break;
				}
				if (ok == false && find == false) {
					if (curr->next != NULL) {
						curr = curr->next;
						while (curr->name != name && curr->next != NULL)
						{
							parent = curr;
							curr = curr->next;
						}
						if (curr->name == name) {
							find = true;
						}
						else if (curr->next == NULL) {
							cout << "В списке нет ученика с такой фамилией." << endl;
							ok = true;
						}
					}
					else ok = true;
				}
			}
			if (find)
			{
				if (curr->prev == NULL && curr->next == NULL) {
					firstStudent = NULL;
					delete curr;
				}
				else if (curr->prev == NULL) {
					firstStudent = curr->next;
					curr->next->prev = NULL;
					delete curr;
				}
				else if (curr->next == NULL) {
					parent->next = NULL;
					delete curr;
				}
				else {
					currnext = curr->next;
					parent->next = currnext;
					currnext->prev = parent;
					delete curr;
				}
				count--;
				deleted = true;
			}
		}
	}
	else cout << "Список пуст." << endl;
	return deleted;
}

void Students::Del(Student* key)
{
	Student* curr = key;


	if (curr != NULL) {
		Student* parent = key->prev;
		Student* currnext = key->next;
		if (curr->prev == NULL && curr->next == NULL) {
			firstStudent = NULL;
			delete curr;
		}
		else if (curr->prev == NULL) {
			firstStudent = curr->next;
			curr->next->prev = NULL;
			delete curr;
		}
		else if (curr->next == NULL) {
			parent->next = NULL;
			delete curr;
		}
		else {
			parent->next = currnext;
			currnext->prev = parent;
			delete curr;
		}
		count--;
	}
}


void Students::clear()
{
	Student* curr = firstStudent;
	if (curr != NULL)
	{
		if (curr->prev == NULL && curr->next == NULL) delete curr;
		while (count != 1) {
			curr = curr->next;
			delete curr->prev;
			count--;
		}
	}
	/*while (curr->next != NULL) {
		if (curr->prev != NULL)
		{
			curr = curr->next;
			delete curr->prev;
		}
		else {
			delete curr;
		}
	}*/
	count = 0;
	firstStudent = NULL;
}

void Students::Get(Student* key, string& name, string& group, vector<int>& grades, double& mdgrade)
{
	if (firstStudent != NULL) {

		name = key->name;
		group = key->group;
		grades = key->grades;
		mdgrade = key->mdgrade;
	}
}

void Students::Set(Student* key, string name, string group, vector<int> grades, double mdgrade)
{
	if (firstStudent != NULL) {
		key->name = name;
		key->group = group;
		key->grades = grades;
		key->mdgrade = mdgrade;
	}
}

double Students::Medium(Student* key)
{
	vector<int> grades = key->grades;
	double medium = 0;
	for (int i = 0; i < grades.size(); i++) {
		medium = medium + grades[i];
	}
	return medium / grades.size();
}



void Students::Sort()
{
	Student* curr = firstStudent;
	Student* curr2 = firstStudent;
	int cnt = count;
	for (int i = 0; i < count; i++) {
		int k = i;
		curr = firstStudent;
		while (k != 0) {
			if (k != 0)
			{
				curr = curr->next;
				k--;
			}
		}
		curr2 = curr;
		for (int j = i; j < count - 1; j++) {
			//if (curr->mdgrade < curr2->next->mdgrade) {
			if (strcmp(curr->name.c_str(), curr2->next->name.c_str()) > 0) {
				string tempname = curr->name;
				string tempgroup = curr->group;
				vector <int> tempgrades = curr->grades;
				double tempmdgrade = curr->mdgrade;
				curr->name = curr2->next->name;
				curr->group = curr2->next->group;
				curr->grades = curr2->next->grades;
				curr->mdgrade = curr2->next->mdgrade;
				curr2->next->name = tempname;
				curr2->next->group = tempgroup;
				curr2->next->grades = tempgrades;
				curr2->next->mdgrade = tempmdgrade;
			}
			curr2 = curr2->next;
		}
	}
}

