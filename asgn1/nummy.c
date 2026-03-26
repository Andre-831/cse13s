#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EPSILON 1e-14

void usage(void) {
    printf("Usage:  ./nummy -e N\n");
    printf("        ./nummy -l N\n");
    printf("        ./nummy -p N\n");
    printf("        ./nummy -s N\n");
    printf("        for positive integer N\n");
    exit(1);
}

/*
*   abasolute_value
    purpose: return the absolute value of a number
    parameters: double x
    returns: the absolute value of x (a double)

*/
double absolute_value(double x) {

    if (x < 0){
        return -x;
    }
    return x;
}

/*
*   my_sqrt
    purpose: return the square root of a number
    paramaters:double x
    returns: the square root of x (a double)
*/
double my_sqrt(double x) {

    double next_y = 1.0;
    double y = 0.0;

    while (absolute_value(next_y - y) > EPSILON){
        y = next_y;
        next_y = 0.5 * (y + x /y);
    }
        
    return next_y;
}

/*
*   my_e
    purpose: approximate e using its taylor series 
    paramaters: int n 
    returns: the approximation of e (a double)
*/
double my_e(int n) {

    double factorial  = 1.0;    //0! = 1
    double e = 1.0;             //first term is 1/0! = 1

    for(int k = 1; k <= n -1; k++){

        factorial *= k;
        e += 1.0 / factorial;

    }
    return e;
}

/*
*   my_ln2
    purpose : approximate ln(2) using its taylor series with n terms
    parameters: int n
    returns: the approximation of ln(2) (a double)
*/
double my_ln2(int n) {

    double ln2 = 0.0;
    double power = 1.0;
    for(int i = 1; i <= n; i++){
        power *= 2.0;
        ln2 += 1.0 / (power * i);
    }
    return ln2;
}

/*
*   my_pi
    purpose : approximate pi using its taylor series with n terms
    parameters: int n
    returns: the approximation of pi (a double)
*/
double my_pi(int n) {
    double pi = 0;
    double power = 1.0;
    const double sqrt12 = my_sqrt(12);


    for(int i = 0; i <= n -1; i++){
     pi += 1.0 / (power * (2*i + 1));
     power *= -3;   
    }

    return sqrt12 * pi;
}

/*
* Example usage:  nummy -p 10
*                 ^     ^  ^---argv[2]
*   argc == 3     ^     ^----argv[1]
*                 ^--------argv[0]
*/
int main(int argc, char **argv) {
    if (argc != 3) {
        usage();
    }

    int n = atoi(argv[2]);

    if (n <= 0) {
        usage();
    }

    if        (strcmp(argv[1], "-e") == 0) {
        printf("e is %.13f\n", my_e(n));
    } else if (strcmp(argv[1], "-l") == 0) {
        printf("ln 2 is %.13f\n", my_ln2(n));
    } else if (strcmp(argv[1], "-p") == 0){
        printf("pi is %.13f\n", my_pi(n));
    } else if(strcmp(argv[1], "-s") == 0){
        printf("sqrt is %.13f\n", my_sqrt(n));
    }
    else {
        usage();
    }

    return 0;
}

