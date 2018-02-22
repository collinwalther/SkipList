#include "SkipList.h"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *args[]) {
    SkipList l;
    while(true) {
        char c;
        if(scanf(" %c", &c) == EOF) {
            break;
        } else if (c == 'p') {
            cout << l << endl;
        } else if (c == 'i') {
            int elt;
            scanf(" %d", &elt);
            l.insert(elt);
        } else if (c == 'f') {
            int elt;
            scanf(" %d", &elt);
            cout << l.find(elt) << endl;
        } else if (c == 'd') {
            int elt;
            scanf(" %d", &elt);
            cout << l.deleteElement(elt) << endl;
        } else {
            cout << "bruh" << endl;
        }
    }
}

