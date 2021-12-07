//Simon Yoon
//ECE 264: Data Structures and Algorithms, Part I Fall 2020
//Professor Sable
//Program follows specific directions from a text document provided by the user
//and performs the actions needed. The results are printed to a seperate
//text document also provided by the user

#include <iostream> 
#include <list> 
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

ifstream inputFile; 
ofstream outputFile;  

//create base class SimpleList
//includes head and tail pointers, size, and name
//includes add and remove functions

template <typename T> 
class SimpleList 
{
private: 
	//set up nodes for linked list
	class Node 
	{
	public:
		Node(T data, Node *n=NULL)
    {
      value = data;
      next = n;
    }
    T value;
    Node *next;
  };

  int size = 0;
  Node *head;
  Node *tail;
  string name;

protected: 
	//push/pop f(x)
	void insertStart(T value); 
	void insertEnd(T value); 
	T removeStart(); 

public: 
	SimpleList(string &title) : name{title} {}        //constructor allows to set the name of object


	//pure virtual functions to make sure derived classes define push/pop
	virtual void push(T value) = 0;
	virtual T pop() = 0; 
	
	//functions to return the name of object/return true or false if the object is empty 
	string getName() const
	{
		return name;
	}
	bool isEmpty() const
	{
		return size == 0;
	}

};

//adds node to start, moves head to new node, increase size
template <typename T> 
void SimpleList<T>::insertStart(T value)
{
	class Node* newNode = new Node{value, head}; 
	head = newNode; 
	size++;
	return; 	
}

//adds node to end, moves tail to new node, increase size 
template <typename T>
void SimpleList<T>::insertEnd(T value)
{
	class Node* newNode = new Node{value}; 
	if (size > 0)
	{
		tail->next = newNode; 
	}
	tail = newNode; 
	++size;
	//if first node, both head and tail point to node
	if (size == 1)
	{
		head = tail; 
	}
	return;
}

//temp at start, move head over to next node, delete temp, reduce size
template <typename T>
T SimpleList<T>::removeStart()
{
	T retValue = head->value; 
	Node *temp = head; 
	head = head->next; 
	delete temp; 
	if (size == 1) 
	{
		tail = nullptr; 
	}
	--size; 
	return retValue; 
}


//define pop and push, for stack, both from front
template <typename T> 
class Stack : public SimpleList<T> 
{
public:
	Stack(string &title) : SimpleList<T>{title} {}  
	
	void push(T value) override
	{
		SimpleList<T>::insertStart(value);
	}

	T pop() override
	{
		return SimpleList<T>::removeStart();
	} 	

};

//define pop and push, for queue, add to back, remove from front
template <typename T> 
class Queue : public SimpleList<T> 
{
public:
	Queue(string &title) : SimpleList<T>{title} {} 
	
	void push(T value) override
	{
		SimpleList<T>::insertEnd(value);
	}

	T pop() override
	{
		return SimpleList<T>::removeStart();
	} 	
};

//check if object's name is unique 
template <typename T> 
bool nameExist(string &name, list<SimpleList<T> *> &tList)
{
	for (auto structure : tList)
	{
		if (structure->getName() == name)
		{
			return true; 
		}
	}
	return false; 
}

//gets the type of the object (if it's a stack or queue). True for stack, false for q
bool getType(string &inputText)
{
	if (inputText[inputText.length()-1] == 'k') //checks the last letter of input line
	{
		return true; // stack
	}
	else 
	{
		return false; // queue
	}
}

//retrieves the name of the object from given input
string getName(string &text)
{	
	int i = 0; 
	string temp = text; 
	temp += '\0'; //created a temporary object to modify it without modifying input. Add \0 so we have a condition to check for
	while (temp[i] != ' ') //gets past the command
	{
		++i; 
	}

	++i; 
	string name;	
	while (temp[i] != ' ') //adds char by char the value of the input to name var.
	{								
		if (temp[i] == '\0') // If (for pop) \0 is reached, break. Otherwise end at first space
			break; 
		name += temp[i]; 
		++i; 
	} 

	return name; 
}

//create stacks and queues of type int
void createI(string &titleci, string &sqci, list<SimpleList<int> *> &intL)
{
	if (nameExist(titleci, intL) == false) //checks if the name exists or not, if not, proceed
	{
		if (getType(sqci)) //check if it's stack or q
		{
			intL.push_front(new Stack<int>{titleci}); //add to the list a stack
		}
		else 
		{
			intL.push_front(new Queue<int>{titleci}); //add to the list a q
		}
	}
	else 
	{
		outputFile << "ERROR: This name already exists!\n";
	}	
}

//create stack and queue for type double. same process as int
void createD(string &titlecd, string &sqcd, list<SimpleList<double> *> &doubL)
{
	if (!nameExist(titlecd, doubL))
	{
		if (getType(sqcd))
		{
			doubL.push_front(new Stack<double>{titlecd});
		}
		else 
		{
			doubL.push_front(new Queue<double>{titlecd});
		}
	}
	else 
	{
		outputFile << "ERROR: This name already exists!\n";
	}	
}

//create stack and queue for strings. same process and int and double
void createS(string &titlecs, string &sqcs, list<SimpleList<string> *> &strL)
{
	if (!nameExist(titlecs, strL))
	{
		if (getType(sqcs))
		{
			strL.push_front(new Stack<string>{titlecs});
		}
		else 
		{
			strL.push_front(new Queue<string>{titlecs});
		}
	}
	else 
	{
		outputFile << "ERROR: This name already exists!\n";
	}	
}

//retrieves the value from the input 
string getVal(string &text)
{
	int count = 0; 
	int i = 0; 
	string temp = text;
	temp += '\0';  
	string data; 
	while (count != 2)
	{
		while (temp[i] != ' ') {++i;}
		++count; 
		++i;
	}
	while (temp[i] != '\0')
	{
		data += temp[i]; 
		++i; 
	} 

	return data; 

}

//call this function to push/pop from an integer object
void pushpopI(string &commandpi, string &titlepi, string &valpi, list<SimpleList<int> *> &intL)
{
	if(nameExist(titlepi, intL))  //checks if name exists
	{

		for (auto structure : intL)
		{
			if (structure->getName() == titlepi) //checks if the name matches what we're looking for
			{
				if (commandpi[1] == 'u') //checks if push

				{
					int i = atoi(valpi.c_str());
					structure->push(i); 
					break;
				}
				if (commandpi[1] == 'o') //checks if pop
				{
					if (structure->isEmpty()) //checks if empty
					{
						outputFile << "ERROR: This list is empty!\n"; 
						break;
					} 
					else
					{
						outputFile << "Value popped: " << structure->pop() << '\n';
						break; 
					}
				}
			}
		}

	}
	else 
	{
		outputFile << "ERROR: This name does not exist!\n";
	}
}

//call this function to push/pop from an double object
void pushpopD(string &commandpd, string &titlepd, string &valpi, list<SimpleList<double> *> &doubL)
{
	if(nameExist(titlepd, doubL))
	{

		for (auto structure : doubL)
		{
			if (structure->getName() == titlepd)
			{
				if (commandpd[1] == 'u')
				{
					double d = atof(valpi.c_str());
					structure->push(d); 
					break;
				}
				if (commandpd[1] == 'o')
				{
					if (structure->isEmpty())
						{
							outputFile << "ERROR: This list is empty!\n"; 
							break;
						} 
					else
					{
						outputFile << "Value popped: " << structure->pop() << '\n';
						break; 
					}
				}
			}
		}

	}
	else 
	{
		outputFile << "ERROR: This name does not exist!\n";
	}
}

//call this function to push/pop from an string object
void pushpopS(string &commandps, string &titleps, string &valpi, list<SimpleList<string> *> &strL)
{
	if(nameExist(titleps, strL)) 
	{

		for (auto structure : strL)
		{
			if (structure->getName() == titleps)
			{
				if (commandps[1] == 'u')
				{
					structure->push(valpi); 
					break;
				}
				if (commandps[1] == 'o')
				{
					if (structure->isEmpty())
						{
							outputFile << "ERROR: This list is empty!\n"; 
							break;
						} 
					else
					{
						outputFile << "Value popped: " << structure->pop() << '\n';
						break; 
					}
				}
			}
		}

	}
	else 
	{
		outputFile << "ERROR: This name does not exist!\n";
	}
}

//determine what action needs to be taken and call that function
void executeCommand(string command, string title, string sq,
   list<SimpleList<int> *> &intList, list<SimpleList<double> *> &doubList, list<SimpleList<string> *> &strList)
{
  //if create
  if(command[0] == 'c')
  {
    if (title[0] == 'i')
    {
      createI (title, sq, intList);
    }
    if (title[0] == 's')
    {
      createS (title, sq, strList);
    }
    if (title[0] == 'd')
    {
      createD (title, sq, doubList);
    }
  }
  //if push or pop
  if(command[0] == 'p')
  {
    if (title[0] == 'i')
    {
      pushpopI (command, title, sq, intList);
    }
    if (title[0] == 's')
    {
      pushpopS (command, title, sq, strList);
    }
    if (title[0] == 'd')
    {
      pushpopD (command, title, sq, doubList);
    }
  }
}

int main() 
{
	list<SimpleList<int> *> intList; 
	list<SimpleList<double> *> doubList; 
	list<SimpleList<string> *> strList; 

	string in; 
	string out; 
	cout << "Enter name of input file: ";   //enter input/output files
	cin >> in;  
	cout << "Enter name of output file: "; 
	cin >> out; 

	inputFile.open(in.c_str()); 
	outputFile.open(out.c_str()); 

	string myText; 
	 while (getline (inputFile, myText))
  {
    outputFile << "EXECUTING COMMAND: " << myText << endl;
    string name = getName(myText);
    string val = getVal(myText);
    executeCommand(myText, name, val, intList, doubList, strList);
  }

	inputFile.close();
	outputFile.close(); 
	return 0; 
}