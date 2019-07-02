//Name: KARA PRIYANKA       Batch: A1        Roll no.: 03
// Assignment 6: DFS and BFS

/*Consider a friends’ network on face book social web site. Model it as a graph to represent each node as a user and a link to represent the fried relationship between them. Store data such as date of birth, number of comments for each user.
1. Find who is having maximum friends
2. Find who has post maximum and minimum comments
3. Find users having birthday in this month.
Hint: (Use adjacency list representation and perform DFS and BFS traversals)
*/

#include<iostream>
#include<string.h>
#include<ctime>
using namespace std;

#define infi 99999999

static int maxc[2]={0,0};
static int minc[2]={infi,infi};
int curr_month;
int visited[20];

char same_month[30][30];

int curr_month_find()
{
  time_t t=time(0);
  struct tm *now=localtime(&t);
  curr_month=now->tm_mon+1;
  return curr_month;
}

//for node structure
class user
{
  public:
    int day,month,year;//for date of birth
    char name[30];
    int comments,likes;
    int index;
    user *next;
    user()
    {
      day=month=year=0000;
      strcpy(name,"Default");
      next=NULL;
    }
    user(int d,int m,int y,char n[30],int co,int like,int i)
    {
      day=d;
      month=m;
      year=y;
      comments=co;
      likes=like;
      strcpy(name,n);
      index=i;
    }
};

class queues
{
  class user*que[100];
  int front,rear;
  public:
    queues()
    {
      front=rear=-1;
    }
    void enque(user*);
    user* deques();
    int isempty();
};


int queues::isempty()
{
   if(rear==-1)
     return 1;
   else
     return 0;
}


void queues::enque(class user *T)
{
  if(isempty())
   {
     front=rear=0;
     que[rear]=T;
   }
   else
   {
     que[++rear]=T;
   }
}


class user* queues::deques()
{
  class user *temp;
  if(isempty())
   return NULL;
  else if(front==rear)
  {
    temp=que[front];
    front=rear=-1;
    return temp ;
  }
  else
  {
    temp=que[front++];
    return temp;
  }
}



class graph
{
  public:
    user *g[20];	// for the array to contain the pointers for the vertex
    int nouser,edges;
    graph()
    {
      cout<<"Enter number of users:\n";
      cin>>nouser;
      edges=0;
      for(int i=0;i<nouser;i++)
        g[i]=NULL;
    }
    void read_graph();
    void insert(int ,int);
    void print_graph();
    void max_friends();
    void init();
    void DFS_call()
    {
      init();
      DFS(0);  
    }
    void DFS(int);
    void BFS();
};

//static int min_cost;
void graph::read_graph()
{
  int m,d,y,co,like;
  char nam[30];
  
  // enter the details of the user of the social media
  cout<<"Enter the Data of the User :\n\n";
  for(int i=0;i<nouser;i++)
  {
    cout<<"\nEnter the Data of user "<<i+1<<endl;
    cout<<"Enter name:\n";
    cin>>nam;
    cout<<"Enter the day of birth:\n";
    cin>>d;
    cout<<"Enter the month of birth:\n";
    cin>>m;
    cout<<"Enter the year of birth:\n";
    cin>>y;
    cout<<"Enter the Number of Comments:\n";
    cin>>co;
    cout<<"Enter the Number of Likes:\n";
    cin>>like;
    
    user *nn=new user(d,m,y,nam,co,like,i);
    
    g[i]=nn;  //making array of pointers to have the data of its own user
  }
  
  //enter the user who is friend of 
  cout<<"\n\nEnter the Number of edges:\n";
  cin>>edges;
  for(int i=0;i<edges;i++)
  {
    cout<<"enter:\n";
    cout<<"Enter the Source :\n";
    int source;
    cin>>source;
    cout<<"Enter the Destination:\n";
    int dest;
    cin>>dest;
    insert(source,dest);
    insert(dest,source);
  }
}

void graph::insert(int s,int d)
{
  user *p,*q;
  q=new user(*g[d]);
  q->next=NULL;
  
  p=g[s];
  while(p->next!=NULL)
    p=p->next;
  p->next=q;
}

void graph::print_graph()
{
   user *temp;
   cout<<"Details:\n";
   for(int i=0;i<nouser;i++)
   {
     temp=g[i];
     cout<<"\n\nDetails of USER "<<i+1<<endl;
     cout<<"Name: "<<temp->name<<endl;
     cout<<"DOB: "<<temp->day<<"/"<<temp->month<<"/"<<temp->year<<endl;
     cout<<"Number of Comments: "<<temp->comments<<endl;
     cout<<"Number of Likes: "<<temp->likes<<endl;
     
     cout<<"\nFriends of the user:\n";    
     temp=temp->next;
     while(temp!=NULL)
     {
       cout<<"Name: "<<temp->name<<endl;
       temp=temp->next;
     }
   }
}


void graph::max_friends()
{
  user *temp;
  
  int cnt[10],loc;
  
  for(int i=0;i<nouser;i++)
  {
    temp=g[i]->next;
    cnt[i]=0;
    while(temp!=NULL)
     { cnt[i]++;
       temp=temp->next;
     }
  }
  
  /*cout<<"Count array:\n";
  for(int i=0;i<nouser;i++)
  {
    cout<<cnt[i]<<"\t";
  }
  */
  
  
 //finding who has the maximum frnds from cnt[]
 int max;
 for(int i=0;i<nouser;i++)
  {
    max=cnt[i];
    for(int j=i+1;j<nouser;j++)
    {
      if(cnt[j]>max)
      {
        max=cnt[j];
        loc=j;
      }
    }
 }
 
 cout<<"\nMaximum friends are of user "<<loc+1<<endl;
}

void graph::init()
{
  for(int i=0;i<nouser;i++)
  {
    visited[i]=0;
  }
}

void graph::DFS(int src)
{
  user *temp=g[src];
  visited[src]=1;// marking the node as visited
  
  if( minc[0] > temp->comments )
  {
    minc[0]=temp->comments;
    minc[1]=temp->index;
  }
  if( maxc[0] < temp->comments )
  {
    maxc[0]=temp->comments;
    maxc[1]=temp->index;
  }
  
  
  cout<<"\t"<<temp->name;
  
  while(temp!=NULL)	// since the graph is made through the adjacency list then the traversal for adjacent vertex will be through the next ptr
  {
    src=temp->index;	//so as to check for the case of whether visited or not .
    if(visited[src]==0)// nodes which are not visited
       DFS(src);
    temp=temp->next;	// since the list is made according to the ascending order of vertices so it would visit the smallest one numbered only
  }
}


void graph::BFS()
{
   	queues q;
   	user *temp;
	int tim=curr_month_find();
   	int k=0;
   
   	init();// initializing the visited array
   
   	q.enque(g[0]);
   	visited[0]=1;
   
   	while(!q.isempty())
   	{
      		class user *t=q.deques();
   	   	int i=t->index;
   	   	cout<<"\t"<<g[i]->name;
      
      		if(tim==t->month)	//checking condition so as to find the people having birthday in the current month
      		{
        		strcpy(same_month[k],g[i]->name);
        		k++;
      		}
      
      		for(temp=g[i];temp!=NULL;temp=temp->next)
      		{
        		int j=temp->index;
		        if(visited[j]==0)
        		{
			          visited[j]=1;
			          q.enque(g[j]);
        		}
      		}
   	}
   
   	cout<<"\n\nUsers having birthday in this month:\n";
   	for(int i=0;i<nouser;i++)
   		cout<<same_month[i]<<endl;
}


int main()
{
  int choice;
  graph obj;
  do
  {
    cout<<"\n****************MENU****************\n1.Read Graph\n2.Print Graph\n3.Maximum Number Of Friends\n4.DFS\n5.BFS\n6.EXIT\n";
    cin>>choice;
    switch(choice)
    {
      case 1:
      {
         obj.read_graph();
         break;
      }
      case 2:
      {
         obj.print_graph();
         break;
      }
      case 3:
      {
         obj.max_friends();
         break;
      }
      case 4:
      {
        cout<<"DFS of the Graph is:\n";
        obj.DFS_call();
        cout<<"\nMinimum Comments are: "<<minc[0];
        cout<<"\n of "<<obj.g[minc[1]]->name<<endl;
        cout<<"Maximum Comments are: "<<maxc[0];
        cout<<"\n of "<<obj.g[maxc[1]]->name<<endl;        
        break;
      }
      case 5:
      {
        cout<<"\nBreadth First Traversal of the Graph:\n";
        obj.BFS();
        break;
      }
    }
  
  }while(choice!=6);
  return 0;
}



/********************************************************************************************
					OUTPUT
*********************************************************************************************
kara@kara-VirtualBox:~/Downloads$ g++ ass6.cpp
kara@kara-VirtualBox:~/Downloads$ ./a.out
Enter number of users:
5

****************MENU****************
1.Read Graph
2.Print Graph
3.Maximum Number Of Friends
4.DFS
5.BFS
6.EXIT
1
Enter the Data of the User :


Enter the Data of user 1
Enter name:
Kara
Enter the day of birth:
04
Enter the month of birth:
07
Enter the year of birth:
1998
Enter the Number of Comments:
2542
Enter the Number of Likes:
254

Enter the Data of user 2
Enter name:
Mansi 
Enter the day of birth:
09
Enter the month of birth:
03
Enter the year of birth:
1998
Enter the Number of Comments:
65452
Enter the Number of Likes:
254

Enter the Data of user 3
Enter name:
Neha
Enter the day of birth:
05
Enter the month of birth:
03
Enter the year of birth:
1998
Enter the Number of Comments:
654
Enter the Number of Likes:
12

Enter the Data of user 4
Enter name:
Swati
Enter the day of birth:
08
Enter the month of birth:
04
Enter the year of birth:
1997
Enter the Number of Comments:
25
Enter the Number of Likes:
12

Enter the Data of user 5
Enter name:
Tripti
Enter the day of birth:
07
Enter the month of birth:
03
Enter the year of birth:
1998
Enter the Number of Comments:
658
Enter the Number of Likes:
24


Enter the Number of edges:
5
enter:
Enter the Source :
0
Enter the Destination:
1
enter:
Enter the Source :
1
Enter the Destination:
2
enter:
Enter the Source :
2
Enter the Destination:
3
enter:
Enter the Source :
0
Enter the Destination:
3
enter:
Enter the Source :
3
Enter the Destination:
4

****************MENU****************
1.Read Graph
2.Print Graph
3.Maximum Number Of Friends
4.DFS
5.BFS
6.EXIT
2
Details:


Details of USER 1
Name: Kara
DOB: 4/7/1998
Number of Comments: 2542
Number of Likes: 254

Friends of the user:
Name: Mansi
Name: Swati


Details of USER 2
Name: Mansi
DOB: 9/3/1998
Number of Comments: 65452
Number of Likes: 254

Friends of the user:
Name: Kara
Name: Neha


Details of USER 3
Name: Neha
DOB: 5/3/1998
Number of Comments: 654
Number of Likes: 12

Friends of the user:
Name: Mansi
Name: Swati


Details of USER 4
Name: Swati
DOB: 8/4/1997
Number of Comments: 25
Number of Likes: 12

Friends of the user:
Name: Neha
Name: Kara
Name: Tripti


Details of USER 5
Name: Tripti
DOB: 7/3/1998
Number of Comments: 658
Number of Likes: 24

Friends of the user:
Name: Swati

****************MENU****************
1.Read Graph
2.Print Graph
3.Maximum Number Of Friends
4.DFS
5.BFS
6.EXIT
3

Maximum friends are of user 4

****************MENU****************
1.Read Graph
2.Print Graph
3.Maximum Number Of Friends
4.DFS
5.BFS
6.EXIT
4
DFS of the Graph is:
	Kara	Mansi	Neha	Swati	Tripti
Minimum Comments are: 25
 of Swati
Maximum Comments are: 65452
 of Mansi

****************MENU****************
1.Read Graph
2.Print Graph
3.Maximum Number Of Friends
4.DFS
5.BFS
6.EXIT
5

Breadth First Traversal of the Graph:
	Kara	Mansi	Swati	Neha	Tripti

Users having birthday in this month:
Mansi
Neha
Tripti



****************MENU****************
1.Read Graph
2.Print Graph
3.Maximum Number Of Friends
4.DFS
5.BFS
6.EXIT
6


*******************************************************************************************/				
				
