#include <stdio.h>

int main()

{
    char card_name[3];
    int count = 0;

    while (card_name[0]!='X') {
      puts("Enter the card name (X to exit): ");
      scanf("%2s", card_name);
      int val = 0;
      switch(card_name[0]){
        case 'K':
        case 'Q':
        case 'J':
          val = 10;
          break;
        case 'A':
          val = 11;
          break;
        case 'X':
          puts("You exited the program");
          break;
        default:
          val = atoi(card_name);
          if (val>10||val<1) {
            puts("Invalid card!");
            continue;
          }
      }
      if (val>2 && val <7) {
        count++;
      } else if (val==10){
        count--;
      }
      printf("Current count is  %i\n", count);
    }

    return 0;
}
