// Name: KARA PRIYANKA     Roll no.: 03    Batch: A1
// Assignment 3: binary tree

/*Create Binary tree and perform following operations:
a. Insert
b. Display
c. Depth of a tree
d. Display leaf-nodes
e. Create a copy of a tree
*/

#include<iostream>
using namespace std;

class node
{
	public:
	int data;
	node *l,*r;
	node(int x)
	{
		data=x;
		l=r=NULL;
	}
};


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

class queue
{
	node* q[30];
	int front,rear;
	public:
		queue()
		{
			front=rear=-1;
		}
		void enque(node *);
		int isempty();
		int isfull();
		node* deque();
		int size();
};

int queue::isempty()
{
	if(front==-1)
		return 1;
	return 0;
}

int queue::isfull()
{
	if(rear==29)
		return 1;
	return 0;
}
void queue::enque(node *t)
{
	if(isempty())
	{
		front++;rear++;
		q[rear]=t;
		return;
	}
	else if(isfull())
	{
		cout<<"Cannot be enqueued!!\n";
	}
	else
	{
		rear++;
		q[rear]=t;
		return;
	}
}

node* queue::deque()
{
	if(isempty())
	{
		cout<<"no elements in queue\n";
	}
	if(front ==rear)
	{
		node *t;
		t=q[rear];
		front=rear=-1;
		return t;
	}
	else
	{
		node *t;
		t=q[rear];
		rear--;
		return t;
	}
}

int queue::size()
{
	if(isempty())
	{
		return 0;
	}
	if(front==rear)
		return 1;
	else
	{
		int value;
		value=rear-front+1;
		return value;
	}
}

class tree
{
	node* root;
	node* create_rec();
	void inorder(node*);
	void preorder(node*);
	void postorder(node*);
	void disp_leaf(node*);
	node* copy_rec(node*);
	int height_rec(node*);

	public:
	tree()
	{
		root=NULL;
	}
	void create_tree();
	void intrav();
	void pretrav();
	void posttrav();
	void display();
	void copy_tree();
	void height();

	void intrav_non();
	void pretrav_non();
	int height_non();
	void displayleaf_non();
	int non_recursive_height();
};


void tree::create_tree()
{
	root=create_rec();
}


node* tree::create_rec()
{
	node *p;
	int x;
	cout<<"Enter data (-1 for NULL): \n";
	cin>>x;
	
	if(x==-1)
		return NULL;

	p = new node(x);
	
	cout<<"Enter left child of "<<x<<" : \n";
	p->l=create_rec();
	
	cout<<"Enter right child of "<<x<<" : \n";
	p->r=create_rec();
	
	return p;
}


void tree::intrav()
{
	inorder(root);
}


void tree::pretrav()
{
	preorder(root);
}


void tree::posttrav()
{
	postorder(root);
}


void tree::inorder(node *p)
{
	if(p)
	{
		inorder(p->l);
		cout<<"\t"<<p->data;
		inorder(p->r);
	}
}


void tree::preorder(node *p)
{
	if(p)
	{
		cout<<"\t"<<p->data;
		preorder(p->l);
		preorder(p->r);
	}
}


void tree::postorder(node *p)
{
	if(p)
	{
		postorder(p->l);
		postorder(p->r);
		cout<<"\t"<<p->data;
	}
}


void tree::display()
{
	disp_leaf(root);
}


void tree::disp_leaf(node * p)		//using inorder recursive 
{
	if(p)
	{
		disp_leaf(p->l);
		
		if(p->l==NULL && p->r==NULL)
			cout<<"\t"<<p->data;
		
		disp_leaf(p->r);
	}
}


void tree::copy_tree()
{
	node *cpy;
	cpy=copy_rec(root);
	inorder(cpy);
}


node* tree::copy_rec(node * p)
{
	node *t;
	int x;
	t=p;
	
	if(t==NULL)
		return NULL;

	t->data = p->data;
	t->l=copy_rec(p->l);
	t->r=copy_rec(p->r);
	
	return t;

}


void tree:: height()
{
	int h;
	h=height_rec(root);
	cout<<"The height of tree is : "<<h<<endl;
}


int tree:: height_rec(node *t)
{
	if(t==NULL)
	return -1;

	if(t->l==NULL && t->r==NULL)
	return 0;

	return(max(height_rec(t->l),height_rec(t->r))+1);
}


void tree::intrav_non()
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
		
		cout<<t->data<<"\t";
		
		t=t->r;
		while(t!=NULL)
		{
			S.push(t);
			t=t->l;
		}
	}
}


void tree::pretrav_non()
{
	stack1 S;
	node* t=root;

	while(t!=NULL)
	{
		cout<<t->data<<"\t";
		S.push(t);
		t=t->l;
	}
	while(!S.isempty())
	{
		t=S.pop();
		t=t->r;
		while(t!=NULL)
		{
			cout<<t->data<<"\t";
			S.push(t);
			t=t->l;
		}
	}
}


int tree::height_non()
{
	int h=-1;
	stack1 S;
	node* t=root;
	while(t!=NULL)
	{
		S.push(t);
		t=t->l;
	}
	h = S.top;

	while(!S.isempty())
	{
		t=S.pop();
		t=t->r;
		while(t!=NULL)
		{
			S.push(t);
			t=t->l;
			if(h<S.top)
			h=S.top;
		}
	}
	return h;
}


void tree::displayleaf_non()		//using inorder non-recursive
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
		
		if(t->l==NULL && t->r==NULL)
			cout<<t->data<<"\t";
			
		t=t->r;
		while(t!=NULL)
		{
			S.push(t);
			t=t->l;

		}
	}
}



int tree::non_recursive_height()
{
    node *temp = root;
     queue queue_obj1;
    node *p;
    int height=-1,size;

    if (temp == NULL)
        return 0;

   
    queue_obj1.enque(temp);
    
    while (!queue_obj1.isempty()) 
    {
    
    	size = queue_obj1.size();
        while (size--) 
        {
            p = queue_obj1.deque();

            if (p->l != NULL)
                queue_obj1.enque(p->l);

            if (p->r != NULL)
                queue_obj1.enque(p->r);
        }
        height++;
    }
    return height+1;
}


int main()
{
	int ch,h;
	tree t;
	do
	{
		cout<<"\nEnter your choice : \n1. Create tree\n2. Inorder traversal\n3. Preorder traversal\n4. Postorder traversal\n5. Display Leaf\n6. Copy\n7. Height\n8. Intrav(Non Recursive)\n9. Pretrav(Non Recursive)\n10. Height(Non Recursive)\n11. Display Leaf (Non Recursive)\n12. Exit\n";
		cin>>ch;

		switch(ch)
		{
			case 1:
				t.create_tree();
			    break;

			case 2:
				cout<<"The inorder traversal is : \n";
				t.intrav();
			    break;

			case 3:
				cout<<"The preorder traversal is : \n";
				t.pretrav();
                break;

			case 4:
				cout<<"The postorder traversal is : \n";
				t.posttrav();
			    break;

			case 5:
				cout<<"Leaf nodes are : \n";
				t.display();
			    break;

			case 6:
				cout<<"Copied tree is : \n";
				t.copy_tree();
			    break;

			case 7:
				t.height();
			    break;

			case 8:
				cout<<"The inorder traversal is : \n";
				t.intrav_non();
			    break;

			case 9:
				cout<<"The preorder traversal is : \n";
				t.pretrav_non();
			    break;

			case 10:
				h=t.non_recursive_height();
				cout<<"The height of tree is : "<<h<<endl;
                break;

			case 11:
				cout<<"Leaf nodes are : \n";
				t.displayleaf_non();
			    break;
		}
	}while(ch<12);
}

/*
Output:
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
1
Enter data (-1 for NULL):
1
Enter left child of 1 :
Enter data (-1 for NULL):
2
Enter left child of 2 :
Enter data (-1 for NULL):
4
Enter left child of 4 :
Enter data (-1 for NULL):
6
Enter left child of 6 :
Enter data (-1 for NULL):
-1
Enter right child of 6 :
Enter data (-1 for NULL):
-1
Enter right child of 4 :
Enter data (-1 for NULL):
-1
Enter right child of 2 :
Enter data (-1 for NULL):
5
Enter left child of 5 :
Enter data (-1 for NULL):
-1
Enter right child of 5 :
Enter data (-1 for NULL):
-1
Enter right child of 1 :
Enter data (-1 for NULL):
3
Enter left child of 3 :
Enter data (-1 for NULL):
-1
Enter right child of 3 :
Enter data (-1 for NULL):
-1

Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
2
The inorder traversal is :
	6	4	2	5	1	3
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
3
The preorder traversal is :
	1	2	4	6	5	3
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
4
The postorder traversal is :
	6	4	5	2	3	1
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
5
Leaf nodes are :
	6	5	3
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
6
Copied tree is :
	6	4	2	5	1	3
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
7
The height of tree is : 3

Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
8
The inorder traversal is :
6	4	2	5	1	3
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
9
The preorder traversal is :
1	2	4	6	5	3
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
10
The height of tree is : 3

Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
11
Leaf nodes are :
6	5	3
Enter your choice :
1. Create tree
2. Inorder traversal
3. Preorder traversal
4. Postorder traversal
5. Display Leaf
6. Copy
7. Height
8. Intrav(Non Recursive)
9. Pretrav(Non Recursive)
10. Height(Non Recursive)
11. Display Leaf (Non Recursive)
12. Exit
12
[student@localhost ~]$

*/
