#include <iostream>
#include <vector>
#include "b_tree.h"

#include "danya.cpp"

#define i(data) tree.insert(data);
#define r(data) tree.remove(data);
#define p tree.print();

void test_mine ();
void compare ();
void answer ();

int main () {
    test_mine ();
    //compare ();
}

void test_mine () {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    B_tree<int, 2> tree;
    int n_requests = 0;
    unsigned long long last_sum = -1;
    char command[2] = {};
    int value = 0, arg = 0;
    std::cin >> n_requests;

    for (int i = 0; i < n_requests; ++i) {
        std::cin >> command;
        if (command[0] == '+') {
            std::cin >> value;
            if (last_sum != -1) {
                tree.insert ((value + last_sum) % 1000000000);
                last_sum;
                last_sum = -1;
            }
            else {
                tree.insert (value);
                last_sum = -1;
            }
        }
        else if (command[0] == '?') {
            std::cin >> value >> arg;
            last_sum = tree.sum_range (value, arg);
            printf ("%lld\n", last_sum);
        }
        else {
            printf ("abort....\n");
            abort ();
        }

        p
    }
}

/*
6
+ 1
+ 3
+ 3
? 2 4
+ 1
? 2 4

 */
