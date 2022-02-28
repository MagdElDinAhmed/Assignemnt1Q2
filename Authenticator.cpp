#include "Authenticator.h"
Authenticator::Authenticator()
{
	validUser = false;
	validPass = true;
	success = false;
}
bool Authenticator::userCheck(string userIn,string passIn)
{
	ifstream file;
	string userTest;
	string passTest = ""; //a dummy variable in case it is never called
	file.open("LogInData.txt");
	while (!file.eof() && validUser == false) //continues until the user is found or the file ends
	{
		file.ignore(4,'\n'); //skips first line
		getline(file, userTest); //gets username
		if (userTest == userIn) //compares usenrame to input
		{
			validUser = true; //sets te username validity to true
			getline(file, passTest);
			if (passTest != passIn) //compares password input to the one in the log in file
				validPass = false; //makes the validity of the password false if they don't match
		}
		else
		{
				file.ignore(256,'<'); //skips to the next entry
		}
	}
	if (validUser)
	{
		if (validPass)
		{
			success = true; //indicates successsful log in
		}
	}
	file.close();
	return success;
}

bool Authenticator::regCheck(string& userIn, string& passIn)
{
	ifstream file;
	string passTest = "";
	file.open("LogInData.txt");
	validUser = false;
	while (!validUser)
	{
		validUser = true; //temporarily sets username validity to true
		UsernameAuth(file, userIn); //authenticates username
	}

	
	if (validUser)
	{
		cout << "Enter Password:";
		cin >> passIn; //inputs password
		cout << "Confirm password:";
		cin >> passTest; //confirms password
		while (passTest != passIn) //if the passwords don't match, input them again
		{
			cout << "Passwords do not match" << endl;
			cout << "Enter password:";
			cin >> passIn;
			cout << "Confirm password:";
			cin >> passTest;
		}
		success = true;
	}
	else
		cout << "Username already taken" << endl; //output if the username is taken
	file.close();
	return success;
}

bool Authenticator::UsernameAuth(ifstream& file, string& userIn)
{
	string userTest;
	file.seekg(0); //returns the file's pointer to the beginning
	while (!file.eof() && validUser == true) //continues until the username is found to be a duplicate or the file ends
	{
		file.ignore(4, '\n'); //skips the '<'
		getline(file, userTest); //gets the username from the file
		if (userTest == userIn) //compares the file username to input
		{
			validUser = false; //if they're equal, username is not valid
			cout << "Username already taken" << endl;
			cout << "Enter Username: " << endl; //input username again
			cin >> userIn;
		}
		else
		{
			file.ignore(256, '<'); //skips to the next line if the usernames don't match
		}
	}
	return validUser;
}