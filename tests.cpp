#include "linkedlist.h"
#include <cassert>

// Unit tests for LinkedList<T>, erase, add, forward and back traversals.

// Helper functions to advance / reverse iterators and assert cur iterator value equals given value.
template<typename T>
typename LinkedList<T>::Node* advance_equal(typename LinkedList<T>::Node& node, const T& val)
{
    assert(node.get_data() == val);
    return node.get_next();
}

template<typename T>
typename LinkedList<T>::Node* reverse_equal(typename LinkedList<T>::Node& node, const T& val)
{
    assert(node.get_data() == val);
    return node.get_prev();
}

void add()
{
    LinkedList<int> l;

    assert(l.get_head() == nullptr);
    assert(l.get_tail() == nullptr);

    l.push_back(1);
    assert(l.get_head() != nullptr);
    assert(l.get_tail() != nullptr);
    assert(l.get_head()->get_data() == 1);
    assert(l.get_tail()->get_data() == 1);

    l.push_back(2);
    assert(l.get_head()->get_data() == 1);
    assert(l.get_tail()->get_data() == 2);
}


void erase_empty()
{
    LinkedList<int> l;
    l.erase(5);
    assert(l.get_head() == nullptr);
    assert(l.get_tail() == nullptr);
}

void erase_one_element() // head == tail
{
    LinkedList<int> l;
    l.push_back(10);
    assert(l.get_head() != nullptr);
    assert(l.get_tail() != nullptr);
    assert(l.get_head()->get_data() == 10);
    assert(l.get_tail()->get_data() == 10);

    l.erase(10);
    assert(l.get_head() == nullptr);
    assert(l.get_tail() == nullptr);
}



void erase_middle()
{
    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    l.erase(3);

    auto* it = l.get_head();

    it = advance_equal(*it, 1);
    it = advance_equal(*it, 2);
    it = advance_equal(*it, 4);
    it = advance_equal(*it, 5);

    assert(it == nullptr);
}

void erase_head()
{
    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    l.erase(1);

    auto* it = l.get_head();

    it = advance_equal(*it, 2);
    it = advance_equal(*it, 3);

    assert(it == nullptr);
}


void erase_tail()
{
    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    l.erase(3);

    assert(l.get_tail() != nullptr);
    assert(l.get_tail()->get_data() == 2);

    auto* it = l.get_head();

    it = advance_equal(*it, 1);
    it = advance_equal(*it, 2);

    assert(it == nullptr);
}

void erase_by_node()
{
    LinkedList<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    auto* to_erase = l.find_node(2);
    assert(to_erase != nullptr);

    l.erase(*to_erase);


    auto* it = l.get_head();

    it = advance_equal(*it, 1);
    it = advance_equal(*it, 3);

    assert(it == nullptr);
}


void forward_iterate()
{
    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    
    auto* it = l.get_head();

    it = advance_equal(*it, 1);
    it = advance_equal(*it, 2);
    it = advance_equal(*it, 3);
    it = advance_equal(*it, 4);
    it = advance_equal(*it, 5);

    assert(it == nullptr);
}


void reverse_iterate()
{
    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    auto* it = l.get_tail();
    
    it = reverse_equal(*it, 3);
    it = reverse_equal(*it, 2);
    it = reverse_equal(*it, 1);

    assert(it == nullptr);
}

void reverse_iterate_after_erase()
{
    LinkedList<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    l.erase(2);

    auto* it = l.get_tail();
    
    it = reverse_equal(*it, 3);
    it = reverse_equal(*it, 1);
    
    assert(it == nullptr);
}

int main()
{
    add();
    erase_empty();
    erase_one_element();
    erase_middle();
    erase_head();
    erase_tail();
    erase_by_node();
    forward_iterate();
    reverse_iterate();
    reverse_iterate_after_erase();
    
    return 0;
}
