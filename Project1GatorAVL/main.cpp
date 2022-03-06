#include <iostream>
using namespace std;

class Student {
public:
    int ID;
    string NAME;
};

class Node {
public:
    int ID;
    string NAME;
    Node* left;
    Node* right;
    int height;
};

class AVL{
private:
    Node* rotationLeft(Node* currentNode)
    {
        int temp1LeftHeight;
        int temp1RightHeight;
        int currentNodeLeftHeight;
        int currentNodeRightHeight;
        Node* temp1 = nullptr;
        Node* temp2 = nullptr;

        //do left rotation
        temp1 = currentNode -> right;
        temp2 = temp1 -> left;

        temp1 -> left = currentNode;
        currentNode -> right = temp2;

        //calculate currentNode left pointer height
        if(currentNode->left != nullptr){
            currentNodeLeftHeight = currentNode->left->height;
        }
        else {
            currentNodeLeftHeight = 0;
        }

        //calculate currentNode right pointer height
        if(currentNode->right != nullptr){
            currentNodeRightHeight = currentNode->right->height;
        }
        else {
            currentNodeRightHeight = 0;
        }


        //adjust height of currentNode based on rotations
        if(currentNodeLeftHeight > currentNodeRightHeight){
            currentNode -> height = currentNodeLeftHeight + 1;
        }
        else if (currentNodeRightHeight > currentNodeLeftHeight){
            currentNode -> height = currentNodeRightHeight + 1;
        }
        else {
            currentNode -> height = currentNodeLeftHeight + 1;
        }

        //calculate temp1 left pointer height
        if(temp1 -> left != nullptr){
            temp1LeftHeight = temp1 -> left -> height;
        } else {
            temp1LeftHeight = 0;
        }

        //calculate temp1 right pointer height
        if(temp1 -> right != nullptr){
            temp1RightHeight = temp1 -> right -> height;
        }
        else {
            temp1RightHeight = 0;
        }



        //adjust height of currentNode based on rotations
        if(temp1LeftHeight > temp1RightHeight){
            temp1 -> height = temp1LeftHeight + 1;
        }
        else if (temp1RightHeight > temp1LeftHeight){
            temp1 -> height = temp1RightHeight + 1;
        }
        else {
            temp1 -> height = temp1LeftHeight + 1;
        }



        return temp1;
    }

    Node* rotationRight(Node* currentNode)
    {
        int temp1LeftHeight;
        int temp1RightHeight;
        int currentNodeLeftHeight;
        int currentNodeRightHeight;
        Node* temp1 = nullptr;
        Node* temp2 = nullptr;

        //do right rotation
        temp1 = currentNode -> left;
        temp2 = temp1 -> right;

        temp1 -> right = currentNode;
        currentNode -> left = temp2;

        //calculate currentNode left pointer height
        if(currentNode -> left != nullptr){
            currentNodeLeftHeight = currentNode -> left -> height;
        }
        else {
            currentNodeLeftHeight = 0;
        }
        //calculate currentNode right pointer height
        if(currentNode -> right != nullptr){
            currentNodeRightHeight = currentNode -> right -> height;
        }
        else {
            currentNodeRightHeight = 0;
        }

        //adjust height of currentNode based on rotations
        if(currentNodeLeftHeight > currentNodeRightHeight){
            currentNode -> height = currentNodeLeftHeight + 1;
        }
        else if (currentNodeRightHeight > currentNodeLeftHeight){
            currentNode -> height = currentNodeRightHeight + 1;
        }
        else {
            currentNode -> height = currentNodeLeftHeight + 1;
        }

        //calculate temp1 left pointer height
        if(temp1 -> left != nullptr){
            temp1LeftHeight = temp1 -> left -> height;
        }
        else {
            temp1LeftHeight = 0;
        }
        //calculate temp1 right pointer height
        if(temp1 -> right != nullptr){
            temp1RightHeight = temp1 -> right -> height;
        }
        else {
            temp1RightHeight = 0;
        }

        //adjust height of currentNode based on rotations
        if(temp1LeftHeight > temp1RightHeight){
            temp1 -> height = temp1LeftHeight + 1;
        }
        else if (temp1RightHeight > temp1LeftHeight){
            temp1 -> height = temp1RightHeight + 1;
        }
        else {
            temp1 -> height = temp1LeftHeight + 1;
        }

        return temp1;
    }

    Node* rotationLeftRight(Node* currentNode){
        currentNode -> left = rotationLeft(currentNode -> left);
        return rotationRight(currentNode);
    }

    Node* rotationRightLeft(Node* currentNode){
        currentNode -> right = rotationRight(currentNode -> right);
        return rotationLeft(currentNode);
    }

    Node* insert (Node* currentNode, int id, string name, bool *successCheck){
        //if nullptr make a new node with values
        if(currentNode == nullptr){
            Node* newRoot = new Node();
            newRoot -> ID = id;
            newRoot -> NAME = name;
            newRoot -> left = nullptr;
            newRoot -> right = nullptr;
            newRoot -> height = 1;
            return newRoot;
        }
        else {
            //traverse to correct section of tree to insert on
            if(id > currentNode -> ID){
                currentNode -> right = insert(currentNode -> right, id, name, successCheck);
            }
            else if(id < currentNode -> ID) {
                currentNode -> left = insert(currentNode->left, id, name, successCheck);
            }
            else {
                //id is not unique
                *successCheck = false;
                return currentNode;
            }
        }

        int currentNodeLeftHeight;
        int currentNodeRightHeight;

        //calculate currentNode left pointer height
        if(currentNode -> left != nullptr){
            currentNodeLeftHeight = currentNode->left->height;
        }
        else {
            currentNodeLeftHeight = 0;
        }

        //calculate currentNode right pointer height
        if(currentNode -> right != nullptr){
            currentNodeRightHeight = currentNode->right->height;
        }
        else {
            currentNodeRightHeight = 0;
        }

        //make currentNode's height accurate
        if(currentNodeLeftHeight > currentNodeRightHeight){
            currentNode -> height = currentNodeLeftHeight + 1;
        }
        else if (currentNodeRightHeight > currentNodeLeftHeight){
            currentNode -> height = currentNodeRightHeight + 1;
        }
        else {
            currentNode -> height = currentNodeLeftHeight + 1;
        }

        //calculate heights of left and right of currentNode to get correct BF
        if (currentNode -> left != nullptr) {
            currentNodeLeftHeight = currentNode->left->height;
        }
        else {
            currentNodeLeftHeight = 0;
        }
        if (currentNode -> right != nullptr) {
            currentNodeRightHeight = currentNode->right->height;
        }
        else {
            currentNodeRightHeight = 0;
        }

        int BF = currentNodeLeftHeight - currentNodeRightHeight;


        //right heavy
        if (BF < -1 && id > currentNode -> right -> ID){
            return rotationLeft(currentNode);
        }
        //left heavy
        if (BF > 1 && id < currentNode -> left -> ID){
            return rotationRight(currentNode);
        }

        //right heavy left heavy
        if (BF < -1 && id < currentNode->right->ID){
            return rotationRightLeft(currentNode);
        }

        //left heavy right heavy
        if (BF > 1 && id > currentNode->left->ID){
            return rotationLeftRight(currentNode);
        }

        return currentNode;
    }

    Node* rightChildChecker(Node* currentNode){
        Node* temp1 = nullptr;
        temp1 = currentNode -> right;
        delete currentNode;
        return temp1;
    }

    Node* leftChildChecker(Node* currentNode){
        Node* temp1 = nullptr;
        temp1 = currentNode -> left;
        delete currentNode;
        return temp1;
    }

    Node* removeById(Node* currentNode, int id, bool *successCheck){
        //Id not found
        if(currentNode == nullptr){
            *successCheck = false;
            return nullptr;
        }
        //traverse left side of tree
        if(id < currentNode -> ID){
            currentNode -> left = removeById(currentNode -> left, id, successCheck);
        }
            //traverse right side of tree
        else if (id > currentNode -> ID){
            currentNode -> right = removeById(currentNode -> right, id, successCheck);
        }
        else if (id == currentNode -> ID){
            //no children case
            if (currentNode -> left == nullptr && currentNode -> right == nullptr){
                return nullptr;
            }
                //only has right child
            else if (currentNode -> left == nullptr){
                rightChildChecker(currentNode);
            }
                //only has left child
            else if (currentNode -> right == nullptr){
                leftChildChecker(currentNode);
            }

            //get in order successor
            Node* temp2 = currentNode -> right;
            while (temp2 != nullptr && temp2 -> left != nullptr){
                temp2 = temp2 -> left;
            }
            currentNode -> ID = temp2 -> ID;
            currentNode -> NAME = temp2 -> NAME;

            currentNode -> right = removeById(currentNode -> right, temp2 -> ID, successCheck);
        }

        return currentNode;
    }
    void searchById(Node* currentNode, int id, bool *successCheck){
        if (currentNode == nullptr){
            return;
        }
        //if id is found print it
        if(currentNode -> ID == id){
            cout << currentNode -> NAME << endl;
            *successCheck = true;
        }

        searchById(currentNode->left, id, successCheck);
        searchById(currentNode->right, id, successCheck);
    }
    void searchByName(Node* currentNode, string name, bool *successCheck){
        if (currentNode == nullptr){
            return;
        }
        //if name found print it
        if(currentNode -> NAME == name){
            cout << currentNode -> ID << endl;
            *successCheck = true;
        }
        //traverse tree to find name
        searchByName(currentNode->left, name, successCheck);
        searchByName(currentNode->right, name, successCheck);
    }
    void printInorder(Node* currentNode, char** delimiter){
        if (currentNode == nullptr){
            return;
        }
        else {
            //left,root,right
            printInorder(currentNode->left, delimiter);
            cout << *delimiter << currentNode->NAME;
            *delimiter = (char*)", ";
            printInorder(currentNode->right, delimiter);
        }
    }
    void printPreorder(Node* currentNode, char** delimiter){
        if (currentNode == nullptr){
            return;
        }
        else {
            //root,left,right
            cout << *delimiter << currentNode->NAME;
            *delimiter = (char*)", ";
            printPreorder(currentNode->left, delimiter);
            printPreorder(currentNode->right, delimiter);
        }
    }
    void printPostorder(Node* currentNode, char** delimiter){
        if (currentNode == nullptr){
            return;
        }
        else {
            //left,right,root
            printPostorder(currentNode->left, delimiter);
            printPostorder(currentNode->right, delimiter);
            cout << *delimiter << currentNode->NAME;
            *delimiter = (char*)", ";
        }
    }
    int printLevelCount(Node* currentNode){
        if(currentNode == nullptr){
            return 0;
        }

        int left_child = 1 + printLevelCount(currentNode->left);
        int right_child = 1 + printLevelCount(currentNode->right);
        //take the bigger of the left and right child and return it as the level count
        if(left_child > right_child){
            return left_child;
        }
        if(right_child > left_child){
            return right_child;
        }
        if(right_child == left_child){
            return left_child;
        }
    }
    Node* removeInorder(Node* currentNode, int numberNodeToRemove, bool *successChecker, int* countChecker){
        if (currentNode == nullptr){
            return nullptr;
        }
        removeInorder(currentNode->left, numberNodeToRemove, successChecker, countChecker);

        if (*countChecker == numberNodeToRemove){
            *successChecker = true;
            //call removeById and pass in the currentNode's ID
            removeById(currentNode->ID);
            return currentNode;
        }
        *countChecker = *countChecker + 1;
        removeInorder(currentNode->right, numberNodeToRemove, successChecker, countChecker);
    }

public:
    Node* baseRoot;
    AVL(){
        this -> baseRoot = nullptr;
    }
    void insert(int id, string name) {
        bool successCheck = true;
        baseRoot = insert(baseRoot, id, name, &successCheck);
        if(successCheck == true){
            cout << "successful" << endl;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    void removeById(int id){
        bool successCheck = true;
        removeById(baseRoot, id, &successCheck);
        if(successCheck == true){
            cout << "successful" << endl;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    void searchById(int id){
        bool successCheck = false;
        searchById(baseRoot, id, &successCheck);
        if(successCheck == false){
            cout << "unsuccessful" << endl;
        }
    }
    void searchByName(string name){
        bool successCheck = false;
        searchByName(baseRoot, name, &successCheck);
        if(successCheck == false){
            cout << "unsuccessful" << endl;
        }
    }
    void printInorder(){
        char* delimiter = (char*)"";
        printInorder(baseRoot, &delimiter);
        cout << endl;
    }
    void printPreorder(){
        char* delimiter = (char*)"";
        printPreorder(baseRoot, &delimiter);
        cout << endl;
    }
    void printPostorder(){
        char* delimiter = (char*)"";
        printPostorder(baseRoot, &delimiter);
        cout << endl;
    }
    void printLevelCount(){
        int levelCount = printLevelCount(baseRoot);
        cout << levelCount << endl;
    }
    void removeInorder(int N){
        int countChecker = 0;
        bool successChecker = false;
        removeInorder(baseRoot, N, &successChecker, &countChecker);
        if(successChecker == false){
            cout << "unsuccessful" << endl;
        }
    }
};

int main() {
    AVL avlObj;
    Student studentObj;
    string numberOfCommandsString;
    getline(cin, numberOfCommandsString);
    int numberOfCommandsInt;
    numberOfCommandsInt = stoi(numberOfCommandsString);
    string userInput;

    for (int i = 0; i < numberOfCommandsInt; i++) {
        getline(cin, userInput);

        if (userInput == "printInorder") {
            avlObj.printInorder();
            continue;
        }
        if (userInput == "printPreorder") {
            avlObj.printPreorder();
            continue;
        }
        if (userInput == "printPostorder") {
            avlObj.printPostorder();
            continue;
        }
        if (userInput == "printLevelCount") {
            avlObj.printLevelCount();
            continue;
        }

        string parsableString = userInput;
        string spaceDelimiter = " ";
        string binaryTreeCommand = parsableString.substr(0, parsableString.find(spaceDelimiter));

        if (binaryTreeCommand == "insert") {
            parsableString = parsableString.substr(parsableString.find("\"") + 1, parsableString.length() - 1);
            string name = parsableString.substr(0, parsableString.find("\""));
            bool nameIsValid = true;
            studentObj.NAME = name;
            parsableString = parsableString.substr(parsableString.find("\"") + 1, parsableString.length() - 1);
            string UFID = parsableString.substr(1, parsableString.length());
            char charArray[name.length()];

            for (int i = 0; i < sizeof(charArray); i++) {
                charArray[i] = name[i];
            }

            for (char c : charArray) {
                if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
                    continue;
                }
                else if (c == ' ') {
                    continue;
                }
                else {
                    nameIsValid = false;
                    break;
                }
            }

            if (UFID.length() != 8 || nameIsValid == false) {
                cout << "unsuccessful" << endl;
            }
            else {
                studentObj.ID = stoi(UFID);
                avlObj.insert(studentObj.ID, studentObj.NAME);
            }
        }

        if (binaryTreeCommand == "search") {
            bool isValid = true;
            parsableString = parsableString.substr(parsableString.find(spaceDelimiter) + 1,parsableString.length() - 1);
            string searchableValue;

            if (parsableString.find('\"') == 0) {
                searchableValue = parsableString.substr(1, parsableString.length() - 2);
                char charArray[searchableValue.length()];

                for (int i = 0; i < sizeof(charArray); i++) {
                    charArray[i] = searchableValue[i];
                }
                //check for valid alphabetic characters
                for (char c : charArray) {
                    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
                        continue;
                    }
                    else if (c == ' ') {
                        continue;
                    }
                    else {
                        isValid = false;
                        break;
                    }
                }

                if (isValid == true) {
                    avlObj.searchByName(searchableValue);
                }
                else {
                    cout << "unsuccessful" << endl;
                }

            }
            else {
                searchableValue = parsableString;
                if(searchableValue.length() == 8){
                    searchableValue = parsableString;
                    avlObj.searchById(stoi(searchableValue));
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
        }

        if (binaryTreeCommand == "remove") {
            parsableString = parsableString.substr(parsableString.find(spaceDelimiter) + 1,parsableString.length() - 1);
            string searchableValue;
            searchableValue = parsableString;
            if(searchableValue.length() == 8){
                avlObj.removeById(stoi(searchableValue));
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }

        if(binaryTreeCommand == "removeInorder"){
            parsableString = parsableString.substr(parsableString.find(spaceDelimiter) + 1,parsableString.length() - 1);
            string searchableValue;
            searchableValue = parsableString;
            avlObj.removeInorder(stoi(searchableValue));
        }
    }

    return 0;
}