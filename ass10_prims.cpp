// Name: KARA PRIYANKA     Batch: A1     Roll no.:03
// Assignment 10: Graph Implementation (undirected graph)

/*A business house has several offices in different countries; they want to lease phone lines to
connect them with each other and the phone company charges different rent to connect
different pairs of cities. Business house want to connect all its offices with a minimum total
cost. Solve the problem by suggesting appropriate data structures
*/

#include<iostream>
using namespace std;

#define infinity 99999;

class graph
{
  int n;   //number of vertices
  int g[20][20];
  public:
   void read_graph();
   void print_graph();
   void prims();
   
};

void graph::read_graph()
{
  int s,d,wt,check,ne,i,j;
  
  cout<<"Enter number of vertices in the graph:\n";
  cin>>n;
  
  cout<<"Enter Number of edges:\n";
  cin>>ne;
  
  check=(n*(n-1))/2;
  
  if(ne<=check)
  {
    for(i=0;i<n;i++)    // for intialising matrix of nXn size with zero;
    {
      for(j=0;j<n;j++)
        g[i][j]=0;
    }
    
    for(i=0;i<ne;i++)  // accepting value 
    { 
      cout<<"\nEnter details of edge "<<i+1<<":\n";
      cout<<"Enter the Source of the edge:\n";
      cin>>s;
      
      cout<<"Enter the Destination of the edge:\n";
      cin>>d;
      
      cout<<"Enter the weight of the edge:\n";
      cin>>wt;
      
      g[s][d]=g[d][s]=wt;
      
    }
    
    cout<<"Graph saved!!\n";
  }
  else
   cout<<"Graph cannot be created !!! \nretry!!!\n";
}


void graph::print_graph()
{
  int i,j;
   
  cout<<"\tSource\tDestination\tWeight\n";
  for(i=0;i<n;i++)
  {
    for(j=i;j<n;j++)
    {
      if(g[i][j]!=0)
      {
        cout<<"\t"<<i<<"\t"<<j<<"\t\t"<<g[i][j]<<"\n";
      }
    }
  }

}


void graph::prims()
{
  graph s;
  
  int i,j;
  int cost[20][20];
  
  int distance[20],visited[20],from[20];
  
  int min_dist=0,start,cnt=1,nextnode,min_cost=0;
  
  s.n=n;
  
  // for intialising matrix of nXn size with zero which will be the resultant tree
  for(i=0;i<n;i++)    
    {
      for(j=0;j<n;j++)
        s.g[i][j]=0;
    }
    
    
  // initializing the Cost matrix
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      if(g[i][j]!=0)
        cost[i][j]=g[i][j];
      else if(i==j)
        cost[i][j]=0;
      else
        cost[i][j]=infinity;
    }
  }
  
  // the below part is for checkin whether the creation is proper or not
  cout<<"Created Cost matrix:\n";
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      cout<<cost[i][j];
      cout<<"\t";
    }
    cout<<"\n";
  }
  
  //initializing the array
  for(i=0;i<n;i++)
  {
    visited[i]=0;
    from[i]=0;
    distance[i]=cost[0][i];
   
  }
  
  distance[0]=0;// already aaya hoga throught ht above initialization
  visited[0]=1;
  
  while(cnt<n)// since we have to visit all the vertices
  {
  
    cout<<"\nDistance:";
    for(i=0;i<n;i++)
    {
	cout<<"\t"<<distance[i];					//printing the 1st iteration of distance array and from array
    }
		
    cout<<"\nVisited:";
    for(i=0;i<n;i++)
    {
	cout<<"\t"<<visited[i];					//printing the 1st iteration of distance array and from array
    }
		
    cout<<"\nFrom : \t";
    for(i=0;i<n;i++)
    {
        cout<<"\t"<<from[i];
    }
    cout<<endl;
		
		
    min_dist=infinity;
    
    for(i=1;i<n;i++)// finding minimum value
    {
      if(visited[i]==0 && distance[i]<min_dist)
      {
        nextnode=i;
        min_dist=distance[i];
      }
      
    }
    visited[nextnode]=1;

    int u;
    u=from[nextnode];// this is for adding the new edge that we found whose distance is smallest.
    
    s.g[u][nextnode]=min_dist;// adding the edge in the minimum spanning tree
    s.g[nextnode][u]=min_dist;
    
    min_cost+=min_dist;
    
    for(i=1;i<n;i++)
    {
      if(visited[i]!=1 && (cost[nextnode][i] < distance[i]) )
      {
        distance[i]=cost[nextnode][i];
        from[i]=nextnode;
      }
    }
         
    cnt++;
      
  }// end of while
  
  cout<<"\nMinimum Cost is : "<<min_cost<<endl;
  cout<<"\nThe minimum spanning tree is:\n\n";
  s.print_graph();
  
}



int main()
{
  int choice;
  graph obj;
  
  graph s; // for finding the minimum spanning tree
  
 do
 {
    cout<<"\n**************MENU************\n1.Read Graph\n2.Display Graph\n3.Prims Algorithm\n4.EXIT\n";
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
        cout<<"Graph created is :\n"; 
        obj.print_graph();
        break;
      }
      case 3:
      {
        obj.prims();
        
       
        break;
      }
      
    }
 
 }while(choice!=4);

 return  0;
}

/*****************************************************************************************************************************************
						OUTPUT
***************************************************************************************************************************************
kara@kara-VirtualBox:~/Downloads$ g++ prims.cpp
kara@kara-VirtualBox:~/Downloads$ ./a.out

**************MENU************
1.Read Graph
2.Display Graph
3.Prims Algorithm
4.EXIT
1
Enter number of vertices in the graph:
6
Enter Number of edges:
8

Enter details of edge 1:
Enter the Source of the edge:
0
Enter the Destination of the edge:
1
Enter the weight of the edge:
15

Enter details of edge 2:
Enter the Source of the edge:
0
Enter the Destination of the edge:
3
Enter the weight of the edge:
10

Enter details of edge 3:
Enter the Source of the edge:
1
Enter the Destination of the edge:
2
Enter the weight of the edge:
12

Enter details of edge 4:
Enter the Source of the edge:
2
Enter the Destination of the edge:
3
Enter the weight of the edge:
10

Enter details of edge 5:
Enter the Source of the edge:
2
Enter the Destination of the edge:
5
Enter the weight of the edge:
15

Enter details of edge 6:
Enter the Source of the edge:
3
Enter the Destination of the edge:
4
Enter the weight of the edge:
9

Enter details of edge 7:
Enter the Source of the edge:
3
Enter the Destination of the edge:
5
Enter the weight of the edge:
5

Enter details of edge 8:
Enter the Source of the edge:
4
Enter the Destination of the edge:
5
Enter the weight of the edge:
8
Graph saved!!

**************MENU************
1.Read Graph
2.Display Graph
3.Prims Algorithm
4.EXIT
2
Graph created is :
	Source	Destination	Weight
	0	1		15
	0	3		10
	1	2		12
	2	3		10
	2	5		15
	3	4		9
	3	5		5
	4	5		8

**************MENU************
1.Read Graph
2.Display Graph
3.Prims Algorithm
4.EXIT
3
Created Cost matrix:
0	15	99999	10	99999	99999	
15	0	12	99999	99999	99999	
99999	12	0	10	99999	15	
10	99999	10	0	9	5	
99999	99999	99999	9	0	8	
99999	99999	15	5	8	0	

Distance:	0	15	99999	10	99999	99999
Visited:	1	0	0	0	0	0
From : 		0	0	0	0	0	0

Distance:	0	15	10	10	9	5
Visited:	1	0	0	1	0	0
From : 		0	0	3	0	3	3

Distance:	0	15	10	10	8	5
Visited:	1	0	0	1	0	1
From : 		0	0	3	0	5	3

Distance:	0	15	10	10	8	5
Visited:	1	0	0	1	1	1
From : 		0	0	3	0	5	3

Distance:	0	12	10	10	8	5
Visited:	1	0	1	1	1	1
From : 		0	2	3	0	5	3

Minimum Cost is : 45

The minimum spanning tree is:

	Source	Destination	Weight
	0	3		10
	1	2		12
	2	3		10
	3	5		5
	4	5		8

**************MENU************
1.Read Graph
2.Display Graph
3.Prims Algorithm
4.EXIT
4
kara@kara-VirtualBox:~/Downloads$ 

*************************************************************************************************************************************/						
