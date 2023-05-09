#include <iomanip>
#include <iostream>
#include<sstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cmath>
#include <algorithm>    
using namespace std;

class AdjacencyList {
public:
    double numberofVertices;
    int count = 0;
    double sum;
    vector <double> rankVector;
    
    unordered_map<string, vector<pair<string, double>>> myMap; //the main graph
    unordered_map<string, int> myMapOutOrder; // stores the numerical outorder
    unordered_map<string, int> myMapNumbers; // assigns a numerical value to each string
    map<string, double> resultMap; //stores the website name and rank pair for the final output
    void insert(string to, string from);
    void insertOutOrder(string from);
    void insertNumbers(string from);
    void PageRank(int n);
    void setRank();
};

void AdjacencyList::insert(string to, string from)
{
    unordered_map<string, vector<pair<string, double>>>::iterator mapIterator = this->myMap.find(to);
    this->myMap[to].push_back(make_pair(from, 1));
}

void AdjacencyList::insertOutOrder(string from)
{
    unordered_map<string, int>::iterator mapIterator = this->myMapOutOrder.find(from);
    if (mapIterator != myMapOutOrder.end()){
        myMapOutOrder[from] += 1;
    }
    else{
        this->myMapOutOrder.insert({ from, 1 });
    }
}

void AdjacencyList::insertNumbers(string from)
{
    unordered_map<string, int>::iterator mapIterator = this->myMapNumbers.find(from);
    if (mapIterator == myMapNumbers.end())
    {
        myMapNumbers.insert({ from, this->count });
        this->count += 1;
    }
}

void AdjacencyList::PageRank(int p)
{
    for (int i = 0; i < this->numberofVertices; i++) // sets vector to 1/# of vertices
    {
        this->rankVector.push_back(double(1 / (this->numberofVertices)));
    }
    map<string, double>::iterator mapIterator3; //sets the result map to 1/# of vertices
    for (mapIterator3 = resultMap.begin(); mapIterator3 != resultMap.end(); mapIterator3++)
    {
        mapIterator3->second = (1 / (this->numberofVertices)); //used for when power iteration is only 1
    }
    
    for (int i = 0; i < p-1; i++)
    {
        vector<double> originalVector = this->rankVector; // sets initial ranks to 0 so that nodes with no incoming values are at 0
        for (int i = 0; i < this->numberofVertices; i++)
        {
            this->rankVector[i]=0;
        }

        map<string, double>::iterator mapIterator10; // sets result ranks to 0 so that nodes with no incoming values are at 0
        for (mapIterator10 = this->resultMap.begin(); mapIterator10 != resultMap.end(); mapIterator10++) // for each key
        {
            this->resultMap[mapIterator10->first] = 0;
        }

        unordered_map<string, vector<pair<string, double>>>::iterator mapIterator;
        for (mapIterator = this->myMap.begin(); mapIterator != myMap.end(); mapIterator++) // for each key
        {
            for (int i = 0; i < mapIterator->second.size(); i++) // for the vector
            {
                int rankIndex = myMapNumbers[mapIterator->first]; 
                sum+= (mapIterator->second[i].second) * (originalVector[this->myMapNumbers[mapIterator->second[i].first]]);
                this->rankVector[rankIndex] = sum;

            }
            this->resultMap[mapIterator->first] = sum;
            this->sum = 0;
        }
    }
}

void AdjacencyList::setRank() // sets every nodes out factor
{
    unordered_map<string, vector<pair<string, double>>>::iterator mapIterator;
    for (mapIterator = this->myMap.begin(); mapIterator != myMap.end(); mapIterator++) // for each key
    {
        for (int i = 0; i < mapIterator->second.size(); i++) // for the vector
        {
            string website = mapIterator->second[i].first; //get website string
            unordered_map<string, int>::iterator mapIterator2 = this->myMapOutOrder.find(website); //find its outlevel from the other map
            double outLevelCount = mapIterator2->second;
            mapIterator->second[i].second = (1 / (outLevelCount)); //input the value into our map
        }
    }
}

int main()
{
    string choice;
    std::getline(cin, choice);
    istringstream ss(choice);
    string commands;
    std::getline(ss, commands, ' ');
    string powerlevel;
    std::getline(ss, powerlevel, ' ');

    AdjacencyList myGraph;

    int numberOfCommands = stoi(commands);
    int powerLevel = stoi(powerlevel);
    for (int i = 0; i < numberOfCommands; i++)
    {
        string choice;
        std::getline(cin, choice);
        istringstream ss(choice);
        string word1;
        std::getline(ss, word1, ' ');
        string word2;
        std::getline(ss, word2, ' ');
       
        
        myGraph.insert(word2, word1);
        myGraph.insertOutOrder(word1);
        myGraph.insertNumbers(word1);
        myGraph.insertNumbers(word2);
        myGraph.resultMap.insert({ word1,0 });
        myGraph.resultMap.insert({ word2,0 });

    }
    myGraph.numberofVertices = myGraph.myMapNumbers.size();
    myGraph.setRank();
    myGraph.PageRank(powerLevel);
    map<string, double>::iterator mapIterator6;
    for (mapIterator6 = myGraph.resultMap.begin(); mapIterator6 != myGraph.resultMap.end(); mapIterator6++)
    {
        cout << fixed << setprecision(2) << mapIterator6->first << " " << round(mapIterator6->second*100+.05)/100 << endl; //floor(mapIterator6->second*100+.5)/100
    }
        
    return 0;
}


