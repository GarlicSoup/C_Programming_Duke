#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  for (size_t i=0; i<hand->n_cards; i ++) {
    print_card(*(hand->cards[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  int is_contained = 0;
  for (size_t i=0; i<d->n_cards; i++) {
    if (d->cards[i]->value == c.value && d->cards[i]->suit == c.suit) {
      is_contained++;
    }
  }
  return is_contained;;
}

void shuffle(deck_t * d){
  // Separate the deck into n groups
  // randomly shuffle each group with another one
  int n_gr;
  int cur_gr;
  card_t * temp;
  size_t n_cards_gr;
  int ran_num=0;
  
  do {
    n_gr = rand()%7;
  } while (n_gr == 0 || n_gr == 1);
  n_cards_gr = (d->n_cards) / n_gr;
  for (int i=0; i<n_gr; i++) {
    cur_gr = rand() % n_gr;
    while (cur_gr == i) {
      cur_gr = rand() % n_gr;
    }
    for (size_t j=0; j<n_cards_gr; j++) { 
      ran_num = rand() % n_cards_gr;
      temp = d->cards[i*n_cards_gr + j];
      d->cards[i*n_cards_gr + j] = d->cards[cur_gr*n_cards_gr + ran_num];
      d->cards[cur_gr*n_cards_gr + ran_num] = temp;
    }
  }

  /* n_gr = 3; */
  /* n_cards_gr = (d->n_cards) / n_gr; */
  /* for (int i=0; i<n_gr; i++) { */
  /*   cur_gr = rand() % n_gr; */
  /*   while (cur_gr == i) { */
  /*     cur_gr = rand() % n_gr; */
  /*   } */
  /*   for (size_t j=0; j<n_cards_gr; j++) { */
  /*     ran_num = rand() % n_cards_gr; */
  /*     temp = d->cards[i*n_cards_gr + j]; */
  /*     d->cards[i*n_cards_gr + j] = d->cards[cur_gr*n_cards_gr + ran_num]; */
  /*     d->cards[cur_gr*n_cards_gr + ran_num] = temp; */
  /*   } */
  /* } */

  for (size_t i=0; i<(d->n_cards); i++) {
    temp = d->cards[i];
    do {
      ran_num = rand() % (d->n_cards);
    } while (ran_num == i);
    d->cards[i] = d->cards[ran_num];
    d->cards[ran_num] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  unsigned rep[52]={0};
  card_t cur_card;
  for(unsigned i=0; i<52; i++){
    cur_card = card_from_num(i);
    assert_card_valid(cur_card);
    if(deck_contains(d,cur_card)){
      rep[i]++;
    }
  }
  for(unsigned i=0; i<52; i++){
    cur_card = card_from_num(i);
    if(rep[i] > 1){
      printf("Duplicate card:");
      print_card(cur_card);
      printf("\n");
      assert(rep[i] == 1);
    }
    if (rep[i] == 0) {
      printf("The card ");
      print_card(cur_card);
      printf(" was not found");
      printf("\n");
      assert(rep[i] == 1);
    }
  }
}
