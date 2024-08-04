#include <stdio.h>
#include "headers/rede.h"

int main(int argc, char *argv[]){
    if(argc < 2)
		exit(printf("ERROR: Missing arguments!\n"));

	char* input_file_path = argv[1];
	char* output_file_path = argv[2];

	FILE *input = fopen(input_file_path, "r");
	if(!input)
		exit(printf("ERROR: File %s did not open", input_file_path));

    FILE *output = fopen(output_file_path, "w");
    if(!output)
        exit(printf("ERROR: File %s did not open", output_file_path));

    Rede *r = rede_create_from_file(input);

    rede_calc_inflacao_RTT(r, output);

    rede_destroy(r);
    fclose(output);
	fclose(input);
    return 0;
}

