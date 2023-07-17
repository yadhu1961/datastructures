#include "LinkedList.h"

#include <iostream>

int main()
{
    std::cout << "!!!Hello World to reverse linked list!!!" << std::endl; // print

    LinkedList<int> list = LinkedList<int>();

    list.addElement(2);

    list.print_list();

    list.addElement(3);

    list.print_list();

    list.addElement(1);

    list.print_list();

    list.reverseList();

    list.print_list();

    list.sort();

    list.print_list();

    list.deleteNodeGivenValue(3);

    list.print_list();

    list.deleteNodeGivenValue(10);

    list.print_list();

    list.deleteNodeGivenValue(1);

    list.print_list();

    return 0;
}