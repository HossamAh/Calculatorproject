#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#define NULL ((void*)0)
struct Node
{
    int data;
    struct Node* next;
};
struct linked_list
{
    struct Node* head;
    int count;
};
typedef struct Node Node;
typedef struct linked_list linked_list;

Node* create_node(int data,Node* next);
void insert_node(int index,int data,linked_list* llist);
void append_node(linked_list* llist,int data);
void display_linkedlist(linked_list* llist);
void delete_node(linked_list* llist,int index);
void destroy_list(linked_list* llist);
Node* get_node(linked_list* llist,int index);
Node* get_last(linked_list* llist);
#endif // LINKEDLIST_H_INCLUDED
