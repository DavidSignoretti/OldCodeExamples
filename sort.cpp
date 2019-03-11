/***********************************************************
*	David F. Signoretti
*	C/C++ ISYS326
*
*	Instructor John Selmys
*
*	Project Name: Assignment 2
*	File:sort.cpp
*	Date:March 24 2000
************************************************************/
#include <iostream.h>
#include <fstream.h>

class Student
{
	char *name_ptr;
	Student *next_ptr;
	Student *back_ptr;
public:
	Student();
	Student(char *str);
	~Student();
	
	//Class Functions
	void getnext_ptr();
	void getback_ptr();
	void getname();
	int comp(Student &q);
	
	friend class StudentList;
};

Student::Student()
{
	strcpy(name_ptr, "\0");
	next_ptr = NULL;
	back_ptr = NULL;
}

Student::Student(char *str)
{
	name_ptr = new char[strlen(str) + 1];
	strcpy(name_ptr, str);
	next_ptr = NULL;
	back_ptr = NULL;
}

Student::~Student()
{
	delete[] name_ptr;
}

class StudentList
{

	Student *start_ptr;
	int counter;
public:
	StudentList();
	~StudentList();
	
	void sortName(char *str);
	void remove(int n);
	void view(void) const;
	void counterP(){ ++counter; }
	void counterM(){ --counter; }
	int getcounter(){ return counter; }
};

StudentList::StudentList()
{
	start_ptr = NULL;
	counter = 0;
}
	
StudentList::~StudentList()
{	
}

void StudentList::sortName(char *str)
{
	++counter;
 	Student *p;
 	Student *q;
 	q = new Student(str);
 	
 	p = start_ptr;
 	
 	if ( start_ptr == NULL )
 	{
 		q->back_ptr = q;
 		q->next_ptr = q;
 		start_ptr = q;
 	}
 	else
	{
		do
		{
			if (strcmp(p->name_ptr, q->name_ptr) >= 0)
			{
				
				if (strcmp(p->name_ptr, q->name_ptr) == 0)
				{
					delete []q;
					return;
				}

				q->next_ptr = p;
				q->back_ptr = p->back_ptr;
				p->back_ptr->next_ptr = q;
				p->back_ptr = q;				
				
				if ( p == start_ptr)
			 	{
					start_ptr = q;
					return;
				}
				return;
			}
			else
			{
				p = p->next_ptr;
			}
		}while(p->next_ptr != start_ptr);
		
	}
	
 }

 void StudentList::remove(int n)
 {
 	Student *p;
 	int i = 0;
 	
 	if ( n < 0 )
 		start_ptr = start_ptr->back_ptr;

 	p = start_ptr;
 	
 	if ( n < 0)
 	{
 		while ( i != n )
 		{
 			p = p->back_ptr;
 			--i;
 		}
 	}
 	else
 	{
 		while ( i != n)
 		{
 			p = p->next_ptr;
 			++i;
 	        }
 	}
 	
 	
 	p->back_ptr->next_ptr = p->next_ptr;
 	p->next_ptr->back_ptr = p->back_ptr;
 	
 	if ( p == start_ptr )
 		start_ptr = p->next_ptr;
 		
 	if ( getcounter() <= 10)
 		cout << p->name_ptr;
 		
 	delete []p; 	
 		
 }

void StudentList::view(void) const
{
	Student *p;
	p = start_ptr;
	do
	{ 
		cout << p->name_ptr << "\n";
		p = p->next_ptr;
	}while(p != start_ptr);
}

int main(int argc, char *argv[])
{
	if (argv [1] == NULL)
	{
		cout << "\n***Name of file required***\n\n";
		exit(1);
	}
	
	char name[80];
	ifstream f(argv[1]);
	StudentList s;
        while ( !f.eof())
	{
		f >> name;
		s.sortName(name);
		
	}
	
	s.view();
	cout << s.getcounter() << endl;
	int number;
	
	cout << "Enter the magic number :";
	cin >> number;
	cout << endl;
	int i = 0;
	while ( i < s.getcounter())
	{
		s.remove(number);
		s.counterM();
	}
	cout << "\n\n\n" << "Have a nice day!";
	
	return 0;
}
