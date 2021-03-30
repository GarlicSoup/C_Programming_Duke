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
  for (size_t i=0; i<strlen(str)+1; i++) {
    if (str[i+1] == '\0' || str[i] == '\0') {
      break;
    }
    if (str[i+1] == ' ' || str[i] == ' ') {
      continue;
    }
      
    if ((isdigit(str[i]) || str[i]=='A' || str[i]=='K' || str[i]=='Q' || str[i]=='J') && (str[i+1]=='s' || str[i+1]=='h' || str[i+1]=='d' || str[i+1]=='c')) {
      card_t card = card_from_letters(str[i], str[i+1]);
      add_card_to(cur_deck, card);
    }
    else if (str[i] == '?' && isdigit(str[i+1])) {
      /* card_t * empty_card = add_empty_card(cur_deck); */
      /* print_card(*empty_card); */
      /* printf("\n"); */
      /* add_future_card(fc, str[i+1], empty_card); */
      char *number=malloc(2*sizeof(*number));
      assert(number!=NULL);
      size_t j=0;
      number[j++]=str[i+1];
      number[j]='\0';
      if(isdigit(str[i+2])){
	number=realloc(number,3*sizeof(*number));
	assert(number!=NULL);
	number[j++]=str[i+2];
	number[j]='\0';
	i++;
      }
      add_future_card(fc,atoi(number),add_empty_card(cur_deck));
      free(number);
    }
    else {
      fprintf(stderr,"Error: Invalid input file format, line %s",str);
      card_from_letters(0,0);
    }
  }
  return cur_deck;

  
  /* deck_t *ans=malloc(sizeof(*ans)); */
  /* assert(ans!=NULL); */
  /* ans->cards=NULL; */
  /* ans->n_cards=0; */
  /* size_t i=0; */
  /* while(str[i]!='\0'){ */
  /*   if(str[i]=='?' && isdigit(str[i+1])){ */
  /*     char *number=malloc(2*sizeof(*number)); */
  /*     assert(number!=NULL); */
  /*     size_t j=0; */
  /*     number[j++]=str[i+1]; */
  /*     number[j]='\0'; */
  /*     if(isdigit(str[i+2])){ */
  /* 	number=realloc(number,3*sizeof(*number)); */
  /* 	assert(number!=NULL); */
  /* 	number[j++]=str[i+2]; */
  /* 	number[j]='\0'; */
  /* 	i++; */
  /*     } */
  /*     add_future_card(fc,atoi(number),add_empty_card(ans)); */
  /*     free(number); */
  /*   } */
  /*   else if((isdigit(str[i]) || str[i]=='A' || str[i]=='K' || str[i]=='Q' || str[i]=='J') && (str[i+1]=='s' || str[i+1]=='h' || str[i+1]=='d' || str[i+1]=='c')){ */
  /*     add_card_to(ans,card_from_letters(str[i],str[i+1])); */
  /*   } */
  /*   else{ */
  /*     fprintf(stderr,"Error: Invalid input file format, line %s",str); */
  /*     card_from_letters(0,0); */
  /*   } */
  /*   i++; */
  /*   while(isspace(str[i+1]) && str[i+1]!='\0'){ */
  /*     i++; */
  /*   } */
  /*   i++; */
  /* } */
  /* return ans; */
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  /* char * line = NULL; */
  /* size_t sz = 0; */
  /* deck_t ** deck = malloc(sizeof(*deck)); */
  /* if (f == NULL) { */
  /*   perror("Error: Could not read file"); */
  /*   exit(EXIT_FAILURE); */
  /* } */
  /* while (getline(&line, &sz, f) >= 0) { */
  /*   (*n_hands)++; */
  /*   deck = realloc(deck, (*n_hands)* sizeof(*deck)); */
  /*   assert(deck != NULL); */
  /*   deck_t * cur_deck = hand_from_string(line, fc); */
  /*   deck[*n_hands-1] = cur_deck; */
  /*   //print_hand(cur_deck); */
  /*   if(deck[(*n_hands)-1]->n_cards<5){ */
  /*     fprintf(stderr,"Error: Invalid number of cards in input file\n"); */
  /*     exit(EXIT_FAILURE); */
  /*   } */
  /*   free(line); */
  /*   line=NULL; */
  /* } */
  /* free(line); */

  /* if (fclose(f) != 0) { */
  /*   perror("Error: Could not close file!\n"); */
  /*   exit(EXIT_FAILURE); */
  /* } */
  /* return deck; */
  
  deck_t **ans=NULL;
  /**n_hands=0;*/

  char *line=NULL;
  size_t sz=0;
  while(getline(&line,&sz,f)>=0){
    char *p=strchr(line,'\n');
    if(p!=NULL){
      *p='\0';
    }
    else{
      fprintf(stderr,"Error: Invalid line '%s' in input file!\n",line);
      assert(p!=NULL);
    }
    ans=realloc(ans,((*n_hands)+1)*sizeof(*ans));
    assert(ans!=NULL);
    (*n_hands)++;
    ans[(*n_hands)-1]=hand_from_string(line,fc);
    if(ans[(*n_hands)-1]->n_cards<5){
      fprintf(stderr,"Error: Invalid number of cards in input file\n");
      assert(ans[(*n_hands)-1]->n_cards>=5);
    }
    free(line);
    sz=0;
  }
  free(line);

  return ans;
}
