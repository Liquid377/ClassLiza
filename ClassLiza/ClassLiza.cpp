/*
* 
* 
* 
* 
* слегка заапргрейженный класс xd
* 
* 
* 
Вариант 3
Описать класс, реализующий стек и работу с ним.
1.)	Класс должен содержать следующие сведения о студентах:
•	фамилия и инициалы;
•	номер группы;
•	успеваемость (массив из пяти элементов).
2.)	В классе должны быть реализованы следующие операции над стеком:
•	добавление данных о новых студентах;
•	удаление данных о студенте, фамилия которого введена с клавиатуры;
•	вывод сведений обо всех студентах;
•	изменение оценок у студента, фамилия которого введена с клавиатуры.
3.)	Программа должна обеспечивать диалог с помощью меню.
4.)	В программе должны быть созданы два экземпляра класса: двоечники (имеют хотя бы одну оценку 2) и успевающие студенты (не имеют оценок 2). 
При добавлении нового студента должен быть автоматически выбран экземпляр стека, в который добавляются данные. 
При изменении оценок студента информация о студенте должна быть автоматически перенесена в другой список. 
При выводе информации о студентах, пользователь должен выбрать какой список студентов выводить (двоечники или успевающие студент), 
либо вывести всех студентов из обоих списков.
*/

#include <iostream>
#include <string>
#include <vector>
#include "students.h"
#include "Windows.h"
#include <fstream>

#define pause system("pause")
#define clr system("cls")


using namespace std;

int Menu() {
    int i;
    cout << "1. Добавление нового студента." << endl;
    cout << "2. Вывод информации о всех студентах." << endl;
    cout << "3. Удаление данных о студенте, фамилия которого введена с клавиатуры." << endl;
    cout << "4. Изменение оценок студента." << endl;
    cout << "5. Сортировка по алфавиту по фамилии." << endl;
    cout << "6. Чтение из файла." << endl;
    cout << "7. Запись в файл." << endl;
    cout << "8. Справка и о программе." << endl;
    cout << "9. О программе." << endl;
    cout << "0. Выход." << endl;
    cout << "Введите пункт меню: ";
    cin >> i;
    return i;
}

Students _Students;
Students _Students2;

void ReadFromFile() {
    string name, group, grade; vector<int> grades;
    string grad;
    ifstream f("input.txt");
    if (f) {
        while (!f.eof()) {
            grad = "";
            getline(f, name);
            getline(f, group);
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));
            getline(f, grade);
            grad += grade;
            grades.push_back(stoi(grade));

            if (grad.find("2") != std::string::npos) {
                _Students2.Add(name, group, grades);
                cout << "Ученик добавлен во второй список." << endl;
                grades.clear();
            }
            else 
            {
                _Students.Add(name, group, grades);
                cout << "Ученик добавлен в первый список." << endl;
                grades.clear();
            }
        }
    }
    else {
        cout << "Файла не существует или файл пуст." << endl;
    }
    f.close();
}

void WriteToFile() {
    ofstream f("output.txt");
    if (f) {
            string grad;
            Student* OutputStudent = _Students.GetFirst();
            f << "Успевающие студенты: " << endl << endl;
            for (int i = 0; i <= _Students.GetCount() - 1; i++) {
                grad = "";
                string name; string group; vector<int> grades; double mdgrade;
                _Students.Get(OutputStudent, name, group, grades, mdgrade);
                for (int i = 0; i < grades.size(); i++) {
                    grad = grad + " " + to_string(grades[i]);
                }
                f << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
                OutputStudent = _Students.GoNext(OutputStudent);
            }
            f << "Отстающие студенты: " << endl << endl;
            OutputStudent = _Students2.GetFirst();
            for (int i = 0; i <= _Students2.GetCount() - 1; i++) {
                grad = "";
                string name; string group; vector<int> grades; double mdgrade;
                _Students2.Get(OutputStudent, name, group, grades, mdgrade);
                for (int i = 0; i < grades.size(); i++) {
                    grad = grad + " " + to_string(grades[i]);
                }
                f << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
                OutputStudent = _Students2.GoNext(OutputStudent);
            }
    }
    else {
        cout << "Файла не существует или файл пуст." << endl;
    }
    cout << "Результаты записаны в файл" << endl;
    f.close();
}

void Delete() {
    string name;
    bool del = false;
    cout << "Введите фамилию и инициалы ученика, которого желаете удалить: ";
    cin.get(); getline(cin, name);
    cout << "Ищем в первом списке..." << endl;
    del = _Students.Del(name);
    if (del == false) 
    {
        cout << "Ищем во втором списке..." << endl;
        del = _Students2.Del(name);
    }
    if (del == true) {
        cout << "Ученик удален." << endl;
    }
}

void SetGrades() {
    string name1;
    string choose;
    int grade;
    cout << "Введите в каком список желаете искать (1-Успевающие студенты/2-Двоечники): ";
    cin.get(); getline(cin, choose);
    if (choose == "1")
    {
        cout << "Введите фамилию и инициалы ученика, которого желаете изменить: ";
        getline(cin, name1);
        string grad;
        bool ok = false;
        Student* OutputStudent = _Students.GetFirst();
        for (int i = 0; i <= _Students.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            if (name1 == name)
            {
                cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
                cout << "Желаете поменять оценки у этого ученика?(1-Да/2-Нет): ";
                getline(cin, choose);
                if (choose == "1") {
                    grades.clear();
                    grad = "";
                    for (int i = 0; i < 5; i++) {
                        cout << "Введите успеваемость по предмету номер " << i + 1 << ": ";
                        cin >> grade;
                        grades.push_back(grade);
                        grad = grad + " " + to_string(grade);
                        ok = true;
                    }
                    if (grad.find("2") != string::npos)
                    {
                        _Students2.Add(name, group, grades);
                        _Students.Del(OutputStudent);
                    }
                    else
                    {
                        double medium = 0;
                        for (int i = 0; i < grades.size(); i++) {
                            medium = medium + grades[i];
                        }
                        mdgrade = medium / grades.size();
                        _Students.Set(OutputStudent, name, group, grades, mdgrade);
                    }
                }
            }
            if (ok == false) OutputStudent = _Students.GoNext(OutputStudent);
        }
    }
    else {
        cout << "Введите фамилию и инициалы ученика, которого желаете изменить: ";
        getline(cin, name1);
        string grad;
        bool ok = false;
        Student* OutputStudent = _Students2.GetFirst();
        for (int i = 0; i <= _Students2.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students2.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            if (name1 == name)
            {
                cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
                cout << "Желаете поменять оценки у этого ученика?(1-Да/2-Нет): ";
                getline(cin, choose);
                if (choose == "1") {
                    grades.clear();
                    grad = "";
                    for (int i = 0; i < 5; i++) {
                        cout << "Введите успеваемость по предмету номер " << i + 1 << ": ";
                        cin >> grade;
                        grades.push_back(grade);
                        grad = grad + " " + to_string(grade);
                        ok = true;
                    }
                    if (grad.find("2") != std::string::npos)
                    {
                        double medium = 0;
                        for (int i = 0; i < grades.size(); i++) {
                            medium = medium + grades[i];
                        }
                        mdgrade = medium / grades.size();
                        _Students.Set(OutputStudent, name, group, grades, mdgrade);
                        _Students.Add(name, group, grades);
                        _Students2.Del(OutputStudent);
                    }
                    else
                    {
                        _Students.Add(name, group, grades);
                        _Students2.Del(OutputStudent);
                    }
                }
            }
            if (ok == false) OutputStudent = _Students2.GoNext(OutputStudent);
        }
    }
}

void Input() {
    string name, group; vector<int> grades;
    int grade;
    string grad;
    cout << "Введите фамилию и инициалы ученика: ";
    cin.get(); getline(cin, name);
    cout << "Введите номер группы ученика: ";
    getline(cin, group);
    for (int i = 0; i < 5; i++) {
        cout << "Введите успеваемость по предмету номер " << i + 1 << ": ";
        cin >> grade;
        grades.push_back(grade);
        grad = grad + " " + to_string(grade);
    }
    if (grad.find("2") != string::npos) _Students2.Add(name, group, grades);
    else _Students.Add(name, group, grades);

}

void Output() {
    string chooselist, chooseorder;
    cout << "Введите какой список желаете вывести(1-Успевающие студенты/2-Двоечники): ";
    cin.get(); getline(cin, chooselist);
    cout << "Введите в каком порядке вывести(1-Прямой/2-Обратный): ";
    getline(cin, chooseorder);
    if (chooselist == "1" && chooseorder == "1")
    {
        string grad;
        Student* OutputStudent = _Students.GetFirst();
        for (int i = 0; i <= _Students.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
            OutputStudent = _Students.GoNext(OutputStudent);
        }
    }
    else if (chooselist == "2" && chooseorder == "1"){
        string grad;
        Student* OutputStudent = _Students2.GetFirst();
        for (int i = 0; i <= _Students2.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students2.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
            OutputStudent = _Students2.GoNext(OutputStudent);
        }
    }
    else if (chooselist == "1" && chooseorder == "2") {
        string grad;
        Student* OutputStudent = _Students.GetFirst();
        for(int i = 0; i < _Students.GetCount() -1; i++)
        {
            OutputStudent = _Students.GoNext(OutputStudent);
        }
        for (int i = 0; i <= _Students.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
            OutputStudent = _Students.GoPrev(OutputStudent);
        }
    } 
    else if (chooselist == "2" && chooseorder == "2") {
        string grad;
        Student* OutputStudent = _Students2.GetFirst();
        for (int i = 0; i < _Students2.GetCount() - 1; i++)
            OutputStudent = _Students2.GoNext(OutputStudent);
        for (int i = 0; i <= _Students2.GetCount() - 1; i++) {
            grad = "";
            string name; string group; vector<int> grades; double mdgrade;
            _Students2.Get(OutputStudent, name, group, grades, mdgrade);
            for (int i = 0; i < grades.size(); i++) {
                grad = grad + " " + to_string(grades[i]);
            }
            cout << "ФИО: " << name << endl << "Группа: " << group << endl << "Средний балл: " << mdgrade << endl << "Оценки: " << grad << endl << endl;
            OutputStudent = _Students2.GoPrev(OutputStudent);
        }
    }
    else if (chooselist == "1" && _Students.GetCount() == 0) {
        cout << "Список пуст." << endl;
    }
    else if (chooselist == "2" && _Students2.GetCount() == 0) {
        cout << "Список пуст." << endl;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Student* _Student;
    int iM;
    do {
        clr;
        iM = Menu();
        switch (iM)
        {
        case 1:
            clr;
            Input();
            break;
        case 2:
            clr;
            Output();
            pause;
            break;
        case 3:
            clr;
            Delete();
            pause;
            break;
        case 4:
            clr;
            SetGrades();
            pause;
            break;
        case 5:
            clr;
            _Students.Sort();
            _Students2.Sort();
            cout << "Списки отсортированы." << endl;
            pause;
            break;
        case 6:
            clr;
            ReadFromFile();
            pause;
            break;
        case 7:
            clr;
            WriteToFile();
            pause;
            break;
        case 8:
            clr;
            cout << "Вариант 3" << endl;
            cout << "Описать класс, реализующий стек и работу с ним." << endl;
            cout << "1.)	Класс должен содержать следующие сведения о студентах:" << endl;
            cout << "•	фамилия и инициалы;" << endl;
            cout << "•	номер группы;" << endl;
            cout << "•	успеваемость (массив из пяти элементов)." << endl;
            cout << "2.)	В классе должны быть реализованы следующие операции над стеком:" << endl;
            cout << "•	добавление данных о новых студентах" << endl;
            cout << "•	удаление данных о студенте, фамилия которого введена с клавиатуры;" << endl;
            cout << "•	вывод сведений обо всех студентах;" << endl;
            cout << "•	изменение оценок у студента, фамилия которого введена с клавиатуры." << endl;
            cout << "3.)	Программа должна обеспечивать диалог с помощью меню." << endl;
            cout << "4.)	В программе должны быть созданы два экземпляра класса: двоечники (имеют хотя бы одну оценку 2) и успевающие студенты (не имеют оценок 2)." << endl;
            cout << "При добавлении нового студента должен быть автоматически выбран экземпляр стека, в который добавляются данные." << endl;
            cout << "При изменении оценок студента информация о студенте должна быть автоматически перенесена в другой список." << endl;
            cout << "При выводе информации о студентах, пользователь должен выбрать какой список студентов выводить (двоечники или успевающие студент)," << endl;
            cout << "либо вывести всех студентов из обоих списков." << endl;
            pause;
            break;
        case 9:
            clr;
            cout << "Программа: Класс" << endl
                << "Версия : 1.0" << endl
                << "Год : 2023" << endl
                << "Разработчик : Орлова Е.И." << endl
                << "Группа : ИНБб - 1301" << endl;
            pause;
            break;
        case 0:
            _Students.clear();
        }
    } while (iM != 0);
}



