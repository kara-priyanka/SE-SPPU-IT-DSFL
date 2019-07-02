// Name: KARA PRIYANKA        Batch:A1         Roll No.: 03
//Assignment 11: Sequential File

#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

struct address
{
	char lane[30];
	char city[30];
	long int pin;
};

class student
{
	int roll_no;
	char name[50];
	char div;
	struct address add;
	
	public:
		void fn_getdata();
		void fn_putdata();
		int fn_roll_no()
		{
			return roll_no;
		}	 
};

void student::fn_getdata()
{
	cout<<"Enter the roll number\n";
	cin>>roll_no;
	
	cout<<"Enter the name\n";
	ws(cin);
	cin.getline(name,50);
	
	cout<<"Enter the Division\n";
	cin>>div;
	
	cout<<"Enter the Address\n";
	cout<<"Enter the Lane:\n";
	ws(cin);
	cin.getline(add.lane,30);

	cout<<"Enter the City:\n";
	ws(cin);
	cin.getline(add.city,30);
	
	cout<<"Enter the Pincode:\n";
	cin>>add.pin;
	
}

void student::fn_putdata()
{
	cout<<roll_no<<"\t"<<name<<"\t\t"<<add.lane<<"\t"<<add.city<<"\t"<<add.pin<<endl;
}

class seq_file
{
	char filename[30];
	public:
		void fn_create();
		void fn_display();
		void fn_add();
		void fn_search(int key);
		void fn_modify(int key);
		void fn_delete(int key);
};

void seq_file::fn_create()
{
	ofstream file;
	file.open("stud.txt");
	student s;
	s.fn_getdata();
	file.write((char *)(&s),sizeof(s));
	file.close();
}

void seq_file::fn_display()
{
	ifstream file;
	file.open("stud.txt");
	student s;
	cout<<"Roll No.\tName\t\tLane\tCity\tPincode\n";
	
	file.read((char *)(&s),sizeof(s));
	while(!file.eof())
	{ 
		s.fn_putdata();
		file.read((char *)(&s),sizeof(s));
		
	}
	file.close();
}
void seq_file::fn_add()
{
	ofstream file;
	file.open("stud.txt",ios::app);
	student s;
	s.fn_getdata();
	file.write((char *)(&s),sizeof(s));
	file.close();
}

void seq_file::fn_search(int key)
{
	ifstream file;
	file.open("stud.txt");
	student s;
	int flag=0;
	file.read((char *)(&s),sizeof(s));
	while(!file.eof())
	{

		if(key==s.fn_roll_no())
		{
			cout<<"Data present\n";
			s.fn_putdata();
			flag=1;
		}//if
		file.read((char*)(&s),sizeof(s));
	}//while()
	if(flag==0)
	{
		cout<<"Data not present";
	}//if
}//search()

//function to modify or update a record in a file
void seq_file::fn_modify(int key)
{
	fstream file;
	file.open("stud.txt");
	student s;
	int flag=0;
	file.read((char *)(&s),sizeof(s));
	while(!file.eof())
	{

		if(key==s.fn_roll_no())
		{
			s.fn_getdata();
			file.seekg(-(sizeof(s)),ios::cur);
			file.write((char *)(&s),sizeof(s));
			flag=1;
		}//if
		file.read((char *)(&s),sizeof(s));
	}//while()
	if(flag==0)
	{
		cout<<"Data not present";
	}//if
	file.close();
}//fn_modify

//function to delete a record from a file
void seq_file::fn_delete(int key)
{
	fstream file;
	ofstream temp;
	file.open("stud.txt");
	temp.open("temp.txt");
	student s;
	int flag=0;
	file.read((char *)(&s),sizeof(s));
	while(!file.eof())
	{

		if(key==s.fn_roll_no())
		{
			s.fn_putdata();
			flag=1;
			file.read((char *)(&s),sizeof(s));
		}//if
		else
		{
			temp.write((char *)(&s),sizeof(s));
			file.read((char *)(&s),sizeof(s));
		}//else
	}//while
	file.close();
	temp.close();
	if(flag==0)
	{
		cout<<"Data not present";
	}//if
	else
	{
		remove("stud.txt");
		rename("temp.txt","stud.txt");
	}//else
}//fn_delete

int main()
{
	int i, choice, num, key;
	
	seq_file obj;
	ofstream file;
	
	do
	{	
		cout<<"\n****************MENU**************\n1.Create\n2.Display\n3.Add Record\n4.Search\n5.Modify\n6.Delete\n7.EXIT\n";
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"Enter number of records\n";
			cin>>num;
			
			obj.fn_create();
		        
		        for(i=0;i<(num-1);i++)
		        	obj.fn_add();
			break;
			 	
		case 2:
			file.seekp(0);
			obj.fn_display();
			break;
			 	
		case 3:
			obj.fn_add();
			break;
		case 4:
			cout<<"Enter Roll number of the data to be searched:\n";
			cin>>key;
			obj.fn_search(key);
			break;
		case 5:
			cout<<"Enter Roll number of the data to be Modify:\n";
			cin>>key;
			obj.fn_modify(key);
			break;
		case 6:
			cout<<"Enter Roll number of the data to be Deleted:\n";
			cin>>key;
			obj.fn_delete(key);
			break;
		
		}
	}while(choice != 7);
        return 0;
}

/***********************************************************************************************************
						OUTPUT
************************************************************************************************************

[student@localhost Downloads]$ g++ ass11.cpp
[student@localhost Downloads]$ ./a.out

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
2
Roll No.	Name		Lane	City	Pincode

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
1
Enter number of records
3
Enter the roll number
1
Enter the name
kara
Enter the Division
B
Enter the Address
Enter the Lane:
Lohegaon
Enter the City:
pune
Enter the Pincode:
411047
Enter the roll number
2
Enter the name
mansi
Enter the Division
A
Enter the Address
Enter the Lane:
Gangadham
Enter the City:
Pune
Enter the Pincode:
411048
Enter the roll number
3
Enter the name
tripti
Enter the Division
C
Enter the Address
Enter the Lane:
KLE
Enter the City:
Banglore
Enter the Pincode:
411048

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
2
Roll No.	Name		Lane	City	Pincode
1	kara		Lohegaon	pune	411047
2	mansi		Gangadham	Pune	411048
3	tripti		KLE	Banglore	411048

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
3
Enter the roll number
4
Enter the name
neha
Enter the Division
A
Enter the Address
Enter the Lane:
kondhwa
Enter the City:
Pune
Enter the Pincode:
411047

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
2
Roll No.	Name		Lane	City	Pincode
1	kara		Lohegaon	pune	411047
2	mansi		Gangadham	Pune	411048
3	tripti		KLE	Banglore	411048
4	neha		kondhwa	Pune	411047

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
4
Enter Roll number of the data to be searched:
3
Data present
3	tripti		KLE	Banglore	411048

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
4
Enter Roll number of the data to be searched:
12
Data not present
****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
5
Enter Roll number of the data to be Modify:
3
Enter the roll number
3
Enter the name
tripti
Enter the Division
C
Enter the Address
Enter the Lane:
lohegaon
Enter the City:
Pune
Enter the Pincode:
411032

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
2
Roll No.	Name		Lane	City	Pincode
1	kara		Lohegaon	pune	411047
2	mansi		Gangadham	Pune	411048
3	tripti		lohegaon	Pune	411032
4	neha		kondhwa	Pune	411047

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
6
Enter Roll number of the data to be Deleted:
2
2	mansi		Gangadham	Pune	411048

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
2
Roll No.	Name		Lane	City	Pincode
1	kara		Lohegaon	pune	411047
3	tripti		lohegaon	Pune	411032
4	neha		kondhwa	Pune	411047

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
7
[student@localhost Downloads]$ ./a.out

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
2
Roll No.	Name		Lane	City	Pincode
1	kara		Lohegaon	pune	411047
3	tripti		lohegaon	Pune	411032
4	neha		kondhwa	Pune	411047

****************MENU**************
1.Create
2.Display
3.Add Record
4.Search
5.Modify
6.Delete
7.EXIT
7
[student@localhost Downloads]$ 

****************************************************************************************************/						

