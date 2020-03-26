#include <iostream>
#include <vector>
#include "b_tree.h"
void test ();

int main () {
    test ();

    /*
    int n_requests = 0;
    B_tree<int, 10> tree;
    std::cin >> n_requests;
    int id = 0;
    std::string command;

    bool was_question = false;
    int saved_result = 0;

    for (int i = 0; i < n_requests; ++i) {
        std::cin >> command >> id;
        if (command[0] == '+') {
            if (was_question) {
                id = (id + saved_result) % 1000000000;
            }
            tree.insert (id);
            was_question = false;
        }
        else if (command[0] == '?') {
            was_question = true;
            std::pair<bool, int> answer= tree.next (id);
            if (answer.first) {
                printf ("%d\n", answer.second);
                saved_result = answer.second;
            }
            else {
                printf ("-1\n");
                saved_result = -1;
            }
        }
        else {
            printf ("command = %c\n", command[0]);
        }
    }*/
}

void test () {
    B_tree<int, 2> tree;
    tree.insert (12);
    tree.insert (3);
    tree.insert (5);
    tree.insert (6);
    tree.insert (1);
    tree.insert (44);
    tree.insert (1324);
    tree.insert (4);
    tree.insert (66);

    tree.print ();

    std::cout << tree.next (200).second;
}

/*
6
+ 1
+ 3
+ 3
? 2
+ 1
? 4

 */