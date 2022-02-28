#include "Courses.h"
Courses::Courses()
{
	int i = 1;
	ifstream file;
	file.open("CourseDat.txt"); //opens the folder containing the courses
	while (i < line) //it checks if i (value of current line) is less than line (value of line to read)
	{
		file.ignore(256, '\n'); //it skips the line
		i++; //it increments the current line
	}
	file >> name >> credit; //when the correct line is reacehd, the course's name and credit hours are input into the class
	line++; //tells the code it's supposed to read the line afterwards
	file.close();
}

string Courses::getName() const
{
	return name;
}

int Courses::getCredit() const
{
	return credit;
}

Courses::~Courses()
{
	line--; //tells the code that if it reads the file again to generate courses, to start 1 line prior to where it was
}