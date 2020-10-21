#include <stdio.h> //remove if not using.
#include <math.h>

#include "util.h"//implementing

static int isPrime(int n)
{
    if(n == 1)
    {
        return 0;
    }
    else if(n == 2 || n == 3)
    {
        return 1;
    }

    int limit = sqrt((double) n);
    //printf("n = %d, limit = %d\n", n, limit);
    for(int i = 2; i <= limit; i++)
    {
        //printf("%d %% %d = %d\n", n, i, n % i);
        if(n % i == 0)
        {
          return 0;
        }
    }
    return 1;
}

void primes_st(unsigned int max, unsigned int verb){
    int i = 1;
    int limit = max;
    while(i <= limit)
    {
        if(isPrime(i) && verb)
        {
            printf("%d\n", i);
        }
        i++;
    }
    return;
}

void primes_mt(unsigned int max, unsigned int threads,	\
	       unsigned int verb){
    return;
}
