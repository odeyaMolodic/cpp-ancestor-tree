#include "FamilyTree.hpp"
using namespace family;

Tree& Tree::addFather (string childName, string fatherName) {
    node* n = search(childName, root);
    if (n == NULL) {
        throw runtime_error("that name doesn't exist");
    } else if (n->father != NULL) {
        throw runtime_error(childName+" already has a father");
    } else {
        n->father = new node(fatherName);
    }
    return *this;
}

Tree& Tree::addMother (string childName, string motherName) {
    node* n = search(childName, root);
    if (n == NULL) {
        throw runtime_error("that name doesn't exist");
    } else if (n->mother != NULL) {
        throw runtime_error(childName+" already has a mother");
    } else {
        n->mother = new node(motherName);
    }
    return *this;
}


string Tree::relation (string name) {

    return "";
}

string Tree::find (string name) {

    return "";
}

void Tree::display () {
    printBT("", root, false);
}

void Tree::remove (string name) {
    node* n = search(name, root);
    if(n == NULL) {
        throw runtime_error("that name doesn't exist");
    } else if(n->name.compare(root->name) == 0) {
        throw runtime_error("You can't delete the root");
    } else {
        delete_tree(n);
    }
}

node* search(string name, node* n) {
    if(n != NULL) {
        if(n->name.compare(name) == 0) {
            return n;
        }
        search(name, n->mother);
        search(name, n->father);
    }
    return NULL;
}

void printBT(const string& prefix, const node* node, bool isLeft) {
    if(node != NULL) {
        cout << prefix;

        cout << (isLeft ? "├──" : "└──" );

        cout << node->name << endl;

        printBT(prefix + (isLeft ? "│   " : "    "), node->mother, true);
        printBT(prefix + (isLeft ? "│   " : "    "), node->father, false);
    }
}

void delete_tree(node* n) {
    if(n != NULL) {
        delete_tree(n->mother);
        delete_tree(n->father);
        delete n;
    }
}