#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
typedef unsigned long long ull;

int error(char*msg)
{
printf("ERROR: %s\n",msg);
exit(-1);
}

void count(ull ** second)
{
while(1) *second+=1;
}


int main(int arg,char**argd)
{
if(arg < 3) return error("./programm threads seconds"); 
pthread_t tmp;
ull threads=atoi(argd[1]);
ull * counter = (ull*)malloc(sizeof(ull*) * threads );
for(ull i = threads; i--;)
 pthread_create(&tmp, NULL, count, &counter[i]);

sleep( atoi(argd[2]) );

for(ull i = threads; i--;)
 printf("Thread(%d): %u of %i second\n", i , counter[i] , atoi(argd[2]));

return 1;
}
