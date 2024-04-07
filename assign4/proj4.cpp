#include <iostream>
#include <string>
#include <sstream>
//#include "hashtable.h"
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

string getInput()
{
    string str;
    getline(cin, str);
    return str;
}

int main() {

    string hashsize_t;
    // choice the size of the hashtable
    cout << "Enter preferred hash table capacity:" << endl;
    getline(cin, hashsize_t);

    stringstream stream(hashsize_t);
 
    // associating a string object with a stream
    size_t hashsize;
 
    // to read something from the stringstream object
    stream >> hashsize;

    PassServer p(hashsize);

    string choice;
    string username;
    string password;
    string newpassword;

    Menu();
    while (getline(cin, choice)){
	if(choice == "x")
	    break;
	if(choice == "l"){
	    cout << "Enter password file name to load from: ";
	    string str = getInput();
	    if(!p.load(str.c_str()))
		cout << "Error: Cannot open file " << str << "." << endl;
	    Menu();
	}
	else if(choice == "a"){
	    cout << "Enter username: " ;
	    username = getInput();
	    cout << "Enter password: " ;
	    password = getInput();
	    if(p.addUser(make_pair(username, password)))
		cout << "User " << username << " added. " << endl;
	    else
		cout << "*****Error: User already exists. Could not add user." << endl;
	    Menu();
	}
	else if(choice == "r"){
	    cout << "Enter username: " ;
	    username = getInput();
	    if(p.removeUser(username))
		cout << "User " << username << " deleted." << endl;
	    else
		cout << "*****Error: User not found.  Could not delete user." << endl;
	    Menu();
	}
	else if(choice == "c"){
	    cout << "Enter username: ";
	    username = getInput();
	    cout << "Enter password: ";
	    password = getInput();
	    cout << "Enter new password: ";
	    newpassword = getInput();
	    if(p.changePassword(make_pair(username, password), newpassword))
		cout << "Password changed for user " << username << endl;
	    else
		cout << "*****Error: Could not change user password" << endl;
	    Menu();
	}
	else if(choice == "f"){
	    cout << "Enter username: ";
	    username = getInput();
	    if(p.find(username))
		cout << "User \'" << username << "\' found. " << endl; 
	    else
		cout << "User \'" << username << "\' not found. " << endl; 

	    Menu();
	}
	else if(choice == "d"){
	    p.dump();
	    Menu();
	}
	else if(choice == "s"){
	    cout << "Size of hashtable: " << p.size() << endl;
	    Menu();
	}
	else if(choice == "w"){
	    cout << "Enter password file name to write to: ";
	    string str = getInput();
	    p.write_to_file(str.c_str());
	    Menu();
	}
	else{
	    cout << "****Error: Invalid entry. Try again." << endl;
	    Menu();
	}
    } 
	
}
