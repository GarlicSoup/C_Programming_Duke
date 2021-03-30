#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include <assert.h>
#include <ctype.h>

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t *cur_deck = NULL;
  cur_deck = malloc(sizeof(*cur_deck));
  cur_deck->n_cards = 0;
  cur_deck->cards = NULL;
  char *p=strchr(str,'\n');
  if(p!=NULL){
    *p='\0';
  }
  // printf("%s\n", str);
  // printf("hand string length %zu\n", strlen(str));
  for (size_t i=0; i<strlen(str)+1; i++) {
    if (str[i+1] == '\0' || str[i] == '\0') {
      break;
    }
    if (str[i+1] == ' ' || str[i] == ' ') {
      continue;
    }
      
    if (str[i] != '?') {
      card_t card = card_from_letters(str[i], str[i+1]);
      add_card_to(cur_deck, card);
      //print_card(card);
      //printf("\n");
    }
    else if (str[i] == '?' && isdigit(str[i+1])) {
      //printf("Should not have this!\n");
      card_t * empty_card = add_empty_card(cur_deck);
      print_card(*empty_card);
      printf("\n");
      add_future_card(fc, str[i+1], empty_card);
    }
    else {
      fprintf(stderr,"Error: Invalid input file format, line %s",str);
      card_from_letters(0,0);
    }
  }
  // print_hand(cur_deck);
  
  return cur_deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  char * line = NULL;
  size_t sz = 0;
  deck_t ** deck = malloc(sizeof(*deck));
  if (f == NULL) {
    perror("Error: Could not read file");
    exit(EXIT_FAILURE);
  }
  while (getline(&line, &sz, f) >= 0) {
    (*n_hands)++;
    deck = realloc(deck, (*n_hands)* sizeof(*deck));
    assert(deck != NULL);
    deck_t * cur_deck = hand_from_string(line, fc);
    deck[*n_hands-1] = cur_deck;
    //print_hand(cur_deck);
    if(deck[(*n_hands)-1]->n_cards<5){
      fprintf(stderr,"Error: Invalid number of cards in input file\n");
      exit(EXIT_FAILURE);
    }
    free(line);
    line=NULL;
  }
  free(line);

  if (fclose(f) != 0) {
    perror("Error: Could not close file!\n");
    exit(EXIT_FAILURE);
  }
  return deck;
}
