//Name: KARA PRIYANKA		Batch: A1	Roll no: 03
//Assignment 12: Direct Access File

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string.h>

#define SIZE 10
#define h(x) x%SIZE
using namespace std;
struct student
{ 
	int rollno;
	char name[20];
	float marks;
	int status; 
	int link;  
};

class lin_probe
 {
   char table[30];	//contains name of the file
   fstream tab;
   student rec;
   public:
	 lin_probe();
	 
	 void displayall();
	 void insert(student rec1);
	 void  Delete(int rollno);
	 int  search(int rollno);
	 void display(int recno) 
	   {
	       int i=recno;
	       tab.open(table,ios::binary  | ios::in);
	       tab.seekg(recno*sizeof(student),ios::beg);
	       tab.read((char*)&rec,sizeof(student));
	       if(rec.status==0)
		  {
		       cout<<"\n"<<i<<") "<<rec.rollno<<"\t"<<rec.name<<"\t"<<setprecision(2)<<rec.marks;
		       cout<<"\t"<<rec.link;
		  }
	       else
		       cout<<"\n"<<i<<") ********* Empty ********";
	       tab.close();
	   }
	 void read(int recno)
	   {
	       tab.open(table,ios::binary | ios::in  );
	       tab.seekg(recno*sizeof(student),ios::beg);
	       tab.read((char*) &rec,sizeof(student));
	       tab.close();
	   }
	  void write(int recno)
	   {
	       tab.open(table,ios::binary| ios::out|ios::in);
	       tab.seekp(recno*sizeof(student),ios::beg);
	       tab.write((char*)&rec,sizeof(student));
	       tab.close();
	   }

};
 lin_probe::lin_probe()
 {
	int i;char a;
	strcpy(table," yo.txt");
	rec.status=1;rec.link=-1;
	tab.open(table,ios::binary | ios::out );	
	tab.close();
	for(i=0;i<SIZE;i++)
		 write(i);

 }
void lin_probe::displayall()
 {
	int i=1,n;
	cout<<"\n*********Data File*********\n";
	for(i=0;i<SIZE;i++)
		display(i);
 }

void lin_probe::insert(student rec1)
{
	int n,i,j,start,k;
	rec1.status=0;	//record is present
	rec1.link=-1;	//is like chain
	
	start=h(rec1.rollno);
	
 	for(i=0;i<SIZE;i++)
	  {
		j=(start+i)%SIZE;
		read(j);
		if(rec.status==0 && h(rec.rollno)==start)
		   break;
	  }
	if(i<10)
	  {
	        while(rec.link!=-1)
	      	{
			j=rec.link;
			read(j);
	      	}
	       for(i=0;i<SIZE;i++)
	       {
		  k=(start+i)%SIZE;
		  read(k);
		 if(rec.status==1)  
		    {
			rec=rec1;
			write(k);
			read(j);
			rec.link=k;
			write(j);
			return;
		    }
	       }
	    cout<<"\nTable is full ";
	}
     else
       {  
	  for(i=0;i<SIZE;i++)
	       {
		  k=(start+i)%SIZE;
		  read(k);
		 if(rec.status==1)
		    {
			rec=rec1;
			write(k);
			return;
		    }
	       }
	    cout<<"\nTable is full ";
	}

}


void lin_probe::Delete(int rollno)
{
	student rec1;
	int recno;
	int i,j,start,k;
	start=h(rollno); 	
	for(i=0;i<SIZE;i++)
	  {
		j=(start+i)%SIZE;
		read(j);
		if(rec.status==0 && h(rec.rollno)==start)//synonim found
		   break;
	  }
	if(i<10)
	{
	     if(rec.rollno==rollno )
		{
			rec.status=1;
			write(j);
		}
	     else
		{
			while(rec.rollno !=rollno && rec.link!=-1)
			   {
				k=j;
				j=rec.link;
				read(j);
			   }

			if(rec.rollno==rollno)
			   {   rec.status=1;
			       write(j);
			       int nextlink=rec.link;
			       read(k);
			       rec.link=nextlink;
			       write(k);
			   }
			else
				cout<<"\nElement not found";
	       }
	 }
       else
		cout<<"\nRecord Not Found ";
}
int lin_probe::search(int rollno)
{
	int start,i,j;
	start=h(rollno);
	for(i=0;i<SIZE;i++)
	  {
		j=(start+i)%SIZE;
		read(j);
		if(rec.status==0 && h(rec.rollno)==start)//synonim found
		   break;
	  }
	if(i<10)
	 {
			while(rec.rollno !=rollno && rec.link!=-1)
			   {
				j=rec.link;
				read(j);
			   }

			if(rec.rollno==rollno)
				return(j);

			else
				return -1;
	 }
       else
		return -1;

}


int main()
 { 
   lin_probe object;
   int rollno,op,recno;
   student rec1;
   do
     { 
       cout<<"\n\n*****************MENU*********************\n1.Insert\n2.Display\n3.Delete\n4.Search\n5.Exit\n";
       cin>>op;
       switch(op)
	{ 
	  case 2:	object.displayall();
		break;
	  case 1: 
		cout<<"\nEnter the roll no. : ";
		cin>>rec1.rollno;
		cout<<"Enter the name : ";
		cin>>rec1.name;
		cout<<"Enter the marks : ";
		cin>>rec1.marks;
		object.insert(rec1);
		break;
	  case 3: 
		cout<<"\nEnter the roll no.:";
		cin>>rollno;
		object.Delete(rollno);
		 break;
	   case 4: 
		cout<<"\nEnter a roll no. : ";
		cin>>rollno;
		recno=object.search(rollno);
		if(recno>=0)
		 { 
  			cout<<"\n Record No.:  "<<recno;
		    	object.display(recno);
		 }
		else
		  	cout<<"\nRecord Not Found ";
		break;
       }
     }while(op!=5);
 return 0;
}


/***********************************************************************************************************
						OUTPUT
************************************************************************************************************


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:1

Enter the roll no. : 1
Enter the name : Kara
Enter the marks : 98


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) ********* Empty ********
1) 1	Kara	98	-1
2) ********* Empty ********
3) ********* Empty ********
4) ********* Empty ********
5) ********* Empty ********
6) ********* Empty ********
7) ********* Empty ********
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:1

Enter the roll no. : 2
Enter the name : mansi
Enter the marks : 89


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) ********* Empty ********
1) 1	Kara	98	-1
2) 2	mansi	89	-1
3) ********* Empty ********
4) ********* Empty ********
5) ********* Empty ********
6) ********* Empty ********
7) ********* Empty ********
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:1

Enter the roll no. : 11
Enter the name : neha
Enter the marks : 78


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) ********* Empty ********
1) 1	Kara	98	3
2) 2	mansi	89	-1
3) 11	neha	78	-1
4) ********* Empty ********
5) ********* Empty ********
6) ********* Empty ********
7) ********* Empty ********
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:1

Enter the roll no. : 3
Enter the name : tripti
Enter the marks : 86


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) ********* Empty ********
1) 1	Kara	98	3
2) 2	mansi	89	-1
3) 11	neha	78	-1
4) 3	tripti	86	-1
5) ********* Empty ********
6) ********* Empty ********
7) ********* Empty ********
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:1

Enter the roll no. : 13
Enter the name : swati
Enter the marks : 89


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) ********* Empty ********
1) 1	Kara	98	3
2) 2	mansi	89	-1
3) 11	neha	78	-1
4) 3	tripti	86	5
5) 13	swati	89	-1
6) ********* Empty ********
7) ********* Empty ********
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:1

Enter the roll no. : 12
Enter the name : shilpa
Enter the marks : 89


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) ********* Empty ********
1) 1	Kara	98	3
2) 2	mansi	89	6
3) 11	neha	78	-1
4) 3	tripti	86	5
5) 13	swati	89	-1
6) 12	shilpa	89	-1
7) ********* Empty ********
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:1

Enter the roll no. : 10
Enter the name : ketaki
Enter the marks : 89


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) 10	ketaki	89	-1
1) 1	Kara	98	3
2) 2	mansi	89	6
3) 11	neha	78	-1
4) 3	tripti	86	5
5) 13	swati	89	-1
6) 12	shilpa	89	-1
7) ********* Empty ********
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:1

Enter the roll no. : 40
Enter the name : ritu
Enter the marks : 75


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) 10	ketaki	89	7
1) 1	Kara	98	3
2) 2	mansi	89	6
3) 11	neha	78	-1
4) 3	tripti	86	5
5) 13	swati	89	-1
6) 12	shilpa	89	-1
7) 40	ritu	75	-1
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:3

Enter the roll no.:11


1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:2

*********Data File*********

0) 10	ketaki	89	7
1) 1	Kara	98	-1
2) 2	mansi	89	6
3) ********* Empty ********
4) 3	tripti	86	5
5) 13	swati	89	-1
6) 12	shilpa	89	-1
7) 40	ritu	75	-1
8) ********* Empty ********
9) ********* Empty ********

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:4

Enter a roll no. : 1

 Record No.:  1
1) 1	Kara	98	-1

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:4

Enter a roll no. : 111

Record Not Found 

1)Insert
2)Display
3)Delete
4)Search
5)Exit

Enter Your Choice:5

**************************************************************************************************/
