#include "Student.h"

int Student::lineCount() const
{
	ifstream file;
	file.open("CourseDat.txt");
	int lineCount = 0;
	while (!file.eof())
	{
		file.ignore(256, '\n'); //it ignores the line and adds it to the counter lineCount that indicates number of lines
		lineCount++;
	}
	file.close();
	return lineCount;
}

int Student::lineCount2() const
{
	ifstream file;
	file.open("LogInData.txt");
	int lineCount = 0;
	while (!file.eof())
	{
		file.ignore(256, '>');
		file.ignore(1);
		if (file.peek()=='<') //it checks if it is looking at a new entry
			lineCount+=6; //it counts the number of lines by adding 6 to thee counter each time it passes by a student entry
	}
	lineCount += 6; //it adds the final entry into the lineCount as the prior code omits the last entry
	file.close();
	return lineCount;
}

void Student::setValues()
{
	string searchName;
	string initCred;
	ifstream file;
	file.open("LogInData.txt");
	while (UserName != searchName)
	{
		file.ignore(4, '\n'); //it skips the '<' character, 4 is an arbitrary number
		getline(file, searchName); //this line takes the username in the file record to compare it to the one logged in
		if (UserName == searchName) //checks if logged in username is equal to current username in the file
		{
			file.ignore(256, '\n'); //it skips the password line, 256 is an arbitrarily large number
			getline(file, initCred); //it takes in the number of credit hours the student has
			credit = stoi(initCred); //it assigns the integer value of the initial credit hours to the credit hours data member of the student
			getline(file, courses); //it reads the courses and inputs them directly into the data member reesponsible for handling them
		}
		else
		{
			file.ignore(256, '<'); //skips the entry if it is not the correct one
		}
	}
	file.close();
}

void Student::addCourse(const Courses* student)
{
	string pick;
	string name;
	int numberOfLines = cCount; //counts the number of lines in the file that has course information
	cout << "Enter a number to choose course: " << endl;
	printCourses();
	do
	{
		cin >> pick;
		if (pick < "1" || pick > to_string(numberOfLines)) //it checks if input is valid, this particular method prevents the code from breaking if the user were to input a string or character nsted of an integer
			cout << "Please enter a valid choice" << endl;
	} while (pick < "1" || pick > to_string(numberOfLines));
	name = (student + (stoi(pick) - 1))->getName(); //a method I occasionally use to shorten code length while getting course name
	if (((credit + (student + (stoi(pick) - 1))->getCredit()) <= maxCredit) && courses.find(name) == string::npos) //I check if inputing the course exceeds the credit hour limit and if the course is present or not
	{
		credit += (student + (stoi(pick) - 1))->getCredit(); //adds the credit hours
		courses = courses + (student + (stoi(pick) - 1))->getName() + " "; //adds the course name
	}
	else if (((credit + (student + (stoi(pick) - 1))->getCredit()) > maxCredit)) //output when credit limit is exceeded
	{
		cout << "Credit limit exceeded" << endl;
	}
	else if (courses.find(name) != string::npos) //output when the course is already present
	{
		cout << "Course is already present" << endl;
	}
}

void Student::dropCourse(const Courses* student)
{
	string pick;
	string name;
	int numberOfLines = cCount;
	cout << "Enter a number to choose course: " << endl;
	printCourses();
	do
	{
		cin >> pick;
		if (pick < "1" || pick > to_string(numberOfLines))
			cout << "Please enter a valid choice" << endl;
	} while (pick < "1" || pick > to_string(numberOfLines));
	name = (student + (stoi(pick) - 1))->getName(); //for the function up to this point, refer to "addCourse" for its unction documentation
	if (courses == "") //output if student has no courses
	{
		cout << "No courses to drop" << endl;
	}
	else if (courses.find(name) == string::npos) //output if the student is enrolled in courses, but is trying to drop one they aren't enrolled in
	{
		cout << "Course isn't present" << endl;
	}
	else
	{
		credit -= (student + (stoi(pick) - 1))->getCredit(); //deducs the credit hours from the course dropped
		courses.erase(courses.find((student + (stoi(pick) - 1))->getName()), ((student + (stoi(pick) - 1))->getName().length() + 1)); //removes the course name from the courses data member
	}
}

void Student::printCourses() const
{
	ifstream file;
	file.open("CourseDat.txt");
	string line;
	int i = 1;
	while (!file.eof())
	{
		getline(file, line);
		cout << i << ". " << line << '\n'; //outputs the course and credit hours with a corresponding course number
		i++; //increments the number responsible for determining course number in the menu output
	}
	file.close();
}

void Student::setCourses()
{
	addCourse(S1); //adds a course to the student object
	string searchName;
	string line;
	ifstream file;
	ofstream file2;
	int l = 0; //line number
	int linecount = lineCount2(); //it counts the number of lines in the log in folder
	//this was done to avoid issues where an extra blank is created at the end of each add and drop, thus breaking later runs since the file's format is broken
	file.open("LogInData.txt"); //the original file
	file2.open("LogInNew.txt"); //the new replacement file
	while (UserName != searchName)
	{
		getline(file, line); //gets the line from the original file to output in new file
		l++; //increments the line counter
		file2 << line << '\n'; //outputs the line to the new folder
		getline(file, searchName); //gets the username of a user
		l++;
		file2 << searchName << '\n'; //outputs the name to the new file (It's hypothetically possible this could also be done with line, but I'm afraid of breaking the code)
		if (UserName == searchName) //checks if current user logged in is the one the file is pointing to right now
		{
			file.ignore(256, '>'); //skips reading the data to allow for manual input in the second file
			l += 3; //increments the line counter by the number of lines skipped
			file2 << Password << "\n";
			file2 << credit << "\n";
			file2 << courses << "\n";
			file2 << ">";
			//outputs the data to the new folder
		}
		else
		{
			if (!file.eof()) //checks if original file is over before continuing
			{
				for (int i = 0; i < 4; i++)
				{
					getline(file, line);
					l++;
					file2 << line << '\n'; //prints data from old file to new file
				}
			}
		}
	}
	while (l<linecount)
	{
		getline(file, line);
		l++;
		if (l < linecount)
			file2 << line << '\n';
		else
			file2 << line;
	} //gets all the lines after the required username and prints them in the new one
	file2.close();
	file.close();
	remove("LogInData.txt"); //deletes the old file
	int dummy = rename("LogInNew.txt", "LogInData.txt"); //renames the new file but the function returns a value so it has to put it in a variable
}

void Student::dropCourses()
{
	//same explanation as add courses (come to think of it, it could've been possible to take a boolean to determine the course of action instead of creating 2 functions, but that may be difficult to make work with the time I have)
	dropCourse(S1);
	string searchName;
	string line;
	ifstream file;
	ofstream file2;
	int l = 0;
	int linecount = lineCount2();
	file.open("LogInData.txt");
	file2.open("LogInNew.txt");
	while (UserName != searchName)
	{
		getline(file, line);
		l++;
		file2 << line << '\n';
		getline(file, searchName);
		l++;
		file2 << searchName << '\n';
		if (UserName == searchName)
		{
			file.ignore(256, '>');
			l += 3;
			file2 << Password << "\n";
			file2 << credit << "\n";
			file2 << courses << "\n";
			file2 << ">";
		}
		else
		{
			if (!file.eof())
			{
				for (int i = 0; i < 4; i++)
				{
					getline(file, line);
					l++;
					file2 << line << '\n';
				}
			}
		}
	}
	while (l < linecount)
	{
		getline(file, line);
		l++;
		if (l < linecount)
			file2 << line << '\n';
		else
			file2 << line;
	}
	file2.close();
	file.close();
	remove("LogInData.txt");
	int dummy = rename("LogInNew.txt", "LogInData.txt");
}

string Student::getCred() const
{
	return to_string(credit);
}

string Student::getCourse() const
{
	return courses;
}

int Student::getMaxCred() const
{
	return maxCredit;
}

void Student::setUsername(string name)
{
	UserName = name;
}

void Student::setPassword(string pass)
{
	Password = pass;
}