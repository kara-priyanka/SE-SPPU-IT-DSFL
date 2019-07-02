// Name : KARA PRIYANKA        Roll no.: 03   Batch: A1
//Assignment 4: Expression tree

/*Construct an expression tree from postfix/prefix expression and perform recursive and nonrecursive  In-order, pre-order and post-order traversals.
*/

#include<iostream>
using namespace std;

/*********************************************************************************************************************************************
                                                                  NODE
*********************************************************************************************************************************************/

class node
{
	public:
        char data;
	node *l,*r;
	node()
	{
		l=r=NULL;
	}
};

/*********************************************************************************************************************************************
ARRAY implementation of stack                                                    Stack for the Node type
*********************************************************************************************************************************************/
class stack1
{
	node* data[20];
        
	public:
	int top;
	node* pop();
	void push(node*);
	int isfull();
	int isempty();
	stack1()
	{
	 	top=-1;
	}
};


int stack1::isfull()
{
	 if(top==9)
		 return 1;
	 return 0;
}


int stack1::isempty()
{
	 if(top==-1)
		 return 1;
	 return 0;
}


void stack1::push(node* ele)
{
	int full = isfull();
	if(full==0)
	{
		top++;

	   data[top]=ele;
	}
}


node* stack1::pop()
{	int empty = isempty();
	node* ele;
	if(empty==0)
	{
		ele=data[top];
		top--;
		return ele;
	}
	cout<<"Stack is empty ";
	return NULL;
}


/*********************************************************************************************************************************************
array implementation                                             Stack for int type data
*********************************************************************************************************************************************/
class stack2
{
	int data[20];
        
	public:
	int top;
	int pop();
	void push(int);
	int isfull();
	int isempty();
	stack2()
	{
	 	top=-1;
	}
};


int stack2::isfull()
{
	 if(top==19)
		 return 1;
	 return 0;
}


int stack2::isempty()
{
	 if(top==-1)
		 return 1;
	 return 0;
}


void stack2::push(int ele)
{
	int full = isfull();
	if(full==0)
	{
		top++;

	   data[top]=ele;
	}
}


int stack2::pop()
{	int empty = isempty();
	int ele;
	if(empty==0)
	{


	ele=data[top];
	top--;
	return ele;
	}
	cout<<"Stack is empty ";
	return 0;
}


/*********************************************************************************************************************************************
                                                                Expression tree class
*********************************************************************************************************************************************/
class exp_tree
{
	node *root;
	void inorder_rec(node *);
	void preorder_rec(node*);
	void postorder_rec(node*);
	public:
		exp_tree(){root=NULL;}
	        void create_tree();
	        void inorder(){inorder_rec(root);}
	        void preorder(){preorder_rec(root);}
		void postorder(){postorder_rec(root);}
		void inorder_non();
		void preorder_non();
		void postorder_non();
};

void exp_tree::create_tree()
{
	char postfix[30];
	stack1 st;
	int i;
	char x;//for token
	
	
	
	cout<<"Enter the Postfix expression of whose tree is to be created:\n";
	cin>>postfix;
	
	
	
	for(i=0;postfix[i]!='\0';i++)
	{
	   x=postfix[i];
	   node *n;
	   n=new node;
	   if(isalnum(x)!=0)	//if operand
	   {
	      n->data=x;
	      st.push(n);	//node type stack
	   }
	   else      // if operator
   	   {             
              n->data=x;
              n->r=st.pop();
              n->l=st.pop();
              st.push(n);
           }
	}
	root=st.pop(); 
}

void exp_tree::inorder_rec(node *T)
{
   if(T!=NULL)
   {
     inorder_rec(T->l);
     cout<<T->data;
     inorder_rec(T->r);
   }
   
}

void exp_tree::preorder_rec(node *T)
{
   if(T!=NULL)
   {
     cout<<T->data;
     preorder_rec(T->l);
     preorder_rec(T->r);
   }
   
}

void exp_tree::postorder_rec(node *T)
{
   if(T!=NULL)
   {
     postorder_rec(T->l);
     postorder_rec(T->r);
     cout<<T->data;
   }
   
}

void exp_tree::inorder_non()
{
	stack1 S;
	node* t=root;
	while(t!=NULL)
	{
		S.push(t);
		t=t->l;
	}

	while(!S.isempty())
	{
		t=S.pop();
		cout<<t->data;
		t=t->r;
		while(t!=NULL)
		{
			S.push(t);
			t=t->l;
		}
	}
}


void exp_tree::preorder_non()
{
	stack1 S;
	node* t=root;

	while(t!=NULL)
	{
		cout<<t->data;
		S.push(t);
		t=t->l;
	}
	while(!S.isempty())
	{
		t=S.pop();
		t=t->r;
		while(t!=NULL)
		{
			cout<<t->data;
			S.push(t);
			t=t->l;
		}
	}
}

void exp_tree::postorder_non()
{
   stack1 st;	//node type stack
   stack2 s;	//int type stack
   node *t;
   t=root;
   
   while(t!=NULL)
   {
     st.push(t);
     s.push(0);
     t=t->l;   
   }
   
   while(st.isempty()!=1)
   {
     t=st.pop();
     int x;
     x=s.pop();
     if(x==1)
     {
       cout<<t->data;
     }
     else
     {
       st.push(t);
       s.push(1);
       t=t->r;
       while(t!=NULL)
       {
        st.push(t);
        s.push(0);
        t=t->l;
       }
      
     }
   }

}


/*********************************************************************************************************************************************
                                                              main()
*********************************************************************************************************************************************/

int main()
{
	exp_tree obj;
	int choice;
	do
	{
	   cout<<"\n************MENU*************\n1.Create Tree\n2.Inorder Recursive\n3.Preorder Recursive\n4.Postorder Recursive\n5.Inorder Non-Recursive\n6.Preorder Non-Recursive\n7.Postorder Non-Recursive\n8.EXIT\n";
	   cin>>choice;
	   switch(choice)
	   {
	     case 1:
	      {
	         obj.create_tree();
	         cout<<"Tree created successfully\n";
	         break;
	      }
	     case 2:
	      {
	         cout<<"Inorder Expression:\n";
	         obj.inorder();
	        
	         break;
	      }
	      case 3:
	      {
	         cout<<"Preorder Expression:\n";
	         obj.preorder();
	        
	         break;
	      }
	      case 4:
	      {
	         cout<<"Postorder Expression:\n";
	         obj.postorder();
	        
	         break;
	      }
	      case 5:
	      {
	         cout<<"Inorder NON-RECURSIVE Expression:\n";
	         obj.inorder_non();
	        
	         break;
	      }
	      case 6:
	      {
	         cout<<"Preorder NON-RECURSIVE Expression:\n";
	         obj.preorder_non();
	        
	         break;
	      }
	      case 7:
	      {
	         cout<<"Postorder Expression:\n";
	         obj.postorder();
	        
	         break;
	      }
	   }
	 }while(choice!=8);   
	return 0;
}



/*********************************************************************************************************************************************
                                                                  OUTPUT
*********************************************************************************************************************************************

[student@localhost Documents]$ g++ submit.cpp
[student@localhost Documents]$ ./a.out

************MENU*************
1.Create Tree
2.Inorder Recursive
3.Preorder Recursive
4.Postorder Recursive
5.Inorder Non-Recursive
6.Preorder Non-Recursive
7.Postorder Non-Recursive
8.EXIT
1
Enter the Postfix expression of whose tree is to be created:
ab*c-d+
Tree created successfully

************MENU*************
1.Create Tree
2.Inorder Recursive
3.Preorder Recursive
4.Postorder Recursive
5.Inorder Non-Recursive
6.Preorder Non-Recursive
7.Postorder Non-Recursive
8.EXIT
2
Inorder Expression:
a*b-c+d
************MENU*************
1.Create Tree
2.Inorder Recursive
3.Preorder Recursive
4.Postorder Recursive
5.Inorder Non-Recursive
6.Preorder Non-Recursive
7.Postorder Non-Recursive
8.EXIT
3
Preorder Expression:
+-*abcd
************MENU*************
1.Create Tree
2.Inorder Recursive
3.Preorder Recursive
4.Postorder Recursive
5.Inorder Non-Recursive
6.Preorder Non-Recursive
7.Postorder Non-Recursive
8.EXIT
4
Postorder Expression:
ab*c-d+
************MENU*************
1.Create Tree
2.Inorder Recursive
3.Preorder Recursive
4.Postorder Recursive
5.Inorder Non-Recursive
6.Preorder Non-Recursive
7.Postorder Non-Recursive
8.EXIT
5
Inorder NON-RECURSIVE Expression:
a*b-c+d
************MENU*************
1.Create Tree
2.Inorder Recursive
3.Preorder Recursive
4.Postorder Recursive
5.Inorder Non-Recursive
6.Preorder Non-Recursive
7.Postorder Non-Recursive
8.EXIT
6
Preorder NON-RECURSIVE Expression:
+-*abcd
************MENU*************
1.Create Tree
2.Inorder Recursive
3.Preorder Recursive
4.Postorder Recursive
5.Inorder Non-Recursive
6.Preorder Non-Recursive
7.Postorder Non-Recursive
8.EXIT
7
Postorder Expression:
ab*c-d+
************MENU*************
1.Create Tree
2.Inorder Recursive
3.Preorder Recursive
4.Postorder Recursive
5.Inorder Non-Recursive
6.Preorder Non-Recursive
7.Postorder Non-Recursive
8.EXIT
8
[student@localhost Documents]$ 

************************************************************************************************************************************************/
