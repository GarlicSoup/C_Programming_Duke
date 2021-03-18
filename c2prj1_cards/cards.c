#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert((c.value >= 2) && (c.value<=VALUE_ACE));
  assert((c.suit >= SPADES) && (c.suit <= CLUBS));
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r) {
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  default: return "NOTHING";
  }
}

char value_letter(card_t c) {
  char ans;
  if (c.value >= 2 && c.value <=9) {
    ans = '0' + c.value;
  }
  else {
    switch(c.value) {
    case 10: ans = '0'; break;
    case VALUE_JACK: ans = 'J'; break;
    case VALUE_QUEEN: ans = 'Q'; break;
    case VALUE_KING: ans = 'K'; break;
    case VALUE_ACE: ans = 'A'; break;
    default: ans = '!';
    }
  }
  return ans;
}


char suit_letter(card_t c) {
  char suit;
  switch(c.suit) {
  case SPADES: suit = 's'; break;
  case HEARTS: suit = 'h'; break;
  case DIAMONDS: suit = 'd'; break;
  case CLUBS: suit = 'c'; break;
  default: suit = '!';
  }
  return suit;
}

void print_card(card_t c) {
  char value = value_letter(c);
  char suit = suit_letter(c);
  printf("%c%c", value, suit);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t card;
  unsigned value_num;

  // Assign numerical value of input value from character value
  if (value_let >= '2' && value_let <= '9') {
    value_num = value_let - '0';
  }
  else {
    switch(value_let) {
    case '0': value_num = 10; break;
    case 'J': value_num = VALUE_JACK; break;
    case 'Q': value_num = VALUE_QUEEN; break;
    case 'K': value_num = VALUE_KING; break;
    case 'A': value_num = VALUE_ACE; break;
    default: value_num = 99999999;
    }
  }
  card.value = value_num;

  // Get right suit for card from input letter of suit
  switch(suit_let) {
  case 's': card.suit = SPADES; break;
  case 'h': card.suit = HEARTS; break;
  case 'd': card.suit = DIAMONDS; break;
  case 'c': card.suit = CLUBS; break;
  default: card.suit = NUM_SUITS;
  }

  assert_card_valid(card);
  
  return card;
}

card_t card_from_num(unsigned c) {
  card_t card;
  assert((c >= 0) || (c <52));
  if (c < 13) {
    card.suit = SPADES;
    card.value = c%13 + 2;
  }
  else if ((c >= 13) && (c < 26)) {
    card.suit = HEARTS;
    card.value = c%13 + 2;
  }
  else if ((c >= 26) && (c < 39)) {
    card.suit = DIAMONDS;
    card.value = c%13 + 2;
  }
  else {
    card.suit = CLUBS;
    card.value = c%13 + 2;
  }
  
  return card;
}
