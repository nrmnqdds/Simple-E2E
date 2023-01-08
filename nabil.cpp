#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void Login();
void Action();
void StoreMessage();
void ViewMessage();
void Logout();
void Continue();
void Banned();
string encryptData(string data);
string decryptData(string data);

int main(){
	
	Login();
	Action();
	Logout();
	
	return 0;
}

void Action(){
	
	int choice;
	
	do{
		
		cout << "\tWELCOME ADMIN!" << endl << endl;
		
		cout << "1. Store a message" << endl << "2. View a message" << endl << "3. Log out" << endl << endl << "Hi admin, what would you like to do now? => ";
		cin >> choice;
		
		switch(choice){
			case 1:
				system("cls");
				StoreMessage(); break;
			case 2:
				system("cls");
				ViewMessage(); break;	
		}
	}while(choice!=3);
	
}

void StoreMessage(){
	
	string password, message;
	
	ofstream messagefile;
	messagefile.open("message.txt");
	
	ofstream passwordfile;
	passwordfile.open("password.txt");
	
	cout << "Create your password: ";
	cin >> password;
	
	string encryptedData = encryptData(password);
	cout << "Encrypted data: " << encryptedData << endl;
	passwordfile << encryptedData;
	
	cout << endl << "Enter your message: ";
	cin.ignore();
	getline(cin, message);
	messagefile << message;
	
	cout << "Your message has been stored successfully";
	
	passwordfile.close();
	messagefile.close();
	Continue();
}


void ViewMessage(){
	
	string password, message, userpassword;
	
	ifstream read("message.txt");
	bool isEmpty = read.peek() == EOF;
	if(isEmpty==true){
		cout << "No file";
		Continue();
		return;
	}
	
	ifstream messagefile;
	messagefile.open("message.txt");
	
	ifstream passwordfile;
	passwordfile.open("password.txt");
	
	passwordfile >> password;
	cin.ignore();
	getline(messagefile, message);
	
	while(true){
		cout << "Enter password to decrypt the message:" << endl << "Hint: " << password << endl << endl << "=> ";
		getline(cin, userpassword);
		
		string decryptedData = decryptData(password);
		
		if(userpassword==decryptedData){
			cout << endl << "Correct! Here are the message: " << endl << message;
			break;
		}else{
			cout << "Wrong! Try again!" << endl << endl;
		}
	}
	
	
	passwordfile.close();
	messagefile.close();
	Continue();
}

string encryptData(string data){
	string encryptedData;
	
	for (int i = 0; i < data.length(); i++){
		encryptedData += (char)(data[i] + i + 1);
	}
	
	return encryptedData;
}

string decryptData(string data){
	
	string decryptedData;
	
	for (int i = 0; i < data.length(); i++){
		decryptedData += (char)(data[i] - i - 1);
	}
	
	return decryptedData;
}

void Logout(){
	
	system("cls");
	
	int choice;
	
	cout << "1. Log In" << endl << "2. Exit Program" << endl << endl << "=> ";
	cin >> choice;
	
	switch(choice){
		case 1:
			system("cls");
			main(); break;
		default:
			cout << "Thankyou for using our program!"; break;
	}
	
}

void Login(){

	const string username[2]={"admin1", "admin2"};
	const string password[2]={"admin2", "admin1"};
	
	string setusername, setpassword;
	int count=0;
	bool succ;
	
	do{
		cout << "\tKindly log in to your account" << endl << endl;
		cout << "Username: ";
		cin >> setusername;
		cout << "Password: ";
		cin >> setpassword;
		
		for(int i=0; i<2; i++){
			if(setusername==username[i] && setpassword==password[i]){
				cout << "Login Successful!" << endl << endl << "Press any key to continue";
				getch();
				system("cls");
				succ=true;
				break;
			}else if(i==1 && (setusername!=username[i] || setpassword!=password[i])){
				cout << "Try again!" << endl << endl;
				count++;
				if(count==3){
					Banned();
				}
			}
		}
		if(succ){
			break;
		}
	}while(count!=3);
	
}

void Banned(){
	
	system("cls");
	cout << endl << "You are unable to access the program";
	Continue();
	Banned();
	
}

void Continue(){
	
	cout << endl << endl << "Press any key to continue";
	getch();
	system("cls");
	
}


