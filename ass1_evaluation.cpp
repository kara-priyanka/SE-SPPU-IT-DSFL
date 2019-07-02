// Name : Kara Priyanka     Batch: A1     Roll no.: 03
// Assignment 1: Stack for the evaluation of prefix and postfix expression

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


//int type stack
class stack			//Stack implemented using LINKED LIST
{
   public:
   struct node *top;
     stack()
     {  top=NULL;  }
     void push(char);		// Checking condition: here no full be checked as it is linked list implementation so never full till there is memory available for dynamic allocation
     char pop();		// Checking condition: Is empty or not
     char readtop();
     int isempty();
};

class evalexp
{
   char postfix[20],prefix[20];
   public:
      evalexp()
      {}
      void acceptpost();   //for accepting the postfix expression
      void acceptpre();    // for accepting the prefix expression
      int calculate(int op1,int op2,char oper);// calculating the the expressions value
      void evalpost();     // evaluating the postfix expression
      void evalpre();      // evaluating the prefix expression
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

/************************************************************************************************************************************************
                                                    accept postfix expression
************************************************************************************************************************************************/
void evalexp::acceptpost()
{
  cin>>postfix;
}

/************************************************************************************************************************************************
                                                    accept the prefix expression
************************************************************************************************************************************************/
void evalexp::acceptpre()
{
  cin>>prefix;
}

/************************************************************************************************************************************************
                                                    evaluate the postfix expression
************************************************************************************************************************************************/
void evalexp::evalpost()
{
  stack s;
  int i,op1,op2,val;
  for(i=0;postfix[i]!='\0';i++)
  {
    char token=postfix[i];

    if(isalnum(token)!=0)  // checking whether operator or operand
    {
      cout<<"Enter the value for "<<token<<endl;
      int value;
      cin>>value;
      s.push(value);
    }
    else      // if operator
    {
      op2=s.pop();			// first pop is the OPERAND NO. 2
      op1=s.pop();			// second pop is the OPERAND NO.1
      val=calculate(op1,op2,token);
      s.push(val);
    }
  }
  val=s.pop();
  cout<<"the evaluation of the postfix expression:\n"<<val;

}

/************************************************************************************************************************************************
                                                    evaluate prefix expression
************************************************************************************************************************************************/
void evalexp::evalpre()
{
  stack s;
  int i,op1,op2,val;
  int j;
  int l=strlen(prefix);
  for(i=l-1;i>=0;i--)			// the list is to be traversed from the last
  {
    char token=prefix[i];

    if(isalnum(token)!=0)
    {
      cout<<"Enter the value for "<<token<<endl;
      int value;
      cin>>value;
      s.push(value);
    }
    else
    {
      op1=s.pop();			// first pop is OPERAND NO. 1
      op2=s.pop();			// second pop is OPERAND NO. 2
      val=calculate(op1,op2,token);
      s.push(val);
    }
  }
  val=s.pop();
  cout<<"the evaluation of the prefix expression:\n"<<val;
}

/************************************************************************************************************************************************
                                                          calculate
************************************************************************************************************************************************/
int evalexp::calculate(int op1,int op2, char token)
{
  switch(token)
	{
		case '+': return op1 + op2;
		case '-': return op1 - op2;
		case '*': return op1 * op2;
		case '/': return op1 / op2;
		case '$': return pow(op1,op2);
		case '%': return op1 % op2;

	}
}

/************************************************************************************************************************************************
                                                    main()
************************************************************************************************************************************************/
int main()
{
  int choice;
  evalexp obj;
  do
  {
  cout<<"\n*******MENU*******\n1.Evaluate Postfix\n2.Evaluate Prefix\n3.EXIT\n";
  cin>>choice;

  switch(choice)
  {
    case 1:
    {
      cout<<"Enter the postfix expression:\n";
      obj.acceptpost();
      obj.evalpost();
      break;
    }// end of case 1
    case 2:
    {
      cout<<"Enter the prefix expression:\n";
      obj.acceptpre();
      obj.evalpre();
      break;
    }
  }//end choice

  }while(choice!=3);
}//end of main


/**********************************************************************************************************************************************************
                                                                OUTPUT
***********************************************************************************************************************************************************


*******MENU*******
1.Evaluate Postfix
2.Evaluate Prefix
3.EXIT
1
Enter the postfix expression:
ABC*DE/-+
Enter the value for A
2
Enter the value for B
3
Enter the value for C
1
Enter the value for D
4
Enter the value for E
5
the evaluation of the postfix expression:
5
*******MENU*******
1.Evaluate Postfix
2.Evaluate Prefix
3.EXIT
2
Enter the prefix expression:
-+A*BC/DE
Enter the value for E
5
Enter the value for D
4
Enter the value for C
1
Enter the value for B
3
Enter the value for A
2
the evaluation of the prefix expression:
5
*******MENU*******
1.Evaluate Postfix
2.Evaluate Prefix
3.EXIT
3

Process returned 0 (0x0)   execution time : 52.730 s
Press any key to continue.
**********************************************************************************************************************************************************/
