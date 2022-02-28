#pragma once
#include <iostream>
#include <string>
#include "Student.h"
using namespace std;
class LogIn
{
	bool runtime;
	bool loggedIn;
	bool registr;
	string userNameIn;
	string passwordIn;

public:
	LogIn(); //creates LogIn instance
	void printScrn(); //outputs the menu
	void inputUserName(); //It allows user to input the username
	void inputPassword(); //It allows the user to input the password
	string getUserName() const; //It returns the username
	string getPassword() const; //it returns the password
	bool getRuntime() const; //It checks if the program is running
	void loggingIn(); //It logs in the user if they input correct data
	void registration(); //It registers the user

};

