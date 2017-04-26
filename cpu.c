#define _GNU_SOURCE
#include <sched.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>


typedef unsigned long long ull;
typedef enum {false,true} bool;
bool Worked=false;

int CPUsize,cpus;
cpu_set_t * cpu;

int error(char*msg)
{
printf("ERROR: %s\n",msg);
exit(-1);
}

void count(ull ** second)
{
sched_setaffinity(0, sizeof(cpu), &cpu); // set to this pid, cpusetsize, addr cpu
cpu++;//to  cpu(addr) ++
while(!Worked);
while(1) *second+=1;
}


int main(int arg,char**argd)
{
if(arg < 2) return error("./programm seconds"); 

cpus = sysconf(_SC_NPROCESSORS_ONLN); // get cores from sysconf
cpu = CPU_ALLOC(cpus-1);// ALLOC cp

if (cpu == NULL) return error("CPU_ALLOC");

static pthread_t tmp;
ull * counter = (ull*)malloc(sizeof(ull*) * cpus );
for(ull i = cpus; i--;)
 pthread_create(&tmp, NULL, count, &counter[i]);

Worked=true;

sleep( atoi(argd[1]) );

for(ull i = cpus; i--;)
 printf("Thread(%d): %u of %i second\n", i , counter[i] , atoi(argd[1]));
CPU_ZERO(&cpu);
return 1;
}
