#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);

/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function.
  game_state_t* default_state=(game_state_t*)malloc(sizeof(game_state_t));
  default_state->num_rows=18;
  
  char first[21]="####################\0";
  char other[21]="#                  #\0";
  char **default_board=malloc(default_state->num_rows*sizeof(char*));
  for(int i=0;i<default_state->num_rows;i++){
    default_board[i]=(char*)malloc(21*sizeof(char));
  }
  strcpy(default_board[0],first);
  strcpy(default_board[17],first);
  for(int i=1;i<17;i++){
    strcpy(default_board[i],other);
  }
  
  default_state->board=default_board;

  default_state->num_snakes=1;

  snake_t* default_snake=malloc(default_state->num_snakes*sizeof(snake_t));
  default_snake[0].tail_row=2;
  default_snake[0].tail_col=2;
  default_snake[0].head_row=2;
  default_snake[0].head_col=4;
  default_snake[0].live=true;

  default_state->snakes=default_snake;

  set_board_at(default_state,default_snake[0].tail_row,default_snake[0].tail_col,'d');
  set_board_at(default_state,2,3,'>');
  set_board_at(default_state,default_snake[0].head_row,default_snake[0].head_col,'D');
  set_board_at(default_state,2,9,'*');

  return default_state;
}

/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function.
  free(state->snakes);
  for(int i=0;i<state->num_rows;i++){
    free(state->board[i]);
  }
  free(state->board);
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.
  for(int i=0;i<state->num_rows;i++){
    fprintf(fp,"%s\n",state->board[i]);
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  if (c=='w' || c=='a' || c=='s' || c=='d'){
    return true;
  }else{
    return false;
  }
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  if (c=='W' || c=='A' || c=='S' || c=='D' || c=='x'){
    return true;
  }else{
    return false;
  }
}

/*
  Returns true if c is part of the snake's body.
  The snake consists of these characters: "^<v>"
*/

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  if (c=='<'|| c=='>'|| c=='^'|| c=='v'|| is_head(c) || is_tail(c)){
    return true;
  }else{
    return false;
  } 
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  if (c=='<'|| c=='>'|| c=='^'|| c=='v'){
    char body[4]={'^','<','v','>'};
    char tail[4]={'w','a','s','d'};
    int index=0;
    while(index<4){
      if (body[index]==c)
        break;
      index+=1;
    }
    return tail[index];
  }else{
    return '?';
  }
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  if ( c!='x' && is_head(c)){
    char body[4]={'^','<','v','>'};
    char head[4]={'W','A','S','D'};
    int index=0;
    while(index<4){
      if (head[index]==c)
        break;
      index+=1;
    }
    return body[index];
  }else{
    return '?';
  }
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  if (c=='v' || c=='s' || c=='S'){
    return cur_row+1;
  }else if(c== '^' || c=='w' || c=='W'){
    return cur_row-1;
  }else{
    return cur_row;
  }
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if (c=='>' || c=='d' || c=='D'){
    return cur_col+1;
  }else if(c=='<' || c=='a' || c=='A'){
    return cur_col-1;
  }else{
    return cur_col;
  }
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int current_row=state->snakes[snum].head_row;
  unsigned int current_col=state->snakes[snum].head_col;
  
  char head=get_board_at(state,current_row,current_col);
  char next;
  if (head=='W' || head=='S'){
    unsigned int next_row=get_next_row(current_row,head);
    next=get_board_at(state,next_row,current_col);
  }else{
    unsigned int next_col=get_next_col(current_col,head);
    next=get_board_at(state,current_row,next_col);
  }
  return next;
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int current_row=state->snakes[snum].head_row;
  unsigned int current_col=state->snakes[snum].head_col;

  char head=get_board_at(state,current_row,current_col);
  set_board_at(state,current_row,current_col,head_to_body(head));

  if (head=='W' || head=='S'){
    unsigned int next_row=get_next_row(current_row,head);
    set_board_at(state,next_row,current_col,head);
    state->snakes[snum].head_row=next_row;
  }else{
    unsigned int next_col=get_next_col(current_col,head);
    set_board_at(state,current_row,next_col,head);
    state->snakes[snum].head_col=next_col;
  }
  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int current_row=state->snakes[snum].tail_row;
  unsigned int current_col=state->snakes[snum].tail_col;

  char tail=get_board_at(state,current_row,current_col);
  set_board_at(state,current_row,current_col,' ');

  if (tail=='w' || tail=='s'){
    unsigned int next_row=get_next_row(current_row,tail);
    char body=get_board_at(state,next_row,current_col);
    set_board_at(state,next_row,current_col,body_to_tail(body));
    state->snakes[snum].tail_row=next_row;
  }else{
    unsigned int next_col=get_next_col(current_col,tail);
    char body=get_board_at(state,current_row,next_col);
    set_board_at(state,current_row,next_col,body_to_tail(body));
    state->snakes[snum].tail_col=next_col;
  }

  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  for(unsigned int snum=0;snum<state->num_snakes;snum++){
    char next=next_square(state,snum);
    if (next=='#' || is_snake(next)){
      set_board_at(state,state->snakes[snum].head_row,state->snakes[snum].head_col,'x');
      state->snakes[snum].live=false;
    }else if(next=='*'){
      update_head(state,snum);
      add_food(state);
    }else{
      update_head(state,snum);
      update_tail(state,snum);
    }
  }
  return;
}

/*Conut number of line in given file*/
unsigned int count_rows(char* filename){
  FILE* file=fopen(filename, "r");
  unsigned int rows=0;
  int ch = fgetc(file);
  while(ch != EOF){
    if(ch == '\n'){
      rows+=1;
    }
    ch = fgetc(file);
  }
  fclose(file);
  return rows;
}

/*Count number of column in each line*/
void count_columns(char* filename,unsigned int* array){
  FILE* file=fopen(filename, "r");
  unsigned int count=0;
  int index=0;
  int ch = fgetc(file);
  while(ch != EOF){
    count+=1;
    if(ch == '\n'){
      array[index]=count;
      count=0;
      index+=1;
    }
    ch = fgetc(file);
  }
  fclose(file);
}

/* Task 5 */
game_state_t* load_board(char* filename) {
  // TODO: Implement this function.
  FILE* file=fopen(filename, "r");
  game_state_t* load=malloc(sizeof(game_state_t));
  load->num_rows=count_rows(filename);

  char** board=malloc(load->num_rows*sizeof(char*));
  unsigned int array[load->num_rows];
  count_columns(filename,array);
  for (int i=0;i<load->num_rows;i++){
    board[i]=malloc(array[i]*sizeof(char));
  }
  
  for(int i=0;i<load->num_rows;i++){
    for(int j=0;j<array[i];j++){
      char ch=(char)fgetc(file);
      if (ch=='\n'){
        board[i][j]='\0';
      }else{
        board[i][j]=ch;
      }
    }
  }
  load->board=board;
  load->snakes=NULL;
  load->num_snakes=0;
  return load;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  unsigned int current_row=state->snakes[snum].tail_row;
  unsigned int current_col=state->snakes[snum].tail_col;
  char current=get_board_at(state,current_row,current_col);
  while (!is_head(current)){
    current_row=get_next_row(current_row,current);
    current_col=get_next_col(current_col,current);

    current=get_board_at(state,current_row,current_col);
  }
  state->snakes[snum].head_row=current_row;
  state->snakes[snum].head_col=current_col;
  return;
}

//get number of snakes at current state

unsigned int get_snum(game_state_t* state){
  unsigned int snum=0;
   for(unsigned int current_row=0;current_row<state->num_rows;current_row++){
    unsigned int current_col=0;
    while(state->board[current_row][current_col]!='\0'){
      if (is_tail(state->board[current_row][current_col])){
        snum+=1;
      }
      current_col+=1;
    }
  }
  return snum;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  state->num_snakes=get_snum(state);
  snake_t* initial_snakes=malloc(state->num_snakes*sizeof(snake_t));
  state->snakes=initial_snakes;
  unsigned int snake_index=0;

  for(unsigned int current_row=0;current_row<state->num_rows;current_row++){
    unsigned int current_col=0;
    while(state->board[current_row][current_col]!='\0'){
      if (is_tail(state->board[current_row][current_col])){
        initial_snakes[snake_index].tail_row=current_row;
        initial_snakes[snake_index].tail_col=current_col;
        initial_snakes[snake_index].live=true;
        find_head(state,snake_index);
        snake_index+=1;
      }
      current_col+=1;
    }
  }
  return state;
}
