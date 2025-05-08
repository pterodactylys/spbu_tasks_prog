#include "src/doubly_linked_list.hpp"
#include <iostream>

using abc::DoublyLinkedList;

int main() {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.remove_first(2);
    DoublyLinkedList<int> list2 = list;
    DoublyLinkedList<int> list3(list);
    list2.push_back(6);
    list3.print();
    std::cout << std::endl;
    list.print();
}
