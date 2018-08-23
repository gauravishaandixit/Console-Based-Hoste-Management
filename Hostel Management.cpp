#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
using namespace std;
class hostel
{
	int room_no;
	char name[30];
	char address[50];
	char phone[10];

	public:
	void main_menu();		//to dispay the main menu
	void add();			//to allot a room
	void display(); 		//to display the student record
	void rooms();			//to display alloted rooms
	void edit();			//to edit the student record
	int check(int);			//to check room status
	void modify(int);		//to modify the record
	void delete_rec(int);		//to delete the record
};

void hostel::main_menu()
{
	int choice;
	while(choice!=5)
	{
		system("cls");
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t*************";
		cout<<"\n\n\n\t\t\t1.Allot a room";
		cout<<"\n\t\t\t2.Student record";
		cout<<"\n\t\t\t3.Rooms Allotted";
		cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\t5.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;

		switch(choice)
		{
			case 1:	add();
				break;
			case 2: display();
				break;
			case 3: rooms();
				break;
			case 4:	edit();
				break;
			case 5:break;
			default:
				{
					cout<<"\n\n\t\t\tWrong choice.....!!!";
					cout<<"\n\t\t\tPress any key to continue....!!";
					getch();
				}
		}
	}
}

void hostel::add()
{
	system("cls");
	int r,flag;
	ofstream fout("Record.dat",ios::app);

	cout<<"\n Enter Student Detalis";
	cout<<"\n ----------------------";
	cout<<"\n\n Room no: ";
	cin>>r;
	flag=check(r);

	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";

	else
	{
		room_no=r;
		cout<<" Name: ";
		fflush(stdin);
		gets(name);
		cout<<" Address: ";
		gets(address);
		cout<<" Phone No: ";
		gets(phone);
		fout.write((char*)this,sizeof(hostel));
		cout<<"\n Room is booked...!!!";
	}

	cout<<"\n Press any key to continue.....!!";
	getch();
	fout.close();
}

void hostel::display()
{
	system("cls");
	ifstream fin("Record.dat",ios::in);
	int r,flag;
	cout<<"\n Enter room no: ";
	cin>>r;
	flag=check(r);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hostel));
		if(room_no==r)
		{
			system("cls");
			cout<<"\n Student Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone;
			flag=1;
			break;
		}
	}

	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant....!!";

	cout<<"\n\n Press any key to continue....!!";
	getch();
	fin.close();

}


void hostel::rooms()
{
	system("cls");
	ifstream fin("Record.dat",ios::in);
	cout<<"\n\t\t\t    List Of Rooms Allotted";
	cout<<"\n\t\t\t    ----------------------";
	cout<<"\n\n Room No.\tName\t\tAddress\t\t\t\tPhone No.\n";

	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hostel));
		cout<<"\n\n "<<room_no<<"\t"<<name;
		cout<<"\t\t"<<address<<"\t\t\t"<<phone;
	}
	cout<<"\n\n\n\t\t\tPress any key to continue.....!!";
	getch();
	fin.close();
}

void hostel::edit()
{
	system("cls");
	int choice,r;

	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.Modify Student Record";
	cout<<"\n 2.Delete Student Record";
	cout<<"\n Enter your choice: ";
	cin>>choice;
	system("cls");
	cout<<"\n Enter room no: " ;
	cin>>r;

	switch(choice)
	{
		case 1:	modify(r);
			break;
		case 2:	delete_rec(r);
			break;
		default: cout<<"\n Wrong Choice.....!!";
	}
	cout<<"\n Press any key to continue....!!!";
	getch();
}


int hostel::check(int r)
{
	int flag=0;
	ifstream fin("Record.dat",ios::in);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hostel));
		if(room_no==r)
		{
			flag=1;
			break;
		}
	}

	fin.close();
	return(flag);
}


void hostel::modify(int r)
{
	long pos,flag=0;
	fstream file("Record.dat",ios::in|ios::out|ios::binary);
	while(!file.eof())
	{
		pos=file.tellg();
		file.read((char*)this,sizeof(hostel));
		if(room_no==r)
		{
			cout<<"\n Enter New Details";
			cout<<"\n -----------------";
			cout<<"\n Name: ";
			fflush(stdin);
			gets(name);
			cout<<" Address: ";
			gets(address);
			cout<<" Phone no: ";
			gets(phone);

			file.seekg(pos);
			file.write((char*)this,sizeof(hostel));
			cout<<"\n Record is modified....!!";
			flag=1;
			break;
		   }
	}

	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant...!!";
	file.close();
}

void hostel::delete_rec(int r)
{
	int flag=0;
	char ch;
	ifstream fin("Record.dat",ios::in);
	ofstream fout("temp.dat",ios::out);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(hostel));
		if(room_no==r)
		{
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone No: "<<phone;
			cout<<"\n\n Do you want to delete this record(y/n): ";
			cin>>ch;

			if(ch=='n')
				fout.write((char*)this,sizeof(hostel));
			flag=1;
		}
		else
			fout.write((char*)this,sizeof(hostel));
	}

	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant...!!";
	else
	{
		remove("Record.dat");
		rename("temp.dat","Record.dat");
	}
}


int main()
{
	hostel h;
	system("cls");
	cout<<"\n\t\t\t****************************";
	cout<<"\n\t\t\t* HOSTEL MANAGEMENT PROJECT *";
	cout<<"\n\t\t\t****************************";
	Sleep(2000);

	cout<<"\n\n\n\n\t\tMade By:";
	Sleep(1000);
	cout<<"\tGAURAV DIXIT";
	Sleep(1000);
	cout<<"\n\n\t\tSubmitted To:";
	Sleep(1000);
	cout<<"\tSHAILESH KUMAR";
	cout<<"\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue....!!";
	getch();
	h.main_menu();
}

