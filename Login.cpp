#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class loginpage{
	string username, password;
	string regname, regpass;
	string email;
		
	public:
		void dispWelcome();
		int operation();
		bool verifyLogin();
		void registerpage();
		void forget();

};

void loginpage::dispWelcome(){
	system("Color 0A");
	cout << "==============================================================================" << endl;
	cout << "|                                                                            |" << endl; 
	cout << "|                                                                            |" << endl; 
	cout << "|                                                                            |" << endl; 
	cout << "|                                                                            |" << endl; 
	cout << "|                                                                            |" << endl; 
	cout << "|                        Welcome to MITI login page                          |" << endl;
	cout << "|                                                                            |" << endl; 
	cout << "|                                                                            |" << endl; 
	cout << "|                                                                            |" << endl; 
	cout << "|                                                                            |" << endl; 
	cout << "|                                                                            |" << endl; 
	cout << "==============================================================================" << endl;
}

int loginpage::operation(){
	int choice;
	
	cout << "Please slect: " << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Forget Password" << endl;
	cout << "4. EXIT" << endl;
	cout << endl;
	cout << "Enter your choice : ";
	cin >> choice;
	cin.ignore();
	system("cls");
	return choice;
}

bool loginpage::verifyLogin(){
	bool verify = false;
	ifstream input("database.txt");
	
	string user, pass;
	cout << "==================LOGIN==================" << endl;
	cout << "Enter the username : ";
	cin >> username;
	cout << "Enter the password : ";
	cin >> password;
	
	if(!input){
		cout << "ERROR! Login system have some error. Please try it later!" << endl;
		exit(1);
	}else{
		while(input >> user >>pass) 
		{
			if(username == user && password == pass){
				verify = true;
			}
		}
	}
	
	input.close();
	
	return verify;
}

void loginpage::registerpage(){
	string checkname, tempass, tempe;
	
	ifstream analyse("database.txt");
	ofstream reg("database.txt", ios::app);

	cout << "==================REGISTER==================" << endl;
	cout << "Enter the username : ";
	cin>>regname;
	cout << "Enter the password : ";
	cin>>regpass;
	
	cout << "For safety purpose, please fill in the information below: " << endl;
	cout << "Email: ";
	cin >> email;
	
	while(analyse >> checkname >> tempass >> tempe){
		if(checkname == regname){
			cout << "The username has been register!" << endl;
			cout << endl;
			return;
		}
	}

	if(!reg){
		cout << "ERROR! Register system have some error. Please try it later!" << endl;
		exit(1);
	}else{
		reg << regname << " " << regpass << " "<<email << endl;
		cout << "Registration Successfully" << endl;

	}
	
	analyse.close();
	reg.close();
}

void loginpage::forget(){
	string name , emel;
	string tempass, tempEmel;
	string A,B,C;
	bool S1_verify = false;
	
	ifstream searchpass("database.txt");
	
	cout << "==================FORGET PASSWORD==================" << endl;
	cout << "Enter remembered username: " ;
	cin >> name;
	cout << endl;

	if(!searchpass){
		cout << "ERROR! Searching password system have some error. Please try it later!" << endl;
		exit(1);
	}else{
		while(searchpass >> username >> password >> email){
			if(name == username){
				tempass = password;
				tempEmel = email;
				S1_verify = true;
			
			}
		}
	}

	if(S1_verify == true){
			cout << "To get back your password, you are required to fill in the information with correct answer" <<endl;
			cout << "Enter your email: ";
			cin >> emel;

			if(emel == tempEmel){
				cout << "You are correct!" << endl;
				cout << "Your password : " << tempass <<endl;
			}else{
				cout << "Your answer is incorrect!" <<endl;
				return;
			}
	}else{
		cout << "Your username is incorrect! " <<endl;
	}

}

int main(){
	loginpage L;
	int choice;
	bool verify = false;

	L.dispWelcome();
	choice = L.operation();
	while(choice <1 || choice >4){
		cout << "Please enter the correct option" << endl;
		cout << "TRY AGAIN" << endl;
		cout << endl;
	L.dispWelcome();		
	choice = L.operation();
	}
	
	while(choice !=5 ){
		switch(choice){
			case 1: 
					verify = L.verifyLogin();
					
					if(verify == true){
						cout << "Login successfully!" << endl;
					}else{
						cout << "Username or Password or both incorrect" << endl;
						cout << endl;	
					}
				break;
			case 2: L.registerpage(); 
				break;
			case 3: L.forget();
				break;
		}
	L.dispWelcome();		
	choice = L.operation();		
	}
	
}
