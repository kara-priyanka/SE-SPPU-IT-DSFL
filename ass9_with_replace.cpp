//Assignment 9: Chaining with replacement

/*
Store data of students with telephone no and name in the structure using hashing function for
telephone number and implement chaining with and without replacement.
*/


#include<iostream>
#include<string.h>

using namespace std;
#define size 10

int hash(long int key)
{
	return key%size;
}

struct student
{
	char name[30];
	long int contact;
};

class hashtable
{
	struct student st[size];
	int flag[size];
	int chain[size];
	public:
		hashtable()
		{
			for(int i=0;i<size;i++)
			{
				strcpy(st[i].name,"************");
				st[i].contact=0;
				flag[i]=0;	// indicates that data is not there
				chain[i]=-1;				
			}
		}	
		void insert();
		void display();
		int hash(long int key)	
		{
			return key%size;
		}
		void search(long int);
};

void hashtable::insert()
{
	student s;
	cout<<"Enter Name of the Student:\n";
	cin>>s.name;
	cout<<"Enter contact number of the Student:\n";
	cin>>s.contact;
	
	int start;
	start=hash(s.contact);
	
	//if the exact location is empty
	if(flag[start]==0)
	{
		strcpy(st[start].name,s.name);
		st[start].contact=s.contact;
		flag[start]=1;
		return;
	}
	
	//if the exact location has a synonym
	if(hash(st[start].contact)==start)
	{
		int i=start,j=0;
		
		while( flag[i] && j<size)
		{
			i=(i+1)%size;
			j++;
		}
		if(j==size)
		{
			cout<<"\n****************************Table is full******************\n";
			return;
		}
		strcpy(st[i].name,s.name);
		st[i].contact=s.contact;
		flag[i]=1;
		
		j=start;
		while(chain[j]!=-1)
		{
			j=chain[j];
		}
		if(chain[j]==-1)
		{
			chain[j]=i;
		}	
		return;	
	}
	
	//if at exact location element is there but not a synonym
	else
	{
		int j=start,i=0;    
			while(flag[j]==1&&i<size)
			{
				j=(j+1)%size;
				i++;
			}
			// now j contains the index of empty location
			
			i = st[start].contact % size;
			
			while(chain[i] != start)	// start has the data which was not supposed to be there
				i = chain[i];
				
			chain[i] = chain[start];
			
			while(chain[i] != -1)
				i = chain[i];
				
			chain[i] = j;
			
			st[j] = st[start];
			flag[j] = 1;
			chain[j] = -1;
			
			chain[start] = -1;
			st[start].contact = s.contact;
			strcpy(st[start].name,s.name);	
	}
}

void hashtable::display()
{
	cout<<"\nIndex\tName\tContact\tFlag\tChain\n";
	for(int i=0;i<size;i++)
	{
		cout<<i<<"\t"<<st[i].name<<"\t"<<st[i].contact<<"\t"<<flag[i]<<"\t"<<chain[i]<<endl;
	}
}


void hashtable::search(long int key)
{
	int start;
	
	start=hash(key);
	int i=start;
	int j=0;
		
	while(chain[i]!=-1)
	{
		if(st[i].contact==key)
		{
			cout<<"Key is present\n";
			cout<<i<<"\t"<<st[i].name<<"\t"<<st[i].contact<<"\t"<<flag[i]<<"\t"<<chain[i]<<endl;
			return;
		}
		i=chain[i];
	}
	if(chain[i]==-1 && st[i].contact==key)
	{
		cout<<"Key is present\n";
		cout<<i<<"\t"<<st[i].name<<"\t"<<st[i].contact<<"\t"<<flag[i]<<"\t"<<chain[i]<<endl;
		return;
	}	
	else
		cout<<"Record not present";
}


int main()
{
	int choice;
	hashtable obj;
	
	do
	{
		cout<<"\n****************MENU**************\n1.Insert\n2.Display\n3.Search\n4.EXIT\n";
		cin>>choice;
		
		switch(choice)
		{
			case 1:
				obj.insert();
				break;
			case 2:
				obj.display();
				break;
			case 3:
				cout<<"Enter contact number to be searched:\n";
				long int key;
				cin>>key;
				obj.search(key);
				break;
		}
		
	}while(choice!=4);
}
