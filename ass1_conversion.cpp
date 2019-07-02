// Name : Kara Priyanka     Batch: A1     Roll no.: 03
// Assignment 1: Conversion of infix to prefix and postfix

/*Implement stack as an abstract data type using linked list and use this ADT for conversion of infix expression to postfix, prefix and evaluation of postfix and prefix expression.*/

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>

using namespace std;

struct node
{
     char data;
     struct node *next;
};

class stack
{
   public:
   struct node *top;
     stack()
     {  top=NULL;  }
     void push(char);
     char pop();
     char readtop();
     int isempty();
};

/************************************************************************************************************************************************
                                                    isempty()
************************************************************************************************************************************************/
int stack::isempty()
{
  if(top==NULL)
  return 1;           // if its empty then the top will be NULL
  else
  return 0;
}


/************************************************************************************************************************************************
                                                    push()
************************************************************************************************************************************************/
void stack::push(char ele)
{
    struct node *nn;
    nn=new node;
    nn->data=ele;
    nn->next=NULL;
  if(isempty())
  {
    top=nn;    // checking whether empty or not ,if empty then make the accepted node as top
  }
  else
  {
    nn->next=top;
    top=nn;
  }

}// end of push


/************************************************************************************************************************************************
                                                    pop()
************************************************************************************************************************************************/
char stack::pop()
{
  if(isempty())   // if list is empty
  {
    return -1;
  }
  if(top->next==NULL)   // if there's only 1 node
  {
    char ol;
    ol=top->data;
    top=NULL;
    return ol;
  }
  else
  {
    char ol;
    ol=top->data;
    struct node *temp;
    temp=top;
    top=top->next;
    temp->next=NULL;
    delete temp;
    return ol;
  }

}


/************************************************************************************************************************************************
                                                    read top of the stack
************************************************************************************************************************************************/
char stack::readtop()
{
  if(isempty())
  {
  return 1;
  }
  else
  return top->data;
}



class conversion		// class conversion with arrays infix, postfix, prefix
{
	char infix[20];
	char prefix[20];
	char postfix[20];
  public:
	void in_post(char []);
	void in_pre(char []);
	int precedence(char);
};

/********************************************************************************************************************************************************
                                                             checking precedence
*********************************************************************************************************************************************************/
int conversion::precedence(char op)		// function to calculate the precedence of the operator
{
	switch(op)
	{
	case '$': return 4;
	case '%': return 3;
	case '*': return 2;
	case '/': return 2;
	case '+': return 1;
	case '-': return 1;
	default: return 0;
	}
}

/********************************************************************************************************************************************************
                                                             converting infix to prefix
*********************************************************************************************************************************************************/
void conversion::in_pre(char arr[])		// function to convert infix expression to prefix
{
		int i;
		stack s2;
		for( i=0;arr[i]!='\0';i++)	// for reversing the prefix expression taken input in arr[]
			s2.push(arr[i]);

		int j=0;
		while(j<i)
			{
				arr[j]=s2.pop();
				j++;
			}
		  i=0;
			int old_pre;
			int curr_pre;
			char top_ele;
			int index=0;	//for keeping the index of the 
			stack s;
			while(arr[i]!='\0')
			{
				if(!isalnum(arr[i]))	//whether an operand or not 		So this condition is for operator or ( )
					{	if(arr[i]==')')
						{
								s.push(arr[i]);
						}
						else if(arr[i]=='(')
						{
							int k;
							k= s.readtop();
							while(k!=')')
							{
								prefix[index++]=s.pop();
								k=s.readtop();
							}
							k=s.pop();// for popping the ) which breaks the above while
						}
						else	// when normal operator
						{
							top_ele= s.readtop();
							old_pre= precedence(top_ele);
							curr_pre= precedence(arr[i]);

							if(s.isempty() || (curr_pre>= old_pre))	// the current token's precedence is greater than or equal to the operator present in stack
								s.push(arr[i]);
							else	// if precedence of current operator is smaller than the operator in stack
							{
								prefix[index++]=s.pop();
								while(old_pre>curr_pre) // working till the oldprecedence is not greater than current precedence
								{
									top_ele=s.readtop();
									old_pre= precedence(top_ele);
									if(curr_pre>=old_pre)
										s.push(arr[i]);
									else 
										prefix[index++]=s.pop();
								}

							}

						}
					}

				else	// if it is an operand 
				{
					prefix[index++]=arr[i];
				}
				i++;
			}
			
			//now popping the remaining elements in the stack 
			while(!s.isempty())
				prefix[index++]=s.pop();
			
			prefix[index]='\0';
			//now reverse the obtained expression	
			for( i=0;prefix[i]!='\0';i++)
						s2.push(prefix[i]);

			j=0;
			while(j<i)
			{
				prefix[j]=s2.pop();
				j++;
			}
			
			
			cout<<"The prefix expression is\n"<<prefix;


}

/********************************************************************************************************************************************************
                                                             converting infix to postfix
*********************************************************************************************************************************************************/
void conversion::in_post(char arr[])		// function to convert infix expression to postfix
{
	int i=0;
	int old_pre;
	int curr_pre;
	char top_ele;
	int index=0;
	stack s;
	while(arr[i]!='\0')
	{
		if(!isalnum(arr[i]))	// if an operator or ( )
			{	
				if(arr[i]=='(')
					{
						s.push(arr[i]);
					}
				else if(arr[i]==')')
				{
					int k;
					k= s.readtop();
					while(k!='(')
					{
						postfix[index++]=s.pop();
						k=s.readtop();
					}
					k=s.pop();
				}
				else
				{
					top_ele= s.readtop();
					old_pre= precedence(top_ele);
					curr_pre= precedence(arr[i]);

					if(s.isempty() || (curr_pre > old_pre))
						s.push(arr[i]);
					else if(curr_pre <= old_pre)
					{
						postfix[index++]=s.pop();
						while(old_pre >= curr_pre)
						{
							top_ele=s.readtop();
							old_pre= precedence(top_ele);
							if(curr_pre > old_pre)
								s.push(arr[i]);
							else 
								postfix[index++]=s.pop();
						}

					}

				}
			}

		else	// if an operand
		{
			postfix[index++]=arr[i];
		}
		i++;
	}
	
	//to empty the stack
	while(!s.isempty())
				postfix[index++]=s.pop();
				
	postfix[index]='\0';//close the array
	
	cout<<"The postfix expression is\n"<<postfix;

}

/**********************************************************************************************************************************************************
                                                                       Main
**********************************************************************************************************************************************************/
int main()
{	conversion c1;
	char arr1[20];

	cout<<"Enter the Infix expression\n";
    cin>>arr1;

	int ch;
	do{
			cout<<"\nEnter your choice\n1.Infix to postfix\n2.Infix to prefix\n3.Exit\n";
			cin>>ch;
			switch(ch)
			{
			   case 1:
			       {
			           c1.in_post(arr1);
                       cout<<"\n";
                       break;
			       }
               case 2:
                   {
                       c1.in_pre(arr1);
				       cout<<"\n";
				       break;
                   }
			}
	}while(ch!=3);
}


/*********************************************************************************************************************************************************
                                                              OUTPUT
**********************************************************************************************************************************************************
[kara@localhost Videos]$ g++ ass1_conversion.cpp
[kara@localhost Videos]$ ./a.out
Enter the Infix expression
(a+b$c)*d+e$f

Enter your choice
1.Infix to postfix
2.Infix to prefix
3.Exit
1
The postfix expression is
abc$+d*ef$+

Enter your choice
1.Infix to postfix
2.Infix to prefix
3.Exit
2
The prefix expression is
+*+a$bcd$ef

Enter your choice
1.Infix to postfix
2.Infix to prefix
3.Exit
3
[kara@localhost Videos]$ 
**********************************************************************************************************************************************************/
