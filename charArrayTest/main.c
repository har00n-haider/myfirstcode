#include <stdio.h>

void message_details(char msg[]){

  printf("First character of the message is: %c\n",msg[0]);
  printf("Message is: \n %s \n",msg);
  printf("Message pointer is %p \n",msg);
  printf("Message size is %i\n",sizeof(msg));

}

int main(){

system("clear");
char message[] = "Dude!";
message_details(message);
return 0;

}
