#include <stdio.h>

int main() {

	float latitude;
	float longitude;
	char info[80];
	int started = 0;

  FILE *in_file = fopen("gpsdata.csv", "r");
  FILE *out_file = fopen("output.json", "w");

	fprintf(out_file, "data=[\n");

	while (fscanf(in_file,"%f, %f, %79[^\n]", &latitude, &longitude, info) == 3) {

		if (started) {
			fprintf(out_file,",\n");
		} else {
			started = 1;
		}

		if ((latitude < -90.0) || (latitude > 90.0)) {
			fprintf(stderr, "Invalid latitude %f\n", latitude);
			return 2;
		}

		if ((longitude < -180.0) || (longitude > 180.0)) {
			fprintf(stderr, "Invalid longitude %f\n", longitude);
			return 2;
		}

		fprintf(out_file,"{ latitude: %f, longitude: %f, info: '%s'}", latitude, longitude, info);
	}

	fprintf(out_file, "\n]");
	return 0;
}
