#include "LogIn.h"
#include "Authenticator.h"

int main()
{
	LogIn login;
	ifstream file;
	ofstream file2;
	file.open("LogInData.txt");
	if (file.fail())
	{
		file2.open("LogInData.txt"); //creates a file for student log in data if it is not present
		file2.close();
	}
	else
		file.close();
	while (login.getRuntime())
	{
		login.printScrn(); //runs the log in code starting from the menu if the boolean controlling the running status of the program is true 
	}
	return 0;
}
