#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>



/**
 * xd.c
 *
 * Purpose:
 *   Reads from stdin or a file and prints output formatted like xxd:
 *   - Offset (hex, 8 digits)
 *   - 16-byte hex values (grouped in pairs, padded if incomplete)
 *   - ASCII representation (non-printable characters shown as '.')
 *
 * Parameters:
 *   argc number of command-line arguments
 *   argv argument array (optional filename)
 *
 * Exit Codes:
 *   0  Success
 *   1  Error: invalid argument count or file couldnt be opened/read
 *
 * Constraints:
 *   Only open(), read(), and close() are used for I/O.
 *   Output must be done via printf().
 *
 * 
 * output: xd format of input data
*/


int main(int argc, char *argv[]){
    int fd;
    unsigned char buffer[16];
    ssize_t bytes_read;
    int bytes_in_buffer = 0;
    long offset = 0;

    if(argc > 2){ //too many args
        return 1;
    }
    if( argc == 2) { //if file provided, open it; else read from stdin
        fd = open(argv[1], O_RDONLY);
        if(fd == -1){ // failed to open
            return 1;
        }
    } else {
        fd = STDIN_FILENO; // read from stdin
    }


    while(1){
        bytes_in_buffer = 0;
        while(bytes_in_buffer < 16){ //read up to 16 bytes
            bytes_read = read(fd, buffer + bytes_in_buffer, 16 - bytes_in_buffer);
            
            if(bytes_read < 0 && fd != STDIN_FILENO){ //error reading file
                    close(fd);
                    return 1;
            }
            if(bytes_read == 0){
                break; //EOF
            }
            else{
                bytes_in_buffer += bytes_read;
            }
        }

        if( bytes_in_buffer == 0){
            break; //no more data to read
        }
        
        // print offset
        printf("%08lx: ", offset);

        //hex column
        for(int i = 0; i < 16; i++){
            if( i < bytes_in_buffer){
                printf("%02x", buffer[i]);
            }
            else{
                printf("  ");
            }

            if ( i  % 2 == 1 && i != 15){
                printf(" ");
            }

        }
        printf("  "); // end spacing before ascii column

        //ascii column
        for(int i = 0; i < bytes_in_buffer; i++){
            if(isprint(buffer[i])){
                printf("%c", buffer[i]);
            }
            else{
                printf("."); // if
            }

        }
        printf("\n");
        offset += bytes_in_buffer;

    }


    if(fd != STDIN_FILENO){
        close(fd);
    }

    return 0;
}