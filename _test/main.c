#include <stdio.h>
#include <math.h>


static void colorSet(unsigned char colorArray[],float *colorPercent){

if (*colorPercent<=50) colorArray[0] = 255;
if (*colorPercent<=50) colorArray[1] = floor(((*colorPercent)/50)*255);

if (*colorPercent>50) colorArray[0] = floor(((*colorPercent-50)/50)*255);;
if (*colorPercent>50) colorArray[1] = 255;

printf("Red is %02x\n", colorArray[0]);
printf("Green is %02x\n\n", colorArray[1]);

}



int main(){

unsigned char colorArray[] = {0,0};
int x = 180;
float sin_of_x = 0;

for (int i = 0; i <= x; i++) {
  sin_of_x = 100*(sin(i*M_PI/180));
  printf("Setting color to %2f %% \n",sin_of_x);
  colorSet(colorArray,&sin_of_x);
}

return 0;

}
