#include "LogIn.h"
#include "Authenticator.h"
LogIn::LogIn()
{
	runtime = true;
	loggedIn = false;
	registr = false;
	userNameIn = "";
	passwordIn = "";
}

void LogIn::printScrn()
{
	Student student("","", false);
	string choice;
	while (runtime)
	{
		if (!loggedIn)
		{
			cout << "Pick an option: " << endl;
			cout << "1. Log in" << endl;
			cout << "2. Register" << endl
				<< "3. Exit" << endl;
			do
			{
				cin >> choice;
				if (choice < "1" || choice > "3")
					cout << "Please enter a valid choice" << endl; //why is this loop broken
			} while (choice < "1" || choice > "3");

			if (stoi(choice) == 1)
			{
				loggingIn();
				if (loggedIn)
				{
					student.setUsername(userNameIn);
					student.setPassword(passwordIn);
					student.setValues();
				}

				
			}
			else if (stoi(choice) == 2)
			{
				registration();
				student.setUsername(userNameIn);
				student.setPassword(passwordIn);
				student.setValues();
			}
			else if (stoi(choice) == 3)
			{
				runtime = false;
			}
		}
		else
		{
			

			cout << "Pick an option: " << endl;
			if (stoi(student.getCred()) < student.getMaxCred())
			{
				cout << "1. Add Course" << endl;
				cout << "2. Drop Course" << endl
					<< "3. View Schedule" << endl
					<< "4. Log Out" << endl;
				do
				{
					cin >> choice;
					if (choice < "1" || choice > "4")
						cout << "Please enter a valid choice" << endl;
				} while (choice < "1" || choice > "4");
			}
			else
			{
				cout << "1. Add Course (credits full)" << endl;
				cout << "2. Drop Course" << endl
					<< "3. View Schedule" << endl
					<< "4. Log Out" << endl;
				do
				{
					cin >> choice;
					if (choice < "2" || choice > "4")
						cout << "Please enter a valid choice" << endl;
				} while (choice < "2" || choice > "4");
			}

			switch (stoi(choice))
			{
			case 1:
				student.setCourses();
				break;
			case 2:
				student.dropCourses();
				break;
			case 3:
				cout << student.getCourse() << endl;
				break;
			case 4:
				loggedIn = false;
				break;
			}
		}
	}
	
}


void LogIn::inputUserName()
{
	cin>>userNameIn;
}

void LogIn::inputPassword()
{
	cin>>passwordIn;
}

string LogIn::getUserName() const
{
	return userNameIn;
}

string LogIn::getPassword() const
{
	return passwordIn;
}

bool LogIn::getRuntime() const
{
	return runtime;
}

void LogIn::loggingIn()
{
	Authenticator auth;
	cout << "Username and Password: " << endl;
	inputUserName();
	inputPassword();
	if (auth.userCheck(getUserName(), getPassword()))
	{
		loggedIn = true;
	}
	else
	{
		cout << "Wrong username or password" << endl;
		printScrn();
	}
}

void LogIn::registration()
{
	Authenticator regConf;
	ofstream file;
	string username, password;
	cout << "Enter Username: ";
	cin >> userNameIn;
	username = userNameIn;
	password = passwordIn;
	if (regConf.regCheck(username, password))
	{
		registr = true;
		loggedIn = true;
		Student student(username,password,registr);
		file.open("LogInData.txt", fstream::app);
		file << endl << "<" << endl << username << endl << password << endl << student.getCred() << endl << student.getCourse() << endl << ">";
		file.close();
	}
	
}