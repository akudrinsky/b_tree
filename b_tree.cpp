#ifndef B_TREE_CPP
#define B_TREE_CPP
#include "b_tree.h"

template<typename T, const int min_degree, class compare>
B_tree<T, min_degree, compare>::B_tree () {
    root = new B_node;
}

template<typename T, const int min_degree, class compare>
B_tree<T, min_degree, compare>::B_node::B_node () {
    size = 0;
    keys = new T[2 * min_degree - 1];
    children = new B_node*[2 * min_degree];
    is_leaf = true;
}

template<typename T, const int min_degree, class compare>
bool B_tree<T, min_degree, compare>::B_node::is_in (const T& value) {
    compare less;
    for (int i = 0; i < size; ++i) {
        if (!less (keys[size], value) and !less (value, keys[size])) {
            return true;
        }
    }
    return false;
}

template<typename T, const int min_degree, class compare>
void B_tree<T, min_degree, compare>::insert (const T& value) {
    compare less;

    if (root == nullptr) {
        root = new B_node;
        root->keys[0] = value;
        root->size = 1;
    }
    else {
        if (root->is_full ()) {
            B_node* new_root = new B_node;
            new_root->is_leaf = false;
            new_root->children[0] = root;
            new_root->split_child (0);

            int index = 0;
            if (less (new_root->keys[0], value)) {
                ++index;
            }
            new_root->children[index]->insert (value);

            root = new_root;
        }
        else {
            root->insert (value);
        }
    }
}

template<typename T, const int min_degree, class compare>
void B_tree<T, min_degree, compare>::B_node::insert (const T& value) {
    compare less;
    int index = size - 1;

    if (is_leaf) {
        if (is_in (value))                                                      /// No several equal values needed
            return;

        while (index >= 0 and less (value, keys[index])) {
            keys[index + 1] = keys[index];
            --index;
        }

        keys[index + 1] = value;
        ++size;
    }
    else {
        while (index >= 0 and less (value, keys[index])) {
            --index;
        }

        if (children[index + 1]->is_full ()) {
            split_child (index + 1);

            // after split we need to see where our value goes
            if (less (keys[index + 1], value)) {
                ++index;
            }
        }

        children[index + 1]->insert (value);
    }
}

template<typename T, const int min_degree, class compare>
void B_tree<T, min_degree, compare>::B_node::split_child (int index) {
    B_node* to_split = children[index];
    B_node* node_new = new B_node;
    node_new->is_leaf = to_split->is_leaf;

    node_new->size = min_degree - 1;
    for (int i = 0; i < min_degree - 1; ++i) {
        node_new->keys[i] = to_split->keys[min_degree + i];
    }

    if (!to_split->is_leaf) {
        for (int i = 0; i < min_degree; ++i) {
            node_new->children[i] = to_split->children[min_degree + i];
        }
    }

    to_split->size = min_degree - 1;

    for (int i = size; i > index; --i) {
        children[i + 1] = children[i];
    }

    children[index + 1] = node_new;

    for (int i = size - 1; i >= index; --i) {
        keys[i + 1] = keys[i];
    }

    keys[index] = to_split->keys[min_degree - 1];

    ++size;
}

template<typename T, const int min_degree, class compare>
bool B_tree<T, min_degree, compare>::B_node::is_full () {
    return size == 2 * min_degree - 1;
}

template<typename T, const int min_degree, class compare>
std::pair<bool, const T&> B_tree<T, min_degree, compare>::next (const T& value) {
    return root->next (value);
}

template<typename T, const int min_degree, class compare>
std::pair<bool, const T&> B_tree<T, min_degree, compare>::B_node::next (const T& value) {
    compare less;
    if (is_leaf) {
        for (int i = 0; i < size; ++i) {
            if (!less (keys[i], value)) {                       // i - first index in this node such that ...
                return std::make_pair (true, keys[i]);
            }
        }
        return std::make_pair (false, keys[0]);
    }
    else {
        for (int i = 0; i < size; ++i) {
            if (!less (keys[i], value)) {                       // i - first index in this node such that ...
                std::pair<bool, const T&> before_found = children[i]->next (value);
                if (before_found.first) {
                    return before_found;
                }
                else {
                    return std::make_pair (true, keys[i]);
                }
            }
        }
        return children[size]->next (value);
    }
}

template<typename T, const int min_degree, class compare>
void B_tree<T, min_degree, compare>::print () {
    std::string id = "0";
    std::cout << "Printing tree: root's id is 0\n";
    root->print (id);
}

template<typename T, const int min_degree, class compare>
B_tree<T, min_degree, compare>::~B_tree () {
    root->destroy_subtree ();
}

template<typename T, const int min_degree, class compare>
void B_tree<T, min_degree, compare>::B_node::destroy_subtree () {
    if (!is_leaf) {
        for (int i = 0; i <= size; ++i) {
            children[i]->destroy_subtree ();
        }
    }
    delete[] children;
    delete[] keys;
}

template<typename T, const int min_degree, class compare>
void B_tree<T, min_degree, compare>::B_node::print (const std::string& id) {
    std::cout << "<---------------------------->\nVertice id: " << id << (is_leaf ? " - leaf" : " - not a leaf") << "\nKeys are: \n";
    for (int i = 0; i < size; ++i) {
        std::cout << i << ": " << keys[i] << '\n';
    }
    std::cout << "\n<---------------------------->\n\n";

    if (!is_leaf) {
        for (int i = 0; i < size + 1; ++i) {
            children[i]->print (id + std::to_string (i));
        }
    }
}

#endif
