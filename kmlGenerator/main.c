#include <stdio.h>
#include <math.h>

static void printCircle();

int main() {

  FILE *output_file = fopen("output.kml","w");

  //print KML header

  fprintf(output_file,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
  fprintf(output_file,"<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
  fprintf(output_file,"  <Document>\n");
  fprintf(output_file,"    <name>Paths</name>\n");
  fprintf(output_file,"    <description> Jut a KML path + poly</description>\n");
  fprintf(output_file,"    <Folder>\n");
  fprintf(output_file,"      <name>Paths folder</name>\n");
  // fprintf(output_file,"      <Placemark>\n");
  // fprintf(output_file,"        <name>Line @ath</name>\n");
  // fprintf(output_file,"        <description>Transparent green wall with yellow outlines</description>\n");
  // fprintf(output_file,"        <LineString>\n");
  // fprintf(output_file,"          <altitudeMode>clampedToGround</altitudeMode>\n");
  // fprintf(output_file,"          <coordinates>\n");

  //Print the output coordinates

  // fprintf(output_file,"            -1.2,51.36,2357\n");
  // fprintf(output_file,"            -1.2,51.38,2357\n");
  //
  //Print the rest of the KML

  // fprintf(output_file,"          </coordinates>\n");
  // fprintf(output_file,"        </LineString>\n");
  // fprintf(output_file,"      </Placemark>\n");

  printCircle(output_file);

  fprintf(output_file,"    </Folder>\n");
  fprintf(output_file,"   </Document>\n");
  fprintf(output_file,"</kml>\n");

  fclose(output_file);

  return 0;
}

static void printCircle(FILE *output_file){

  float lat_center = 51.36;
  float lon_center = -1.2;

  float lat_circle = 0;
  float lon_circle = 0;

  float radius = 0.0001;
  int circle_points = 50;

  fprintf(output_file,"      <Placemark>\n");
  fprintf(output_file,"        <name>TestPoly</name>\n");
  fprintf(output_file,"        <Polygon>\n");
  fprintf(output_file,"          <extrude>1</extrude>\n");
  fprintf(output_file,"          <altitudeMode>clampedToGround</altitudeMode>\n");
  fprintf(output_file,"          <outerBoundaryIs>\n");
  fprintf(output_file,"            <LinearRing>\n");
  fprintf(output_file,"              <coordinates>\n");

  for (size_t i = 0; i < circle_points; i++) {

    lat_circle = lat_center + radius*(cos(2*M_PI*((float)i/circle_points)));
    lon_circle = lon_center + radius*(sin(2*M_PI*((float)i/circle_points)));

    fprintf(output_file,"              %0.8f,%0.8f,2357\n",5*lon_circle,lat_circle);

  }


  fprintf(output_file,"              </coordinates>\n");
  fprintf(output_file,"            </LinearRing>\n");
  fprintf(output_file,"          </outerBoundaryIs>\n");
  fprintf(output_file,"        </Polygon>\n");
  fprintf(output_file,"      </Placemark>\n");


}
