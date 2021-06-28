//============================================================================================================
//!
//! \file main.c
//!
//! \brief Program for converting NCom files to text. Also demonstrates how to use the C NCom libraries.
//!
//============================================================================================================

#define MAIN_DEV_ID "111027"  //!< Development identification.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "NComRxC.h"


//============================================================================================================
// Prototypes for some helper functions.

static void report(const NComRxC *nrx);
static void print(FILE *fp, const NComRxC *nrx);
static void printEnd(FILE *fp);


//============================================================================================================
//! \brief Function where the program starts execution.
//!
//! Program for converting NCom files to text.
//!
//! \return Exit status.

int main(
		int argc,           //!< Number of arguments supplied to the program.
		const char *argv[]  //!< Array of arguments supplied to the program.
	)
{
	FILE *fpin   = NULL;  // input file
	FILE *fpout  = NULL;  // output file
	FILE *fptrig = NULL;  // optional trigger file

	int c;                // char from input file
	NComRxC *nrx;         // NComRxC object

	// Output the header and the Development ID
	printf("NComC_file: Converts NCom file data to text. (ID: " MAIN_DEV_ID ")\n");

	// Check the command line for 2 or 3 user parameters
	if(argc !=3 && argc != 4)
	{
		fprintf(stderr, "Usage: NComC_file <input file> <output file> [<trig_file>]\n");
		exit(EXIT_FAILURE);
	}

	// Open the input file
	fpin = fopen(argv[1], "rb");
	if(fpin == NULL)
	{
		fprintf(stderr, "Error: Could not open input file '%s'.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// Open the output file
	fpout = fopen(argv[2], "wt");
	if(fpout == NULL)
	{
		fprintf(stderr, "Error: Could not open output file '%s'.\n", argv[2]);
		if(fpin != NULL) fclose(fpin);
		exit(EXIT_FAILURE);
	}

	// Open the (optional) output trigger text file
	if(argc >= 4)
	{
		fptrig = fopen(argv[3], "wt");
		if(fptrig == NULL)
		{
			fprintf(stderr, "Error: Could not open output trigger file '%s'.\n", argv[3]);
			if(fpin  != NULL) fclose(fpin);
			if(fpout != NULL) fclose(fpout);
			exit(EXIT_FAILURE);
		}
	}

	// Create NCom decoder and check
	nrx = NComCreateNComRxC();
	if(nrx == NULL)
	{
		fprintf(stderr, "Error: Unable to create NCom decoder.\n");
		if(fpin   != NULL) fclose(fpin);
		if(fpout  != NULL) fclose(fpout);
		if(fptrig != NULL) fclose(fptrig);
		exit(EXIT_FAILURE);
	}

	// Read all of the input file and convert to text
	while((c = fgetc(fpin)) != EOF)
	{
		// Decode the data
		if(NComNewChar(nrx, (unsigned char) c) == COM_NEW_UPDATE)
		{
			// For regular updates then output to main output file, otherwise,
			// for falling edge input triggers then output to trigger file.
			switch(nrx->mOutputPacketType)
			{
				case OUTPUT_PACKET_REGULAR : print(fpout,  nrx); break;
				case OUTPUT_PACKET_IN1DOWN : print(fptrig, nrx); break;
				default : break;
			}
		}

		// Report some statistics every 4096 chars processed
		if( (NComNumChars(nrx) & UINT32_C(0xFFF)) == 0) report(nrx);
	}

	// Report final statistics
	report(nrx);
	printf("\n");

	//Pring KML footer
	printEnd(fpout);

	// Clean up
	if(fpin   != NULL) fclose(fpin);
	if(fpout  != NULL) fclose(fpout);
	if(fptrig != NULL) fclose(fptrig);
	NComDestroyNComRxC(nrx);

	return EXIT_SUCCESS;
}


//============================================================================================================
//! \brief Simple decoding progress report.

static void report(const NComRxC *nrx)
{
	assert(nrx);

	printf("\rChars Read %" PRIu32 ", Packets Read %" PRIu32 ", Chars Skipped %" PRIu32,
		NComNumChars(nrx), NComNumPackets(nrx), NComSkippedChars(nrx));

	fflush(stdout);
}


//============================================================================================================
//! \brief Used to write some of the NCom data to a file pointer.
//!
//! There are only a few examples here of how to use the data values.

static void print(FILE *fp, const NComRxC *nrx)
{
	assert(fp);
	assert(nrx);
	static int printed_KML_header = 0;

	// Print KML header
	if (printed_KML_header == 0){

		fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	  fprintf(fp,"<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	  fprintf(fp,"  <Document>\n");
	  fprintf(fp,"    <name>Paths</name>\n");
	  fprintf(fp,"    <description> Jut a KML path</description>\n");
	  fprintf(fp,"    <Style id=\"yellowLineGreenPoly\">\n");
	  fprintf(fp,"      <LineStyle>\n");
	  fprintf(fp,"        <color>7f00ffff</color>\n");
	  fprintf(fp,"        <width>4</width>\n");
	  fprintf(fp,"      </LineStyle>\n");
	  fprintf(fp,"      <PolyStyle>\n");
	  fprintf(fp,"        <color>7f00ff00</color>\n");
	  fprintf(fp,"      </PolyStyle>\n");
	  fprintf(fp,"    </Style>\n");
	  fprintf(fp,"    <Placemark>\n");
	  fprintf(fp,"      <name>Absolute Extruded</name>\n");
	  fprintf(fp,"      <description>Transparent green wall with yellow outlines</description>\n");
	  fprintf(fp,"      <styleUrl>#yellowLineGreenPoly</styleUrl>\n");
	  fprintf(fp,"      <LineString>\n");
	  fprintf(fp,"        <extrude>1</extrude>\n");
	  fprintf(fp,"        <tessellate>1</tessellate>\n");
	  fprintf(fp,"        <altitudeMode>absolute</altitudeMode>\n");
	  fprintf(fp,"        <coordinates>\n");

		printed_KML_header = 1;
	}

	// Print the lon/lat
	if(nrx->mIsLatValid && nrx->mIsLonValid) fprintf(fp, "          %.8f,%.8f,255\n", nrx->mLon,nrx->mLat);

}

static void printEnd(FILE *fp)
{
	assert(fp);

	// Print KML header

	fprintf(fp,"        </coordinates>\n");
	fprintf(fp,"      </LineString>\n");
	fprintf(fp,"    </Placemark>\n");
	fprintf(fp,"  </Document>\n");
	fprintf(fp,"</kml>\n");

}
