#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
int main(int c, char *v[]){
if(c>2)return 1;
int f=c==2?open(v[1],O_RDONLY):0;
if(c==2&&f<0)return 1;
unsigned char b[16];
long o=0;
while(1){
int n = 0;
while(n<16){
ssize_t r=read(f,b+n,16-n);
if(r<0){if(f>0)close(f);return 1;}
if(r==0)break;
n+=r;
}
if (n==0)break;
printf("%08lx: ",o);
for(int i=0;i<16;i++){
if(i<n)printf("%02x",b[i]);
else printf("  ");
if(i%2==1&&i!=15)printf(" ");
}
printf("  ");
for(int i=0;i<n;i++)printf("%c",isprint(b[i])?b[i]:'.');
printf("\n");
o+=n;
}
if(f>0)close(f);
return 0;
}