#include "cards.h"
#include <stdio.h>

int main(void) {
  // Test assert
  card_t card = {12, SPADES};
  //assert_card_valid(card);

  // Test raking_to_string
  hand_ranking_t ranking = STRAIGHT_FLUSH;
  printf("%s\n", ranking_to_string(ranking));

  hand_ranking_t ranking1 = 111;
  printf("%s\n", ranking_to_string(ranking1));

  // Test print_card
  print_card(card);

  // Test card from letter
  card_t card_1 = card_from_letters('J', 's');
  print_card(card_1);
  
  return 0;
}
