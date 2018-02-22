#include "SkipList.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>

using std::cout;
using std::endl;
using std::rand;

void SkipListTest(int);
void NaiveTest(int);

int main(int argc, char *args[]) {
    if (argc != 3) {
        return 1;
    }

    if (!strncmp(args[1], "skiplist", 10)) {
        SkipListTest(atoi(args[2]));
    } else if (!strncmp(args[1], "naive", 10)) {
        NaiveTest(atoi(args[2]));
    } else {
    }
    return 0;
}

void SkipListTest(int n) {
    SkipList l;
    
    // Run n tests, each of which is either an insert, find, or delete
    for (int i = 0; i < n; i++) {
        int kind = rand();
        int val = rand() % (int) (n);
        if (kind % 3 == 0) {
            l.insert(val);
        } else if (kind % 3 == 1) {
            l.find(val);
        } else if (kind % 3 == 2) {
            l.deleteElement(val);
        }
    }

    cout << l << endl;
}

void NaiveTest(int n) {
    std::vector<int> l;

    // Run n tests, each of which is either an insert, find, or delete
    for (int i = 0; i < n; i++) {
        int kind = rand();
        int val = rand() % (int) (n);
        if (kind % 3 == 0) {
            l.push_back(val);
        } else if (kind % 3 == 1) {
            std::find(l.begin(), l.end(), val);
        } else if (kind % 3 == 2) {
            std::vector<int>::iterator index = std::find(l.begin(), l.end(), val);
            if (index != l.end()) {
                l.erase(std::find(l.begin(), l.end(), val));
            } 
        }
    }
}
