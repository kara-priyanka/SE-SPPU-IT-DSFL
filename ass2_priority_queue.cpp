// Name : Kara Priyanka     Batch: A1     Roll no.: 03
// Assignment 2:Priority Queue

/*Implement priority queue as ADT using single linked list for servicing patients in an hospital with priorities as i) Serious (top priority) ii) medium illness (medium priority) iii) General (Least priority).*/


#include<iostream>
#include<string.h>
using namespace std;

struct node
{
  int id;
  char name[20];
  struct node *next;
};

//LINKED LIST queue
class queues
{
  public:
      struct node *front;
      struct node *rear;
      queues()
      {
        front=NULL;
        rear=NULL;
      }
      void enque(struct node*);		//condition: first node or normal node
      struct node deques();		//condition: 1) empty queue  2)single node  3)normal node
      void readfront();
      void readrear();
      void read_all();
};

class patient
{
  queues Q[3];
  public:
    void addpatient();
    void servepatient();
    void displayall();

};
/************************************************************************************************************************************************
                                                    enque()
************************************************************************************************************************************************/

void queues::enque(struct node *nn)		
{
    if(front==NULL)
    {        
        front=rear=nn;
        rear->next=NULL;
    }

    else
    {
        rear->next=nn;
        rear=nn;
    }
    rear->next=NULL;
}

/************************************************************************************************************************************************
                                                    deques()
************************************************************************************************************************************************/

struct node queues::deques()
{
    if(front==NULL)
    {
        struct node nothing;
        
        strcpy(nothing.name,"nothing");
        return nothing;
    }
    if(front->next==NULL)
    {
        struct node temp;
        strcpy(temp.name,front->name);
        front=rear=NULL;
        return temp;
    }
    else
    {
        struct node *temp,type;
        type.id=front->id;
        strcpy(type.name,front->name);
        temp=front;
        front=front->next;
        temp->next=NULL;
        delete temp;
        return type;
    }

}

/************************************************************************************************************************************************
                                                    readfront()
************************************************************************************************************************************************/

void queues::readfront()
{
  if(front==NULL)
  {
      cout<<"No patient available";
  }
  else
  {
    cout<<"\nName: "<<front->name<<"\n Id: "<<front->id;
  }

}


/************************************************************************************************************************************************
                                                    Adding patient
************************************************************************************************************************************************/
void patient::addpatient()
{
   struct node *nn;
   int type;
   
   nn=new node;
   
   cout<<"Enter the Id:\n";
   cin>>nn->id;
   cout<<"Enter the name:\n";
   cin>>nn->name;
   cout<<"Disease:\n1.Unconcious\n2.Heart attack\n3.Severe Burnt\n4.Accident\n5.Dengue\n6.Malaria\n7.Thyphoid\n8.General Check Up\n";
   cin>>type;
   
   if(type==1||type==2||type==3||type==4)
   	Q[0].enque(nn);
   else if(type==5||type==6||type==7)
   	Q[1].enque(nn);
   else if(type==8)
  	Q[2].enque(nn);
}

/************************************************************************************************************************************************
                                                    Displaying all the data
************************************************************************************************************************************************/
void patient::displayall()
{
  struct node *temp;
  
  temp=Q[0].front;
  if(temp!=NULL)
  {
  cout<<"High precedence pateints:";
  while(temp!=NULL)
  {
    cout<<"\nName: "<<temp->name<<"\n Id: "<<temp->id;
    temp=temp->next;
  }
  }
    
  temp=Q[1].front;
  if(temp!=NULL)
  {
    cout<<"\n\nMedium Precedence Patients:";
    while(temp!=NULL)
    {
      cout<<"\nName: "<<temp->name<<"\n Id: "<<temp->id;
      temp=temp->next;
    }
  }
 
  temp=Q[2].front;
  if(temp!=NULL)
  {
    cout<<"\n\nLower Precedence Patients:";
    while(temp!=NULL)
    {
      cout<<"\nName: "<<temp->name<<"\n Id: "<<temp->id;
      temp=temp->next;
    }
  }
  
  else
  cout<<"No Patients available";
}


/************************************************************************************************************************************************
                                                    Serving patient
************************************************************************************************************************************************/
void patient::servepatient()
{
  if(Q[0].front!=NULL)
  {
    Q[0].readfront();
    Q[0].deques();
    return;
  }
  
  else if(Q[1].front!=NULL)
  {
    Q[1].readfront();
    Q[1].deques();
    return;
  }
  
  else if(Q[2].front!=NULL)
  {
    Q[2].readfront();
    Q[2].deques();
    return;
  }
  
  else
  {
    cout<<"No patient is Available";
  }

}


/************************************************************************************************************************************************
                                                    main()
************************************************************************************************************************************************/
int main()
{
    int choice;
    patient obj;

    do
    {
        cout<<"\n***************MENU***************\n1.Add Patient\n2.Serve patient\n3.Display all\n4.exit\n";
        cin>>choice;

        switch(choice)
        {
          case 1:
            {
                
        	obj.addpatient();
        	break;
            }
          case 2:
            {
                obj.servepatient();
                break;
            }
          case 3:
          {
             obj.displayall();
             break;
            
          }
        }//end of switch
    }while(choice!=4);
}




/************************************************************************************************************************************************
                                                         OUTPUT
************************************************************************************************************************************************


[student@localhost ~]$ cd Documents
[student@localhost Documents]$ g++ ass2.cpp
[student@localhost Documents]$ ./a.out

***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
1
Enter the Id:
1
Enter the name:
kara
Disease:
1.Unconcious
2.Heart attack
3.Severe Burnt
4.Accident
5.Dengue
6.Malaria
7.Thyphoid
8.General Check Up
1

***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
1
Enter the Id:
8
Enter the name:
swati
Disease:
1.Unconcious
2.Heart attack
3.Severe Burnt
4.Accident
5.Dengue
6.Malaria
7.Thyphoid
8.General Check Up
8

***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
3
High precedence pateints:
Name: kara
 Id: 1

Lower Precedence Patients:
Name: swati
 Id: 8
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
2

Name: kara
 Id: 1
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
2

Name: swati
 Id: 8
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
2
No patient is Available
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
1
Enter the Id:
1
Enter the name:
kara 
Disease:
1.Unconcious
2.Heart attack
3.Severe Burnt
4.Accident
5.Dengue
6.Malaria
7.Thyphoid
8.General Check Up
2

***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
1
Enter the Id:
2
Enter the name:
mansi
Disease:
1.Unconcious
2.Heart attack
3.Severe Burnt
4.Accident
5.Dengue
6.Malaria
7.Thyphoid
8.General Check Up
5

***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
3
High precedence pateints:
Name: kara
 Id: 1

Medium Precedence Patients:
Name: mansi
 Id: 2No Patients available
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
1
Enter the Id:
8
Enter the name:
swati
Disease:
1.Unconcious
2.Heart attack
3.Severe Burnt
4.Accident
5.Dengue
6.Malaria
7.Thyphoid
8.General Check Up
8

***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
3
High precedence pateints:
Name: kara
 Id: 1

Medium Precedence Patients:
Name: mansi
 Id: 2

Lower Precedence Patients:
Name: swati
 Id: 8
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
2

Name: kara
 Id: 1
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
2

Name: mansi
 Id: 2
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
2

Name: swati
 Id: 8
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
2
No patient is Available
***************MENU***************
1.Add Patient
2.Serve patient
3.Display all
4.exit
4
[student@localhost Documents]$ ^C

*************************************************************************************************************************************************/


