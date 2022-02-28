#pragma once
#include "LogIn.h"
#include <fstream>
class Authenticator
{
	bool validUser;
	bool validPass;
	bool success;

public:
	Authenticator();
	bool userCheck(string userIn, string passIn); //checks if the username and password are correct
	bool regCheck(string& userIn, string& passIn); //checks if the username is unique and if the password has been verified
	bool UsernameAuth(ifstream& file, string& userIn); //Checks if the username is unique
};

