#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { return NULL; }

void insert_at_head(struct linked_list *list, size_t value)
{
  struct list_node *new = malloc(sizeof(struct list_node));

  new->value = value;

  if(list->head == NULL)
  {
    new->next = NULL;
    list->head = new;
    return;
  }

  new->next = list->head;
  list->head = new;
}

void insert_at_tail(struct linked_list *list, size_t value)
{
  struct list_node *new = malloc(sizeof(struct list_node));

  new->value = value;
  new->next = NULL;

  if(list->head == NULL)
  {
    list->head = new;
    return;
  }

  struct list_node *curr = list->head;

  while(curr->next != NULL)
  {
    curr = curr->next;
  }

  curr->next = new;
}

size_t remove_from_head(struct linked_list *list)
{
  if(list == NULL || list->head == NULL)
  {
    return 0;
  }

  size_t val = list->head->value;

  if(list->head->next == NULL)
  {
    free(list->head);
    list->head = NULL;
    return val;
  }
   
  struct list_node *next = list->head->next;
  free(list->head);
  list->head = next;

  return val;

}

size_t remove_from_tail(struct linked_list *list)
{ 
  if(list == NULL || list->head == NULL)
  { 
    return 0;
  }
  
  struct list_node *curr = list->head;

  if(curr->next == NULL)
  { 
    size_t val = curr->value;
    free(curr);
    list->head = NULL;
    return val;
  }
  
  while(curr->next->next != NULL)
  { 
    curr = curr->next;
  }
 
  size_t val = curr->next->value;
  free(curr->next);
  curr->next = NULL;

  return val;
}

void free_list(struct linked_list list)
{
  struct list_node *curr = list.head;
  
  while(curr != NULL)
  {
    struct list_node *next = curr -> next;
    free(curr);
    curr = next;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
