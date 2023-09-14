﻿#define _CRT_SECURE_NO_DEPRECATE

// library
#include <iostream> //cin and cout
#include <iomanip> //setw, left, right, fixed
#include <climits> 
#include <cctype> //isalpha, isnum, isalnum, ispunc, isupper, islower
#include <cmath> //pow, abs, fabs, ceil, floor, sqrt
#include <cstring> //strcat, strncat, strcpy, strncpy
#include <ctime> 
#include <stdlib.h> 
#include <fstream> 
#include <string> 
#include <vector> 
using namespace std;

// typedef for client
typedef struct
{
	char username[50];
	char password[50];
	char ic[30];
	char contactnum[30];
	char status[10];
}USER;

// typedef for doctor
typedef struct
{
	char d_name[50];
	char d_password[50];
	char d_ic[30];
	char d_contactnum[30];
}DOCTOR;

// Doctor login interface functions
void doctor_login_interface(DOCTOR d[], int* id_ptr);
int doctor_login(DOCTOR d[], int* i_ptr);
void doctor_signup(DOCTOR d[]);

// Patients login interface functions
void user_login_interface(USER c[], int* id_ptr);
int user_login(USER c[], int* i_ptr);
void user_signup(USER c[]);

// Doctor main menu functions
void doctor_mainmenu(USER c[], int id);
int doctor_resetpwd(DOCTOR d[], int* i_ptr);
void doctor_feedback(USER c[], int* i_ptr);

// Patients main menu functions
void user_mainmenu(USER c[], int id);
int user_resetpwd(USER c[], int* i_ptr);
int user_update(USER c[], int id);
void diagnose(USER c[], int id);
int updatePhonenum(USER c[], int id);
int updateStatus(USER c[], int id);
void faq(USER c[], int id);

// Function used to logout of the account
void exit();

//Check input is number or no
bool check_number(string str);

//faq functions
void hyperglycemia_faq(USER c[], int id);
void hypoglycemia_faq(USER c[], int id);
void diabetes_faq(USER c[], int id);



// main function
int main()
{
	// Clear screen
	system("CLS");

	// Create an array of CLIENT structs
	USER c[20];
	DOCTOR d[20];

	// Open input files (patients)
	ifstream name_file("username.txt", ios::in);
	ifstream pass_file("userpassword.txt", ios::in);
	ifstream ic_file("useric.txt", ios::in);
	ifstream phonenum_file("userphone.txt", ios::in);
	ifstream stats_file("status.txt", ios::in);

	// Open input files (doctor)
	ifstream doc_name_file("d_username.txt", ios::in);
	ifstream doc_pass_file("d_password.txt", ios::in);
	ifstream doc_ic_file("d_ic.txt", ios::in);
	ifstream doc_phonenum_file("d_phone.txt", ios::in);

	// Check if file opening was successful (patient)
	if (!name_file)
		cout << "Error opening username file\n";
	else if (!pass_file)
		cout << "Error opening userpassword file\n";
	else if (!ic_file)
		cout << "Error opening useric file\n";
	else if (!phonenum_file)
		cout << "Error opening user phone number file\n";
	else if (!stats_file)
		cout << "Error opening user status file\n";
	else
	{
		// Read data from input files into the CLIENT array
		for (int i = 0; i < 20; i++)
		{
			name_file >> c[i].username;
			pass_file >> c[i].password;
			ic_file >> c[i].ic;
			phonenum_file >> c[i].contactnum;
			stats_file >> c[i].status;
		}
		// Close input files
		name_file.close();
		pass_file.close();
		ic_file.close();
		phonenum_file.close();
		stats_file.close();
	}

	// Check if file opening was successful (doctor)
	if (!doc_name_file)
		cout << "Error opening doctor name file\n";
	else if (!doc_pass_file)
		cout << "Error opening doctor password file\n";
	else if (!doc_ic_file)
		cout << "Error opening doctor ic file\n";
	else if (!doc_phonenum_file)
		cout << "Error opening doctor phone number file\n";
	else
	{
		// Read data from input files into the CLIENT array
		for (int i = 0; i < 20; i++)
		{
			doc_name_file >> d[i].d_name;
			doc_pass_file >> d[i].d_password;
			doc_ic_file >> d[i].d_ic;
			doc_phonenum_file >> d[i].d_contactnum;
		}
		// Close input files
		doc_name_file.close();
		doc_pass_file.close();
		doc_ic_file.close();
		doc_phonenum_file.close();
	}

	// Call login interface function
	
	int decision;
	int id;
	do {
		cout << "Are you a doctor or patient?";
		cout << endl;
		cout << "<1> Patient" << endl;
		cout << "<2> Doctor" << endl;
		cout << "--->\t";
		cin >> decision;
	} while (decision != 1 && decision != 2);

	// Login and call respective main menu function
	if (decision == 1)
	{
		user_login_interface(c, &id);
		user_mainmenu(c, id);
	}
	else
	{
		doctor_login_interface(d, &id);
		doctor_mainmenu(c, id);
	}
	return 0;
}




// user login function definitions
void user_login_interface(USER c[], int* id_ptr)
{
	char interfaceAns;
	do
	{
		cout << "Do you want to <L>ogin or <S>ign up or <R>eset password? >>> ";
		cin >> interfaceAns;
		interfaceAns = toupper(interfaceAns);
	} while (interfaceAns != 'L' && interfaceAns != 'S' && interfaceAns != 'R');

	int i;

	if (interfaceAns == 'L') // If user chooses to login
	{
		user_login(c, &i); // Call the login function to perform login process
		*id_ptr = i; // Store the user ID in the memory location pointed by id_ptr
	}
	else if (interfaceAns == 'S') // If user chooses to sign up
	{
		user_signup(c); // Call the signup function to perform sign up process
	}
	else if (interfaceAns == 'R') // If user chooses to reset password
	{
		user_resetpwd(c, &i); // Call the resetpwd function to perform password reset process
		*id_ptr = i; // Store the user ID in the memory location pointed by id_ptr
		main(); // Call the main function to restart the program after password reset
	}

	return;
}

//function for user login
int user_login(USER c[], int* i_ptr)
{
	char username[50], password[50];
	bool userpassopt, usernameopt;

	int i;
	do
	{
		cin.ignore(1); // Ignore a single character in the input buffer to clear any remaining newline characters
		cout << "Please enter your username --> ";
		cin >> username; // Read user input for username

		cout << "Please enter your password --> ";
		cin >> password; // Read user input for password

		fflush(stdin); // Flush the input buffer to clear any remaining characters

		for (int i = 0; i < 50; i++) // Iterate through the array of CLIENT objects
		{
			if (strcmp(c[i].username, username) == 0) // Compare the entered username with the username in CLIENT object
			{
				usernameopt = true; // Set usernameopt flag to true indicating username match

				if (strcmp(c[i].password, password) == 0) // Compare the entered password with the password in CLIENT object
				{
					userpassopt = true; // Set userpassopt flag to true indicating password match
					*i_ptr = i; // Store the index of the matched CLIENT object in the memory location pointed by i_ptr
					break; // Break out of the loop as the login is successful
				}
				else
				{
					userpassopt = false; // Set userpassopt flag to false indicating incorrect password
				}
			}
			else
			{
				usernameopt = false; // Set usernameopt flag to false indicating no username match
			}
		}

		if ((userpassopt == false || usernameopt == false))
		{
			cout << "\nIncorrect password or username\n" << endl; // Display error message for incorrect username or password
		}
		else
		{
			cout << "\nLogin successful\n" << endl; // Display success message for successful login
		}

	} while (usernameopt == false); // Continue looping until a valid username is entered

	return 0;
}

//function for user to signup
void user_signup(USER c[])
{
	int phone_len, ic_len;
	string name, password1, password2, age, contact_num, ic, stats;
	bool validate, validrange, validateic, validrangeic, validate2, validrangephone;
	validateic = true;
	validate2 = true;
	validate = true;
	stats = "NULL";

	// Get user's name
	cout << "Please enter your name: ";
	getline(cin >> ws, name);

	// Get user's IC number
	cout << "Please enter your ic number without '-' (0123456789012): ";
	do
	{
		cin >> ic;
		// Validate if IC number is a number
		bool validateic = check_number(ic);
		if (validateic == true)
		{
			char icarray[30];
			strcpy(icarray, ic.c_str());
			ic_len = strlen(icarray);
			// Check if IC number length is within valid range (11 to 13)
			if ((ic_len < 13) && (ic_len > 11))
			{
				validrangeic = true;
			}
			else
			{
				validrangeic = false;
			}
		}
		else
		{
			cout << "Invalid input" << endl;
		}

		if (validateic == false || validrangeic == false)
			cout << "Please enter your ic again: ";

	} while (validateic == false || validrangeic == false);

	// Get user's contact number
	cout << "Please enter your contact number without '-' (i.e:0183958711): ";
	do
	{
		cin >> contact_num;
		// Validate if contact number is a number
		bool validate2 = check_number(contact_num);
		char contactnumarray[30];
		strcpy(contactnumarray, contact_num.c_str());
		phone_len = strlen(contactnumarray);
		// Check if contact number length is within valid range (10 to 13)
		if ((phone_len <= 13) && (phone_len >= 10))
		{
			validrangephone = true;
		}
		else
		{
			validrangephone = false;
		}
		if (validate2 == false || validrangephone == false)
		{
			cout << "Invalid input" << endl;
			cout << "Please enter your contact number again without '-' (i.e:0183958711): ";
		}
	} while (validate2 == false || validrangephone == false);

	// Get user's password
	do
	{
		cout << "Please enter your password: ";
		cin >> password1;

		cout << "Please enter your password again: ";
		cin >> password2;
		if (password1 != password2)
		{
			cout << "Different password entered \n"; // Prompt user that different passwords were entered
			cout << "Please try again\n"; // Prompt user to try again
			cout << "Please enter your password: "; // Prompt user to enter password again
			cin >> password1;

			cout << "Please enter your password again: "; // Prompt user to enter password again
			cin >> password2;
		}

	} while (password1 != password2); // Repeat until password1 and password2 match


	ofstream passwordfile("userpassword.txt", ios::app); // Create an output file stream to append to userpassword.txt file
	passwordfile << password2 << endl; // Write password2 to userpassword.txt followed by newline


	ofstream username("username.txt", ios::app); // Create an output file stream to append to username.txt file
	username << name << endl; // Write name to username.txt followed by newline


	ofstream agefile("userage.txt", ios::app); // Create an output file stream to append to userage.txt file
	agefile << age << endl; // Write age to userage.txt followed by newline


	ofstream phonenumfile("userphone.txt", ios::app); // Create an output file stream to append to userphone.txt file
	phonenumfile << contact_num << endl; // Write contact_num to userphone.txt followed by newline


	ofstream icfile("useric.txt", ios::app); // Create an output file stream to append to useric.txt file
	icfile << ic << endl; // Write ic to useric.txt followed by newline


	ofstream stats_file("status.txt", ios::app); // Create an output file stream to append to stats.txt file
	stats_file << stats << endl; // Write vac to vac_stats.txt followed by newline


	system("CLS"); // Clear screen
	cout << "Sign up complete \n"; // Prompt user that sign up is complete
	main(); // Call main() function to restart the program
}

//function to reset user's password
int user_resetpwd(USER c[], int* i_ptr)
{
	// Input for username and new password
	string username, resetpassword;
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your new password: ";
	cin >> resetpassword;

	string usernameToFind = username; // Username to find
	string newPassword = resetpassword; // New password to replace

	// Open the username text file for reading
	ifstream usernameFile("username.txt");
	if (!usernameFile.is_open()) {
		cout << "Failed to open username file." << endl;
		//return 1;
	}

	// Open the password text file for reading
	ifstream passwordFile("userpassword.txt");
	if (!passwordFile.is_open()) {
		cout << "Failed to open password file." << endl;
		usernameFile.close();
		//return 1;
	}

	vector<string> usernames; // Vector to store usernames from file
	vector<string> passwords; // Vector to store passwords from file
	string line;

	// Read usernames and passwords from the files into memory
	while (getline(usernameFile, line)) {
		usernames.push_back(line);
		getline(passwordFile, line);
		passwords.push_back(line);
	}

	usernameFile.close(); // Close username file
	passwordFile.close(); // Close password file

	// Search for the username to find and update the corresponding password
	bool found = false;
	for (size_t i = 0; i < usernames.size(); ++i) {
		if (usernames[i] == usernameToFind) {
			found = true;
			passwords[i] = newPassword; // Update password
			*i_ptr = i; // Store index of updated password
			break;
		}
	}

	if (found) {
		// Write the updated passwords back to the password file
		ofstream updatedPasswordFile("userpassword.txt");
		if (!updatedPasswordFile.is_open()) {
			cout << "Failed to open updated password file." << endl;
			return 1;
		}

		for (size_t i = 0; i < passwords.size(); ++i) {
			updatedPasswordFile << passwords[i] << endl;
		}

		updatedPasswordFile.close(); // Close updated password file

		cout << "Password updated successfully." << endl;

	}
	else {
		cout << "Username not found." << endl;
	}
	return 0;
}



//// doctor login function definitions
//void user_login_interface(USER c[], int* id_ptr)
//{
//	char interfaceAns;
//	do
//	{
//		cout << "Do you want to <L>ogin or <S>ign up or <R>eset password? >>> ";
//		cin >> interfaceAns;
//		interfaceAns = toupper(interfaceAns);
//	} while (interfaceAns != 'L' && interfaceAns != 'S' && interfaceAns != 'R');
//
//	int i;
//
//	if (interfaceAns == 'L') // If user chooses to login
//	{
//		user_login(c, &i); // Call the login function to perform login process
//		*id_ptr = i; // Store the user ID in the memory location pointed by id_ptr
//	}
//	else if (interfaceAns == 'S') // If user chooses to sign up
//	{
//		user_signup(c); // Call the signup function to perform sign up process
//	}
//	else if (interfaceAns == 'R') // If user chooses to reset password
//	{
//		user_resetpwd(c, &i); // Call the resetpwd function to perform password reset process
//		*id_ptr = i; // Store the user ID in the memory location pointed by id_ptr
//		main(); // Call the main function to restart the program after password reset
//	}
//
//	return;
//}
//
////function for user login
//int user_login(USER c[], int* i_ptr)
//{
//	char username[50], password[50];
//	bool userpassopt, usernameopt;
//
//	int i;
//	do
//	{
//		cin.ignore(1); // Ignore a single character in the input buffer to clear any remaining newline characters
//		cout << "Please enter your username --> ";
//		cin >> username; // Read user input for username
//
//		cout << "Please enter your password --> ";
//		cin >> password; // Read user input for password
//
//		fflush(stdin); // Flush the input buffer to clear any remaining characters
//
//		for (int i = 0; i < 50; i++) // Iterate through the array of CLIENT objects
//		{
//			if (strcmp(c[i].username, username) == 0) // Compare the entered username with the username in CLIENT object
//			{
//				usernameopt = true; // Set usernameopt flag to true indicating username match
//
//				if (strcmp(c[i].password, password) == 0) // Compare the entered password with the password in CLIENT object
//				{
//					userpassopt = true; // Set userpassopt flag to true indicating password match
//					*i_ptr = i; // Store the index of the matched CLIENT object in the memory location pointed by i_ptr
//					break; // Break out of the loop as the login is successful
//				}
//				else
//				{
//					userpassopt = false; // Set userpassopt flag to false indicating incorrect password
//				}
//			}
//			else
//			{
//				usernameopt = false; // Set usernameopt flag to false indicating no username match
//			}
//		}
//
//		if ((userpassopt == false || usernameopt == false))
//		{
//			cout << "\nIncorrect password or username\n" << endl; // Display error message for incorrect username or password
//		}
//		else
//		{
//			cout << "\nLogin successful\n" << endl; // Display success message for successful login
//		}
//
//	} while (usernameopt == false); // Continue looping until a valid username is entered
//
//	return 0;
//}
//
////function for user to signup
//void user_signup(USER c[])
//{
//	int phone_len, ic_len;
//	string name, password1, password2, age, contact_num, ic, stats;
//	bool validate, validrange, validateic, validrangeic, validate2, validrangephone;
//	validateic = true;
//	validate2 = true;
//	validate = true;
//	stats = "NULL";
//
//	// Get user's name
//	cout << "Please enter your name: ";
//	getline(cin >> ws, name);
//
//	// Get user's age
//	cout << "Please enter your age: ";
//	do
//	{
//		cin >> age;
//		// Validate if age is a number
//		bool validate = check_number(age);
//		if (validate == true)
//		{
//			// Check if age is within valid range (12 to 110)
//			if ((atoi(age.c_str()) <= 110) && (atoi(age.c_str()) >= 12))
//			{
//				validrange = true;
//			}
//			else
//			{
//				validrange = false;
//			}
//		}
//		else
//		{
//			cout << "Invalid input" << endl;
//		}
//
//		if (validate == false || validrange == false)
//			cout << "Please enter your age again: ";
//
//	} while (validate == false || validrange == false);
//
//	// Get user's IC number
//	cout << "Please enter your ic number without '-' (0123456789012): ";
//	do
//	{
//		cin >> ic;
//		// Validate if IC number is a number
//		bool validateic = check_number(ic);
//		if (validateic == true)
//		{
//			char icarray[30];
//			strcpy(icarray, ic.c_str());
//			ic_len = strlen(icarray);
//			// Check if IC number length is within valid range (11 to 13)
//			if ((ic_len < 13) && (ic_len > 11))
//			{
//				validrangeic = true;
//			}
//			else
//			{
//				validrangeic = false;
//			}
//		}
//		else
//		{
//			cout << "Invalid input" << endl;
//		}
//
//		if (validateic == false || validrangeic == false)
//			cout << "Please enter your ic again: ";
//
//	} while (validateic == false || validrangeic == false);
//
//	// Get user's contact number
//	cout << "Please enter your contact number without '-' (i.e:0183958711): ";
//	do
//	{
//		cin >> contact_num;
//		// Validate if contact number is a number
//		bool validate2 = check_number(contact_num);
//		char contactnumarray[30];
//		strcpy(contactnumarray, contact_num.c_str());
//		phone_len = strlen(contactnumarray);
//		// Check if contact number length is within valid range (10 to 13)
//		if ((phone_len <= 13) && (phone_len >= 10))
//		{
//			validrangephone = true;
//		}
//		else
//		{
//			validrangephone = false;
//		}
//		if (validate2 == false || validrangephone == false)
//		{
//			cout << "Invalid input" << endl;
//			cout << "Please enter your contact number again without '-' (i.e:0183958711): ";
//		}
//	} while (validate2 == false || validrangephone == false);
//
//	// Get user's password
//	do
//	{
//		cout << "Please enter your password: ";
//		cin >> password1;
//
//		cout << "Please enter your password again: ";
//		cin >> password2;
//		if (password1 != password2)
//		{
//			cout << "Different password entered \n"; // Prompt user that different passwords were entered
//			cout << "Please try again\n"; // Prompt user to try again
//			cout << "Please enter your password: "; // Prompt user to enter password again
//			cin >> password1;
//
//			cout << "Please enter your password again: "; // Prompt user to enter password again
//			cin >> password2;
//		}
//
//	} while (password1 != password2); // Repeat until password1 and password2 match
//
//
//	ofstream passwordfile("userpassword.txt", ios::app); // Create an output file stream to append to userpassword.txt file
//	passwordfile << password2 << endl; // Write password2 to userpassword.txt followed by newline
//
//
//	ofstream username("username.txt", ios::app); // Create an output file stream to append to username.txt file
//	username << name << endl; // Write name to username.txt followed by newline
//
//
//	ofstream agefile("userage.txt", ios::app); // Create an output file stream to append to userage.txt file
//	agefile << age << endl; // Write age to userage.txt followed by newline
//
//
//	ofstream phonenumfile("userphone.txt", ios::app); // Create an output file stream to append to userphone.txt file
//	phonenumfile << contact_num << endl; // Write contact_num to userphone.txt followed by newline
//
//
//	ofstream icfile("useric.txt", ios::app); // Create an output file stream to append to useric.txt file
//	icfile << ic << endl; // Write ic to useric.txt followed by newline
//
//
//	ofstream stats_file("status.txt", ios::app); // Create an output file stream to append to stats.txt file
//	stats_file << stats << endl; // Write vac to vac_stats.txt followed by newline
//
//
//	system("CLS"); // Clear screen
//	cout << "Sign up complete \n"; // Prompt user that sign up is complete
//	main(); // Call main() function to restart the program
//}
//
////function to reset user's password
//int user_resetpwd(USER c[], int* i_ptr)
//{
//	// Input for username and new password
//	string username, resetpassword;
//	cout << "Enter your username: ";
//	cin >> username;
//	cout << "Enter your new password: ";
//	cin >> resetpassword;
//
//	string usernameToFind = username; // Username to find
//	string newPassword = resetpassword; // New password to replace
//
//	// Open the username text file for reading
//	ifstream usernameFile("username.txt");
//	if (!usernameFile.is_open()) {
//		cout << "Failed to open username file." << endl;
//		//return 1;
//	}
//
//	// Open the password text file for reading
//	ifstream passwordFile("userpassword.txt");
//	if (!passwordFile.is_open()) {
//		cout << "Failed to open password file." << endl;
//		usernameFile.close();
//		//return 1;
//	}
//
//	vector<string> usernames; // Vector to store usernames from file
//	vector<string> passwords; // Vector to store passwords from file
//	string line;
//
//	// Read usernames and passwords from the files into memory
//	while (getline(usernameFile, line)) {
//		usernames.push_back(line);
//		getline(passwordFile, line);
//		passwords.push_back(line);
//	}
//
//	usernameFile.close(); // Close username file
//	passwordFile.close(); // Close password file
//
//	// Search for the username to find and update the corresponding password
//	bool found = false;
//	for (size_t i = 0; i < usernames.size(); ++i) {
//		if (usernames[i] == usernameToFind) {
//			found = true;
//			passwords[i] = newPassword; // Update password
//			*i_ptr = i; // Store index of updated password
//			break;
//		}
//	}
//
//	if (found) {
//		// Write the updated passwords back to the password file
//		ofstream updatedPasswordFile("userpassword.txt");
//		if (!updatedPasswordFile.is_open()) {
//			cout << "Failed to open updated password file." << endl;
//			return 1;
//		}
//
//		for (size_t i = 0; i < passwords.size(); ++i) {
//			updatedPasswordFile << passwords[i] << endl;
//		}
//
//		updatedPasswordFile.close(); // Close updated password file
//
//		cout << "Password updated successfully." << endl;
//
//	}
//	else {
//		cout << "Username not found." << endl;
//	}
//	return 0;
//}



//function to validate if the string is number
bool check_number(string str) {
	for (int i = 0; i < str.length(); i++) {
		// Check if the character at position i is not a digit
		if (isdigit(str[i]) == false) {
			return false; // If a non-digit character is found, return false
		}
	}
	return true; // If all characters are digits, return true
}

// main menu function definitions
void user_mainmenu(USER c[], int id)
{
	system("CLS"); // Clear the screen
	time_t ttime = time(0); // Variable to store current time
	char* dt = ctime(&ttime); // Get current time as string
	cout << "Today's Date and Time -->\t" << dt << endl; // Print current date and time
	char status = ' '; // Variable to store status
	cout << "========================================================================================================================" << endl;
	cout << left << setw(25) << "Name" << left << setw(20) << "Ic number" << left << setw(23) << "Contact Number" << left << setw(25) << "Status" << left << setw(18)<< endl; // Display column headers
	cout << "========================================================================================================================" << endl;
	cout << left << setw(25);
	cout << c[id].username; // Display username from the USER array
	cout << left << setw(20);
	cout << c[id].ic; // Display IC number from the USER array
	cout << left << setw(23);
	cout << c[id].contactnum; // Display contact number from the USER array
	cout << left << setw(25);
	cout << c[id].status; // Display status from the USER array
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	char ans;

	do {
		cout << "Press <1> to do diagnose" << endl; // Display menu option
		cout << "Press <2> to update your user profile" << endl; // Display menu option
		cout << "Press <3> to review the FAQ" << endl; // Display menu option
		cout << "Press <4> to Exit" << endl << endl; // Display menu option
		cout << "--->";
		cin >> ans; // Get user input
		cout << endl;
	} while (ans != '1' && ans != '2' && ans != '3' && ans != '4'); // Continue to display the menu if input is invalid

	if (ans == '1')
	{
		system("CLS"); // Clear the screen
		diagnose(c, id); // Call the diagnose() function to diagnose
	}

	else if (ans == '2')
	{
		system("CLS"); // Clear the screen
		user_update(c, id); // Call the userupdate() function
	}

	else if (ans == '3')
	{
		system("CLS"); // Clear the screen
		faq(c, id); // Call the faq() function
	}

	else if (ans == '4')
	{
		system("CLS"); // Clear the screen
		exit(); // Call the exit() function
	}

	else
	{
		cout << "invalid input please try again"; // Display error message
		user_mainmenu(c, id); // Call the user_mainmenu() function recursively to retry
	}

	return; // Return from the function
}

//function for user to diagnose their status
void diagnose(USER c[], int id)
{
	int disease; //1 for hyperglycemia, 2 for hypoglycemia, 3 for diabetes
	cout << "Diagnose waiting to be done";
}

//function for user to update their info
int user_update(USER c[], int id)
{
	char choice;
	cout << "    Name: " << c[id].username << endl; // Displaying current name
	cout << "    Ic number: " << c[id].ic << endl; // Displaying current IC number
	cout << "<1> Contact number: " << c[id].contactnum << endl; // Displaying current contact number
	cout << "<2> Status: " << c[id].status << endl; // Displaying current status
	cout << "---------------------------------------------------" << endl; // Displaying separator line
	cout << "Enter number to change: "; // Prompting user to enter their choice
	cin >> choice; // Reading user's choice

	switch (choice)
	{
	case '1':
		updatePhonenum(c, id); // Calling function to update contact number
		break;
	case '2':
		updateStatus(c, id); // Calling function to update status
		break;
	default:
		user_update(c, id); // If invalid choice, recursively calling the same function again
		break;
	}
	return 0;
}

//function for user to update their contact number
int updatePhonenum(USER c[], int id)
{
	string resetphonenum;
	cout << "Enter your new contact number: "; // Prompting user to enter new contact number
	cin >> resetphonenum; // Reading new contact number from user

	string usernameToFind = c[id].username; // Username to find
	string newPhonenum = resetphonenum;

	ifstream usernameFile("username.txt"); // Opening username file for reading
	if (!usernameFile.is_open()) {
		cout << "Failed to open username file." << endl; // Displaying error message if failed to open file
		return 1;
	}

	ifstream phonenumFile("userphone.txt"); // Opening userphone file for reading
	if (!phonenumFile.is_open()) {
		cout << "Failed to open phone number file." << endl; // Displaying error message if failed to open file
		usernameFile.close();
		return 1;
	}

	vector<string> usernames; // Vector to store usernames
	vector<string> phonenum; // Vector to store contact numbers
	string line;

	// Reading usernames and contact numbers from respective files
	while (getline(usernameFile, line)) {
		usernames.push_back(line);
		getline(phonenumFile, line);
		phonenum.push_back(line);
	}

	usernameFile.close();
	phonenumFile.close();

	bool found = false;
	for (size_t i = 0; i < usernames.size(); ++i) {
		if (usernames[i] == usernameToFind) { // Finding username in the vector
			found = true;
			phonenum[i] = newPhonenum; // Updating contact number in the vector
			break;
		}
	}

	if (found) {
		ofstream updatedPhonenumFile("userphone.txt"); // Opening userphone file for writing
		if (!updatedPhonenumFile.is_open()) {
			cout << "Failed to open updated phonenum file." << endl; // Displaying error message if failed to open file
			return 1;
		}

		// Writing updated contact numbers to the file
		for (size_t i = 0; i < phonenum.size(); ++i) {
			updatedPhonenumFile << phonenum[i] << endl;
		}

		updatedPhonenumFile.close();

		cout << "Contact number updated successfully." << endl; // Displaying success message
	}
	else {
		cout << "Username not found." << endl; // Displaying error message if username not found
	}

	return 0;
}

//function for user to update their status
int updateStatus(USER c[], int id)
{
	string resetstatus;
	cout << "Enter your new status: ";
	cin >> resetstatus; // Get the new status from user input

	string usernameToFind = c[id].username; // Username to find
	string newstatus = resetstatus; // Store the new status

	// Open the username text file for reading
	ifstream usernameFile("username.txt");
	if (!usernameFile.is_open()) {
		cout << "Failed to open username file." << endl;
		return 1;
	}

	// Open the status text file for reading
	ifstream statusFile("status.txt");
	if (!statusFile.is_open()) {
		cout << "Failed to open status file." << endl;
		usernameFile.close();
		return 1;
	}

	vector<string> usernames;
	vector<string> status;
	string line;

	// Read usernames and status from the files into memory
	while (getline(usernameFile, line)) {
		usernames.push_back(line);
		getline(statusFile, line);
		status.push_back(line);
	}

	usernameFile.close();
	statusFile.close();

	bool found = false;
	// Search for the username to find and update the corresponding status
	for (size_t i = 0; i < usernames.size(); ++i) {
		if (usernames[i] == usernameToFind) {
			found = true;
			status[i] = newstatus; // Update the status
			break;
		}
	}

	if (found) {
		// Write the updated status back to the status file
		ofstream updatedstatusFile("status.txt");
		if (!updatedstatusFile.is_open()) {
			cout << "Failed to open updated status file." << endl;
			return 1;
		}

		for (size_t i = 0; i < status.size(); ++i) {
			updatedstatusFile << status[i] << endl;
		}

		updatedstatusFile.close();

		cout << "Status updated successfully." << endl;
	}
	else {
		cout << "Username not found." << endl;
	}

	return 0;
}



//function for FAQ
void faq(USER c[], int id)
{
	system("CLS");
	char choose;
	do
	{
		cout << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "This is FAQ:" << endl;
		cout << endl;
		cout << "<1> Questions about Diabetes" << endl;
		cout << "<2> Questions about Hyperglycemia" << endl;
		cout << "<3> Questions about Hypoglycemia" << endl;
		cout << "<4> Back to Main Menu" << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Please type in number--->";
		cin >> choose;
		cout << "" << endl;

		if (choose != '1' && choose != '2' && choose != '3' && choose != '4')
		{
			system("CLS");
			cout << "Invalid input, please type in a valid number!";
		}

	} while (choose != '1' && choose != '2' && choose != '3' && choose != '4');

	//------------------------FAQ main page--------------------------------

	if (choose == '1')
	{
		system("CLS");
		diabetes_faq(c, id);
	}

	else if (choose == '2')
	{
		system("CLS");
		hyperglycemia_faq(c, id);
	}

	else if (choose == '3')
	{
		system("CLS");
		hypoglycemia_faq(c, id);
	}

	else if (choose == '4')
	{
		system("CLS");
		user_mainmenu(c, id);
	}
}

void hyperglycemia_faq(USER c[], int id)
{
	char choose;
	do
	{
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Here are most frequent question asked:" << endl;
		cout << endl;
		cout << "<1> What is hyperglycemia?" << endl;
		cout << "<2> What are the symptoms of hyperglycemia?" << endl;
		cout << "<3> Can hyperglycemia be dangerous?" << endl;
		cout << "<4> What foods should I avoid during hyperglycemia?" << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Type in a number>>";
		cin >> choose;

		if (choose != '1' && choose != '2' && choose != '3' && choose != '4')
		{
			system("CLS");
			cout << "Invalid input, please type in a valid number!";
		}

	} while (choose != '1' && choose != '2' && choose != '3' && choose != '4');

	//----------------------Hyperglycemia faq main page---------------------

	if (choose == '1')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What is hyperglycemia?" << endl;
		cout << endl;
		cout << "High blood sugar levels characterize the disease known as hyperglycemia, " << endl;
		cout << "which is frequently linked to diabetes. It happens when the body can't" << endl;
		cout << " utilise insulin properly or doesn't produce enough of it." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}
	}

	if (choose == '2')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What is the symptoms of hyperglycemia?" << endl;
		cout << endl;
		cout << "Frequent urine, excessive thirst, increased hunger, exhaustion, impaired vision, dry mouth, " << endl;
		cout << "sluggish wound healing, recurring infections, unexplained weight loss, and occasionally " << endl;
		cout << "disorientation or nausea are signs of hyperglycemia, or high blood sugar. These signs and " << endl;
		cout << "symptoms result from the body's failure to control blood sugar levels effectively. " << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}

	}

	if (choose == '3')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Can hyperglycemia be dangerous?" << endl;
		cout << endl;
		cout << "Yes,Diabetes complications, such as diabetic ketoacidosis (DKA) in Type 1 diabetes, " << endl;
		cout << "can result from persistent or extreme high blood sugar levels. In the extreme condition" << endl;
		cout << "known as DKA, the body begins metabolizing fat for energy, which causes an accumulation of" << endl;
		cout << "ketones and a risky change in blood pH. Persistent hyperglycemia in Type 2 diabetes can lead" << endl;
		cout << "to long-term issues with the heart, kidneys, nerves, vision, and blood vessels." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}
	}

	if (choose == '4')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What foods should I avoid during hyperglycemia?" << endl;
		cout << endl;
		cout << "It's crucial to stay away from meals that might quickly boost blood sugar levels when you have hyperglycemia. " << endl;
		cout << " Sugary drinks, sweets, desserts, and other foods high in refined sugars are some examples.Limit your" << endl;
		cout << "intake of processed foods as well, especially those with high carbohydrate and sugar content.White bread, " << endl;
		cout << "white rice, and sugary cereals should be avoided. Instead, emphasize full,unprocessed foods that can help" << endl;
		cout << "regulate blood sugar levels and improve general health, such as vegetables, whole grains, lean meats, and healthy fats." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}
	}

}

void hypoglycemia_faq(USER c[], int id)
{
	char choose;
	do
	{
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Here are most frequent question asked:" << endl;
		cout << endl;
		cout << "<1> What is hypoglycemia?" << endl;
		cout << "<2> What causes hypoglycemia?" << endl;
		cout << "<3> What are the symptoms of hypoglycemia？" << endl;
		cout << "<4> How can I prevent hypoglycemia?" << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Type in a number>>";
		cin >> choose;

		if (choose != '1' && choose != '2' && choose != '3' && choose != '4')
		{
			system("CLS");
			cout << "Invalid input, please type in a valid number!";
		}

	} while (choose != '1' && choose != '2' && choose != '3' && choose != '4');

	//----------------------Hypoglycemia faq main page---------------------

	if (choose == '1')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What is hypoglycemia?" << endl;
		cout << endl;
		cout << "Blood sugar levels that are excessively low, usually below 70 mg/dL, are indicative of the condition known" << endl;
		cout << "as hypoglycemia. From minor pain to serious consequences, it may produce symptoms." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			system("CLS");
			user_mainmenu(c, id);
		}

	}

	if (choose == '2')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What causes hypoglycemia?" << endl;
		cout << endl;
		cout << "If you take too much insulin or some diabetic drugs, skip meals, exercise a lot without adjusting" << endl;
		cout << "your insulin or food intake, take alcohol without eating enough, or postpone or skip meals," << endl;
		cout << "you could develop hypoglycemia." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}

	}

	if (choose == '3')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What are the symptoms of hypoglycemia？" << endl;
		cout << endl;
		cout << "Shivering, sweating, dizziness, irritability, a quick heartbeat, hunger, and confusion are just" << endl;
		cout << "a few of the symptoms of hypoglycemia, or low blood sugar. More severe cases may cause memory" << endl;
		cout << "loss, headaches, blurred vision, weakness, convulsions, or even coma. These signs and symptoms" << endl;
		cout << "appear because the brain uses glucose as fuel and is affected when blood sugar levels go too low." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}
	}

	if (choose == '4')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "WHow can I prevent hypoglycemia?" << endl;
		cout << endl;
		cout << "Maintain a regular eating schedule with well-balanced meals and snacks to prevent hypoglycemia." << endl;
		cout << "Maintain regular blood sugar monitoring, and adjust insulin or medicine dosages as necessary." << endl;
		cout << "To swiftly treat moderate episodes, carry fast-acting carbs like glucose pills, fruit juice, or candies." << endl;
		cout << " If you want to exercise, check your blood sugar levels before and after, and make any necessary diet" << endl;
		cout << " or insulin adjustments. To fine-tune your management strategy and reduce the risk of hypoglycemia," << endl;
		cout << " communication with your healthcare practitioner and diabetes care team is crucial." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}
	}

}

void diabetes_faq(USER c[], int id)
{

	char choose;
	do
	{
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Here are most frequent question asked:" << endl;
		cout << endl;
		cout << "<1> What is diabetes?" << endl;
		cout << "<2> What are the types of diabetes?" << endl;
		cout << "<3> What is HbA1c, and why is it important?" << endl;
		cout << "<4> What is insulin, and when is it needed?" << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "Type in a number>>";
		cin >> choose;

		if (choose != '1' && choose != '2' && choose != '3' && choose != '4')
		{
			system("CLS");
			cout << "Invalid input, please type in a valid number!";
		}

	} while (choose != '1' && choose != '2' && choose != '3' && choose != '4');

	//----------------------Hyperglycemia faq main page---------------------

	if (choose == '1')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What is diabetes?" << endl;
		cout << endl;
		cout << "Diabetes is a chronic medical disorder in which your blood sugar levels are perpetually" << endl;
		cout << "higher than normal due to either insufficient insulin production or inefficient insulin usage." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}
	}

	if (choose == '2')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What are the types of diabetes?" << endl;
		cout << endl;
		cout << "Type 1 diabetes, an autoimmune disorder in which the body doesn't make insulin, Type 2  " << endl;
		cout << "diabetes, characterized by insulin resistance and insufficient insulin production, and" << endl;
		cout << "gestational diabetes, which develops during pregnancy and frequently goes away after giving birth," << endl;
		cout << "are the three primary kinds of diabetes. Each category has unique causes and methods of care." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}

	}

	if (choose == '3')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What is HbA1c, and why is it important?" << endl;
		cout << endl;
		cout << "Hemoglobin A1c, often known as HbA1c, is a blood test that gauges the typical blood sugar levels " << endl;
		cout << "during the previous two to three months. Due to the information it offers about long-term " << endl;
		cout << "glucose control, it is crucial for the management of diabetes. Poorer blood sugar management," << endl;
		cout << "which raises the risk of diabetic complications, is indicated by a greater HbA1c.Regular" << endl;
		cout << "HbA1c monitoring aids healthcare professionals in evaluating the efficacy of treatments" << endl;
		cout << "and making necessary adjustments to their plans." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}
	}

	if (choose == '4')
	{
		system("CLS");
		char choose_BM;
		//display information for faq of hyperglycemia
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "What is insulin, and when is it needed?" << endl;
		cout << endl;
		cout << "The pancreas secretes the hormone insulin, which aids in controlling blood sugar levels. It permits" << endl;
		cout << "the bloodstream's glucose to be absorbed by cells for energy. Since their pancreas cannot create any insulin," << endl;
		cout << "people with Type 1 diabetes need it constantly. When oral medications or lifestyle modifications are insufficient" << endl;
		cout << "to properly control blood sugar levels, some people with Type 2 diabetes may need insulin." << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << "<B>ack		<M>ain menu" << endl;
		cout << "(B/M)?--->";
		cin >> choose_BM;

		// Take user input for choice and convert it to uppercase
		choose_BM = toupper(choose_BM);

		// Validate user input and loop until a valid choice is entered
		while (choose_BM != 'B' && choose_BM != 'M')
		{
			cout << "Invalid input, please try again" << endl;
			cout << "(B/M)?--->";
			cin >> choose_BM;
			choose_BM = toupper(choose_BM);
		}

		// Based on user choice, call appropriate functions (faq or mainmenu)
		if (choose_BM == 'B')
		{
			faq(c, id);
		}
		else if (choose_BM == 'M')
		{
			cout << "wait for program done";
			//back to main menu
		}
	}
}






// Doctor login function definition
void doctor_mainmenu(USER c[], int id)
{
	system("CLS"); // Clear the screen
	time_t ttime = time(0); // Variable to store current time
	char* dt = ctime(&ttime); // Get current time as string
	cout << "Today's Date and Time -->\t" << dt << endl; // Print current date and time
	char status = ' '; // Variable to store status
	cout << "========================================================================================================================" << endl;
	cout << "   " << left << setw(25) << "Name" << left << setw(20) << "Ic number" << left << setw(23) << "Contact Number" << left << setw(25) << "Status" << left << setw(18) << endl; // Display column headers
	cout << "========================================================================================================================" << endl;
	for (int i = 0; i < 20; i++)
	{
		cout << i+1 << "." << " ";
		cout << left << setw(25);
		cout << c[id].username; // Display username from the USER array
		cout << left << setw(20);
		cout << c[id].ic; // Display IC number from the USER array
		cout << left << setw(23);
		cout << c[id].contactnum; // Display contact number from the USER array
		cout << left << setw(25);
		cout << c[id].status; // Display status from the USER array
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "1. hyperglycemia" << endl;
	cout << "2. hypoglycemia" << endl;
	cout << "3. diabetes" << endl;
	cout << endl;
	cout << endl;
	int decision;
	cout << "Enter the index number of the patient to provide feedback:\t>>> ";
	cin >> decision;
	//make decision redirect to the specific patient and record down the feedback in feedback.txt

}

void feedback()
{
	cout << "Feedback waiting to be done";
}



void exit()
{
	cout << "EXIT";
}