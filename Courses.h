#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
static int line = 1;
class Courses
{
	string name;
	int credit;
	static int courseCount;
public:
	Courses(); //It creates the objects for courses

	string getName() const; //Gets the name of the course

	int getCredit() const; //Gets the credit hours for the course

	~Courses(); //Removes the course and makes the next instance read 1 line before
};

