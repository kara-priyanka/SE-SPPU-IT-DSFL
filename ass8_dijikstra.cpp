// Name: KARA PRIYANKA     Batch: A1     Roll no.:03
// Assignment 8: dijikstra's

/*
Represent a given graph using adjacency matrix /adjacency list and find the shortest path using
Dijkstra's algorithm (single source all destination).
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
   void dijkstra();
   
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
  cout<<"Graph created is :\n";
  
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


void graph::dijkstra()
{
  int i,j;
  int cost[20][20];
  
  int distance[20],visited[20],from[20];
  
  int min_dist=0,start,cnt=0,nextnode;
  
  //cost matrix initialisation
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
  
  // the below commented part is for checkin whether the creation is proper or not
  
  /*cout<<"Created Cost matrix:\n";
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      cout<<cost[i][j];
      cout<<"\t";
    }
    cout<<"\n";
  }*/
  
  //enter starting vertex
  cout<<"Enter the Starting Vertex:\n";
  cin>>start;
  

  //initializing the array
  for(i=0;i<n;i++)
  {
    visited[i]=0;
    distance[i]=cost[start][i];
    from[i]=start;   
  }
  
  visited[start]=1;
  distance[start]=0;
  /*for(i=0;i<n;i++)
  {
   cout<<distance[i]<<"\t"<<visited[i]<<"\t"<<from[i]<<endl;
  }
  */
 
  while(cnt<n)// since we ahve to visit all the vertices
  {
    min_dist=infinity;
    
    for(i=0;i<n;i++)// finding minimum value
    {
      if(visited[i]==0 && distance[i]<min_dist)
      {
        nextnode=i;
        min_dist=distance[i];
      }
      
    }
    visited[nextnode]=1;
    
    for(i=0;i<n;i++)
    {
      if(visited[i]!=1 && (min_dist+cost[nextnode][i]<distance[i]) )
      {
        distance[i]=cost[nextnode][i]+min_dist;
        from[i]=nextnode;
      }
    }
    
   /* for(i=0;i<n;i++)
     cout<<distance[i]<<"\t";*/
     
   // cout<<"\n"; 
    cnt++;
  }
  
  
  //for printing the shortest path between start and vertex
  for (i=0;i<n;i++)
  {
    cout<<"Minimum distance from "<<i<<" to "<<start<<" is = "<<distance[i]<<endl;
    int j=i;
    while(j!=start)
    {
      cout<<j<<"->";
      j=from[j];
    }
    cout<<start<<endl;
  
  }

}


int main()
{
  int choice;
  graph obj;
  
 do
 {
    cout<<"\n**************MENU************\n1.Read Graph\n2.Display Graph\n3.Dijkstra Algorithm\n4.EXIT\n";
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
        obj.dijkstra();
        break;
      }
      
    }
 
 }while(choice!=4);

 return  -1; //program not completed check the dijikstras algorithm
}




/***********************************************************************************************************************************************
                                                          OUTPUT
************************************************************************************************************************************************

[student@localhost Downloads]$ g++ graph.cpp 
[student@localhost Downloads]$ ./a.out

**************MENU************
1.Read Graph
2.Display Graph
3.Dijkstra Algorithm
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
3
Enter the Destination of the edge:
4
Enter the weight of the edge:
9

Enter details of edge 6:
Enter the Source of the edge:
3 
Enter the Destination of the edge:
5
Enter the weight of the edge:
5

Enter details of edge 7:
Enter the Source of the edge:
4
Enter the Destination of the edge:
5
Enter the weight of the edge:
8

Enter details of edge 8:
Enter the Source of the edge:
2
Enter the Destination of the edge:
5
Enter the weight of the edge:
15
Graph saved!!

**************MENU************
1.Read Graph
2.Display Graph
3.Dijkstra Algorithm
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
3.Dijkstra Algorithm
4.EXIT
3
Enter the Starting Vertex:
1






Minimum distance from 0 to 1 is = 15
0->1
Minimum distance from 1 to 1 is = 0
1
Minimum distance from 2 to 1 is = 12
2->1
Minimum distance from 3 to 1 is = 22
3->2->1
Minimum distance from 4 to 1 is = 31
4->3->2->1
Minimum distance from 5 to 1 is = 27
5->2->1

**************MENU************
1.Read Graph
2.Display Graph
3.Dijkstra Algorithm
4.EXIT
4
[student@localhost Downloads]$ 

*************************************************************************************************************************************************/                                                         
