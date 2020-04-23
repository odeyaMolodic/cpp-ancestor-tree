#include <iostream>
#include <string>
using namespace std;

class node{
public:
    string name;

    node* mother;

    node* father;

    node* kid;

    node (string name) {
        this->name = name;
        this->mother = NULL;
        this->father = NULL;
    }

    ~node() {
        delete father;
        delete mother;
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

        ~Tree() {
            delete root;
        }

        Tree& addFather (string childName, string fatherName);

        Tree& addMother (string childName, string motherName);

        string relation (string name);

        string find (string name);

        void display ();

        void remove (string name);

    };
}