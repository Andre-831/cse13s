/*
* Program:      decompress
*
* Purpose:      Decompress a file that was compressed with "compress".
*
* Usage:        decompress INFILE -o OUTFILE
*/

#include "nibbler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  decompress INFILE -o OUTFILE\n");
    exit(0);
}

/*
* Purpose:  Decompress data from a NIB input file and write the
*           original characters to the output file.
*           Each call to nib_get_nibble() reads one nibble from the NIB file, 
*           returns a 4-bit value

           If the nibble is between 0x01 and 0x0F (1 to 15)
*          it represents one of common characters listed in the switch statement below
*
*             If the nibble is 0x00, then the next TWO nibbles
*                are read and combined into a byte:
*                    high = first nibble
*                    low  = second nibble
*
*
* Parameters: nib  - Pointer to the NIB file opened for reading.
*             fout - Pointer to the output file opened for writing.
*
* Return:    nothing (type void)
*/

void decompress(NIB *nib, FILE *fout) {
    int nibble;
    while (nibble = nib_get_nibble(nib), nibble != EOF){
        if (nibble > 0){

            switch(nibble){
                case 0x01: fputc(' ', fout); break; //0001 (1)
                case 0x02: fputc('e', fout); break;
                case 0x03: fputc('t', fout); break;
                case 0x04: fputc('n', fout); break;
                case 0x05: fputc('r', fout); break;
                case 0x06: fputc('o', fout); break;
                case 0x07: fputc('a', fout); break;
                case 0x08: fputc('i', fout); break;
                case 0x09: fputc('s', fout); break;
                case 0x0A: fputc('d', fout); break;
                case 0x0B: fputc('l', fout); break;
                case 0x0C: fputc('h', fout); break;
                case 0x0D: fputc('c', fout); break;
                case 0x0E: fputc('f', fout); break;
                case 0x0F: fputc('p', fout); break; //1111 (15)
                default:
                    break;
            }
        }
        else{
            int nibble1 = nib_get_nibble(nib);
            if(nibble1 == EOF){
                break;
            }
            int nibble2 = nib_get_nibble(nib);
            if(nibble2 == EOF){
                break;
            }
            //create a byte using nibble1 as high and nibble2 as low
            int byte = (nibble1 << 4) | (nibble2 & 0x0F);
            fputc(byte, fout);

        }
    }
}

/*
* Purpose:  Main program for decompressing a file.
*           Checks command line arguments, opens files, calls decompress(),
*          
*               opens the input file with nib_open() for reading and
*               the output file with fopen() for writing. If a file
*               fails to open, it exits. Then it calls decompress() to 
*               convert the compressed data back to text and closes both files when done.
*
*
*
* Parameters: argc - number of command line arguments
*             argv - array of command line argument strings
*
*
*
* Return: 0 on success, exits with code 1 on failure
*
*/


int main(int argc, char **argv) {
/*
Treat argv[1] as the name of the input file.
Treat argv[3] as the name of the output file
*/
    if (argc != 4 || strcmp(argv[2], "-o") != 0) {
        print_usage();
    }
    //Open the input file using nib_open(), and report any error
    NIB *nib = nib_open(argv[1], "r");
    if(nib == NULL){
        printf("compress: cannot open output file '%s'\n", argv[3]);
        exit(1);
    }
    //Open the output file using fopen(), and report any error.
    FILE *fout = fopen(argv[3], "w");
    if(fout == NULL){
        printf("compress: cannot open output file '%s'\n", argv[3]);
        exit(1);
    }

    decompress(nib, fout);

    //Close the files.
    nib_close(nib);
    fclose(fout);


    return 0;
}
