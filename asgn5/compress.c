/*
* Program:      compress
*
* Purpose:      Compress a file.
*
* Usage:        compress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  compress INFILE -o OUTFILE\n");
    exit(0);
}

//write function header

/*
* Purpose:  Compress the contents of an input file and write the
*           encoded data to a NIB output file.

*
*            For each character read from the input file:
*
*              If it matches one of the 15 most common characters
*                the corresponding 4-bit nibble is written.
*
*              If the character is not in the table, a
*              zero nibble (0x00) is written first, then two
*              nibbles representing the original character are written.



* Parameters: fin - Pointer to the input file opened for reading.
*             nib - Pointer to the NIB file opened for writing.
*
* Return:    nothing (type void) 
*/

void compress(FILE *fin, NIB *nib) {
    int c;

    while((c = fgetc(fin)) != EOF){
        //copy lookup table

        switch(c){
            case ' ': nib_put_nibble(0x01, nib); break; //0001 (1)
            case 'e': nib_put_nibble(0x02, nib); break;
            case 't': nib_put_nibble(0x03, nib); break;
            case 'n': nib_put_nibble(0x04, nib); break;
            case 'r': nib_put_nibble(0x05, nib); break;
            case 'o': nib_put_nibble(0x06, nib); break;
            case 'a': nib_put_nibble(0x07, nib); break;
            case 'i': nib_put_nibble(0x08, nib); break;
            case 's': nib_put_nibble(0x09, nib); break;
            case 'd': nib_put_nibble(0x0A, nib); break;
            case 'l': nib_put_nibble(0x0B, nib); break;
            case 'h': nib_put_nibble(0x0C, nib); break;
            case 'c': nib_put_nibble(0x0D, nib); break;
            case 'f': nib_put_nibble(0x0E, nib); break;
            case 'p': nib_put_nibble(0x0F, nib); break; //1111 (15)
            default:
            // if not in table Write a 0 nibble using nib_put_nibble()
            nib_put_nibble(0x00, nib);

            //Write the high nibble of ch using nib_put_nibble()
            nib_put_nibble((c >> 4) & 0x0F, nib);
            
            //Write the low nibble of ch using nib_put_nibble()
            nib_put_nibble(c & 0x0F, nib);
            break;
        }

    }
}

/*
* Purpose:  This is the main function for the compress program.
*           checks if command line arguments are valid then opens
*           the input file for reading and the output file for writing.
*          
*           Once the files are open, it calls compress() to perform
*           data compression then closes files before exiting
*
*
*
* Paramaters: argc  - The number of command-line arguments.
*             argv - The array of command-line argument strings.
*
*
* Returns:  returns 0 if program runs successfully
*           Exits with 1 if args are invalid or if files cant be opened
*
*/

int main(int argc, char **argv) {
    if (argc != 4 || strcmp(argv[2], "-o") != 0) {
        print_usage();
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL){
        printf("compress: cannot open input file '%s'\n", argv[1]);
        exit(1);
        
    }

    NIB *nib = nib_open(argv[3], "w");
    if (nib == NULL){
        printf("compress: cannot open output file '%s'\n", argv[3]);
        exit(1);
    }

    compress(fin, nib); //call compress

    fclose(fin);
    nib_close(nib);

    return 0;
}
