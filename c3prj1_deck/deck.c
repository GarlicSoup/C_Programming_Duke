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
  int n_gr = 2;
  int cur_gr;
  int do_shuffle=0;
  card_t * temp;
  size_t n_cards_gr = (d->n_cards) / n_gr;
  int ran_num=0;
  
  for (int i=0; i<n_gr; i++) {
    cur_gr = rand() % n_gr;
    while (cur_gr == i) {
      cur_gr = rand() % n_gr;
    }
    for (size_t j=0; j<n_cards_gr; j++) { 
      ran_num = rand() % n_cards_gr;
      do_shuffle = 1;
      if (do_shuffle == 1) {
	temp = d->cards[i*n_cards_gr + j];
	d->cards[i*n_cards_gr + j] = d->cards[cur_gr*n_cards_gr + ran_num];
	d->cards[cur_gr*n_cards_gr + ran_num] = temp;
      }
    }
  }

  n_gr = 5;
  n_cards_gr = (d->n_cards) / n_gr;
  for (int i=0; i<n_gr; i++) {
    cur_gr = rand() % n_gr;
    while (cur_gr == i) {
      cur_gr = rand() % n_gr;
    }
    for (size_t j=0; j<n_cards_gr; j++) {
      ran_num = rand() % n_cards_gr;
      do_shuffle = 1;
      if (do_shuffle == 1) {
	temp = d->cards[i*n_cards_gr + j];
	d->cards[i*n_cards_gr + j] = d->cards[cur_gr*n_cards_gr + ran_num];
	d->cards[cur_gr*n_cards_gr + ran_num] = temp;
      }
    }
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
