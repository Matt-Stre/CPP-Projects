#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class LinkedList
{
public:
	class Node
	{
	public:
		T data;
		Node* next;// next pointer
		Node* prev; //prev pointer

		Node()
		{
			next = NULL;
			prev = NULL;
			data = 0;
		}

		Node(T _data)
		{
			data = _data;
			next = NULL;
			prev = NULL;
		}
	};
public:
	Node* head; //head ptr
	Node* tail; //tail ptr
	unsigned int Node_Count = 0; //ptr count

	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	//Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	Node* GetNode(unsigned int index);
	const Node* GetNode(unsigned int index) const;
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	//Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	//Removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();

	//Operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);


	//Big Three and constructors
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	//LinkedList& operator=(const LinkedList<T>& list);
	~LinkedList();
};

//*======FUNCTION DEFINITIONS============*

//Behaviors
template<typename T>
void LinkedList<T>::PrintForward() const
{
	Node* nodetoprint = head;
	for (unsigned int i = 0; i < Node_Count; i++)
	{
		cout << nodetoprint->data << endl;
		nodetoprint = nodetoprint->next;
	}
}

template<typename T>
void LinkedList<T>::PrintReverse() const
{
	Node* nodetoprint = tail;
	for (unsigned int i = 0; i < Node_Count; i++)
	{
		cout << nodetoprint->data << endl;
		nodetoprint = nodetoprint->prev;
	}
}
template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	const Node* new_node = node;
	cout << new_node->data << endl;
	if (new_node->next != nullptr)
	{
		PrintForwardRecursive(new_node->next);
	}
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	const Node* new_node = node;
	cout << new_node->data << endl;
	if (new_node->prev != nullptr)
	{
		PrintReverseRecursive(new_node->prev);
	}
}

//Accessors
template<typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return Node_Count;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	//Node* comparenode = new Node();
	Node* comparenode = head;
	for (unsigned int i = 0; i < Node_Count; i++)
	{
		if (comparenode->data == value)
		{
			outData.push_back(comparenode);
		}
		comparenode = comparenode->next;
	}
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
	//Node* comparenode = new Node();
	Node* comparenode = head;
	int index = 0;
	for (int i = 0; i < Node_Count; i++)
	{
		if (comparenode->data == data)
		{
			return comparenode;
		}
		comparenode = comparenode->next;
		index += 1;
	}
	return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
	//Node* comparenode = new Node();
	Node* comparenode = head;
	int index = 0;
	for (unsigned int i = 0; i < Node_Count; i++)
	{
		if (comparenode->data == data)
		{
			return comparenode;
		}
		comparenode = comparenode->next;
		index += 1;
	}
	return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	if (index > Node_Count - 1)
	{
		throw out_of_range("Error");
	}
	Node* returnnode = head;
	for (unsigned int i = 0; i < index; i++)
	{
		returnnode = returnnode->next;
	}
	return returnnode;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
	if (index > Node_Count - 1)
	{
		throw out_of_range("Error");
	}
	//returnnode = new Node();
	Node* returnnode = head;
	for (unsigned int i = 0; i < index; i++)
	{
		returnnode = returnnode->next;
	}
	return returnnode;

}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return head;
}
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	return head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	return tail;
}


//Insertion
template<typename T>
void LinkedList<T>::AddHead(const T& data)
{
	Node* new_node = new Node(data);
	new_node->next = head;
	if (head != nullptr)
	{
		head->prev = new_node;
	}
	if (head == nullptr)
	{
		tail = new_node;
	}

	head = new_node;
	if (tail == nullptr)
	{
		tail = head;
		//tail->prev = new_node;
	}
	Node_Count += 1;
}

template<typename T>
void LinkedList<T>::AddTail(const T& data)
{
	Node* new_node = new Node(data);
	new_node->prev = tail;
	if (tail != nullptr)
	{
		tail->next = new_node;
	}

	if (tail == nullptr)
	{
		head = new_node;
	}


	tail = new_node;
	if (head == nullptr)
	{
		head = tail;
		//head->next = new_node;
	}
	Node_Count += 1;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count)
{
	for (int i = count - 1; i >= 0; i--)
	{
		AddHead(data[i]);
	}
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		AddTail(data[i]);
	}
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	Node* new_node = new Node(data);
	new_node->next = node->next;
	node->next->prev = new_node;
	new_node->prev = node;
	node->next = new_node;
	Node_Count += 1;
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	Node* new_node = new Node(data);
	new_node->prev = node->prev;
	node->prev->next = new_node;
	new_node->next = node;
	node->prev = new_node;
	Node_Count += 1;
}

template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
	if (index > Node_Count)
	{
		throw out_of_range("Error");
	}
	if (index == 0)
	{
		AddHead(data);
	}
	else if (index >= Node_Count)
	{
		AddTail(data);
	}
	else
	{
		Node* new_node = head;
		for (unsigned int i = 0; i < index - 1; i++)
		{
			new_node = new_node->next;
		}
		InsertAfter(new_node, data);
	}
}
//Removal
template<typename T>
bool LinkedList<T>::RemoveHead()
{
	if (head != nullptr)
	{
		Node* temp = head->next;
		if (head->next != nullptr)
		{
			head->next->prev = nullptr;
		}
		delete head;
		head = temp;
		Node_Count -= 1;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool LinkedList<T>::RemoveTail()
{
	if (tail != nullptr)
	{
		if (tail->prev != nullptr)
		{
			tail->prev->next = nullptr;
			Node* temp = tail->prev;
			delete tail;
			tail = temp;
			Node_Count -= 1;
			return true;
		}
		else
		{
			delete tail;
			tail = nullptr;
			Node_Count -= 1;
			return true;
		}
	}
	else
	{
		return false;
	}
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{
	unsigned int removedCount = 0;
	Node* temp = head;
	for (unsigned int i = 0; i < Node_Count - 1; i++)
	{
		if (temp->data == data)
		{
			temp->next->prev = nullptr;
			delete head;
			head = temp->next;
			Node_Count -= 1;
			removedCount += 1;
		}
		temp = temp->next;
	}
	return removedCount;
}



template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
	if (index > Node_Count)
	{
		//throw out_of_range("Error");
		return false;
	}
	if (index == 0)
	{
		RemoveHead();
		return true;
	}
	else if (index == Node_Count)
	{
		RemoveTail();
		return true;
	}
	else
	{
		Node* new_node = head;
		for (unsigned int i = 0; i < index ; i++)
		{
			new_node = new_node->next;
		}
		Node* temp = new_node->next;
		temp->prev = new_node->prev;
		new_node->prev->next = temp;
		delete new_node;
		Node_Count -= 1;
		return true;
	}
	return false;
}

template<typename T>
void LinkedList<T>::Clear()
{
	Node_Count = 0;
	Node* tempnext;
	while (head != nullptr)
	{
		tempnext = head->next;	//temporary pointer
		delete head;			//delete header
		head = tempnext;		//set header to next node
	}
	head = nullptr;
	tail = nullptr;
}

//Operators
template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	if (index > Node_Count - 1)
	{
		throw out_of_range("Error");
	}
	Node* comparenode = head;
	for (int i = 0; i < index; i++)
	{
		comparenode = comparenode->next;
	}
	return comparenode->data;
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	if (index > Node_Count)
	{
		throw out_of_range("Error");
	}
	Node* comparenode = head;
	for (int i = 0; i < index; i++)
	{
		comparenode = comparenode->next;
	}
	return comparenode->data;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	Node* leftnode = this->head;
	Node* rightnode = rhs.head;

	while (leftnode != nullptr)
	{
		if (leftnode->data == rightnode->data)
		{
			leftnode = leftnode->next;
			rightnode = rightnode->next;
		}
		else
		{
			return false;
		}

	}
	return true;

}


//Big three and Constructors
template<typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr; //head ptr
	tail = nullptr; //tail ptr
	Node_Count = 0; //ptr count
}
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	//loop
	Node* newhead = new Node();
	newhead->data = list.head->data;
	newhead->next = nullptr;
	newhead->prev = nullptr;

	Node* prevnode = newhead;
	Node* listnode = list.head->next;

	this->head = newhead;
	this->Node_Count = list.Node_Count;

	while (listnode != nullptr)
	{
		Node* tempnode = new Node();
		tempnode->data = listnode->data;

		//tempnode->next = tempnode->next;
		tempnode->prev = prevnode;
		tempnode->next = nullptr;
		prevnode->next = tempnode;
		prevnode = tempnode;

		if (listnode->next == nullptr)
		{
			this->tail = tempnode;
		}
		listnode = listnode->next;
	}
}


template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
	//clear loop 
	Node* tempnext;
	while (this->head != nullptr)
	{
		tempnext = this->head->next;	//temporary pointer
		delete this->head;			//delete header
		this->head = tempnext;		//set header to next node
	}
	this->head = nullptr;
	this->tail = nullptr;

	//loop
	Node* newhead = new Node();
	newhead->data = list.head->data;
	newhead->next = nullptr;
	newhead->prev = nullptr;

	Node* prevnode = newhead;
	Node* listnode = list.head->next;

	this->head = newhead;
	this->Node_Count = list.Node_Count;

	while (listnode != nullptr)
	{
		Node* tempnode = new Node();
		tempnode->data = listnode->data;

		tempnode->prev = prevnode;
		tempnode->next = nullptr;
		prevnode->next = tempnode;
		prevnode = tempnode;

		if (listnode->next == nullptr)
		{
			this->tail = tempnode;
		}
		listnode = listnode->next;
	}
	return *this;
}


template<typename T>
LinkedList<T>::~LinkedList()
{
	Node* tempnext;
	while (head != nullptr)
	{
		tempnext = head->next;	//temporary pointer
		delete head;			//delete header
		head = tempnext;		//set header to next node
	}
}
