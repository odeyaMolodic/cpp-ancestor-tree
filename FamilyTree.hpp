#include <iostream>
#include <string>
using namespace std;

class node{
public:
    string name;

    node* mother;

    node* father;

    node (string name) {
        this->name = name;
        this->mother = NULL;
        this->father = NULL;
    }
};

namespace family {

    class Tree {

    private:
        node* root;

    public:
        Tree (string name) {
            this->root = new node(name);
        }

        Tree& addFather (string childName, string fatherName);

        Tree& addMother (string childName, string motherName);

        string relation (string name);

        string find (string name);

        void display ();

        void remove (string name);

    };
}