#include <iostream>
using namespace std;

class Date
{
private:
	int year;
	int month;
	int day;
public:
	Date(int year, int month, int day)
	{
		this->year = year;
		this->month = month;
		this->day = day;
	}
	Date()
	{

	}
	int GetYear()
	{
		return year;
	}
	int GetMonth()
	{
		return month;
	}
	int GetDay()
	{
		return day;
	}
};

class Employee
{
private:
	string name;
	Date birthDate;
	Date hireDate;
public:
	Employee(string name, Date& birthDate, Date& hireDate)
	{
		this->name = name;
		this->birthDate = birthDate;
		this->hireDate = hireDate;
	}
	void print()
	{
		cout << "직원의 이름 : " << name << endl;
		cout << "직원의 생일 : " << birthDate.GetYear() << "년" << birthDate.GetMonth() << "월" << birthDate.GetDay() << "일" << endl;
		cout << "직원의 이름 : " << hireDate.GetYear() << "년" << hireDate.GetMonth() << "월" << hireDate.GetDay() << "일" << endl;
	}
};

int main()
{
	Date bir(1987, 4, 27);
	Date hir(2011, 2, 05);
	Employee emp("홍길동", bir, hir);
	emp.print();
	return 0;
}