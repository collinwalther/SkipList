#include <cstdlib>
#include <iostream>

using std::endl;

struct Node {
    int key;
    unsigned height;
    struct Node **links;
};

class SkipList {
  private:
    unsigned _length;
    unsigned _height;
    Node *_head;

  public:
    SkipList();
    bool find(int);
    bool insert(int);
    bool deleteElement(int);
    friend std::ostream &operator<<(std::ostream &o, const SkipList &list);
};

SkipList::SkipList() {
    _length = 0;
    _height = 1;
    _head = new Node;
    _head->height = 1;
    _head->links = (Node **) malloc(sizeof(Node *) * 1);
    _head->links[0] = NULL;
}

bool SkipList::find(int elt) {
    Node *currNode = _head;
    unsigned currHeight = currNode->height;
    while (currHeight > 0) {
        if (currNode->links[currHeight - 1] == NULL) {
            currHeight--;
        } else if (currNode->links[currHeight - 1]->key > elt) {
            currHeight--;
        } else if (currNode->links[currHeight - 1]->key < elt) {
            currNode = currNode->links[currHeight - 1];
        } else {
            return true;
        }
    }
    return false;
}

bool SkipList::insert(int elt) {
    if (find(elt)) {
        return false;
    }

    Node *currNode = _head;
    unsigned currHeight = currNode->height;
    Node **nodesToSet = (Node **) malloc(sizeof(Node *) * currHeight);
    while (currHeight > 0) {
        if (currNode->links[currHeight - 1] == NULL) {
            nodesToSet[currHeight - 1] = currNode;
            currHeight--;
        } else if (currNode->links[currHeight - 1]->key > elt) {
            nodesToSet[currHeight - 1] = currNode;
            currHeight--;
        } else if (currNode->links[currHeight - 1]->key < elt) {
            currNode = currNode->links[currHeight - 1];
        } else {
        }
    }

    // Determine the new node's height. 
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = elt;
    newNode->height = 1;
    while (1) {
        int myRand = std::rand();
        if (myRand % 2 == 0) {
            newNode->height++;
        } else {
            break;
        }
    }

    // If the new node is higher than the head node, make the head node bigger.
    if (newNode->height > _head->height) {
        nodesToSet = (Node **) realloc(nodesToSet, sizeof(Node *) * newNode->height);
        _head->links = (Node **) realloc(_head->links, sizeof(Node *) * newNode->height);
        for (int i = _head->height; i < newNode->height; i++) {
            nodesToSet[i] = _head;
            _head->links[i] = NULL;
        }
        _height = newNode->height;
        _head->height = newNode->height;
    }   

    
    // Construct the new links.
    currHeight = newNode->height;
    newNode->links = (Node **) malloc(sizeof(Node *) * currHeight);
    for (int i = 0; i < currHeight; i++) {
        newNode->links[i] = NULL;
    }

    while (currHeight > 0) {
        Node *temp = nodesToSet[currHeight - 1]->links[currHeight - 1];
        nodesToSet[currHeight - 1]->links[currHeight - 1] = newNode;
        newNode->links[currHeight - 1] = temp;
        currHeight--;
    }

    return true;
}

bool SkipList::deleteElement(int elt) {
    if (!find(elt)) {
        return false;
    }

    Node *currNode = _head;
    unsigned currHeight = currNode->height;
    Node *toDelete;
    while (currHeight > 0) {
        if (currNode->links[currHeight - 1] == NULL) {
            currHeight--;
        } else if (currNode->links[currHeight - 1]->key > elt) {
            currHeight--;
        } else if (currNode->links[currHeight - 1]->key < elt) {
            currNode = currNode->links[currHeight - 1];
        } else {
            toDelete = currNode->links[currHeight - 1];
            currNode->links[currHeight - 1] = currNode->links[currHeight - 1]->links[currHeight - 1];
        }
    }

    // Delete the node.
    delete toDelete->links;
    delete toDelete;

    return true;
}

std::ostream &operator<<(std::ostream &o, const SkipList &list) {
    Node *currNode = list._head;
    while (currNode != NULL) {
        o << currNode->key << "\t";
        for (int i = 0; i < currNode->height; i++) {
            if (currNode->links[i] == NULL) {
                o << "NULL\t";
            } else {
                o << currNode->links[i]->key << "\t";
            }
        }
        o << std::endl;
        currNode = currNode->links[0];
    }
    return o;
}

