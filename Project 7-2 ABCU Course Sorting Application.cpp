//============================================================================
// Name        : BinarySearchTree.cpp // PSYCH! Project 7-2 ABCU Course Sorting Application.cpp
// Author      : Clayton Merritt
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree PSYCH!!! Project 7-2  Project 5-2 copy paste and rename :D
//============================================================================

#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold Course information
struct Course {
    string courseNumber; // unique identifier
    string courseTitle;
    vector <string> prerecs; // vector for prerequisites
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    string qualityControl(Node* node);
   

public:
    BinarySearchTree();
    ~BinarySearchTree();
    void InOrder();
    void QualityControl();
    void Insert(Course course);
    Course Search(string courseNumber);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // FixMe (1): initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    //FixMe (2)
    // recurse from root deleting every node
    delete root;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // FixMe (3a): In order root
    // call inOrder fuction and pass root 
    this->inOrder(root);
}

/*
 *Quality Control
 */
void BinarySearchTree::QualityControl() {
    this->qualityControl(root);
}

/*
 * Insert a bid
 */
void BinarySearchTree::Insert(Course course) {
    // FIXME (6a) Implement inserting a bid into the tree
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
    // else
      // add Node root and bid
}

/**
 * Search for a bid
 */
Course BinarySearchTree::Search(string courseNumber) {
    // FIXME (8) Implement searching the tree for a bid

    Node* cur = root;

    while (cur != nullptr) {// keep looping downwards until bottom reached or matching bidId found
        if (cur->course.courseNumber.compare(courseNumber) == 0) {// if match found, return current bid
            return cur->course;
        }
        if (courseNumber.compare(cur->course.courseNumber) < 0) {// if bid is smaller than current node then traverse left
            cur = cur->left;
        }
        else {// else larger so traverse right
            cur = cur->right;
        }
    }

    Course course;
    return course;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // FIXME (6b) Implement inserting a bid into the tree
    // if node is larger then add to left
    if (node-> course.courseNumber.compare(course.courseNumber) > 0) {
        if (node->left == nullptr) {// if no left node
            node->left = new Node(course);// this node becomes left
        }
        else {
            this->addNode(node->left, course);// else recurse down the left node
        }
    }
    else {// else
        if (node->right == nullptr) { // if no right node
            node->right = new Node(course);// this node becomes right
        }
        else {//else
            this->addNode(node->right, course);// recurse down the right node
        }
    }
}

/*
* Prints courses in alpha numeric order
*/

void BinarySearchTree::inOrder(Node* node) {
    // FixMe (3b): Pre order root

    if (node != nullptr) {//if node is not equal to null ptr
        inOrder(node->left);//InOrder not left
        cout << node->course.courseNumber << " -- " << node->course.courseTitle << endl;
        inOrder(node->right);//InOder right
    }
}

/*
 * Preorder search for preprecs  
 */

string BinarySearchTree::qualityControl(Node* node) {
    // Something that I hacked together... Utilized the search feature which already exists to search for individual courses 
    // in order to run quality Control. Makes sense because we are litterally searching for a course in the list of courses.
    // Stole this function out of assignment 5-2 preOrder
    try {
        //if there is something in the nodes being passed from the bst
        if (node != nullptr) {
            //check to see if it has prerecs
            if (node->course.prerecs.size() > 0) {
                // if it does have prerecs, iterate through the prerecs
                for (int i = 0; i < node->course.prerecs.size(); ++i) { // iterator 1
                    string prerecCourse = node->course.prerecs.at(i); // snag the prerec course number
                    Course compare = Search(prerecCourse);// create a shell course, search for the prerec course number and populate the shell course with what comes back

                    if (compare.courseNumber.empty()) {// if the search results come back with an empty course number
                        throw(runtime_error("Course Doesn't exist in the list of courses")); // error out
                        return "a";
                    }
                    
                }// END ITERATOR 1 :: meaning iterate i to examine the next courses prerec OR get out of the loop
            }
            qualityControl(node->left);// proceed to the next node item on the left
            qualityControl(node->right); // then proceed on the right
        }
        
    }
    catch (runtime_error& e) {
        cerr << "ERROR:: qualityControl :: " << e.what() << endl; // messing around with catch. First time using this.
    }
    return "Courses check good and are loaded";
}


//============================================================================
// Static methods used for testing
//============================================================================

/*
* Course Information display
 */
void displayCourse(Course course) {
    //basic course print function
    cout << course.courseNumber << " -- " << course.courseTitle << endl;
    //Check to see if there are, in fact, prerecs... If there arent..
    if (course.prerecs.size() == 0) {
        cout << "Course has no prerequisites." << endl;
    }
    // if there are
    else{
        int i;
        cout << "Course prerequsites:" << endl;
        //cout << " Number of course Prerecs: " << course.prerecs.size() << endl; // used to troubleshoot what was actually going on in the code
        // basic for loop to get us through the course prerecs.
        for (i = 0; i < course.prerecs.size(); ++i) // iterator 1 PROBLEM ITERATOR CORRECTED!
            // if i is the same as course prerecs :: Meaning there are no additional prerequisites left to print , print with no comma
            //cout << "i's value: " << i << endl; // Isolating down the problem
            if (i == course.prerecs.size()-1) { // <-------------- PROBLEM AREA CORRECTED!
                cout << course.prerecs.at(i) << endl;
            }
            // Else :: Print the prerecs with commas inbetween each prerec until the last prerec is reached.
            else {
                cout << course.prerecs.at(i) << ", " << endl;
            }
        //END ITERATOR 1 :: meaning iterate i to the next value OR exit the loop.
    }
    return;
}

/*
* Text File Parser
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file ..." << csvPath << endl;

    ifstream file(csvPath);

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }

    try {
        // loop to read rows of the course text file
        string line; //something to store each line in the file
        int cCount = 0;

        while (getline(file, line)) { // iterator 1

            stringstream ss(line); // Get string stream going...
            string info; // this will be used to store info in the below iterator
            int it = 0; //this will be our iterator used to capture each bit of information
            
            Course course;// Create a data structure and add to the collection of bids

            while (getline(ss, info, ',')) { //iterator 2

                if (it == 0 && !empty(info)) { // if iterator is 0 and info has stuff in it
                    course.courseNumber = info; // store as course.courseNumber
                }
                if (it == 0 && empty(info)) {// Quick QC
                    throw (runtime_error("No Course Number! Check data and try again."));//Making sure the data we're trying to load actually contains something.
                    return;
                }
                if (it == 1 && !empty(info)) { // if iterator is 0 and info has stuff in it
                    course.courseTitle = info;// store as course.courseTitle
                }
                else if (it == 1 && empty(info)) {// Quick QC 
                    throw (runtime_error("No Course Title Provided! Check data and try again.")); //Making sure the data we're trying to load actually contains something.
                    return;
                }
                if (it >= 2 && !info.empty()) {// if iterator is 2 or more and info has stuff in it
                    course.prerecs.push_back(info); //  store as course prerecs
                    }
                //info.clear();
                ++it;
                }// END ITERATOR 2 :: meaning iterate to the next comma Or exit the loop and look for the next line
            
            /*
            * 
            * Little bit of QC to see if my courses are indeed actually being extracted and inserted appropriately
            cout << course.courseNumber << " -- " << course.courseTitle << endl;
            if (course.prerecs.size() > 0) {
                cout << "Course Prerequisites: " << endl;
                for (int i = 0; i < course.prerecs.size(); i++) {
                    cout << course.prerecs.at(i) << endl;
                }

            }
            */
            
            
            bst->Insert(course);// Insert this course into the bST
            ++cCount;
            }// END ITERATOR 1 :: meaning iterate to the next line within the file OR exit the loop
        cout << cCount << " Courses Loaded " << endl;
        }
    catch(runtime_error& e) {
        cerr << "ERROR:: loadCourses :: " << e.what() << endl; // messing around with catch. First time using this.
    }
}

/*
*Main
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, courseSearch;
   
    BinarySearchTree* bst;
    bst = new BinarySearchTree(); 
    Course course; 

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Print all Courses" << endl;
        cout << "  3. Print Individual Course Information" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        //implementing a little bit of quality control, making sure that the user is entering numbers into choice...
        if (cin.fail()) {
            cout << "Enter valid number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        //clearing cin because I figured out that if we dont clear cin, the newline '\n' gets caught in its buffer, making it so that getline doesnt work... :| Ask me how I found this out... 
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {

        case 1:// Option 1 Load the courses from the text file
            cout << "Please type the course listing file name:" << endl;
            getline(cin, csvPath);
            cout << csvPath << endl;
            loadCourses(csvPath, bst);
            bst->QualityControl(); //immediately send the list to quality control to make sure that there is no ambiguous data.
            break;

        case 2: // Option 2 Print a listing of all courses
            bst->InOrder();

            break;

        case 3: // Option 3 Print an individual course
            cout << "Please type the course you're interested in:" << endl;
            getline(cin, courseSearch);
            course = bst->Search(courseSearch);
            if (!course.courseNumber.empty()) {
                displayCourse(course);
            }
            else {
                cout << "Sorry, course " << courseSearch << " not found in the course list" << endl;
            }

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
