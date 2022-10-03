#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* 
*  this is from Linux source, 
*  if you run on linux you don't need this function 
*/
 
/* Reentrant random function frm POSIX.1c.
   Copyright (C) 1996, 1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.
 
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
 
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
 
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */
 
 
int rand_r (unsigned int *seed)
{
  unsigned int next = *seed;
  int result;
 
  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next / 65536) % 2048;
 
  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;
 
  next *= 1103515245;
  next += 12345;
  result <<= 10;
  result ^= (unsigned int) (next / 65536) % 1024;
 
  *seed = next;
 
  return result;
}
/* change this to get size you want */
#define ARRSIZE 5
 
/* use 32 bit extended rand function rand_r */
int main(int argc, char *argv[])
{
    int arr[ARRSIZE];
    unsigned int seed=time(NULL);
    int i=0;
    int j=0;
    int limit=2;
    int tmp=0;
     
    for(i=0;i<ARRSIZE;i++) arr[i]=i+1; /* 1 - ARRSIZE unique values */
   
    while(limit<ARRSIZE)     /* "randomize" */
    {
        j=arr[ rand_r(&seed) % limit ];
        tmp=arr[j];
        arr[j]=arr[limit];
        arr[limit]=tmp;
        limit++;
    }
    for(i=0;i<ARRSIZE;i++) printf("%d ",arr[i]);
    return 0;
}

// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>

// int main(void) 
// {
//     int random_num, count;

//     srand(time(NULL));
//     char nums[100];
//     for(count = 0; count < 100; count++)
//         nums[count] = rand();

//     for(count = 0; count < 100; count++)
//         printf("%d ", nums[count]);
//     return 0;
// }
