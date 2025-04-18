#include "queue.h"
#include "tile_game.h"
#include <stdbool.h>
#include <stdlib.h>

void enqueue(struct queue *q, struct game_state state)
{
  uint64_t serialized_state = serialize(state);
  
  bool in_queue = false;

  struct list_node *curr = q->data.head;

  while(curr != NULL)
  {
    if(curr->value == (size_t)serialized_state)
    {
      in_queue = true;
      break;
    }

    curr = curr->next;
  }
  
  if(!in_queue)
  {
    insert_at_tail(&q->data, serialized_state);
  }
}

struct game_state dequeue(struct queue *q)
{
  size_t val = (size_t)remove_from_head(&q->data);
  return (struct game_state)deserialize(val);
}

bool identical(struct game_state state)
{
  uint8_t count = 1;
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      if(state.tiles[i][j] != count)
      {
        return false;
      }
      count = (count + 1) % 16;
    }
  }

  return true;
}

bool duplicate(struct linked_list *seen, struct game_state state)
{ 
  if(seen->head == NULL)
  {
    insert_at_tail(seen, serialize(state));
    return false;
  }

  struct list_node *curr = seen->head;
  while(curr != NULL)
  {
    bool is_duplicate = true;
    struct game_state comp_state = deserialize((size_t)curr->value);
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        if(comp_state.tiles[i][j] != state.tiles[i][j])
        {
          is_duplicate = false;
          break;
        }
      }
      if(!is_duplicate)
      {
        break;
      }
    }

    if(is_duplicate)
    {
      return true;
    }

    curr = curr->next;
  }

  insert_at_tail(seen, serialize(state));

  return false;
}

int number_of_moves(struct game_state start)
{
  struct list_node *state_head_q = malloc(sizeof(struct list_node));
  state_head_q->value = serialize(start);
  state_head_q->next = NULL;

  struct queue q = {.data.head = state_head_q};

  while(q.data.head != NULL)
  {
    struct game_state curr_state = dequeue(&q);
    if(identical(curr_state))
    {
      free_list(q.data);
      return curr_state.num_steps;
    }
    else
    {
      struct game_state up_state = curr_state;
      struct game_state down_state = curr_state;
      struct game_state left_state = curr_state;
      struct game_state right_state = curr_state;

      move_up(&up_state);
      move_down(&down_state);
      move_left(&left_state);
      move_right(&right_state);

      enqueue(&q, up_state);
      enqueue(&q, down_state);
      enqueue(&q, left_state);
      enqueue(&q, right_state);  
    }
  }

  return 0;
}
