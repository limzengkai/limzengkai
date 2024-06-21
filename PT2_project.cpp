
///////////////////////////////////////////////////////////////////////////////////////////////
///////						TITLE : MITI REGISTRATION SYSTEM                             //////
///////////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<ctime>
#include<cstring>
#define SIZE 50
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   loginpage   /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

class loginpage{
	//encapsulation and data hiding
	private:
		string username, password;
		string regname, regpass;
		string email;
		
	public:
		void dispWelcome();
		int operation();
		bool verifyLogin();
		void registerpage();
		void forget();
		void dispProfile();
		string getusername(){
			return username;
		}

};

//display of the login page
void loginpage::dispWelcome(){
	system("Color E0");
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
	
	cout << "Please select: " << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Forget Password" << endl;
	cout << "4. EXIT" << endl;
	cout << endl;
	cout << "Enter your choice : ";
	cin >> choice;
	cin.ignore();
	system("pause");
	system("cls");
	return choice;
}

bool loginpage::verifyLogin(){
	bool verify = false;
	//file operation (input)
	ifstream input("database.txt");

	string user, pass, tempemail;
	cout << "==================LOGIN==================" << endl;
	cout << "Enter the username : ";
	cin >> username;
	cout << "Enter the password : ";
	
	char ch = _getch();
	while(ch != 13) { //character 13 is enter
		if(ch == 8){ //character 8 is back space		
			if(password.size() != 0){
				password.pop_back(); //if the user press backspace, delete the input just now
				cout << "\b \b"; //delete the * printed just now
			}
		}
	    else {
	      	password.push_back(ch); //The push_back() method puts the character specified as parameter at the end of the string.
			cout << '*'; //Since nothing has been displayed from the input entered -> we display an asterisk ( '*' ) for every key.
		} 
      	ch = _getch();
   	}
   	
   	cout << endl;
   	
	if(!input){
		cout << "ERROR! Login system have some error. Please try it later!" << endl;
		exit(1);
	}else{
		while(!input.eof()) 
		{
			getline(input, user, ',');
			getline(input, pass, ',');
			getline(input, tempemail);
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
	char choice, choice1, choice2;
	//file operation (output-append)
	ofstream reg("database.txt", ios::app);

	do{
		choice = ' ';
	
		do{
			choice1 = ' ';	
			cout << "==================REGISTER==================" << endl;
			cout << "Enter the username : ";
			getline(cin, regname, '\n');
			
			//exception handling
			//The is restriction on the length of username 
			try{
				if(regname.size() < 7){
					throw "The length of your input less 7";
				}

			}
			catch (const char *msg){
				cout << msg << endl;
				cout << "Please enter the username with length more or equal to 7" << endl;	
				cout << endl;
				cout << "Do you want to continue registration?(Y/N) => ";
				cin >> choice1;
				cout << endl;
				
				//Back to login page
				if(toupper(choice1) == 'N' ){
					system("pause");
					system("cls");
					return;
				}else if(toupper(choice1) == 'Y'){
					system("pause");
					system("cls");
					cin.ignore();
				}else{
					cout << "Error! Please enter Y/N, the system will direct back to login page!" <<endl;
					system("pause");
					system("cls");
					return;
				}

			}

		}while(toupper(choice1) == 'Y');
		
		//file operation (input)
		ifstream analyse("database.txt");
		while(!analyse.eof()){

			getline(analyse, checkname, ',');
			getline(analyse, tempass, ',');
			getline(analyse, tempe);
			//exception handling
			//This used for check the existing username
			try{
				if(checkname == regname){
					//close the file
					analyse.close();
					throw "The username has been register!";
				}
			}
			catch (const char *othermsg){
				cout << othermsg << endl;
				cout << "Please register with other username" << endl;
				cout << endl;
				cout << "Do you want to continue registration page?(Y/N) => ";
				cin >> choice;
				
				if(toupper(choice) == 'N'){
					system("pause");
					system("cls");
					analyse.close();
					return;
				}else if(toupper(choice) == 'Y'){
					system("pause");
					system("cls");
					cin.ignore();
				}else{
					cout << "Error! Please enter Y/N, the system will direct back to login page!" <<endl;
					system("pause");
					system("cls");
					analyse.close();
					return;
				}
			}
		}

	}while(toupper(choice) == 'Y');
	
	do{
		choice2 = ' ';	
		cout << "Enter the password : ";
		getline(cin, regpass, '\n');
		
		//exception handling
		//There is restriction on the length of password
		try{
			if(regpass.size() < 7 || regpass.size() > 20){
				throw "The length of your input must in between 7 and 20(include)";
			}
		}
		catch (const char *pssmsg){
			cout << pssmsg << endl;
			cout << "Please enter the password with length in between 7 and 20(include)" << endl;	
			cout << endl;
			cout << "Do you want to continue with password registration?(Y/N) => ";
			cin >> choice2;
			cin.ignore();
				if(toupper(choice2) == 'N'){
					system("pause");
					system("cls");
					return;

				}else if(toupper(choice2) == 'Y'){
					system("cls");
					cout << "==================REGISTER==================" << endl;
					cout << "Enter the username : " << regname << endl;
				
				}else{
					cout << "Error! Please enter Y/N, the system will direct back to login page!" <<endl;
					system("pause");
					system("cls");
					return;
				}
			}	
	}while(toupper(choice2) == 'Y');
	
	cout << endl;
	cout << "For safety purpose, please fill in the information below: " << endl;
	cout << "Email: ";
	cin >> email;

	if(!reg){
		cout << "ERROR! Register system have some error. Please try it later!" << endl;
		exit(1);
	}else{
		reg << endl;
		reg << regname << "," << regpass << ","<<email;
		cout << "Registration Successfully" << endl;
	}
	system("pause");
	system("cls");

	reg.close();
}

void loginpage::forget(){
	string name , emel;
	string storname, storpass, storemail;
	string tempass, tempEmel;
	bool S1_verify = false;
	
	//file operation (input)
	ifstream searchpass("database.txt");
	
	cout << "==================FORGET PASSWORD==================" << endl;
	cout << "Enter remembered username: " ;
	cin >> name;
	cout << endl;
	
	if(!searchpass){
		cout << "ERROR! Searching password system have some error. Please try it later!" << endl;
		exit(1);
	}else{
		while(!searchpass.eof()){
			getline(searchpass,storname,',');
			getline(searchpass,storpass,',');
			getline(searchpass,storemail);
			
			if(name == storname){
				tempass = storpass;
				tempEmel = storemail;
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
				system("pause");
				system("cls");
				return;
			}
	}else{
		cout << "Your username is incorrect! " <<endl;
	}
	system("pause");
	system("cls");
	searchpass.close();
}

void loginpage::dispProfile(){
	//file operation (input)
	ifstream input("database.txt");
	string tempname, temppass, tempemail;
	
		if(!input){
			cout << "There are some error! " << endl;
		
		}else{
			while(!input.eof()){
				getline(input, tempname, ',');
				getline(input, temppass, ',');
				getline(input, tempemail);

				if(tempname == username){
					cout << "========================User Profile========================" << endl;
					cout << "Username: " << username << endl;
					cout << "Email: " << tempemail << endl << endl;
				}
			}	
		}
	input.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////   Admin   //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

class Admin{
	//encapsulation and data hiding
	string adminName, adminPassword;
		
	public:
		Admin(){}
		Admin(string adminName, string adminPassword){
			this->adminName=adminName;
			this->adminPassword=adminPassword;
		}
		void Writefile();
		bool Adminlogin();
		void addAdmin();
		void VerifyUser();
		void viewUser();
};

bool Admin::Adminlogin() {
	string tempuser, temppass;
	bool verify = false;
	//file operation (input)
	ifstream input("admin.txt");

	cout << "==================ADMIN LOGIN==================" << endl;
	cout << "Enter the admin name : ";
	cin >> adminName;
	cout << "Enter the password : ";

	char ch = _getch();
	while(ch != 13) { //character 13 is enter
		if(ch == 8){ //character 8 is back space		
			if(adminPassword.size() != 0){
				adminPassword.pop_back(); //if the user press backspace, delete the input just now
				cout << "\b \b"; //delete the * printed just now
			}
		}
	    else {
	      	adminPassword.push_back(ch); //The push_back() method puts the character specified as parameter at the end of the string.
			cout << '*'; //Since nothing has been displayed from the input entered -> we display an asterisk ( '*' ) for every key.
		} 
      	ch = _getch();
   	}
	
	if(!input){
		cout << "ERROR! Login system have some error. Please try it later!" << endl;
		exit(1);
	}
	else{
		while(!input.eof()) {
			getline(input,tempuser,',');
			getline(input,temppass);
			if(adminName==tempuser && adminPassword==temppass) 
				verify = true;
		}
	}

	input.close();
	return verify;
}

void Admin::addAdmin(){
	//file operation (output - append mode)
	ofstream admin2("admin.txt", ios::app);
	cout << "==================ADMIN  ACCOUNT==================" << endl;
	cout << "Enter admin username : ";
	cin >> adminName;
	cout << "Enter admin password : ";
	cin >> adminPassword;
	admin2 << adminName << "," << adminPassword << endl;
}

void Admin::VerifyUser(){
	string tempname, Cname, SSM, loc, lis, Date, add, type, estimated, total, Coname, des, no, email, subtime, satus;
	string Rtempname[SIZE], RCname[SIZE], RSSM[SIZE], Rloc[SIZE],Rlis[SIZE],RDate[SIZE], Radd[SIZE], Rtype[SIZE],Restimated[SIZE], Rtotal[SIZE],
		   RConame[SIZE], Rdes[SIZE], Rno[SIZE], Remail[SIZE], Rsubtime[SIZE], Rsatus[SIZE];
	string CCname[SIZE], CSSM[SIZE], Cloc[SIZE], Clis[SIZE],CDate[SIZE], Cadd[SIZE], Ctype[SIZE],Cestimated[SIZE], Ctotal[SIZE],
		   CConame[SIZE], Cdes[SIZE], Cno[SIZE], Cemail[SIZE], Csubtime[SIZE] ,Csatus[SIZE];
	char c3;

	//To get the numberof User haven't lulus
	do{
		//file operation (input)
		ifstream Rinfo("UserInfo.txt");
		int count = 0, count2 = 0;
		int count3[SIZE];
		int c;
		char c1;
		if(!Rinfo){
			
			cout << "Cannot open file" << endl;
			
		}else{

			while(!Rinfo.eof()){
				getline(Rinfo, tempname, ',');
				getline(Rinfo, Cname,',');
				getline(Rinfo, SSM,',');
				getline(Rinfo, loc,',');
				getline(Rinfo, lis,',');
				getline(Rinfo, Date,',');
				getline(Rinfo, add,',');
				getline(Rinfo, type,',');
				getline(Rinfo, estimated,',');
				getline(Rinfo, total,',');
				getline(Rinfo, Coname,',');
				getline(Rinfo, des,',');
				getline(Rinfo, no,',');
				getline(Rinfo, email,',');
				getline(Rinfo, subtime,',');
				getline(Rinfo, satus);
				
				Rtempname[count] = tempname;
				RCname[count] = Cname;
				RSSM[count] =  SSM;
				Rloc[count] = loc;
				Rlis[count] = lis;
				RDate[count] = Date;
				Radd[count] = add;
				Rtype[count] = type;
				Restimated[count] = estimated;
				Rtotal[count] = total;
				RConame[count] = Coname;
				Rdes[count] = des;
				Rno[count] = no;
				Remail[count] = email;
				Rsubtime[count] = subtime;
				Rsatus[count] = satus;

				if(satus == "baharu"){
					count3[count2] = count;
					count2++;
				}
				count++;
			}
		}

	system("pause");
	system("cls");

	if(count2 == 0){
		cout << "No more registration! " <<endl;
		break;
	}else{
		cout << endl;
		cout << "==================COMPANY NAME=================" << endl;
		for(int i=0; i<count2; i++){
			//assign the baharu item into the variable.
				CCname[i] = RCname[count3[i]];
				CSSM[i] =  RSSM[count3[i]];
				Cloc[i] = Rloc[count3[i]];
				Clis[i] = Rlis[count3[i]];
				CDate[i]  = RDate[count3[i]];
				Cadd[i]  = Radd[count3[i]];
				Ctype[i]  = Rtype[count3[i]];
				Cestimated[i]  = Restimated[count3[i]];
				Ctotal[i]  = Rtotal[count3[i]];
				CConame[i] = RConame[count3[i]];
				Cdes[i]  = Rdes[count3[i]];
				Cno[i]  = Rno[count3[i]];
				Cemail[i]  = Remail[count3[i]];
				Csubtime[i] = Rsubtime[count3[i]];
				Csatus[i]  = Rsatus[count3[i]];
			cout << i+1 << ".  " << RCname[count3[i]] << endl;
		}
	
		cout << endl;
		cout << "Please choose the company => ";
		cin >> c;
		system("pause");
		system("cls");
		cout << "==================COMPANY INFORMATION=================" << endl;
		cout << "Company Name : " << CCname[c-1] << endl;
		cout << "SSM No. : " << CSSM[c-1] << endl;
		cout << "Local Authority License No. : " << Cloc[c-1] << endl;
		cout << "Local Authority Name : " << Clis[c-1] << endl;
		cout << "Date of Incorporation [dd-mm-yyyy] : " << CDate[c-1] << endl;
		cout << "Enter you company address : " << Cadd[c-1] << endl;
		cout << endl;
		cout << "==================Cluster Economy==================" << endl;
		cout << "Sector : " << Ctype[c-1] << endl;
		cout << "Estimated revenue of your company : RM" <<setw(2) << fixed << Cestimated[c-1] << endl;
		cout << "The latest total employees : "<< Ctotal[c-1] << endl;
		cout << endl;
		cout << "==================Contact Person==================" << endl;
		cout << "Name : " << CConame[c-1] << endl;
		cout <<	"Designation : " << Cdes[c-1] << endl;
		cout <<	"No. of telephone : " << Cno[c-1] << endl;
		cout <<	"Email : " << Cemail[c-1] << endl;
		cout <<	"Satus : " << Csatus[c-1] << endl;
		cout << "The submission time and date : " << Csubtime[c-1] << endl;
	
		cout << "Press (Y/y) to agree with the registration => ";
		cin >> c1;
		if(toupper(c1) == 'Y'){
			Csatus[c-1] = "lulus";
		}else{
			Csatus[c-1] = "xlulus";
		}

		for(int i=0; i<count2; i++){
		Rsatus[count3[i]] = Csatus[i] ;
		}
		
		//file operation (output)
		ofstream Winfo("UserInfo.txt");
 		for(int i=0; i<count-1; i++){
			Winfo << Rtempname[i] << "," << RCname[i]  << "," << RSSM[i] << "," << Rloc[i] << "," << Rlis[i] << "," << RDate[i] << "," << Radd[i] << "," << Rtype[i] << "," << Restimated[i]
			      << "," << Rtotal[i]  << "," << RConame[i] << "," << Rdes[i] << "," << Rno[i] << "," << Remail[i] << ',' << Rsubtime[i] << "," << Rsatus[i] << endl;
		}
		//The below code is used to save the information in .txt file without next line, This is becuase when the .txt file have the free space line and it will cause some error on the system
			Winfo << Rtempname[count-1] << "," << RCname[count-1]  << "," << RSSM[count-1] << "," << Rloc[count-1]<< "," << Rlis[count-1] << "," << RDate[count-1] << "," << Radd[count-1] << "," << Rtype[count-1] << "," << Restimated[count-1]
			      << "," << Rtotal[count-1]  << "," << RConame[count-1] << "," << Rdes[count-1] << "," << Rno[count-1] << "," << Remail[count-1] << "," << Rsubtime[count-1] << ","<< Rsatus[count-1];
		
		cout << "Do you want to continue with the Verify registration? (Y/N) => ";
		cin >> c3;
		
			Winfo.close();
			Rinfo.close();
		}
	}while(toupper(c3) == 'Y');

}

void Admin::viewUser(){
	int count = 0;
	string name, password, email;
	//file operatinon(input)
	ifstream input("database.txt");
		cout << endl;
		cout << "========================================USER DATA========================================" << endl;
		cout << setw(5) << "NO. " << left << setw(20) << "USERNAME" << setw(20) << "PASSWORD" << "EMAIL" << endl;
	while(!input.eof())
	{
		getline(input, name, ',');
		getline(input, password, ',');
		getline(input, email);
		cout << count+1 << ".  " << setw(20) << name << setw(20) << password << email << endl;
		count++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////   Contact   ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//apply composition to Application Form
class Contact{
	private:
		string name, designation, email, noTel;//change

	public:
		void setContact(string name , string designation , string noTel , string email )//change
		{
			this->name = name;
			this->designation = designation;
			this->noTel = noTel;
			this->email = email;
		}
		string getName()
		{
			return name;
		}
		string getDesignation()
		{
			return designation;
		}
		string getNoTel()
		{
			return noTel;
		}
		string getEmail()
		{
			return email;
		}
};

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////   Cluster Economy   ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//apply aggregation to Application Form
//apply polymorphism concept
class ClusterEconomy{
	// encapsulation and data hiding
	protected:
		string type;

	public:
		ClusterEconomy(){}
		virtual void dispSector() {}
		virtual string getSector(){
			return type;
		}
};

///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////   Manudactory   //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//apply inheritance
class Manufactory:public ClusterEconomy{
	// encapsulation and data hiding
	private:
		string sectorManufactory;

	public:
		void dispSector()
		{
			int choice;
			cout << endl;
			cout << "==================MANUFACTORY==================" << endl;
			cout << "[1] Packaging & Printing" << endl
				 << "[2] Personal Protective Supplement (PPE) including Gloves & Fire Safety Supplement" << endl
				 << "[3] Health & Medical Products including Dietary Supplements" << endl
				 << "[4] Personal Care & Cleaning Products" << endl
				 << "[5] Medical Equipment Components" << endl
				 << "[6] Electric & Electronic" << endl
				 << "[7] Fuel & Gas including Petrochemical & Petrochemical Products" << endl
				 << "[8] Chemical Industry Products" << endl
				 << "[9] Machinery & Tools" << endl
				 << "[10] Textile Products Personal Protective Supplement (PPE)" << endl
				 << "[11] Production, Distillation, Storage, Supply & Distribution of Fuels & Lubricants" << endl
				 << "[12] Steel" << endl
				 << "[13] Cement" << endl
				 << "[14] Glass" << endl
				 << "[15] Ceramic" << endl
				 << endl << "Select Your Choice: ";
			cin >> choice;
			cin.ignore();
			
			switch(choice)
			{
				case 1: sectorManufactory = "Packaging & Printing";
						break;

				case 2: sectorManufactory = "Personal Protective Supplement (PPE) including Gloves & Fire Safety Supplement";
						break;

				case 3: sectorManufactory = "Health & Medical Products including Dietary Supplements";
						break;

				case 4: sectorManufactory = "Personal Care & Cleaning Products";
						break;

				case 5: sectorManufactory = "Medical Equipment Components";
						break;

				case 6: sectorManufactory = "Electric & Electronic";
						break;

				case 7: sectorManufactory = "Fuel & Gas including Petrochemical & Petrochemical Products";
						break;

				case 8: sectorManufactory = "Chemical Industry Products";
						break;

				case 9: sectorManufactory = "Machinery & Tools";
						break;

				case 10: sectorManufactory = "Textile Products Personal Protective Supplement (PPE)";
						 break;

				case 11: sectorManufactory = "Production, Distillation, Storage, Supply & Distribution of Fuels & Lubricants";
						 break;

				case 12: sectorManufactory = "Steel";
						 break;

				case 13: sectorManufactory = "Cement";
						 break;

				case 14: sectorManufactory = "Glass";
						 break;

				case 15: sectorManufactory = "Ceramic";
						 break;
			}
		}

		string getSector()
		{
			return sectorManufactory;
		}
};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  ServiceAndOthers  ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//apply inheritance
class ServiceAndOthers:public ClusterEconomy{
	// encapsulation and data hiding
	private:
		string sectorServiceOthers;

	public:
		void dispSector()
		{
			int choice;
			cout << endl;
			cout << "==================SERVICES AND OTHERS==================" << endl;
			cout << "[1] Aviation industry (Maintenance, Repair & Operation - MRO)" << endl
				 << "[2] Food and Bevarage" << endl
				 << "[3] Automobiles & Components" << endl
				 << "[4] Others" << endl
				 << endl << "Select Your Choice: ";
			cin >> choice;
			cin.ignore();
			
			switch(choice)
			{
				case 1: sectorServiceOthers = "Aviation industry (Maintenance, Repair & Operation - MRO)";
						break;

				case 2: sectorServiceOthers = "Food and Bevarage";
						break;

				case 3: sectorServiceOthers = "Automobiles & Components";
						break;

				case 4: cout << "If not, what is the sector you work in?" << endl;
						cout << "Please write your sector : ";
						cin.ignore();
						getline(cin, sectorServiceOthers, '\n');
						break;
			}
		}

		string getSector()
		{
			return sectorServiceOthers;
		}
};

///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////   Date   ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//apply composition
class Date{
	// encapsulation and data hiding
	int comDay, comMonth, comYear;
	string comDate;
	
public:
	 void readCompanyDate(){
		char symbol;
		cout << "Date of Incorporation [dd-mm-yyyy] : ";
		cin >> comDay >> symbol >> comMonth >> symbol >> comYear;
		comDate = to_string(comDay) + "-" + to_string(comMonth) + "-" + to_string(comYear);
	 }
	 string getDate(){
		return comDate;	
	 }

};

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////   Application Form   //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

class ApplicationForm{
	// encapsulation and data hiding
	private:
		string companyName;
		string ssmNo;
		string localAuthorityLicense;
		string localAuthorityName;
		string address;
		string revenue;
		int totEmployee;
		string status;
		Date dateIncorporation;
		ClusterEconomy *cluster;
		Contact contact;


	public:
		//accessor and mutator of companyName
		void setCompName(string companyName){
			this->companyName=companyName;
		}
		string getCompName(){
			return companyName;
		}
		//accessor and mutator of ssmNo
		void setSsm(string ssmNo){
			this->ssmNo=ssmNo;
		}
		string getSsm(){
			return ssmNo;
		}
		//accessor and mutator of license
		void setAuthoLicense(string license){
			localAuthorityLicense = license;
		}
		string getAuthoLicense(){
			return localAuthorityLicense;
		}
		//accessor and mutator of Authority Name
		void setAuthoName(string name){
			localAuthorityName = name;
		}
		string getAuthoName(){
			return localAuthorityName;
		}
		
		void setDate(){
			dateIncorporation.readCompanyDate();
		}
		string getDate(){
			return dateIncorporation.getDate();
		}
		//accessor and mutator of address		
		void setAddress(string address){
			this->address = address;
		}
		string getAddress(){
			return address;
		}
		//accessor and mutator of revenue
		void setRevenue(string revenue){
			this->revenue = revenue;
		}
		string getRevenue(){
			return revenue;
		}
		//accessor and mutator of totEmployee
		void setTotEmplo(int totEmployee){
			this->totEmployee = totEmployee;
		}
		int getTotEmplo(){
			return totEmployee;
		}
		//accessor and mutator of status
		void setStatus(string status){
			 this->status=status;
		}
		string getStatus(){
			return status;
		}
		//To get the contact of the contact person
		void getContact(string Coname, string desg, string nophone, string emel){
			contact.setContact(Coname, desg, nophone, emel);
		}
		Contact getC(){
			return contact;
		}
		//To get the sector of the applicant
		ClusterEconomy* getEconomy(){
			return cluster;
		}
		void setEconomyActivity(ClusterEconomy *CE){
			cluster = CE;
			cluster->dispSector();
		}

		string getsubmissionDate(){
			time_t now = time(0);
   			// convert now to string form
 		  	char* dt = ctime(&now);
			// use to ignore the next line after get the date and time from computer
		    if (dt[strlen(dt)-1] == '\n') 
				dt[strlen(dt)-1] = '\0';
			return dt;
		}
};

int main(){

	ClusterEconomy *cluster;
	int choice;
	
	do{
		loginpage L;	
		L.dispWelcome();
		choice = L.operation();
	
		while(choice <0 || choice >4 ){
			cout << "Please enter the correct option" << endl;
			cout << "TRY AGAIN" << endl;
			cout << endl;
			L.dispWelcome();		
			choice = L.operation();
		}
		
		switch(choice){
		//Admin login
			case 0:	
				{
					Admin admin;
					bool verify1 = true ;
					int choice1;
					char choice2;
					
					verify1 = admin.Adminlogin();
					if(verify1 == true){
							cout << endl;
							cout << "Login successfully!" << endl;
							system("pause");
							system("cls");
						//display admin page menu
						do{
							cout << "========================================SITE ADMINISTRATION========================================" << endl;
							cout << "1. add Admin" << endl;
							cout << "2. view User data" << endl;
							cout << "3. Verify User" << endl;
							cout << "4. Exit" << endl;
							cout << endl;
							cout << "Select : ";
							cin >> choice1;
					
							switch(choice1){
								//add new admin
								case 1:
									admin.addAdmin();
									break;
								//view the user data(include password)
								case 2:
									admin.viewUser();
									break;
								//approved or denied apply of user
								case 3:
									admin.VerifyUser();
									break;
								//Exit the program
								case 4:
									cout << "Thank You for using admin system" << endl;
									system("pause");
									system("cls");
									break;
							}
							if(choice1 == 4){
								break;
							}
							
							cout << endl;
							cout << "Continue with SITE ADMINISTRATION (Y/N) >> " ;
							cin >> choice2;
							
							system("pause");
							system("cls");
						}while(toupper(choice2) == 'Y');
						
					}else{
						cout << endl;
						cout << "Username or Password or both incorrect" << endl;
						cout << endl;
						system("pause");
						system("cls");
					}

					break;
				}
		
		//user login
			case 1: 
				{
					int choice2;
					bool verify;
					char backtomenu;
					verify = L.verifyLogin();
					if(verify == true){
						cout << "Login successfully!" << endl;
						system("pause");
						system("cls");
					do{
						backtomenu = 'n';
					// display user's menu
						cout << "==================MENU==================" << endl;
						cout << "1. Profile" << endl;
						cout << "2. Application Form" << endl;
						cout << "3. Check status" << endl;
						cout << "4. EXIT" << endl;
						cout << endl;
						cout << "Enter your choice => " ;
						cin >> choice2;
						cin.ignore();
						if(choice2 != 4){
							system("pause");
							system("cls");					
						}

						switch(choice2){
							//Display the user's profile
							case 1:
								{
									L.dispProfile();
									cout << endl;
									cout << "Do you want back to menu(Y/N) => ";
									cin >> backtomenu;
									system("pause");
									system("cls");
									break;	
								}
								
							//Application Form	
							case 2:
								{
									ApplicationForm AP;
									int choice3;
									string companyN, totEmployee,license, Aname, address, status, Contactname, designation, email, no_phone, ssm, tot;
									int totemploy;
									ifstream Readata1("UserInfo.txt");
									int numreg = 0,total_reg = 0;
									int MAXnum = 10;
									int i =0;
									bool pending = false;
									string tempusername, tempCname, tempSSM ,templicense, templocalname, tempdate, tempadd, temptype,
									       temprevenue, tempemployee, tempConame, tempdesgnation, tempno_phone, tempemail, tempsubtime, tempstatus;
									string Pusername[MAXnum], PCname[MAXnum], PSSM[MAXnum] ,Plicense[MAXnum], Plocalname[MAXnum], Pdate[MAXnum], Padd[MAXnum], Ptype[MAXnum],
									       Prevenue[MAXnum], Pemployee[MAXnum], PConame[MAXnum], Pdesgnation[MAXnum], Pno_phone[MAXnum], Pemail[MAXnum], Psubtime[MAXnum], Pstatus[MAXnum];  
									string checkstatus;       
									if(!Readata1){
										cout << "The system have some error, File cannot open! Please try it later! " << endl;
										cout << endl;
									}else{
										while(!Readata1.eof()){
											getline(Readata1, tempusername, ',');
											getline(Readata1, tempCname, ',');
											getline(Readata1, tempSSM, ',');
											getline(Readata1, templicense, ',');
											getline(Readata1, templocalname, ',');
											getline(Readata1, tempdate, ',');
											getline(Readata1, tempadd, ',');
											getline(Readata1, temptype, ',');
											getline(Readata1, temprevenue, ',');
											getline(Readata1, tempemployee, ',');
											getline(Readata1, tempConame, ',');
											getline(Readata1, tempdesgnation, ',');
											getline(Readata1, tempno_phone, ',');
											getline(Readata1, tempemail, ',');
											getline(Readata1, tempsubtime, ',');
											getline(Readata1, tempstatus);
										
											if(L.getusername() == tempusername){	
													numreg++;// used to calculate the total number of registration for specific user 
													if(numreg+1 > 10 ){
														cout << "This account already reach the maximum number. The new registration will not saved! " << endl;
														cout << "if you still want to apply, please come to the nearest office or call 05-XXXXXXX" << endl;
														break;
													}else if(tempstatus == "lulus"){
														checkstatus = "lulus" ;
														cout << "Your registration already approved! Cannot register again. Thank You!" << endl;
														cout << "If you have any problem, please contact 05-XXXXXXX or go to nearby MITI office" << endl;
														break;
													}else if(tempstatus == "baharu"){
														pending = true;
														break;
													}
											}

											total_reg++;// used to caluclate the total number of registration of whole program
										}
									}
									
									Readata1.close();

									if(checkstatus == "lulus" || numreg+1 > 10){
										cout << "Do you want back to menu(Y/N) => ";
										cin >> backtomenu;
										system("pause");
										system("cls");
										break;
									}else if(total_reg > 50){
										cout << "The system already reach the Maximum 50 registration! Cannot register already. Thank you!" << endl;
										cout << "Do you want back to menu(Y/N) => ";
										cin >> backtomenu;
										system("pause");
										system("cls");
										break;
									}else if(pending == true){
										cout << "Your registration still in pending, please wait for the verification first" << endl;
										cout << "Please check your status in menu with the option 3. Thank you" << endl;
										cout << "Do you want back to menu(Y/N) => ";
										cin >> backtomenu;
										system("pause");
										system("cls");
										break;
									}
										
									cout << "==================APPLICATION FORM==================" << endl;
									system("color E4");
									cout << "!!!ATTENTION!!!" << endl;
									cout << "DO NOT USE COMMA ( , ) when you fill your information" << endl;
									cout << endl;
									system("color E0");
									cout << "Please enter your information below" << endl;
									cout << endl;

									cout << "Company Name : ";
									getline(cin, companyN, '\n');
									AP.setCompName(companyN);

									cout << "SSM No. : ";
									getline(cin, ssm, '\n');
									AP.setSsm(ssm);
						
									cout << "Local Authority License No. : ";
									getline(cin, license, '\n');
									AP.setAuthoLicense(license);

									cout << "Local Authority Name : ";
									getline(cin, Aname, '\n');
									AP.setAuthoName(Aname);

									
									AP.setDate();
									cin.ignore();
									

									cout << "Enter you company address : ";
									getline(cin, address, '\n');
									AP.setAddress(address);
									cout << endl;
									
									cout << "==================Cluster Economy==================" << endl;
									cout << "1. Manufactory" << endl;
									cout << "2. Services and others" << endl;
									cout << "Choose your Cluster Economy : ";
									cin >> choice3;
									cin.ignore();
									
									if(choice3 == 1)
										cluster = new Manufactory;
									
									if(choice3 == 2)
										cluster = new ServiceAndOthers;
									
									AP.setEconomyActivity(cluster);
									cout << "Estimated revenue of your company : RM ";
									getline(cin, tot, '\n');
									AP.setRevenue(tot);
									AP.getRevenue();
									cout << "Enter the latest total employees : ";
									cin >> totemploy;
									cin.ignore();
									AP.setTotEmplo(totemploy);
									cout << endl;
									
									cout << "==================Contact Person==================" << endl;
									cout << "Enter the name : ";
									getline(cin, Contactname, '\n');


									cout << "Enter the designation : ";
									getline(cin, designation, '\n');

									cout << "Enter the email : ";
									getline(cin, email, '\n');

									
									AP.getContact(Contactname, designation, no_phone, email);
									
									//Write info into output file
									ofstream input("UserInfo.txt", ios::app);							
									input<<endl;
									//input submission time according to the time on computer
									input << L.getusername() << ","<< AP.getCompName() << "," << AP.getSsm() << "," << AP.getAuthoLicense() << "," << AP.getAuthoName() << "," 									
		    							  << AP.getDate() << "," << AP.getAddress() << "," << AP.getEconomy()->getSector() << "," << AP.getRevenue() << "," << AP.getTotEmplo() << "," 
										  << AP.getC().getName() << "," << AP.getC().getDesignation() << "," << AP.getC().getNoTel() << "," << AP.getC().getEmail()  << ","<< AP.getsubmissionDate()  << "," << "baharu";
										 
									cout << "You are complete to fill you registration form!!!" << endl;
									cout << endl;
									cout << "Do you want back to menu(Y/N) => ";
									cin >> backtomenu;
	
									input.close();
									system("pause");
									system("cls");
									//phone number, date
									break;
								}
							//Check the status of user
							case 3:
								{
									ifstream Readata("UserInfo.txt");
									int numreg = 0;
									int MAXnum = 10;
									int check =0;
									string tempusername, tempCname, tempSSM ,templicense, templocalname, tempdate, tempadd, temptype,
									       temprevenue, tempemployee, tempConame, tempdesgnation, tempno_phone, tempemail, tempsubtime, tempstatus;
									string Pusername[MAXnum], PCname[MAXnum], PSSM[MAXnum] ,Plicense[MAXnum], Plocalname[MAXnum], Pdate[MAXnum], Padd[MAXnum], Ptype[MAXnum],
									       Prevenue[MAXnum], Pemployee[MAXnum], PConame[MAXnum], Pdesgnation[MAXnum], Pno_phone[MAXnum], Pemail[MAXnum], Psubtime[MAXnum], Pstatus[MAXnum];  
									if(!Readata){
										cout << "The system have some error, File cannot open! Please try it later! " << endl;
										cout << endl;
									}else{
	
										cout << left << setw(5) << "No." << setw(30) << "Company Name" << setw(15) << "Status" << "Registation Date" << endl;
										while(!Readata.eof()){
										
											getline(Readata, tempusername, ',');
											getline(Readata, tempCname, ',');
											getline(Readata, tempSSM, ',');
											getline(Readata, templicense, ',');
											getline(Readata, templocalname, ',');
											getline(Readata, tempdate, ',');
											getline(Readata, tempadd, ',');
											getline(Readata, temptype, ',');
											getline(Readata, temprevenue, ',');
											getline(Readata, tempemployee, ',');
											getline(Readata, tempConame, ',');
											getline(Readata, tempdesgnation, ',');
											getline(Readata, tempno_phone, ',');
											getline(Readata, tempemail, ',');
											getline(Readata, tempsubtime, ',');
											getline(Readata, tempstatus);
											
											if(L.getusername() == tempusername){
													check++;
														Pusername[numreg] = tempusername;
														PCname[numreg] = tempCname;
														PSSM[numreg] = tempSSM;
														Plicense[numreg] = templicense;
														Plocalname[numreg] = templocalname;
														Pdate[numreg] = tempdate;
														Padd[numreg] = tempadd;
														Ptype[numreg] = temptype;
										       		 	Prevenue[numreg] = temprevenue;
														Pemployee[numreg] = tempemployee;
														PConame[numreg] = tempConame;
														Pdesgnation[numreg] = tempdesgnation;
														Pno_phone[numreg] = tempno_phone;
														Pemail[numreg] = tempemail;
														Psubtime[numreg] = tempsubtime;
														Pstatus[numreg] = tempstatus;
																								
														cout << setw(3) << numreg+1 << "  " << setw(30) << tempCname << setw(15) << tempstatus << tempsubtime << endl;
														numreg++;
												}
											}
										}
											if(check == 0){
												cout << endl;
												cout << "No information! You haven't register! " << endl;
											}
									
										
										for(int i=0; i<numreg; i++){
											char choice4;
										    	if(Pstatus[i] == "lulus"){
										    		cout << endl;
										    		cout << "Congratulation! You pass with the registration! " << endl;
													cout << "Do you want to print out the form?(Y/N) : ";
													cin >> choice4;
													
													if(toupper(choice4) == 'Y'){
														ofstream Form(PCname[i]+".txt");
														
														// Printing format 
														Form << PConame[i] << endl;
														Form << Pdesgnation[i] << endl;
														Form << Padd[i] << endl;
														Form << endl;
														Form << "Tuan/Puan," << endl;
														Form << endl;
														Form << "KEBENARAN BEROPERASI SERTA PENGERAKAN PERKERJA BAGI SYARIKAT-SYSRIKAT DALAM TEMPOH PERINTAH KAWALAN" << endl;
														Form << "PENGERAKAN" << endl;
														Form << "____________________________________________________________________________________________________"<< endl;
														Form << endl;
														Form << "Dengan hormatnya saya merujuk kepada PU (A)116/020 Perintah Pencegahan den Pengawalan Penyakit" << endl; 
														Form << "Berjangkit (Pengisytiharan Kawasan Tempatan Jangkitan) (Pelanjutan Kuatkuasa) (No 2) 2020 yang"  << endl;
														Form << "memberikan kelulusan secara bersyarat bagi syarikat-syarikat yang dibenarkan beroperasi sepanjang" << endl; 
														Form << "tempoh pemerintahan kawalan pergerakan " << endl;
														Form << endl;
														Form << "2.   Maklumat syarikat diberikan berikut: " << endl;
														Form << endl;
														Form << "     Nama Syarikat   : " << PCname[i] << endl;
														Form << "     Jumlah Perkerja : " << Pemployee[i] << endl;
														Form << "     SSM No.         : " << PSSM[i] << endl;
														Form << endl;
														Form << "3.   Dimaklumkan hanya dua per tiga daripada jumlah perkerja dibenarkan berkerja di syarikat tersebut. "<< endl;
														Form << endl;
														Form << "Kerjasama dan perhatian tuan/puan dalam hal ini amat dihargai dan didahului dengan ucapan terima kasih. "<< endl;
														Form << "Sekian, terima kasih." << endl;
														Form << endl;
														Form << "Kementerian Perdagangan Antarabangsa dan Industri (MITI)" << endl;
														
														cout << "Your form has been printed out!" << endl;
														Form.close();
													}else{
														break;
													}
												
											    }	
										}
										Readata.close();
										cout << endl;
										cout << "Do you want back to menu(Y/N) => ";
										cin >> backtomenu;
										system("pause");
										system("cls");
							
									break;									
								}					
							//Exit the program
							case 4:
									cout << "Thank you For using system" << endl;
									system("pause");
									system("cls");
									break;
							}
					
						}while(toupper(backtomenu) == 'Y');
					}else{
							cout << "Username or Password or both incorrect" << endl;
							cout << endl;
					}
				break;
				}
		
		//user register
			case 2: 
					L.registerpage(); 

				break;
		//user forget password		
			case 3: 
					L.forget();
				
				break;
		//Exit the program
			case 4:
					cout << "Thank You for using MITI service :)" << endl;
					exit(0);
				break;
		}
	
	}while(choice !=5 );
	
}
