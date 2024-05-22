/**********************************************
 * File: Proj5.cpp
 * Project: CMSC 202 Project 5, Spring 2024
 * Author: Eden Zhang
 * Date: 4/20/2024
 * Section: 30/34
 * E-Mail: ezhang1@umbc.edu
 * 
 * Queue.cpp
 * Linked List class template file 
 * that manages the MoviePlayer queue
 * 
*****************************************************/
#ifndef QUEUE_CPP
#define QUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated linked list
//Note: Because the linked list is a templated class,
//      there is only ONE file (Queue.cpp)

//Templated node class
template <class T>
class Node {
public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Queue {
 public:
  // Name: Queue() Queue from a linked list - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new queue where m_head and m_tail
  //                 point to nullptr and m_size = 0
  Queue();
  // Name: ~Queue() - Destructor
  // Desc: Used to destruct a Queue
  // Preconditions: There is a Queue
  // Postconditions: Queue is deallocated (including dynamically allocated nodes)
  //                 Can just call Clear()
 ~Queue();
  // Name: Queue (Copy Constructor)
  // Preconditions: Creates a copy of existing Queue in separate memory
  //                address (deep copy)
  //                Requires one already existing Queue
  // Postconditions: Copy of existing Queue
  Queue(const Queue&);
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: When two Queue objects exist, sets one to equal another
  //                Requires two Queue objects
  // Postconditions: When completed, you have two Queues in
  //                 separate memory addresses with the same
  //                 number of nodes with the same values in each node
  Queue<T>& operator= (Queue&);
  // Name: PushBack
  // Preconditions: Takes in data. Creates new node. 
  //                Requires a Queue
  // Postconditions: Adds a new node to the end of the Queue.
  void PushBack(const T&);
  // Name: PopFront
  // Preconditions: Queue with at least one node. 
  // Postconditions: Removes first node in the queue and
  //                 returns the data in the first node
  T PopFront();
  // Name: Display
  // Preconditions: Outputs the queue.
  // Postconditions: Displays the data in each node of queue
  // Required (used only for queue testing)
  void Display();
  // Name: Front
  // Preconditions: Requires a Queue with at least one node
  // Postconditions: Returns whatever data is pointed at by m_head -
  //                 Does NOT remove node
  T Front();
  // Name: IsEmpty
  // Preconditions: Requires a queue
  // Postconditions: Returns if the queue is empty.
  bool IsEmpty();
  // Name: GetSize
  // Preconditions: Requires a queue
  // Postconditions: Returns m_size
  int GetSize();
  // Name: Find()
  // Preconditions: Requires a queue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  int Find(T);
  // Name: Clear
  // Preconditions: Requires a queue
  // Postconditions: Deallocates and removes all nodes in a queue. No memory leaks
  void Clear();
  // Name: At
  // Precondition: Existing Queue
  // Postcondition: Returns object from Queue at a specific location
  // Desc: Iterates to node x and returns data from Queue
  T& At (int x);
  // Name: Swap(int)
  // Preconditions: Requires a queue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Example: Swap(1) would swap the node 0 with node 1 so
  //          that node 1 would now be m_head
  // Desc: Swaps two nodes by updating the pointers (not just the value)
  // Hint: Think about the special cases! Implement before Sort
  void Swap(int);
  // Name: Sort()
  // Preconditions: Requires a queue with a minimum of 2 nodes
  //                (otherwise notifies user)
  // Postconditions: Sorts the Queue (may use overloaded < or >).
  // Desc: This is used to sort anything in the Queue assuming the
  //       < or > is overloaded
  //        Uses bubble sort and Swap function above.
  //        Ensure working with queue_test before rest of project.
  // Note: Allowed to use the break command in just this function if necessary
  void Sort();
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Queue Class Here***********
//**********All Functions Are Required Even If Not Used for Project**************
//**********No references to anything from Movie here*****************

// Queue
// Default constructor
template <class T>
Queue<T>::Queue()
{
   m_head = nullptr;
   m_tail = nullptr;
   m_size = 0;
}

// ~Queue
// Destructor
template <class T>
Queue<T>::~Queue()
{
   Clear();
}

// Queue
// Copy Constructor
template <class T>
Queue<T>::Queue(const Queue& queue)
{
   // Checks if the queue is an empty list
   if (queue.m_size == 0)
   {
      m_head = nullptr;
      m_tail = nullptr;
      m_size = 0;
      return;
   } else 
   {
      // Setting initial variables
      m_head = nullptr;
      m_tail = nullptr;
      m_size = 0;

      // Goes through queue and copies each Node to the new one
      Node<T>* temp = queue.m_head;

      while (temp != nullptr)
      {
         // Copies the node of the queue into a new node of the copy queue
         PushBack(temp->GetData());
         temp = temp->GetNext();
      }
   }
}

// operator=
// Overloaded assignment operator
template <class T>
Queue<T>& Queue<T>::operator=(Queue& queue)
{
   // Clears out current queue to make room for copy
   Clear();

   // Checks if the queue is an empty list
   if (queue.m_size == 0)
   {
      m_head = nullptr;
      m_tail = nullptr;
      m_size = 0;
      return *this;
   } else 
   {
      // Setting initial variables
      m_head = nullptr;
      m_tail = nullptr;
      m_size = 0;

      // Goes through queue and copies each Node to the new one
      Node<T>* temp = queue.m_head;

      while (temp != nullptr)
      {
         // Copies the node of the queue into a new node of the copy queue
         PushBack(temp->GetData());
         temp = temp->GetNext();
      }
   }
   return *this;
}

// PushBack
// Adds a Node to the end of the Queue linked list
template <class T>
void Queue<T>::PushBack(const T& item)
{
   // Creates the new node
   Node<T>* newNode = new Node(item);

   // Checks if the new node is the first
   if (IsEmpty() == true)
   {
      m_head = newNode;
      m_tail = newNode;
      m_size++;
   } else // If not first
   {
      newNode->SetNext(nullptr);
      m_tail->SetNext(newNode);
      m_tail = newNode;
      m_size++;
   }
}

// PopFront
// Removes the front node and returns its data
template <class T>
T Queue<T>::PopFront()
{
   Node<T>* curr = m_head;

   // Removes first node
   m_head = m_head->GetNext();
   T data = curr->GetData();

   delete curr;
   curr = nullptr;

   m_size--;
   return data;
}

// Display
// Displays the linked list for testing
template <class T>
void Queue<T>::Display()
{
   if (IsEmpty() == true)
   {
      cout << "The Linked List is empty." << endl;
   } else 
   {
      Node<T>* temp = m_head;

      // Iterates through the linked list and displays each node
      for (int i = 0; i < m_size; i++)
      {
         cout << temp->GetData() << "->";
         temp = temp->GetNext();
      }

      cout << "END" << endl;
   }
}

// Front
// Returns data of the front node
template <class T>
T Queue<T>::Front()
{
   return m_head->GetData();
}

// IsEmpty
// Boolean flag to check if list is empty
template <class T>
bool Queue<T>::IsEmpty()
{
   if (m_size == 0)
   {
      return true;
   } else
   {
      return false;
   }
}

// GetSize
// Getter for m_size
template <class T>
int Queue<T>::GetSize()
{
   return m_size;
}

// Find
// Finds node with matching data, returns "index" of node
template <class T>
int Queue<T>::Find(T data)
{
   int index = 0;
   Node<T>* curr = m_head;

   // Goes through the list and checks the data in each node
   while (curr != nullptr)
   {
      // If a match is found then returns the index
      if (curr->GetData() == data)
      {
         return index;
      } else 
      {
         curr = curr->GetNext();
         index++;
      }
   }

   // If no match is found then returns -1
   return -1;
}

// Clear
// Deallocates each node in linked list
template <class T>
void Queue<T>::Clear()
{
   Node<T>* curr = m_head;

   // Iterates through the linked list and deallocates the Nodes
   while (curr != nullptr)
   {
      m_head = curr;
      curr = curr->GetNext();
      delete m_head;
   }

   // Resets variables/pointers
   m_head = nullptr;
   m_tail = nullptr;
   m_size = 0;
}

// At
// Finds node of the passed index, returns data
template <class T>
T& Queue<T>::At(int x)
{
   int index = 0;
   Node<T>* curr = m_head;

   // Iterates through the linked list until it finds the node at the index
   while (curr != nullptr)
   {
      if (index == x)
      {
         return curr->GetData();
      } else 
      {
         curr = curr->GetNext();
         index++;
      }
   }

   return curr->GetData();
}

// Swap
// Swaps node with previous node
template <class T>
void Queue<T>::Swap(int x)
{
   Node<T>* before = m_head; // Pointer to prev
   Node<T>* prev = m_head; // Pointer to curr
   Node<T>* curr = m_head;
   int index = 0;

   // Iterates through the linked list
   while (curr != nullptr)
   {
      // Error checking against swapping the first node
      if (index == x && index == 0)
      {
         cout << "Cannot swap the front Node by itself." << endl;
      } else if (index == x)
      {
         // Special case for first two of the list
         if (x == 1)
         {
            m_head->SetNext(curr->GetNext());
            curr->SetNext(m_head);
            m_head = curr;
         } else
         {
            // Curr and prev swap, before points to curr over prev, 
            // prev takes curr spot, and curr takes prev's spot
            before->SetNext(curr);
            prev->SetNext(curr->GetNext());
            curr->SetNext(prev);
            
            // If swapping the last node, then updates m_tail
            if (x == m_size - 1)
            {
               m_tail = prev;
            }
         }
      }

      // Iteration
      before = prev;
      prev = curr;
      curr = curr->GetNext();
      index++;
   }
}

// Sort
// Bubble Sorts the Queue
template <class T>
void Queue<T>::Sort()
{
   Node<T>* curr;
   bool swapped;

   // Loops through the list over and over 
   // again until it no longer needs to swap
   for (int i = 0; i <= m_size; i++)
   {
      curr = m_head;
      swapped = false;

      // If the nodes are unordered, then swaps them
      for (int j = 0; j < m_size - i - 1; j++)
      {
         Node<T>* p1 = curr;
         Node<T>* p2 = p1->GetNext();

         // Checks if a set of two nodes are unordered
         if (p1->GetData() > p2->GetData())
         {
            Swap(j + 1);
            curr = p2;
            swapped = true;
         }
         
         curr = curr->GetNext();
      }

      // Breaks loop if it goes through the list without needing the swap
      if (swapped == false)
         break;
   }
}

#endif
