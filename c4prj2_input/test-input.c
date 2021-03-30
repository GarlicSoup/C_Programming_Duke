#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


void free_future_cards(future_cards_t * fc) {
  if (fc == NULL) {
    printf("Nothing in the future cards!\n");
    return;
  }
  for (size_t i=0; i<fc->n_decks; i++) {
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    perror("Uasge: thisProgram inputFile\n");
    return EXIT_FAILURE;
  }

  deck_t ** hands = NULL;
  size_t n_hands = 0;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  FILE * f = fopen(argv[1], "r");
  hands = read_input(f, &n_hands, fc);

  if (hands == NULL) {
    perror("Error: hands is NULL!\n");
    return EXIT_FAILURE;
  }
  
  for (size_t i=0; i<n_hands; i++) {
    printf("\nPrint hand %zu :\n",i);
    print_hand(hands[i]);
    printf("\n");
  }

  for (size_t i=0; i<n_hands; i ++) {
    free_deck(hands[i]);
  }
  free(hands);

  free_future_cards(fc); 
  
  return EXIT_SUCCESS;
}
