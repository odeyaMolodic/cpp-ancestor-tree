#include "FamilyTree.hpp"
using namespace family;

node* search(string name, node* n) {
    // if(n == NULL) {
    //     return NULL;
    // }
    // if(n->name == name) {
    //     return n;
    // }
    // node* treeMother = search(name, n->mother);
    // node* treeFather = search(name, n->father);
    // if(treeFather != NULL) return treeFather;
    // if(treeMother != NULL) return treeMother;
    // return NULL;

    if (n->name == name) {
       return n;
    }
    if (n->father != NULL) {
        node *ans = search(name, n->father);
        if (ans != NULL){
            return ans;
        }
    }
    if (n->mother != NULL){
        node *ans = search(name, n->mother);
        if (ans != NULL){
            return ans;
        }
    }
    return NULL;
}

Tree& Tree::addFather (string childName, string fatherName) {
    node* n = search(childName, root);
    if (n == NULL) {
        throw runtime_error("that name doesn't exist");
    } else if (n->father != NULL) {
        throw runtime_error(childName+" already has a father");
    } else {
        n->father = new node(fatherName);
        n->father->kid = n;
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
        n->mother->kid = n;
    }
    return *this;
}


string Tree::relation (string name) {
    node* leaf = search(name, root);
    node* ans = leaf;
    if(leaf == NULL) {
        return "unrelated";
    }
    if(leaf == root) {
        return "me";
    }
    int count = 0;
    string rela = "";
    string relation[] = {"", "grand", "great-grand"};
    while (leaf != root) {
        count++;
        leaf = leaf->kid;
    }
    while(count>3) {
        rela+="great-";
        count--;
    }
    ans = ans->kid;
    if(ans->father != NULL && ans->father->name.compare(name) == 0) {
        rela+=relation[count-1];
        return rela+="father";
    }
    else if(ans->mother != NULL && ans->mother->name.compare(name) == 0) {
        rela+=relation[count-1];
        return rela+="mother";
    }
    return NULL;
}

string Find(node* root,string name) {

    if(root == NULL){
        return "";
    }

    if((int)name.find('-') == -1){

        if((int)name.find("father") != -1 && root->father){
            return root->father->name;
        }
        if((int)name.find("mother") != -1 && root->mother){
            return root->mother->name;
        }
        else
            return "";
    }

    int index = name.find('-');
    index++;
    int len = name.length();

    if(Find(root->father,name.substr(index,len)) != ""){
        return Find(root->father,name.substr(index,len));
    } else if(Find(root->mother,name.substr(index,len)) != "" ){
        return Find(root->mother,name.substr(index,len));
    }

    return "";
}

string Tree::find (string name) {
    if (name == "me")
        return this->root->name;
    else if (name == "father"){
        if(this->root->father)
            return this->root->father->name;
        else throw runtime_error(name + " isn't there");
    }
    else if(name == "mother"){
        if(this->root->mother)
            return this->root->mother->name;
        else throw runtime_error(name + " isn't there");
    }

    string f_side, m_side;
    if (this->root->father){
        f_side = Find(this->root->father, name);
        if (f_side != "")
            return f_side;
    }
    if (this->root->mother){
        m_side = Find(this->root->mother, name);
        if (m_side != "")
            return m_side;
    }
    throw runtime_error("Couldn't find it in the tree");
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

void Tree::display () {
    printBT("", root, false);
}

void delete_tree(node* n) {
    if(n != NULL) {
        delete_tree(n->mother);
        delete_tree(n->father);
        delete n;
    }
}

void Tree::remove (string name) {
    if(name == root->name) {
        throw runtime_error("You can't delete the root");
    }
    node* n = search(name, root);
    if(n == NULL) {
        throw runtime_error("that name doesn't exist");
    } else {
        delete_tree(n);
    }
}