#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double calculate_balance(int current_age, double balance, retire_info plan) {
  printf("Age %3d month %2d you have $%.2lf\n", current_age/12, current_age%12, balance);
  balance = balance + balance*plan.rate_of_return + plan.contribution;
  return balance;
}

void retirement (int startAge, double initial, retire_info working, retire_info retired) {
  double account_balance = initial;
  for (int month=startAge; month<startAge+working.months; month++) {
    account_balance = calculate_balance(month, account_balance, working);
  }
  for (int month=startAge+working.months; month<startAge+working.months+retired.months; month++) {
    account_balance = calculate_balance(month, account_balance, retired);
  }
}

int main() {
  retire_info working = {
    .months = 489,
    .contribution = 1000,
    .rate_of_return = 0.045/12
  };
  
  retire_info retired = {384, -4000, 0.01/12};
  int starAge = 327;
  double initial = 21345;
  retirement(starAge, initial, working, retired);
  return 1;
}
