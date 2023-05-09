#include <iomanip>
#include <iostream>
#include<sstream>
#include <regex>
using namespace std;

struct Student
{
    string _name;
    int height;
    string _id;
    Student* leftChild = nullptr;
    Student* rightChild = nullptr;

    Student(string name, string id);
};

Student::Student(string name, string id)
{
    this->_name = name;
    this->_id = id;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}

class AVL
{
public:
    Student* root = nullptr;
    int counter = 0; // a counter used in a few recursive functions
    AVL();
    ~AVL();
    void deleteTree(Student* node);

    Student* insert(string name, string ID, Student* root);
    Student* remove(Student* root, string ID);
    bool searchID(Student* root, string ID);
    bool searchName(Student* root, string name);
    void printInorder(Student* root);
    void printPreorder(Student* root);
    void printPostorder(Student* root);
    int printLevelCount(Student* root);
    bool removeInorder(Student* root, int N);
    void functionSelector(int selection, string name, string ID, int number);

private:
    Student* findRightmostNode(Student* root);
    Student* getInorderSuccessor(Student* node);
    Student* balanceTree(Student* root);
    int getBalanceFactor(Student* root);

    Student* rightRotation(Student* root);
    Student* leftRotation(Student* root);
    Student* leftRightRotation(Student* root);
    Student* rightLeftRotation(Student* root);
};

AVL::AVL()
{
    this->root = nullptr;
}

AVL::~AVL()
{
    deleteTree(this->root);
}

void AVL::deleteTree(Student* node)
{
    if (node != nullptr)
    {
        if (node->leftChild != nullptr)
            deleteTree(node->leftChild);
        if (node->rightChild != nullptr)
            deleteTree(node->rightChild);
        delete node;
    }
}

Student* AVL::insert(string name, string ID, Student* root)
{
    if (root == nullptr) // base case for empty tree
    {
        root = new Student(name, ID);
        cout << "successful" << endl;
        root->height = 1;
        return root;
    }
    if (root->_id == ID) { //unsuccessful because id already exists
        cout << "unsuccessful" << endl;
        return root;
    }
    else
    {
        if (ID < root->_id) // left child
        {
            root->leftChild = insert(name, ID, root->leftChild);
        }
        else if (ID > root->_id) // right child
        {
            root->rightChild = insert(name, ID, root->rightChild);
        }
    }
    root->height = printLevelCount(root);
    root = balanceTree(root); //balance after a successful insert, will balance from bottom up
    root->height = printLevelCount(root);
    return root;
}

Student* AVL::remove(Student* root, string ID)
{
    if (root == nullptr) // if id does not exist
    {
        cout << "unsuccessful" << endl;
        return root;
    }

    if (root->_id == ID)
    {
        if (root->leftChild == nullptr && root->rightChild == nullptr) //root is a leaf or a single noded tree
        {
            delete root;
            cout << "successful" << endl;
            return nullptr;
        }
        else if (root->leftChild != nullptr && root->rightChild == nullptr) // only left child exists
        {
            Student* temp = root;
            root = temp->leftChild;
            delete temp;
            cout << "successful" << endl;
            root = balanceTree(root);
        }
        else if ((root->leftChild == nullptr && root->rightChild != nullptr)) // only right child exists
        {
            Student* temp = root;
            root = temp->rightChild;
            delete temp;
            cout << "successful" << endl;
            root = balanceTree(root);
        }
        else // both children exist
        {
            Student* oldRoot = root;
            Student* newRoot = root->rightChild;
            Student* newRootParent = root->rightChild;
            while (newRoot->leftChild != nullptr) //find inorder successor
            {
                if (newRoot->leftChild->leftChild != nullptr)
                    newRootParent = newRoot->leftChild;
                newRoot = newRoot->leftChild;
            }
            if (newRootParent != root && newRootParent!=newRoot)
                newRootParent->leftChild = newRoot->rightChild; // accounting for if newRoot had a rightChild

            //transferring newroot into place of oldRoot
            newRoot->leftChild = oldRoot->leftChild;
            if (oldRoot == this->root) //only if root is the nodes root
                if (oldRoot->rightChild != newRoot)
                    newRoot->rightChild = oldRoot->rightChild;
            root = newRoot;
            root->height = oldRoot->height;
            delete oldRoot;
            cout << "successful" << endl;
            root = balanceTree(root);
        }

    }
    else if (ID > root->_id)
        root->rightChild = remove(root->rightChild, ID);
    else if (ID < root->_id)
        root->leftChild = remove(root->leftChild, ID);
    root->height = printLevelCount(root);
    root = balanceTree(root); //balance after a successful insert, will balance from bottom up
    root->height = printLevelCount(root);
    return root;
}

bool AVL::searchID(Student* root, string ID)
{
    bool IDFound = false;
    if (root == nullptr)
        return false;
    if (root != nullptr)
    {
        if (root->_id == ID)
        {
            cout << root->_name << endl;
            IDFound = true;
            return IDFound;
        }

        if (ID > root->_id && root->rightChild != nullptr)
            IDFound += searchID(root->rightChild, ID);
        else if (ID < root->_id && root->leftChild != nullptr)
            IDFound += searchID(root->leftChild, ID);
    }
    return IDFound;
}

bool AVL::searchName(Student* root, string name)
{
    bool NameFound = false;

    if (root != NULL) {
        if (root->_name == name)
        {
            cout << root->_id << endl;
            NameFound = true;
        }
        NameFound += searchName(root->leftChild, name);
        NameFound += searchName(root->rightChild, name);

        return NameFound;
    }
    return NameFound;
}

void AVL::printInorder(Student* root)
{
    if (root != nullptr)
    {
        if (root->leftChild != nullptr)
            printInorder(root->leftChild);
        cout << root->_name;
        if (root != findRightmostNode(this->root))
            cout << ", ";
        if (root->rightChild != nullptr)
            printInorder(root->rightChild);
    }
}

void AVL::printPreorder(Student* root)
{
    if (root != NULL) {
        cout << root->_name;
        if (root->leftChild != nullptr || root->rightChild != nullptr)
            cout << ", ";
        printPreorder(root->leftChild);
        if (root->leftChild != nullptr && root->rightChild != nullptr)
            cout << ", ";
        printPreorder(root->rightChild);
    }
}

void AVL::printPostorder(Student* root)
{
    if (root != nullptr)
    {
        if (root->leftChild != nullptr)
            printPostorder(root->leftChild);
        if (root->rightChild != nullptr)
            printPostorder(root->rightChild);
        cout << root->_name;
        if (root != this->root)
            cout << ", ";
    }
}

int AVL::printLevelCount(Student* root)
{
    int levelCount = 0;
    if (root != nullptr)
    {
        int rightCount = 0;
        if (root->rightChild!=nullptr)
            rightCount = root->rightChild->height;
        int leftCount = 0;
        if (root->leftChild!=nullptr)
            leftCount = root->leftChild->height;
        int total = max(leftCount, rightCount);
        levelCount = total;
    }
    return levelCount+1;
}

bool AVL::removeInorder(Student* root, int N)
{
    bool result = false;
    if (root != nullptr && counter <= N)
    {
        if (root->leftChild != nullptr)
            result += removeInorder(root->leftChild, N);

        if (this->counter == N)
        {
            this->root = remove(this->root, root->_id);
            result = true;
        }
        this->counter++;
        if (root != nullptr && root->rightChild != nullptr && counter <= N)
            result += removeInorder(root->rightChild, N);
    }
    return result;
}

void AVL::functionSelector(int selection, string name, string ID, int number)
{
    //this function exists to remove functions that require the root as an arguement from main
    if (selection == 1)
        this->root = insert(name, ID, this->root);

    else if (selection == 2)
        this->root = remove(this->root, ID);

    else if (selection == 3)
    {
        if (!(searchID(this->root, ID)))
            cout << "unsuccessful" << endl;
    }
    else if (selection == 4)
    {
        if ((searchName(this->root, name)) == false)
            cout << "unsuccessful" << endl;
    }
    else if (selection == 5)
    {
        printInorder(this->root);
        cout << endl;
    }
    else if (selection == 6)
    {
        printPreorder(this->root);
        cout << endl;
    }
    else if (selection == 7)
    {
        printPostorder(this->root);
        cout << endl;
    }
    else if (selection == 8)
        if (this->root == nullptr)
            cout << 0 << endl;
        else
            cout << printLevelCount(this->root) << endl;
    else if (selection == 9)
    {
        if (!(removeInorder(this->root, number)))
            cout << "unsuccessful" << endl;
        this->counter = 0; //resets counter variable that is used for the removeInorder function
    }
}

Student* AVL::findRightmostNode(Student* root)
{
    if (root != nullptr)
    {
        while (root->rightChild != nullptr)
            root = root->rightChild;
        return root;
    }
}

Student* AVL::getInorderSuccessor(Student* node)
{
    Student* temp = node->rightChild;
    while (temp->leftChild != nullptr)
        temp = temp->leftChild;
    return temp;
}

Student* AVL::balanceTree(Student* root)
{
    int balance = getBalanceFactor(root);
    if (balance > 1) //left heavy
    {
        int subTreeBalance = getBalanceFactor(root->leftChild);
        if (subTreeBalance > 0)// left left (right rotation)
        {
            root = rightRotation(root);
        }
        else //left right
        {
            root = leftRightRotation(root);
        }
    }
    if (balance < -1) //right heavy  
    {
        int subTreeBalance = getBalanceFactor(root->rightChild);
        if (subTreeBalance > 0)// right left
        {
            root = rightLeftRotation(root);
        }
        else //right right (left rotation)
        {
            root = leftRotation(root);
        }
    }
    return root;
}

int AVL::getBalanceFactor(Student* root)
{
    int returnValue = 0;
    if (root != nullptr)
    {
        int rightBalance;
        if (root->rightChild != nullptr)
            rightBalance = root->rightChild->height;
        else
            rightBalance = 0;
        int leftBalance;
        if (root->leftChild != nullptr)
            leftBalance = root->leftChild->height;
        else
            leftBalance = 0;
        returnValue = leftBalance - rightBalance;
    }

    return returnValue;

}

//Rotations
Student* AVL::rightRotation(Student* root)
{
    Student* temp;
    temp = root->leftChild;
    root->leftChild = temp->rightChild;
    temp->rightChild = root;

    temp->rightChild->height = printLevelCount(temp->rightChild);
    temp->height = printLevelCount(temp);
    return temp;
}

Student* AVL::leftRotation(Student* root)
{
    Student* temp = root->rightChild;
    root->rightChild = temp->leftChild;
    temp->leftChild = root;

    temp->leftChild->height = printLevelCount(temp->leftChild);
    temp->height = printLevelCount(temp);
    return temp;
}

Student* AVL::leftRightRotation(Student* root)
{
    Student* temp = root->leftChild;;
    root->leftChild = leftRotation(temp);
    Student* temp2 = rightRotation(root);

    return temp2;
}

Student* AVL::rightLeftRotation(Student* root)
{
    Student* temp = root->rightChild;
    root->rightChild = rightRotation(temp);
    Student* temp2 = leftRotation(root);

    return temp2;

}

//operator overloads
bool operator==(string left, string right)
{
    bool returnValue = true;
    for (int i = 0; i < left.size(); i++)
    {
        if (left[i] != right[i])
            return false;
    }
    if (left.size() != right.size())
        return false;


    return returnValue;
}

bool operator>(string left, string right)
{
    if (stoi(left) > stoi(right))
        return true;
    else
        return false;
}

bool operator<(string left, string right)
{
    if (stoi(left) < stoi(right))
        return true;
    else
        return false;
}

bool operator>=(string left, string right)
{
    if (stoi(left) >= stoi(right))
        return true;
    else
        return false;
}

bool operator<=(string left, string right)
{
    if (stoi(left) <= stoi(right))
        return true;
    else
        return false;
}

bool operator!=(string left, string right)
{
    if (stoi(left) != stoi(right))
        return true;
    else
        return false;
}

int main()
{
    AVL tree;

    int numberOfCommands;
    string numberLine;
    std::getline(cin, numberLine);
    numberOfCommands = stoi(numberLine);
    for (int i = 0; i < numberOfCommands; i++)
    {
        string choice;
        std::getline(cin, choice);
        istringstream ss(choice);
        string word1;
        std::getline(ss, word1, ' ');

        //Regex
        regex nameRegex = regex("^[a-zA-Z\\s]*$");
        regex IDRegex = regex("^[0-9]{8}$");

        if (word1 == "insert")
        {
            while (true)
            {
                string blank;
                string nameToAdd;
                string idToAdd;
                bool validEntry = true;

                std::getline(std::getline(ss, blank, '"'), nameToAdd, '"');
                if (!(regex_search(nameToAdd, nameRegex)))
                    validEntry = false;

                std::getline(ss, blank, ' '); //removes unneeded space
                std::getline(ss, idToAdd, ' ');

                if (!(regex_search(idToAdd, IDRegex)))
                    validEntry = false;

                if (!validEntry)
                {
                    cout << "unsuccessful" << endl;
                    break;
                }
                else
                {
                    tree.functionSelector(1, nameToAdd, idToAdd, 0);
                    break;
                }
            }
        }
        else if (word1 == "remove")
        {
            string idToRemove;
            std::getline(ss, idToRemove, ' ');
            tree.functionSelector(2, "", idToRemove, 0);
        }
        else if (word1 == "search")
        {
            string itemToAdd;
            std::getline(ss, itemToAdd);
            if (isdigit(itemToAdd[0]))
            {
                if (!(regex_search(itemToAdd, IDRegex)))
                    cout << "unsuccessful" << endl;
                else
                {
                    tree.functionSelector(3, "", itemToAdd, 0);
                }
            }
            else
            {
                string blank;
                string name;
                itemToAdd.erase(remove(itemToAdd.begin(), itemToAdd.end(), '\"'), itemToAdd.end()); //iterates through and removes quotes

                if (!(regex_search(itemToAdd, nameRegex)))
                    cout << "unsuccessful" << endl;
                else
                {
                    tree.functionSelector(4, itemToAdd, "", 0);
                }
            }
        }
        else if (word1 == "printInorder") {
            tree.functionSelector(5, "", "", 0);
        }
        else if (word1 == "printPreorder") {
            tree.functionSelector(6, "", "", 0);
        }
        else if (word1 == "printPostorder") {
            tree.functionSelector(7, "", "", 0);
        }
        else if (word1 == "printLevelCount") {
            tree.functionSelector(8, "", "", 0);
        }
        else if (word1 == "removeInorder")
        {
            string N;
            std::getline(ss, N);
            int N2 = stoi(N);
            tree.functionSelector(9, "", "", N2);
        }
        else
            cout << "invalid entry" << endl;

    }
    return 0;
}
