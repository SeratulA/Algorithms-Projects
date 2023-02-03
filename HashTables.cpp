#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class listNode {
public:
    string firstName;
    string lastName;
    listNode *next;
    
    listNode () {
        next = NULL;
    }
    
    listNode (string firstName, string lastName) {
        this->firstName = firstName;
        this->lastName = lastName;
        next = NULL;
    }
    
    void printNode(listNode *node, ofstream &outFile) {
        if (node->next == NULL) {
            outFile << "(" << node->firstName << ", " << node->lastName << ") -> NULL." << endl << endl;
        }
        else {
            outFile << "(" << node->firstName << ", " << node->lastName << ", " << node->next->firstName << ") ->";
        }
    }
    
};

class hashTable {
public:
    char op;
    int bucketSize;
    listNode* hashArray;
    
    void createHashTable(int bucketSize) {
        this->bucketSize = bucketSize;
        hashArray = new listNode[bucketSize];
        
        for (int i = 0; i <= bucketSize; i++) {
            hashArray[i].firstName = "dummyfirst";
            hashArray[i].lastName = "dummylast";
        }
    }
    
    int doIt(string lastName){
        unsigned int val = 1;
        for (int i = 0; i < lastName.length(); i++) {
            val = val * 32 + (long) lastName[i];
        }
        return val % bucketSize;
    }
    
    listNode * findSpot (int index, string firstName, string lastName) {
        listNode* spot = &hashArray[index];
        while (spot->next != NULL && spot->next->lastName < lastName) {
            spot = spot->next;
        }
        while (spot->next != NULL && spot->next->lastName == lastName && spot ->next->firstName < firstName) {
            spot = spot->next;
        }
        return spot;
    }
    
    void hashInsert (int index, string firstName, string lastName, ofstream &outFile2){
        outFile2 << "***Performing hashInsert on " << firstName << " " << lastName << endl;
        listNode* spot = findSpot(index, firstName, lastName);
        
        if (spot ->next != NULL && spot->next->lastName == lastName && spot->next->firstName == firstName) {
            outFile2 << "***Warning, the record is already in the database!" << endl;
        }
        
        else {
            listNode* newNode = new listNode(firstName,lastName);
            newNode->next = spot->next;
            spot->next = newNode;
            printList(index, outFile2);
        }
    }
    
    void hashDelete (int index, string firstName, string lastName, ofstream &outFile2) {
        outFile2 << "***Performing hashDelete on firstName, lastName" << endl;
        listNode* spot = findSpot(index, firstName, lastName);
        
        if (spot->next != NULL && spot ->next ->lastName == lastName && spot->next->firstName == firstName) {
            listNode* junk = spot->next;
            spot->next = spot->next->next;
            junk->next = NULL;
            free(junk);
            printList(index, outFile2);
        }
        
        else {
            outFile2 << "***Warning, the record is NOT in the database!" << endl;
        }
    }
    
    void hashRetrieval (int index, string firstName, string lastName, ofstream &outFile2) {
        outFile2 << "***Performing hashRetrieval on firstName, lastName" << endl;
        listNode* spot = findSpot(index, firstName, lastName);
        if (spot-> next != NULL && spot->next->lastName == lastName && spot->next->firstName == firstName) {
            outFile2 << "***Yes, the record is in the database!" << endl << endl;
        }
        else {
            outFile2 << "***No, the record is not in the database!" << endl << endl;
        }
    }
    
    void informationProcessing(ifstream &inFile, ofstream &outFile2) {
        string firstName, lastName;
        int index;
        
        while (!inFile.eof()) {
            inFile >> op >> firstName >> lastName;
            outFile2 << "First Name is " << firstName << ". Last name is " << lastName << ". Operations is " << op << "." << endl;
            index = doIt(lastName);
            outFile2 << "Index: " << index << "." << endl;
            printList(index, outFile2);
            
            if (op == '+') {
                hashInsert(index, firstName, lastName, outFile2);
            }
            else if (op == '-') {
                hashDelete(index, firstName, lastName, outFile2);
            }
            else if (op == '?') {
                hashRetrieval(index, firstName, lastName, outFile2);
            }
        }
    }
    
    void printList(int index, ofstream &outFile2) {
        outFile2 << "HashTable [" << index << "]: ";
        listNode* temp = &hashArray[index];
        
        while (temp != NULL) {
            temp->printNode(temp,outFile2);
            temp = temp->next;
        }
    }
    void printHashTable(ofstream &outFile1) {
        int index = 0;
        
        for (int i = 0; i <= bucketSize - 1; i++) {
            index = i;
            outFile1 << "HashTable [" << index << "]: ";
            listNode* temp = &hashArray[index];
            
            while (temp != NULL) {
                temp->printNode(temp,outFile1);
                temp = temp->next;
            }
          
        }
        
    }
    
    
};


int main(int argc, const char * argv[]) {
    
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);
    
    string inputNum = argv[2];
    
    string outputName1 = argv[3];
    ofstream output1;
    output1.open(outputName1);
    
    string outputName2 = argv[4];
    ofstream output2;
    output2.open(outputName2);
    
    int bucketNum = stoi(inputNum);
    hashTable input1;
    input1.createHashTable(bucketNum);
    
    input1.informationProcessing(input,output2);
    input1.printHashTable(output1);
    
    input.close();
    output1.close();
    output2.close();
    
    
    
    return 0;
}
