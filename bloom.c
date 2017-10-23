/*
 *  Copyright (c) 2012-2017, Jyri J. Virkki
 *  All rights reserved.
 *
 *  This file is under BSD license. See LICENSE file.
 */

/*
 * Refer to bloom.h for documentation on the public interfaces.
 */

#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "bloom.h"
#include "murmurhash2.h"

#define MAKESTRING(n) STRING(n)
#define STRING(n) #n

//janki: below function need to know which BF to insert, when to check other BFi' and it should return freq from BF-hist
inline static int test_bit_set_bit(unsigned char * buf,
                                   unsigned int x, int set_bit, unsigned int * freqbuf)
{
  unsigned int byte = x >> 3; // same as x/8 - converting bits to bytes
  //printf("byte = %d\n", byte );
  unsigned char c = buf[byte];        // expensive memory access to find the current state of BF at byte
  unsigned int f = freqbuf[byte];        // expensive memory access to find the current state of freq at byte
  //printf("c = %d\n",c);
  unsigned int mask = 1 << (x % 8);
  //printf("mask = %d\n", mask );
  if (c & mask) { 
    return f; //return frequency if it is a check and we find element in BF
  } else {
    //printf("set_bit = %d\n", set_bit);
    if (set_bit) {
      buf[byte] = c ^ mask; // janki : change to XOR currently OR with the previous status
      freqbuf[byte] = f+1; //increament the freq counter
      //printf("buf[byte] = %d\n",buf[byte]);
      printf("freqbuf[byte] = %d\n",freqbuf[byte]);

    }
    return 0;
  }
}


static int bloom_check_add(struct bloom * bloom,
                           const void * buffer, int len, int add, FILE *fp, struct freq * freq)
{
  if (bloom->ready == 0) {
    printf("bloom at %p not initialized!\n", (void *)bloom);
    return -1;
  }

  int hits = 0;
  register unsigned int a = murmurhash2(buffer, len, 0x9747b28c);
  register unsigned int b = murmurhash2(buffer, len, a);
  register unsigned int x;
  register unsigned int i;

  if (add == 1)
  {
    fprintf(fp, "\nkey of my last added value is:\t");
    for (i = 0; i < bloom->hashes; i++) {
      fprintf(fp, "%d\t", (a + i*b) % bloom->bits);
    }
    fprintf(fp, "\n");
  }

  for (i = 0; i < bloom->hashes; i++) {
    x = (a + i*b) % bloom->bits;
    if (test_bit_set_bit(bloom->bf, x, add, freq->bf)) {
      hits++;
    }
  }

  if (hits == bloom->hashes) { //janki: here we are checking if all digits are 1 then element is in BF - this needs to be changes to check min of freq 
    return 1;                // 1 == element already in (or collision)

  }
  return 0;
}


int bloom_init_size(struct bloom * bloom, int entries, double error,
                    unsigned int cache_size)
{
  return bloom_init(bloom, entries, error);
}


int bloom_init(struct bloom * bloom, int entries, double error)
{
  bloom->ready = 0;

  if (entries < 1000 || error == 0) {
    return 1;
  }

  bloom->entries = entries;
  bloom->error = error;

  double num = log(bloom->error);
  double denom = 0.480453013918201; // ln(2)^2
  bloom->bpe = -(num / denom);

  double dentries = (double)entries;
  bloom->bits = (int)(dentries * bloom->bpe);

  if (bloom->bits % 8) {
    bloom->bytes = (bloom->bits / 8) + 1;
  } else {
    bloom->bytes = bloom->bits / 8;
  }

  bloom->hashes = (int)ceil(0.693147180559945 * bloom->bpe);  // ln(2)

  bloom->bf = (unsigned char *)calloc(bloom->bytes, sizeof(unsigned char));
  if (bloom->bf == NULL) {
    return 1;
  }

  bloom->ready = 1;
  return 0;
}


int freq_init(struct freq * freq, int entries, double error)
{

  double num = log(error);
  double denom = 0.480453013918201; // ln(2)^2
  double dentries = (double)entries;
  freq->bits = (int)(dentries * -(num / denom));
  if (freq->bits % 8) {
    freq->bytes = (freq->bits / 8) + 1;
  } else {
    freq->bytes = freq->bits / 8;
  }
  freq->hashes = (int)ceil(0.693147180559945 * -(num / denom));  // ln(2)
  freq->bf = (unsigned int *)calloc(freq->bytes, sizeof(unsigned int));
  if (freq->bf == NULL) {
    return 1;
  }
  return 0;
}


int bloom_check(struct bloom * bloom, const void * buffer, int len, FILE *fp, struct freq * freq)
{
  return bloom_check_add(bloom, buffer, len, 0, fp, freq);
}


int bloom_add(struct bloom * bloom, const void * buffer, int len, FILE *fp, struct freq * freq)
{
  return bloom_check_add(bloom, buffer, len, 1, fp, freq);
}


void bloom_print(struct bloom * bloom)
{
  printf("bloom at %p\n", (void *)bloom);
  printf(" ->entries = %d\n", bloom->entries);
  printf(" ->error = %f\n", bloom->error);
  printf(" ->bits = %d\n", bloom->bits);
  printf(" ->bits per elem = %f\n", bloom->bpe);
  printf(" ->bytes = %d\n", bloom->bytes);
  printf(" ->hash functions = %d\n", bloom->hashes);
}

void freq_print(struct freq * freq)
{
  printf("freq at %p\n", (void *)freq);
  printf(" ->bits = %d\n", freq->bits * (int)sizeof(unsigned int));
  printf(" ->bytes = %d\n", freq->bytes * (int)sizeof(unsigned int));
}


void bloom_free(struct bloom * bloom)
{
  if (bloom->ready) {
    free(bloom->bf);
  }
  bloom->ready = 0;
}


const char * bloom_version()
{
  return MAKESTRING(BLOOM_VERSION);
}
