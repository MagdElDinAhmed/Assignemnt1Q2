#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "LogIn.h"
#include "Courses.h"
using namespace std;
class Student
{
	string UserName;
	string Password;
	int credit;
	string courses;
	int choice;
	Courses* S1; //this allows for all subjects to be present as potential choices to be easily accessed, it is a pointer to allow for a varied number of courses to be present
	const int maxCredit;
	const int cCount; //it is the number of lines in the courses folder
public:
	Student(string username = "", string password = "", bool registr = false) :maxCredit(18), cCount(lineCount()) //It initialises a student and sets dummy values
	{
		UserName = username;
		Password = password;

		S1 = new Courses[cCount]; //creates an array of Courses to allow for free course selection
		if (registr) //checks if user is registering and sets the values
		{
			credit = 0;
			courses = "";
			bool run = true;
		}
		else
		{
			setValues(); //It sets the values according to 
		}

	}

	int lineCount() const; //counts the number of lines in the Courses file

	int lineCount2() const; //Counts the number of files

	void setValues(); //It sets the values for the username, password, credit hours and courses for the student


	void addCourse(const Courses* student); //it adds a course for the student

	void dropCourse(const Courses* student); //it drops a course for the student

	void printCourses() const; //It prints out the courses available with their credit hours

	void setCourses(); //It puts the course in the file
	
	void dropCourses(); //It drops the course from the file


	string getCred() const; //It returns the number of credit hours

	string getCourse() const; //It returns the courses

	int getMaxCred() const; //It returns the maximum number of credit hours for a student

	void setUsername(string name); //It sets a username

	void setPassword(string pass); //It sets a password

};

