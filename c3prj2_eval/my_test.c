#include<stdio.h>
#include<stdlib.h>
#include "eval.h"
#include "deck.h"


int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  if ((*cp1)->value == (*cp2)->value) {
    return ((*cp2)->suit) - ((*cp1)->suit);
  }
  
  return ((*cp2)->value) - ((*cp1)->value);
}

char value_letter(card_t c) {
  char x='?';
  if ((c.value >= 2 )&&( c.value <=9)) x = '0' + c.value ;
  else {
    switch(c.value){
    case VALUE_KING : {x='K';  break;}
    case 10 : {   x='0';  break;}
    case VALUE_ACE :{ x= 'A' ;  break;}
    case VALUE_QUEEN :{x='Q' ; break;}
    case VALUE_JACK :{x='J' ; break;}
    default :break;
    }
  }
  return x ;
}


char suit_letter(card_t c) {
  char x='?';
  switch(c.suit){
  case  SPADES : {x='s';  break;}
  case HEARTS : {   x='h';  break;}
  case DIAMONDS :{ x= 'd' ;  break;}
  case CLUBS :{x='c' ; break;}
  default :{ x='N'; break;}
  }
  return x;

}

void print_card(card_t c) {
  char suit1= suit_letter( c);
  char value1= value_letter( c);
  printf("%c%c ",value1,suit1);
}

void print_hand(deck_t * hand){
  card_t **card = hand->cards;
  card_t temp;
  for(int i=0; i<(hand->n_cards); i++){
    temp = **card;
    print_card(temp);
    printf(" ");
    card++;
  }
}

suit_t flush_suit(deck_t * hand) {
  int suit_count[4] = {0};
  suit_t ans = NUM_SUITS;
  for (size_t i=0; i<(hand->n_cards); i++) {
    suit_count[hand->cards[i]->suit]++;
  }
  for (int i=0; i<4; i++) {
    if (suit_count[i] == 5) {
      ans = i;
      break;
    }
  }
  return ans;
}


int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  int count_straight = 0;
  int is_straight = 0;
  card_t *const *const cards = hand->cards;
  if (fs != NUM_SUITS && cards[index]->suit != fs) {
    return 0;
  }
  count_straight++;
  for (size_t i=index+1; i<(hand->n_cards); i++) {
    if (fs != NUM_SUITS) {
      if (cards[i]->suit != fs) {
	continue;
      }
    }
    if (cards[i]->value == cards[i-1]->value) {
      continue;
    }
    if (((cards[i]->value)+1) ==  cards[i-1]->value) {
      count_straight++;
    }

    if (count_straight == n) {
      is_straight = 1;
      break;
    }
  }

  return is_straight;
}

int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) {
  int is_ace_low_straight = 0;
  int has_ace_right_suit = 0;
  if (hand->cards[index]->value != 5) {
    return is_ace_low_straight;;
  }

  for (size_t i=0; i<index; i++) {
    if (hand->cards[i]->suit == fs) {
      has_ace_right_suit = 1;
      break;
    }
  }

  if (has_ace_right_suit == 1 || fs == NUM_SUITS) {
    is_ace_low_straight = is_n_length_straight_at(hand, index, fs, 4);
  }
  
  return -is_ace_low_straight;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  int is_straight = 0;
  is_straight = is_n_length_straight_at(hand, index, fs, 5);

  if (is_straight != 1 && hand->cards[0]->value==VALUE_ACE) {
    is_straight = is_ace_low_straight_at(hand, index, fs);
  }
  
  return is_straight;
}


int main() {
  card_t cards[] = {{3, SPADES}, {5, HEARTS}, {7, DIAMONDS}, {8, CLUBS}, {9, HEARTS}, {10, SPADES}, {12, CLUBS}};
  printf("card_0: value = %d, suit=%d\n",cards[0].value, cards[0].suit);
  card_t * ptr0 = &cards[0];
  card_t * ptr1 = &cards[1];
  card_t * ptr2 = &cards[2];
  card_t * ptr3 = &cards[3];
  card_t * ptr4 = &cards[4];
  card_t * ptr5 = &cards[5];
  card_t * ptr6 = &cards[6];
  card_t * set_ptr[7] = {ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6};
  deck_t hand_1 = {
    set_ptr,
    7
  };
  printf("Hand before being sorted:\n");
  print_hand(& hand_1);
  printf("\n");
  qsort(hand_1.cards, 7, sizeof(card_t *), card_ptr_comp);

  printf("Hand after being sorted:\n");
  print_hand(& hand_1);
  printf("\n");

  //Test 2
  printf("\nTest 2!\n");
  card_t cards2[] = {{2, SPADES}, {5, DIAMONDS}, {5, DIAMONDS}, {4, CLUBS}, {9, HEARTS}, {10, SPADES}, {14, CLUBS}};
  printf("card_0: value = %d, suit=%d\n",cards[0].value, cards[0].suit);
  ptr0 = &cards2[0];
  ptr1 = &cards2[1];
  ptr2 = &cards2[2];
  ptr3 = &cards2[3];
  ptr4 = &cards2[4];
  ptr5 = &cards2[5];
  ptr6 = &cards2[6];
  card_t * set_ptr_2[7] = {ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6};
  deck_t hand_2 = {
    set_ptr_2,
    7
  };
  printf("Hand before being sorted:\n");
  print_hand(& hand_2);
  printf("\n");
  qsort(hand_2.cards, 7, sizeof(card_t *), card_ptr_comp);

  printf("Hand after being sorted:\n");
  print_hand(& hand_2);
  printf("\n");
  // Test straight
  int index_straight = 3;
  int is_straight_test = is_straight_at(&hand_2, index_straight, NUM_SUITS);
  printf("Is the hand_2 straight at index %d? %d\n", index_straight, is_straight_test);
  

  
  //Test 3
  printf("\nTest 3!\n");
  card_t cards3[] = {{7, DIAMONDS}, {10, SPADES}, {6, SPADES}, {8, SPADES}, {4, CLUBS}, {5, CLUBS}, {11, SPADES}};
  printf("card_0: value = %d, suit=%d\n",cards3[0].value, cards3[0].suit);
  ptr0 = &cards3[0];
  ptr1 = &cards3[1];
  ptr2 = &cards3[2];
  ptr3 = &cards3[3];
  ptr4 = &cards3[4];
  ptr5 = &cards3[5];
  ptr6 = &cards3[6];
  card_t * set_ptr_3[7] = {ptr0, ptr1, ptr2, ptr3, ptr4, ptr5, ptr6};
  deck_t hand_3 = {
    set_ptr_3,
    7
  };
  printf("Hand before being sorted:\n");
  print_hand(& hand_3);
  printf("\n");
  qsort(hand_3.cards, 7, sizeof(card_t *), card_ptr_comp);

  printf("Hand after being sorted:\n");
  print_hand(& hand_3);
  printf("\n");
  
  // Test flush_suit
  printf("\nTest flush_suit function!\n");
  suit_t flush_suit_test = flush_suit(&hand_3);
  printf("Flush_suit of hand_3: %d\n", flush_suit_test);

  // Test is_straight_at
  index_straight = 3;
  is_straight_test = is_straight_at(&hand_3, index_straight, NUM_SUITS);
  printf("Is the hand_3 straight at index %d? %d\n", index_straight, is_straight_test);
  
  return EXIT_SUCCESS;
}
