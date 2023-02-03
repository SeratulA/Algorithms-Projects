#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class image {
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int power2Size;
    int **imgAry;
    
    image(int numRows, int numCols, int minVal, int maxVal, int power2Size){
        this -> numRows = numRows;
        this -> numCols = numCols;
        this -> minVal = minVal;
        this -> maxVal = maxVal;
        this -> power2Size = power2Size;
        
        
    }
    
    int computePower2(int numRows, int numCols) {
        int size = max(numRows,numCols);
        
        int power2 = 2;
        while (size > power2) {
            power2 *= 2;
        }
        return power2;
    }
    
    void loadImage(ifstream &inFile, int **imgAry) {
        for(int i=0; i<power2Size; i++){
            for(int j=0; j<power2Size; j++){
                inFile >> imgAry[i][j];
            }
        }
    }
    
    void zero2DAry(int **imgAry) {
        for(int i=0; i<power2Size; i++){
            for(int j=0; j<power2Size; j++){
                imgAry[i][j] = 0 ;
            }
        }
    }
};
class QtTreeNode {
public:
    int color, upperR, upperC, size;
    QtTreeNode* NWkid;
    QtTreeNode* NEkid;
    QtTreeNode* SWkid;
    QtTreeNode* SEkid;
    
    QtTreeNode(int color, int upperR, int upperC, int size, QtTreeNode* NWkid, QtTreeNode* NEkid, QtTreeNode* SWkid, QtTreeNode* SEkid) {
        this -> color = color;
        this -> upperR = upperR;
        this -> upperC = upperC;
        this -> size = size;
        this -> NWkid = NWkid;
        this -> NEkid = NEkid;
        this -> SWkid = SWkid;
        this -> SEkid = SEkid;
    }
    void printQtNode(QtTreeNode *newQtNode, ofstream &outFile) {
        
        if (newQtNode->NWkid == NULL && newQtNode->NEkid == NULL && newQtNode->SWkid == NULL && newQtNode->SEkid == NULL) {
            outFile << "Color: " << newQtNode->color<< ", UpperC: "  << newQtNode->upperC << ", UpperR: " << newQtNode->upperR << ", NWkid's color: " << "NULL" << ", NEkid's color: " << "NULL" << ", SWkid's color: " << "NULL" << ", SEkid's color: " << "NULL" << endl;
        }
        
        else {
            outFile << "Color: " << newQtNode->color<< ", UpperC: "  << newQtNode->upperC << ", UpperR: " << newQtNode->upperR << ", NWkid's color: " << newQtNode->NWkid->color << ", NEkid's color: " << newQtNode->NEkid->color << ", SWkid's color: " << newQtNode->SWkid->color << ", SEkid's color: " << newQtNode->SEkid->color << endl;
        }
    }
};
class QuadTree {
public:
    QtTreeNode* QtRoot;
    
    QtTreeNode * buildQuadTree(int **imgAry, int upperR, int upperC, int size, ofstream &outFile2) {
        QtTreeNode* newQtNode = new QtTreeNode(-1, upperR, upperC, size, NULL, NULL, NULL, NULL);
        newQtNode->printQtNode(newQtNode, outFile2);
        
        if (size == 1) {
            newQtNode->color = imgAry[upperR][upperC];
        }
        else {
            int halfSize = size/2;
            newQtNode -> NWkid = buildQuadTree(imgAry, upperR, upperC, halfSize, outFile2);
            newQtNode -> NEkid = buildQuadTree(imgAry, upperR, upperC + halfSize, halfSize, outFile2);
            newQtNode -> SWkid = buildQuadTree(imgAry, upperR + halfSize, upperC, halfSize, outFile2);
            newQtNode -> SEkid = buildQuadTree(imgAry, upperR + halfSize, upperC + halfSize, halfSize, outFile2);
            
            int sumColor = newQtNode -> NWkid->color + newQtNode -> NEkid->color + newQtNode -> SWkid-> color +newQtNode -> SEkid->color;
            if (sumColor == 0) {
                newQtNode-> color = 0;
                newQtNode->NWkid = NULL;
                newQtNode->NEkid = NULL;
                newQtNode->SWkid = NULL;
                newQtNode->SEkid = NULL;
            }
            else if (sumColor == 4) {
                newQtNode-> color = 1;
                newQtNode->NWkid = NULL;
                newQtNode->NEkid = NULL;
                newQtNode->SWkid = NULL;
                newQtNode->SEkid = NULL;
            }
            else newQtNode-> color = 5;
        }
        return newQtNode;
    }
    
    bool isLeaf(QtTreeNode* node) {
        if (node->NWkid == NULL && node->NEkid == NULL && node->SWkid == NULL && node-> SEkid == NULL) return true;
        else return false;
    }
    void preOrder (QtTreeNode* QT, ofstream &outFile1) {
        if (isLeaf(QT)) QT->printQtNode(QT,outFile1);
        else {
            QT->printQtNode(QT,outFile1);
            preOrder(QT->NWkid, outFile1);
            preOrder(QT->NEkid, outFile1);
            preOrder(QT->SWkid, outFile1);
            preOrder(QT->NWkid, outFile1);
        }
    }
    
    void postOrder (QtTreeNode* QT, ofstream &outFile1) {
        if (isLeaf(QT)) QT->printQtNode(QT,outFile1);
        else {
            preOrder(QT->NWkid, outFile1);
            preOrder(QT->NEkid, outFile1);
            preOrder(QT->SWkid, outFile1);
            preOrder(QT->NWkid, outFile1);
            QT->printQtNode(QT,outFile1);
        }
    }
    
};

int main(int argc, const char * argv[]) {
    string inputName = argv[1];
    ifstream input;
    input.open(inputName);
    
    string outputName1 = argv[2];
    ofstream output1;
    output1.open(outputName1);
    
    string outputName2 = argv[3];
    ofstream output2;
    output2.open(outputName2);
    
    int numRows, numCols, minVal, maxVal;
    input >> numRows >> numCols >> minVal >> maxVal;
    
    
    image newImage(numRows, numCols, minVal, maxVal, 0);
    newImage.power2Size = newImage.computePower2(numRows, numCols);
    output2 << "Power2Size = " << newImage.power2Size << endl;
    
    
    newImage.imgAry = new int*[newImage.power2Size] ;
    for(int i=0; i<newImage.power2Size; i++){
        newImage.imgAry[i] = new int[newImage.power2Size] ;
    }
    newImage.zero2DAry(newImage.imgAry);
    newImage.loadImage(input, newImage.imgAry);
    
    for(int i=0; i<newImage.power2Size; i++){
        output2 << endl;
        for(int j=0; j<newImage.power2Size; j++){
            output2 << newImage.imgAry[i][j] << " ";
        }
    }
    output2 << endl;
    
    QuadTree QT;
    QT.QtRoot = QT.buildQuadTree(newImage.imgAry, 0, 0, newImage.power2Size, output2);
    output1 << "----PREFORMING PREORDER----" << endl;
    QT.preOrder(QT.QtRoot, output1);
    output1 << "----PREFORMING POSTORDER----" << endl;
    QT.postOrder(QT.QtRoot, output1);
    
    input.close();
    output1.close();
    output2.close();
    
    return 0;
}
