//Name: KARA PRIYANKA      Roll no.: 03      Batch: A1
// Assignment :binary search tree

/*Implement binary search tree and perform following operations:
a. Insert
b. Delete
c. Search
d. Mirror image
e. Display
f. Display level wise
*/

#include<iostream>

using namespace std;

class node
{
   public:
      int data;
      node *l,*r;
     node()
     {
       l=r=NULL;
     }
     node(int x)
     {
        data=x;
     }
};


class bst
{
    node *root;
    void inorder_rec(node *);
    int search_rec(node*,int);
    node* del_rec(node*,int);
    public:
       bst()
       {
          root=NULL;
       }
       void create();
       void insert(int x);
       void inorder(){inorder_rec(root);}
       int search(int x);
       
       int search_rectry(int x)
       { int flag;
         flag=search_rec(root,x);
         return flag;
       }
       
       node* mirror_rec(node*);
       void mirror_tree();
       void levldisplay();
       void delet(int key){root=del_rec(root,key);}
       
      
};


class queue
{
  node *que[100];
  int front,rear;
  public:
    queue()
    {
      front=rear=-1;
    }
    void enque(node*);
    node* deque();
    int empty();
};


int queue::empty()
{
   if(rear==-1)
     return 1;
   else
     return 0;
}


void queue::enque(node *T)
{
  if(empty())
   {
     front=rear=0;
     que[rear]=T;
   }
   else
   {
     que[++rear]=T;
   }
}


node* queue::deque()
{
  node *temp;
  if(empty())
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


void bst::inorder_rec(node *T)
{
   if(T!=NULL)
   {
     inorder_rec(T->l);
     cout<<"\t"<<T->data;
     inorder_rec(T->r);
   }
}


void bst::create()
{
   int n;
   cout<<"Enter number of elements to be inserted in the Tree:\n";
   cin>>n;
   
   int i;
   for(i=0;i<n;i++)
   {
      int x;
      cout<<"Enter element:\n";
      cin>>x;
      insert(x);
   }
   cout<<"Tree Successfully Created!!";
}


void bst::insert(int x)
{
   node *nn,*curr,*par;
   
   nn=new node;
   nn->data=x;
   
   if(root==NULL)
   {
     root=nn;
   }
   else
   {
     curr=root;
     while(curr!=NULL)
     {
       par=curr;
       if(nn->data < curr->data)
         curr=curr->l;
       else
         curr=curr->r;
     }
     
     if(nn->data  <  par->data)
       par->l=nn;
     else
       par->r=nn;
   }//end else

}


int bst::search(int ele)
{
     node *curr;
     curr=root;
     while(curr!=NULL)
     {
       if(ele < curr->data)
         curr=curr->l;
       else if (ele > curr->data)
         curr=curr->r;
       else
         {
           return 1;
         }
     }
     return 0;
}


int bst::search_rec(node *t,int ele)
{
     if(t==NULL) return 0;
     
     if(t->data==ele) return 1;
     
     if(ele < t->data)
         return search_rec(t->l,ele);
     
     if (ele > t->data)
         return search_rec(t->r,ele);
    
}


void bst::mirror_tree()
{
	//node *mirror;
	
	root=mirror_rec(root);
	
	cout<<"Mirrored Tree's Inorder Traversal:\n";
	inorder_rec(root);
}


node* bst::mirror_rec(node * p)
{
	node *t;
	
	t=new node;
	
	if(p==NULL)
	   return NULL;

        t->data=p->data;
	t->l=mirror_rec(p->r);
	t->r=mirror_rec(p->l);
	
	return t;

}


void bst::levldisplay()
{
   queue q;
   node *T;
   T=root;
   
   q.enque(T);
   
   while(!q.empty())
   {
      T=q.deque();
      
      cout<<"\t"<<T->data;
      
      if(T->l!=NULL)
        q.enque(T->l);
      if(T->r!=NULL)
        q.enque(T->r);
   }
}


node* bst::del_rec(node *T,int key)
{
  node *temp;
  if(T==NULL)
  {
   cout<<"Key not found!!\n";
   return T;
  }
  
  if(key<T->data)
  {
    T->l=del_rec(T->l,key);
    return T;
  }
  if(key>T->data)
  {
    T->r=del_rec(T->r,key);
    return T;
  }
  if(T->l==NULL&&T->r==NULL)   // leaf node deletion
  {
    temp=T;
    delete temp;
    return NULL;
  }
  if(T->l==NULL)  // node having only right child but no left child
  {
    temp=T;
    T=T->r;
    delete temp;
    return T;
  }
  if(T->r==NULL)  // node having only left child but no right child
  {
    temp=T;
    T=T->l;
    delete temp;
    return T;
  }
  else
  {
    temp=T->r;
    
    while(temp->l!=NULL)
      temp=temp->l;
    T->data=temp->data;
    T->r=del_rec(T->r,temp->data);
    return T;
  }
}



int main()
{
   int choice;
   int ele,flag;
   bst obj;
   do
   {
     cout<<"\n**************MENU***************\n1.Create BST\n2.Insert\n3.Inorder Traversal\n4.Search\n5.Recursive Search\n6.Mirror the tree\n7.Level Wise Diplay of the tree\n8.Deletion of a Node\n9.EXIT\n";
     cin>>choice;
     switch(choice)
     {
        case 1:
        {
           
           obj.create();
           break;
        }
        case 2:
        {
           cout<<"Enter element to be inserted:\n";
           cin>>ele;
           obj.insert(ele);
           break;
        }
        case 3:
        {
           cout<<"Inorder Traversal:\n";
           obj.inorder();
           break;        
        }    
        case 4:
        {
           cout<<"Enter the Element to be Searched:\n";
           cin>>ele;
           flag=obj.search(ele);
           if(flag==1)
           cout<<"Element Present!!";
           else
           cout<<"Element not present!!!";
           break;
        }
        case 5:
        {
           cout<<"Enter the Element to be Searched:\n";
           cin>>ele;
           flag=obj.search_rectry(ele);
           if(flag==1)
           cout<<"Element Present!!";
           else
           cout<<"Element not present!!!";
           break;
        }
        case 6:
        {
           obj.mirror_tree();       
           break;
        }
        case 7:
        {
           cout<<"Level Wise Display of the Tree:\n";
           obj.levldisplay();
           cout<<"\nData displayed!!\n";
           break;
        }
        case 8:
        {
          cout<<"Enter the Element to be Deleted from the tree:\n";
          int key;
          cin>>key;
          obj.delet(key);
          cout<<"After Deletion:\n";
          obj.inorder();
          break;  
        }
     }
     
     
   
   }while(choice!=9);   
   return 0;
}




/************************************************************************************************************************************************
								OUTPUT
************************************************************************************************************************************************
[student@localhost Downloads]$ g++ bst.cpp
[student@localhost Downloads]$ ./a.out

**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
1
Enter number of elements to be inserted in the Tree:
8
Enter element:
15
Enter element:
12
Enter element:
18
Enter element:
9
Enter element:
14
Enter element:
17
Enter element:
20
Enter element:
11
Tree Successfully Created!!
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
2
Enter element to be inserted:
19

**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
3
Inorder Traversal:
	9	11	12	14	15	17	18	19	20
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
4
Enter the Element to be Searched:
12
Element Present!!
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
4
Enter the Element to be Searched:
25
Element not present!!!
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
5
Enter the Element to be Searched:
18
Element Present!!
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
5
Enter the Element to be Searched:
98
Element not present!!!
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
6
Mirrored Tree's Inorder Traversal:
	20	19	18	17	15	14	12	11	9
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
6
Mirrored Tree's Inorder Traversal:
	9	11	12	14	15	17	18	19	20
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
7
Level Wise Display of the Tree:
	15	12	18	9	14	17	20	11	19
Data displayed!!

**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
8
Enter the Element to be Deleted from the tree:
11
After Deletion:
	9	12	14	15	17	18	19	20
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
8
Enter the Element to be Deleted from the tree:
12
After Deletion:
	9	14	15	17	18	19	20
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
8
Enter the Element to be Deleted from the tree:
15
After Deletion:
	9	14	17	18	19	20
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
8
Enter the Element to be Deleted from the tree:
25
Key not found!!
After Deletion:
	9	14	17	18	19	20
**************MENU***************
1.Create BST
2.Insert
3.Inorder Traversal
4.Search
5.Recursive Search
6.Mirror the tree
7.Level Wise Diplay of the tree
8.Deletion of a Node
9.EXIT
9
[student@localhost Downloads]$ 

*************************************************************************************************************************************************/
