#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

using namespace std;

// node class
template <class T> class Node
{

public:
  Node* next;
  T value;
  // constructor
  Node(T val);
  ~Node();
};

// Node constructor
template <class T> Node<T>::Node(T val)
{
  this->value = val;
}

// Node destructor
template <class T> Node<T>::~Node()
{
  delete next;
}

template <class T> class LinkedList
{
private:
  Node<T>* head;
  Node<T>* tail;
  int nodeCount;

public:
  // constructor
  LinkedList();
  ~LinkedList();

  // methods
  void AddNodeatEnd(T val);
  void InterLeave(LinkedList<T>* p, int stp);
  void Print();
};

// constructor
template <class T>
LinkedList<T>::LinkedList()
{
  head = NULL;
  tail = NULL;
  nodeCount = 0;
}

// destructor
template <class T>
LinkedList<T>::~LinkedList()
{
  delete head;
  delete tail;
}

// adding the node at the end of the list
template<class T>
void LinkedList<T>::AddNodeatEnd(T val)
{
  Node<T>* newNode = new Node<T>(val);
  nodeCount++;
  if (nodeCount == 1)
  {
    newNode->next = head;
    head = newNode;
    tail = newNode;
  }
  else
  {
    tail->next = newNode;
    tail = newNode;
  }
}

// InterLeaving method
template<class T>
void LinkedList<T>::InterLeave(LinkedList<T>* p, int stp)
{
  Node<T>* currentL1 = head;
  Node<T>* previousL1 = NULL;
  Node<T>* currentL2 = p->head;
  Node<T>* previousL2 = NULL;
  int steps = stp;

  while(currentL2 != NULL)
  {
    for(int j=0; j<steps; j++)
    {
      previousL1 = currentL1;
      currentL1 = currentL1->next;
    }
    previousL2 = currentL2;
    currentL2 = currentL2->next;
    p->head = currentL2;
    previousL1->next = previousL2;
    previousL2->next = currentL1;
    this->nodeCount++;
    p->nodeCount--;
  }
}

// printing values from list
template<class T>
void LinkedList<T>::Print()
{
  Node<T>* current = head;
  for (int i=0; i < nodeCount; i++)
  {
    cout << current->value << " ";
    current = current->next;
  }
  cout << endl;
}

// working with initial list
class ManagementList
{
private:
  string numOfElemS;
  string numOfLs;
  string step;
  string temp;
  int tempValue;
  int numOfElemI;
  int stepInt;
  int numOfLsInt;

public:
  ManagementList();
  ~ManagementList();
  void ManageFirstL();
  void ManageAdditionaL();
  LinkedList<int>* L1;
  LinkedList<int>* L2;
};

ManagementList::ManagementList()
{
  numOfElemS = "";
  numOfLs = "";
  step = "";
  temp = "";
  tempValue = 0;
  numOfElemI = 0;
  stepInt = 0;
  numOfLsInt = 0;
  L1 = new LinkedList<int>();
  L2 = new LinkedList<int>();
}

ManagementList::~ManagementList()
{
  delete L1;
  delete L2;
}

void ManagementList::ManageFirstL()
{
  // getting the number of elements for the first list
  getline(cin,numOfElemS);
  istringstream iss(numOfElemS);
  iss >> numOfElemI;
  iss.clear();

  // getting the elements
  getline(cin,temp);
  iss.str(temp);

  for(int i=0; i < numOfElemI; i++)
  {
    iss >> tempValue;
    L1->AddNodeatEnd(tempValue);
  }
  iss.clear();
}

void ManagementList::ManageAdditionaL()
{
  // getting number of additional lists
  getline(cin,numOfLs);
  istringstream iss(numOfLs);
  iss >> numOfLsInt;
  iss.clear();

  // getting all the additional list elements and steps of each list respectively
  for (int i=0; i < numOfLsInt; i++)
  {
    getline(cin,step);
    iss.str(step);
    iss >> stepInt;
    iss.clear();

    getline(cin,numOfElemS);
    istringstream iss(numOfElemS);
    iss >> numOfElemI;
    iss.clear();

    // getting the elements
    getline(cin,temp);
    iss.str(temp);

    for(int i=0; i < numOfElemI; i++)
    {
      iss >> tempValue;
      L2->AddNodeatEnd(tempValue);
    }
    iss.clear();

    // InterLeaving L2 into L1
    L1->InterLeave(L2, stepInt);

  }
}

int main()
{
  ManagementList* ml = new ManagementList();
  ml->ManageFirstL();
  ml->ManageAdditionaL();
  ml->L1->Print();

  return 0;
}
