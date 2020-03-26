#ifndef B_TREE_H
#define B_TREE_H
#include <iostream>
#include <string>

template<typename T, const int min_degree, class compare = std::less<T> >
class B_tree {
private:
    struct B_node {
        int size;                                   // number of keys
        T* keys;
        B_node** children;
        bool is_leaf;

        B_node ();
        //~B_node ();
        //! Inserts value to a tree if it is not full. The node corresponding to this index must be full when this function is called.
        void insert (const T& value);
        //! Splits index_node of this node. The node corresponding to this index must be full when this function is called.
        void split_child (int index);
        //! If the given node is full
        bool is_full ();
        //! Checks if a given value is in node
        bool is_in (const T& value);
        //! Gets next element (recursive for "next" in tree)
        std::pair<bool, const T&> next (const T& value);
        //! Prints node in print of tree function
        void print (const std::string& identifier);
    };
    B_node* root;
public:
    explicit B_tree ();
    //~B_tree ();

    //!==========================|
    //! Inserts element to a tree
    //!==========================|
    void insert (const T& value);

    //!===================================================================|
    //! Outputs the least element in tree equal or bigger than a given one
    //!===================================================================|
    std::pair<bool, const T&> next (const T& value);

    //!==========================|
    //! Prints tree
    //!==========================|
    void print ();
};

#include "b_tree.cpp"

#endif