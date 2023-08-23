#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;
template<class T>
class stack// stack class
{
private:
	class node// node class nested in stack class
	{
	public:
		T data;
		node* next;

	};
	node* top; // head pointer
	int size;
public:
stack() // default constructor
{
	top=nullptr;
	size=0;
}
bool isempty() // checking if the stack is empty or not
{
	if(size==0)
	{
		return true;
	}
	else
		return false;
}
void deleteatop()// delete function used in pop
{
	if(top!=nullptr)
	{
		node*t=top;
		top=top->next;
		delete t;
	}
}
void push(const T & e)// push function
{
	node* temp= new node;
   temp->data=e;
   temp->next=nullptr;
   if(top==nullptr)
   {
	   top=temp;
	   size++;
   }
   else
	temp->next= top;
	top=temp;
	size++;
}
bool pop(T & e) // pop function
{
		if(top!=nullptr)
		{
		    e=top->data;
			deleteatop();
			size--;
			return true;
		}
		else
			return false;
	}
bool Top(T & e)// checking which element is present at the top of stack
{
		if(size==0)
		{
			return false;
		}
		else
		e=top->data;
		return true;
}
~stack()// destructor
{
	node* current=new node;

	while(top!=nullptr)
	{
		current=top->next;
		delete top;
		top=current;
	}
	top=nullptr;
}

};
class XML // xml class
{
public:
   ifstream in; // for file reading
   int lineno; // line number

XML() // default constructor
{
	lineno=1;
}
void setline() // sets line number
{
	lineno=1;
}

};
void checkprolog(stack<XML> & s,string str) // checks prolog 
{
	int i=0;
	char check;
	stack<char>prolog;

	if(str[i]=='<' && str[i+1]=='?') // if finds these characters then pushes '<' in stack
	{
		prolog.push(str[i]);
	}
	else
	{
		cout<<"Error! prolog is invalid"<<endl;
	}

		while(str[i]!='\n')// traversing until we reach the end of prolog
	{
		i++;
	}

	     if(str[i-1]=='>' && str[i-2]=='?')// if finds these characters at the end of prolog then compares it with the element stored in stack
		{
			if(prolog.Top(check))
			{
				
				if(check!='<')
				{
					 cout<<"Error! prolog is invalid"<<endl;
					
				}
				else
				{
					prolog.pop(check);
				   
					
				}
			}
		}
		 else
		 {
			 cout<<"Error! prolog is invalid"<<endl; }
	
		
}
void checktags(stack<XML> & s,string str) // checks tags
{
	int i=0;
	string temp2;
	XML x;
	
	stack<string>tags;

	while(str[i]!='\0')
	{
		if(str[i]=='\n') // increments line number after every line ends
		{
			x.lineno++;
		}
		
		if(str[i]=='<' && str[i+1]!='?' && str[i+1]!='!' && str[i+1]!='/')// checking for starting tag
		{
			int j=i;
			string temp1;
			while(str[j]!='>' && str[j]!=' ') // storing the starting tag 
			{
				temp1=temp1+str[j];
				j++;
			}
			temp1=temp1+'>';
			tags.push(temp1); // pushing the starting tag in stack
		}
		if(str[i]=='<' && str[i+1]=='/')// checking for ending tag
		{
			string temp3;
			temp3=temp3+'<';
			int j=i+2;
			while(str[j]!='>')// storing the ending tag without the backslash so that we can compare it with the starting tag
			{

				temp3=temp3+str[j];
				j++;
			}
			temp3=temp3+'>';
			tags.Top(temp2);// checking the top element of stack
			
		     if(temp2.compare(temp3)!=0)// comparing the ending tag with the starting tag stored in stack
			{
				cout<<"The opening and closing tags are mismatched at line no.:"<<x.lineno<<endl;
				tags.pop(temp2);
			}
			else
			{
				tags.pop(temp2);
			}
			
	
		}
		i++;
	}
	x.setline(); // setting the line number
}
void checkattributes(stack<XML> & s,string str)// checks attributes
{
	XML x;
	stack<char> att;
	int i=0;
	
	while(str[i]!='\0')
	{
		if(str[i]=='\n')// increments the line number after every line ends
		{
			x.lineno++;
		}
		if(str[i]=='=' && x.lineno!=1)// checking for attributes
		{
			att.push(str[i+1]);// storing the starting quote
			int j=i+2;
			while(str[j]!='>')
			{
				j++;
			}
			   char a;
              att.Top(a);
			
			
				if(a!=str[j-1])// comparing the starting and ending quote
				{
				
					cout<<"Opening and closing quotes of attributes are not matched at line no."<<x.lineno<<endl;
					att.pop(a);
				}
				else
				{
					att.pop(a);
				}
			}
			
		i++;
	}
		x.setline();
	}
void checkcomments(stack<XML> & s,string str)// checks comments
{
	XML x;
	int i=0;
	stack<char> comm;

	while(str[i]!='\0')
	{
		
		if(str[i]=='\n') // increments line number after every line ends
		{
			x.lineno++;
		}
		if(str[i]=='<' && str[i+1]=='!' && str[i+2]=='-' && str[i+3]=='-')// checking if a comment appears
		{
			
			comm.push(str[i]);
			
			int j=i+6; 
			while(str[j]!='\n')
			{
				j++;
			}
			char c;

			if(str[j-1]!='>')// checking the end of comment
			{
				cout<<"Invalid comment  at line no."<<x.lineno<<endl;
				comm.pop(c);
				
			}
			else if(str[j-2]!='-')// checking the end of comment
			{
				cout<<"Invalid comment at line no."<<x.lineno<<endl;
				comm.pop(c);
				
				
			}
			else if(str[j-3]!='-')// checking the end of comment
			{
				cout<<"Invalid comment at line no."<<x.lineno<<endl;
				comm.pop(c);
				
			}
		}

		i++;
	}
	x.setline();// setting line number
}
void readfile(ifstream & in)// file reading
{
	stack<XML> S;
	string str1,str2;

	in.open("xml.txt");
	if(in.is_open())
	{
		while(!in.eof())
		{
			getline(in,str1);
			str2=str2+str1;// storing the file in a single string
			str2=str2 +'\n';
		}
	   cout<<str2<<endl;
     
	}
	else
	{
		cout<<"Unable to open file"<<endl;
	}
	 checkprolog(S,str2);// checking prolog
	 checktags(S,str2); // checking tags
	 checkattributes(S,str2); // checking attributes
	 checkcomments(S,str2); // checking comments
}
int main()
{
	XML x1;
	readfile(x1.in);// calling read file function


	system("pause");
		return 0;
}







