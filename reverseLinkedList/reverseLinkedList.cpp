#include <iostream>
#include <memory>
#include <cstdint>

#define NODES_COUNT 100
class Node 
{
public:
    int value;
    Node* next;

    ~Node()
    {
        if(next != nullptr) {
            free(next);
        }
    }
};

void print_list(Node* head)
{
    if(head == nullptr) {
        std::cout<<"empty list"<<std::endl;
        return;
    }

    Node* curr = head;
    while(curr != NULL)
    {
        std::cout<<curr->value<<", address: "<<curr << ", next: "<<curr->next <<std::endl;
        curr = curr->next;
    }
    std::cout<<std::endl;
}

Node* createList(std::uint32_t listSize)
{
    if(listSize == 0) {
        std::cout <<"List can be created only with nonzero size"<<std::endl;
        return nullptr;
    }

    Node* head = new Node();
    head->value = 0;
    head->next = nullptr;
    Node* curr = head;
    for(std::uint32_t counter = 1; counter < listSize; ++counter)
    {
        curr->next = new Node();
        curr = curr->next;
        curr->value = counter;
    }
    return head; // returning the head of the list
}

/**
 * @brief Reverses the singly linked list and returns the new head
 * 
 * @param head 
 */
Node* reverseList(Node* head)
{
    if(head == nullptr || head->next == nullptr) {
        std::cout <<"List is empty"<<std::endl;
        return head;
    }

    Node* prev = head;
    Node* curr  = head->next;
    head->next = nullptr;
    Node* next = curr->next;

    while(curr != nullptr)
    {
        // std::cout<<"Exchanginging the nodes"<<std::endl;
        Node* currNext = curr->next;
        curr->next = prev;
        prev = curr;
        curr = currNext;
    }
    return prev;
}

int main() {
    std::cout << "!!!Hello World to reverse linked list!!!" << std::endl; // print

    Node* head = createList(0);

    print_list(head);

    head = createList(10);

    print_list(head);

    head = reverseList(head);

    print_list(head);

    return 0;
}