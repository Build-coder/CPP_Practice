//Title: LL.cpp
//Author: Jeremy Dixon / Phil Wood
//Date: 4/20/2020
//Description: LL to hold words

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan
  pair<T,int>& GetData(); //Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();

  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~LL();

  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL&);

  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);

  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);

  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);

  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);

  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display();

  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();

  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>&);

  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL

  // Name: IsLetter
  // Desc: When passed a char, returns true if char is a letter
  // Precondition: Existing char
  // Postcondition: Returns true if char is letter
  bool IsLetter(char letter);

  // Name: ToLowerString
  // Desc: Creates a new string of all lowercase chars
  // Precondition: Existing word
  // Postcondition: Change word to lowercase
  string ToLowerString(string word);

  // Name: IsNumber
  // Desc: Returns true if string is a number
  // Precondition: Existing string
  // Postcondition: Returns true if string is number
  bool IsNumber(char number);

private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue

};



//*****************************************************************
//Implement LL here

// constructor 
template <class T>
LL<T>::LL(){
  m_head = nullptr;
  m_size = 0;
}

// destructor
template <class T>
LL<T>::~LL(){
  Node<T>* curr = m_head;
  while(m_head != nullptr){
    // move tracker to next node
    m_head = m_head->GetNext();
    // delete prev node
    delete curr;
    // set curr to m_head node
    curr = m_head;
  }

  m_head = nullptr;
  m_size = 0;
}

// copy constructor
template <class T>
LL<T>::LL(const LL& src){

  m_head = nullptr;
  m_size = 0;

  // create node pointer
  Node<T>* curr = src.m_head;

  while (curr != nullptr){
    // insert into new list
    for (int i = 0; i < curr->GetData().second; i++){
      Insert(curr->GetData().first);
      }
    // iterate to next node
    curr = curr->GetNext();
  }
}

// overload assignment operator
template <class T>
LL<T> &LL<T>::operator=(const LL<T> &src){

  if (&src != this){

    // deallocate memory
    delete this;

    // initialize m_head & m_size
    m_head = nullptr;
    m_size = 0;

    // create node pointer 
    Node<T>* curr = src.m_head;

    while (curr != nullptr){
      // for loop - multiple occurrences of word
      for (int i = 0; i < curr->GetData().second; i++){
        Insert(curr->GetData().first);
      }
      // iterate to next node
      curr = curr->GetNext();
    }
  }

  return *this;
}

// find
template <class T>
Node<T>* LL<T>::Find(const T& data){

  // create node pointer 
  Node<T>* curr = m_head;

  if (m_size != 0)
  {
    while (curr != nullptr)
    {
      // check to see if curr's string matches string passed in
      if (curr->GetData().first == data)
      {
        return curr;
      }
    // move to next node in LL
    curr = curr->GetNext();
    }
  } 

  return nullptr;
}

// insert
template <class T>
void LL<T>::Insert(const T& data)
{
  cout << "INSERTING " << data << endl;
  
  // create a nodePtr pointing to node with pair.first as "data"
  Node<T>* check = Find(data); 

  // updates freq if already in list
  if(check != nullptr)
  {
    check->SetData(make_pair(check->GetData().first,check->GetData().second+1));
    return;
  }
  // otherwise...
  else
  { 
    Node<T>* newNode = new Node<T>(data);
    Node<T>* curr = m_head;
    Node<T>* prev = m_head;
    newNode->SetNext(nullptr);
  
    //Case if LL is empty
    if(m_head == nullptr)
    {
      m_head = newNode;
      m_size++;
      return;
    }
    //Case when exactly one node (after m_head)
    if(m_size == 1 && newNode->GetData().first > m_head->GetData().first)
    {
      m_head->SetNext(newNode);
      m_size++;
      return;
    }
    //Case if this is before current m_head
    if(newNode->GetData().first < m_head->GetData().first)
    {
      newNode->SetNext(m_head);
      m_head = newNode;
      m_size++;
      return;
    }

    while(curr != nullptr)
    {
      if(curr->GetData().first > newNode->GetData().first &&
      prev->GetData().first < newNode->GetData().first)
      { //Case in middle
        newNode->SetNext(curr);
        prev->SetNext(newNode);
        m_size++;
        return;    
      }
      else if (curr->GetNext() == nullptr)
      { //Case for new end
        curr->SetNext(newNode);
        m_size++;
        return;
      }
      else
      { //Case to iterate
        prev = curr;
        curr = curr->GetNext();
      }
    }
  }
}

// remove at
// Name: RemoveAt
// Desc: Removes a node at a particular position based on data passed (matches first)
// Preconditions: LL with at least one node. 
// Postconditions: Removes node with passed value (in first)
template <class T>
void LL<T>::RemoveAt(const T& word)
{
 // find node that has word and remove it from LL
  Node<T>* prev = m_head; // create pointer to prev node
  Node<T>* curr = m_head; // create pointer to curr node

  // if word to remove is head of list, set new head
  // to what was the second word in list
  if (curr->GetData().first == word){
      m_head = curr->GetNext();
      --m_size;
      delete curr; 
      return;
  }
  // otherwise
  else{
      while (curr != nullptr){
        // connect prev word w/ next word
        if (curr->GetData().first == word){
          prev->SetNext(curr->GetNext());
          --m_size;  
          delete curr;
          return;  
        } 
        prev = curr;
        curr = curr->GetNext();
      } 
  }
  return;
}

// display
// Name: Display
// Desc: Display all nodes in linked list
// Preconditions: Outputs the LL
// Postconditions: Displays the pair in each node of LL 
template <class T>
void LL<T>::Display(){
  if(m_size==0) //Checks to see if the linked list is empty
  { 
    cout << "The linked list is empty" << endl; //Output if it is empty
  }
  else
  {
    Node<T>* curr = m_head; //Creates a new pointer to iterate over list

    while(curr != nullptr)
    {
      cout << curr->GetData().first << ":" << 
      curr->GetData().second << endl;
      curr = curr->GetNext(); //Moves to m_next node
    }
    cout << "END" << endl << endl; //Indicates the end of the linked list
  }
}

// getSize
template <class T>
int LL<T>::GetSize(){

  return m_size;
}

// overload <<
// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node
// Preconditions: Requires a LL
// Postconditions: Returns an ostream with the data from each node on different line
template <class U>
ostream& operator<<(ostream& output, const LL<U>& L){
  
  Node<U>* curr = L.m_head;

  while (curr != nullptr){
    output << curr->GetData().first << ":" << curr->GetData().second << endl;
    curr = curr->GetNext();
  }

  return output;
}

// overload []
// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location
// Precondition: Existing LL
// Postcondition: Returns pair from LL using []
// returns pair
template <class T>
pair<T,int>& LL<T>::operator[] (int i)
{
  Node<T>* curr = m_head;
  int count = 0;
  // return if index can't be found
  pair<T,int> OutOfBounds = make_pair("Out of bounds", 0);

  while(curr != nullptr){

    if (count == i)
    {
      return curr->GetData();
    }
    ++count;
    curr = curr->GetNext();
  }

  return OutOfBounds;
}

// helper function to check if char is a letter
template <class T>
bool LL<T>::IsLetter(char letter){
  if ((letter >= 'A' && letter <= 'Z') ||
      (letter >= 'a' && letter <= 'z')){
    return true;
  }

  return false;
}

// helper function to change word to lowercase
template <class T>
string LL<T>::ToLowerString(string word){
  string lowerCaseWord;

  for (long unsigned i = 0; i < word.size(); i++){
    lowerCaseWord += tolower(word[i]);
  }
  
  return lowerCaseWord;
}

// helper function to identify numbers
template <class T>
bool LL<T>::IsNumber(char number){
  if (!IsLetter(number) && !ispunct(number))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//****************************************************************
// To test just LL follow these instructions:
//   1.  Uncomment out int main below
//   2.  make LL
//   3.  ./LL (try valgrind too!)

// int main () {
//   //Test 1 - Default Constructor and Push
//   cout << "Test 1 - Default Constructor and Push Running" << endl;
//   //Test Default Constructor
//   LL <string>* newLL1 = new LL<string>();
//   //Push 4 nodes into LL
//   newLL1->Insert("candy");
//   newLL1->Insert("cookies");
//   newLL1->Insert("candy");
//   newLL1->Insert("bananas");
//   newLL1->Insert("dogs");
//   newLL1->Insert("apples");
//   newLL1->Insert("elephants");
//   newLL1->Insert("barf");
//   newLL1->Insert("candy");
//   newLL1->Insert("cookies");
//   newLL1->Insert("candy");
//   newLL1->Insert("bananas");
//   newLL1->Insert("dogs");
//   newLL1->Insert("apples");
//   newLL1->Insert("elephants");
//   newLL1->Insert("barf");
//   newLL1->Display();

// //   // delete newLL1;

// //   // // Test 2 - Copy Constructor and Assignment Operator
//   cout << "Test 2 - Copy Constructor and Assignment Operator Running" << endl;
//   // Test Copy constructor
//   LL <string>* newLL2 = new LL<string>(*newLL1);
//   cout << "*******Original*********" << endl;
//   newLL1->Display();
//   cout << "*******Copy*********" << endl;
//   newLL2->Display();
    
// //   // //Test Overloaded Assignment Operator
//   LL <string>* newLL3 = new LL<string>();
//   newLL3 = newLL1;
//   cout << "*******Assignment*********" << endl;
//   newLL3->Display();
//   cout << endl;

// //   // //Test 3 - Test Display and Overloaded <<
//   cout << "Test 3 - Display and Overloaded << Running" << endl;
//   cout << "newLL1 Display Function" << endl;
//   newLL1->Display();
//   cout << "newLL1 Overloaded" << endl;
//   cout << *newLL1;
//   cout << "RemoveAt(candy)" << endl;
//   newLL1->RemoveAt("candy");
//   cout << "newLL1 Display Function" << endl;
//   newLL1->Display();  

//   return 0;
// }



