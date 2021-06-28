#include <stdio.h>
#include <math.h>

static void printHead(FILE *output_file, int *ptr_number_of_rectangles){

  float colorInputPercent = 0;
  unsigned char colorArray[] = {0,0};

    // Print the header start
  fprintf(output_file, "  <head>\n");
  fprintf(output_file, "    <style>\n");

  //Set and print the colors
  for (int i = 1; i <= *ptr_number_of_rectangles; i++) {

    colorInputPercent = 100*(sin(i*M_PI/180));
    printf("Setting color to %2f %% \n",colorInputPercent);

    if (colorInputPercent<=50) colorArray[0] = 255;
    if (colorInputPercent<=50) colorArray[1] = floor(((colorInputPercent)/50)*255);

    if (colorInputPercent>50) colorArray[0] = floor(((50-colorInputPercent)/50)*255);;
    if (colorInputPercent>50) colorArray[1] = 255;

    fprintf(output_file, "    #rectangle%i\n",i);
    fprintf(output_file, "    {\n");
    fprintf(output_file, "    width:auto;\n");
    fprintf(output_file, "    height:10px;\n");
    fprintf(output_file, "    background:#%02x%02x00;\n",colorArray[0],colorArray[1]);
    fprintf(output_file, "    }\n");

  }

  //Print the header end
  fprintf(output_file, "    </style>\n");
  fprintf(output_file, "  <head>\n");

}

static void printBody(FILE *output_file, int *ptr_number_of_rectangles){

  fprintf(output_file, "  <body>\n");

  //Loop for number of rectangles
  for (int i = 1; i <= *ptr_number_of_rectangles; i++) {

    fprintf(output_file, "    <div id=\"rectangle%i\"></div>\n",i);

  }

  fprintf(output_file, "  </body>\n");

}

int main() {

  int number_of_rectangles = 180;
  FILE *output_file = fopen("colorGradient.html","w");

  //Print the html header
  fprintf(output_file,"<!doctype>\n");
  fprintf(output_file,"<html>\n");

  //Print the CSS code for rectangles
  printHead(output_file, &number_of_rectangles);

  //Print the body of HTML code
  printBody(output_file, &number_of_rectangles);

  //Print the footer
  fprintf(output_file,"</html>\n");

  // Clean up
  fclose(output_file);

  return 0;
}
