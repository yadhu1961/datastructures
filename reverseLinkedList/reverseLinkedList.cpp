//============================================================================
// Name        : reverseLinkedList.cpp
// Author      : Yadu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#define NODES_COUNT 100

using namespace std;

struct node {
	int value;
	node *next;
};

void print_list(struct node *head)
{
	struct node *curr = head;
	while(curr != NULL)
	{
		cout<<curr->value<<endl;
		curr = curr->next;
	}
}

int main() {
	cout << "!!!Hello World to reverse linked list!!!" << endl; // print

	struct node *prev = NULL,*head = NULL,*curr = NULL,*next = NULL;

	//Special handling is needed for tail, hence doing outside the loop.
	curr = (struct node*) malloc(sizeof(struct node));
	curr->value = NODES_COUNT - 1;
	curr->next = NULL;
	prev = curr;

	for(int i = NODES_COUNT - 2; i >= 0 ; i--)
	{
		curr = (struct node*) malloc(sizeof(struct node));
		curr->value = i;
		curr->next = prev;
		prev = curr;
	}
	head = curr; //last created node is the head of the list.

	print_list(head);

	//Special handling is needed for head, hence doing outside the loop.
	curr = head;
	next = curr->next;
	curr->next = NULL;
	curr = next;
	prev = head;

	while(next != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	head = curr = prev;
	cout<<"Reversed List"<<endl;
	print_list(head);

	return 0;
}
