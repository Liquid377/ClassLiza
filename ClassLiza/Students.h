#pragma once
#include <string>
#include <vector>
using namespace std;

class Student {
	string name;
	string group;
	vector<int> grades;
	double mdgrade;
	class Student* next;
	class Student* prev;
	friend class Students;
};


class Students
{
private:
	Student* firstStudent;
	int count;
public:
	Students() { firstStudent = NULL; count = 0; }
	void Add(string, string, vector<int>);
	bool Del(string);
	void Del(Student*);
	void clear();


	~Students() { clear(); }


	void Get(Student*, string&, string&, vector<int>&, double&);
	void Set(Student*, string, string, vector<int>, double);
	int GetCount() { return count; }


	Student* GetFirst() { return firstStudent; }
	Student* GoPrev(Student* key) { return key->prev; }
	Student* GoNext(Student* key) { return key->next; };

	double Medium(Student*);
	void Sort();
};

