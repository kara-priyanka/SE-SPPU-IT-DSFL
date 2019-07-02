// Name: KARA PRIYANKA     Batch: A1     Roll no.:03
// Assignment 7: Kruskals Algorithm

/*
Represent any real world graph using adjacency matrix find minimum spanning
tree using Kruskal’s algorithm.
*/

#include<iostream>
using namespace std;

#define infinity 99999;

typedef struct edge
{
   int s,d,wt;
}edge;

class graph
{
  int n;   //number of vertices
  int ne;// for number of edges
  int g[20][20];
  edge e[50];
  int set[20][20],cnt[20];
  public:
   void read_graph();
   void print_graph();
   void create_edge_list();
   void sort_edge_list();
   void print_edge_list();
   int find_set(int);
   void kruskal();
   
};



void graph::read_graph()
{
  int s,d,wt,check,i,j;
  
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


void graph::create_edge_list()
{
   int i,j,k=0;
   for(i=0;i<n;i++)
   {
     for(j=i;j<n;j++)
     {
       if(g[i][j]!=0)
       {
         e[k].s=i;
         e[k].d=j;
         e[k].wt=g[i][j];
         k++;
       }
     }
   }
  
  
}

void graph::sort_edge_list()
{
  int i,j,loc;
  edge temp;
  edge min;
  for(i=0;i<ne;i++)
  {
    min=e[i];
    for(j=i+1;j<ne;j++)
    {
      if(e[j].wt<min.wt)
      {
        min=e[j];	// swapping the structure details
        loc=j;
        temp=e[i];
        e[i]=min;
        e[loc]=temp;
      }
    }  
  }
} 

void graph::print_edge_list()
{
   // printing the Edge list
   cout<<"Edge List:\n\n";
   cout<<"\tSource\tDestination\tWeight\n";
   for(int i=0;i<ne;i++)
   {
     cout<<"\t"<<e[i].s<<"\t"<<e[i].d<<"\t\t"<<e[i].wt<<endl;
   }

}

int graph::find_set(int vertex)
{
 int i,j;
 for(i=0;i<n;i++)// accessing all the vertices set
 {
   for(j=0;j<cnt[i];j++)// checking the count in the set so as to access all the elements in the set 
   {
     if(vertex==set[i][j])
       return i;// if the vertex is found then return the set in which it was present
   }
 }
 return -1;// if not found 
}

void graph::kruskal()
{
  int min_cost=0;
  graph mst;
  mst.n=n;
  
  //creating sorting and displaying the edge list
  create_edge_list();
  sort_edge_list();
  print_edge_list();
  
  // initialising the Set array which has the Details of the components. so as to assure that different component edges are added
  //cnt array is going to store the count of vertices present in a particular component
  for(int i=0;i<n;i++)
  {
    set[i][0]=i;
    cnt[i]=1;
  }
  
  for(int i=0;i<ne;i++)// for accessing number of edges
  {
    int p1=find_set(e[i].s);// so as to find where the vertex is in
    int p2=find_set(e[i].d);
    // if p1 and p2 are equal that means the vertices are at the same location i.e same component so not to be added
    if(p1!=p2)
    {
      mst.g[e[i].s][e[i].d]=e[i].wt;
      mst.g[e[i].d][e[i].s]=e[i].wt;
      min_cost+=e[i].wt;
      
      // for updating count array so as to keep the count of the vertices in a set
      for(int j=0;j<cnt[p2];j++)
      {
        set[p1][cnt[p1]]=set[p2][j];
        cnt[p1]++;
      }
      cnt[p2]=0;// making the transfered components value 0
    }
  }
  
  cout<<"Obtained Minimum Spanning tree:\n ";
  mst.print_graph();
  cout<<"\nMinimum Cost is: "<<min_cost;
}


int main()
{
  int choice;
  graph obj;
  
  graph s; // for finding the minimum spanning tree
  
 do
 {
    cout<<"\n**************MENU************\n1.Read Graph\n2.Display Graph\n3.Kruskal's Algorithm\n4.EXIT\n";
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
        obj.kruskal();
        break;
      }
    }
 
 }while(choice!=4);

 return  0;
}


/***********************************************************************************************************************************************
							OUTPUT
************************************************************************************************************************************************
[student@localhost Downloads]$ g++ kruskal.cpp
[student@localhost Downloads]$ ./a.out

**************MENU************
1.Read Graph
2.Display Graph
3.Kruskal's Algorithm
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
10

Enter details of edge 4:
Enter the Source of the edge:
2
Enter the Destination of the edge:
3
Enter the weight of the edge:
12

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
3.Kruskal's Algorithm
4.EXIT
2
Graph created is :
	Source	Destination	Weight
	0	1		15
	0	3		10
	1	2		10
	2	3		12
	2	5		15
	3	4		9
	3	5		5
	4	5		8

**************MENU************
1.Read Graph
2.Display Graph
3.Kruskal's Algorithm
4.EXIT
3
Edge List:

	Source	Destination	Weight
	3	5		5
	4	5		8
	3	4		9
	1	2		10
	0	3		10
	2	3		12
	2	5		15
	0	1		15
Obtained Minimum Spanning tree:
 Graph created is :
	Source	Destination	Weight
	0	3		10
	1	2		10
	2	3		12
	3	5		5
	4	5		8

Minimum Cost is: 45
**************MENU************
1.Read Graph
2.Display Graph
3.Kruskal's Algorithm
4.EXIT
4
[student@localhost Downloads]$ 

************************************************************************************************************************************************/							
