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
  card_t * temp;
  int n_cards_gr;
  int ran_num=0;
  
  do {
    n_gr = rand()%7;
  } while (n_gr == 0 || n_gr == 1);
  n_cards_gr = (d->n_cards) / n_gr;
  for (int i=0; i<n_gr; i++) {
    for (size_t j=0; j<n_cards_gr; j++) { 
      ran_num = rand() % (d->n_cards);
      temp = d->cards[i*n_cards_gr + j];
      d->cards[i*n_cards_gr + j] = d->cards[ran_num];
      d->cards[ran_num] = temp;
    }
  }
  
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

void add_card_to(deck_t * deck, card_t c) {
  deck->cards = realloc((deck->n_cards + 1) * sizeof(*(deck->cards)));
  deck->cards[deck->n_cards] = malloc(sizeof(*(deck->cards[deck->n_cards])));
  *(deck->cards[deck->n_cards]) = c
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck) {
  card_t c = {0, NUM_SUITS};
  add_card_to(deck, c);
  return deck->cards[deck->n_cards};
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  card_t cur_card;
  deck * deck_exclude = NULL;
  deck_exclude = malloc(sizeof(*(deck_exclude)));
  deck_exclude->n_cards = 0;
  deck_exclude->cards = NULL;

  for (size_t i=0; i<52; i++) {
    cur_card = card_from_num(i);
    if (!deck_contains(excluded_cards, cur_card)) {
      add_card_to(deck_exclude, cur_card);
    }
  }

  return deck_exclude;
}

deck_t * build_remaining_deck (deck_t ** hands, size_t n_hands) {
  deck_t * remaining_deck = NULL;
  deck_t * deck_from_hands = malloc(sizeof(*(deck_from_hand)));
  deck_from_hands->n_cards = 0;
  deck_from_hands->cards = NULL;
  
  for (size_t hand_num=0; i<n_hands; i++) {
    for (size_t card_num=0; j<hands[i]->n_cards; j++) {
      add_card_to(deck_from_hands, *((hands[hand_num]->cards)[card_num]));
    }
  }
  remaining_deck = make_deck_exclude(deck_from_hand);
  return remaining_deck;
}

free_deck(deck_t * deck) {
  for (size_t i=0; i<deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
