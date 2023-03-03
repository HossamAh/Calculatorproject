#include "linkedlist.h"
Node* create_node(int data,Node* next)
{

    Node* node = (Node*)malloc(sizeof(Node));
    node->data=data;
    node->next = next;
    return node;
}
void insert_node(int index,int data,linked_list* llist)
{
    if(index==0)
    {
        llist->head = create_node(data,llist->head);
    }
    else
    {
        Node* prev = llist->head;
        Node* current = llist->head->next;
        int i=1;
        for(i;i<index;i++)
        {
            prev = current;
            current = current->next;
        }
        prev->next = create_node(data,current);
    }
    //llist->count++;
}
void append_node(linked_list* llist,int data)
{
    Node* temp;
    if(llist->head!=NULL)
    {
        Node* current = llist->head;
        while(current->next !=NULL )
        {
            current = current->next;
        }
        Node* new_node = create_node(data,NULL);
        current->next = new_node;
    }
    else
    {
        temp = create_node(data,NULL);
        llist->head = temp;
    }
    //llist->count++;
}
Node* get_last(linked_list* llist)
{
    Node* current=llist->head;
    while(current->next !=NULL)
    {
        current=current->next;
    }
    return current;
}
Node* get_node(linked_list* llist,int index)
{
    Node* current = llist->head;
    int i=0;
    for(i;i<index;i++)
    {
        current = current->next;
    }
    return current;

}
void display_linkedlist(linked_list* llist)
{
    Node* current = llist->head;
    while(current != NULL)
    {
        printf("%d ",current->data);
        current = current->next;
    }
    printf("\n");
}

void delete_node(linked_list* llist,int index)
{
    if(index==0)
    {
        Node* temp = llist->head;
        llist->head = llist->head->next;
        free(temp);
    }
    else
    {
        Node* prev = llist->head;
        Node* current = llist->head->next;
        int i=1;
        for(i;i<index;i++)
        {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        free(current);
        return;
    }


}
void destroy_list(linked_list* llist)
{
    Node* current = llist->head;
    while(current != NULL)
    {
        Node* temp = current->next;
        free(current);
        current = temp;
    }
}

