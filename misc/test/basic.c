/*
 *  Copyright (c) 2016-2017, Jyri J. Virkki
 *  All rights reserved.
 *
 *  This file is under BSD license. See LICENSE file.
 */

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "bloom.h"

#ifdef __linux
#include <sys/time.h>
#include <time.h>
#endif


/** ***************************************************************************
 * A few simple tests to check if it works at all.
 *
 * These are covered in the main test, repeated here just to create a test
 * executable using the static libbloom library to exercise it as well.
 *
 */
int main(int argc, char **argv)
{
  struct bloom bloom;
  struct freq freq;
  FILE *fp;
  fp = fopen("/home/janki/Downloads/BloomStream/key_data.txt","w"); 
  printf("----- Basic tests with static library -----\n");
  //assert(bloom_init(&bloom, 0, 1.0) == 1);
  //assert(bloom_init(&bloom, 10, 0) == 1);
  //assert(bloom.ready == 0);
  //assert(bloom_add(&bloom, "hello world", 11, fp, &freq) == -1);
  //assert(bloom_check(&bloom, "hello world", 11, fp, &freq) == -1);
  //printf("test hello world = %d\n", bloom_check(&bloom, "hello world", 11, fp, &freq));

  //bloom_free(&bloom);

  assert(bloom_init(&bloom, 1000, 0.0001) == 0);
  freq_init(&freq, 1000, 0.0001);
  assert(bloom.ready == 1);
  //bloom_print(&bloom);

  //assert(bloom_check(&bloom, "hello world", 11, fp, &freq) == 0);
  //printf("test hello world = %d\n", bloom_check(&bloom, "hello world", 11, fp, &freq));
  //assert(bloom_add(&bloom, "hello world", 11, fp, &freq) == 0);
  //assert(bloom_check(&bloom, "hello world", 11) == 1);
  //printf("test hello world = %d\n", bloom_check(&bloom, "hello world", 11, fp, &freq));
  //assert(bloom_add(&bloom, "hello world", 11, fp, &freq) > 0);
  //bloom_print(&bloom);

  assert(bloom_add(&bloom, "hello", 5, fp, &freq) == 0);
  bloom_add(&bloom, "hello", 5, fp, &freq);
  bloom_add(&bloom, "hello", 5, fp, &freq);
  //assert(bloom_add(&bloom, "hello", 5, fp, &freq) > 0);
  //bloom_check(&bloom, "hello", 5, fp, &freq);
  printf("test hello = %d\n", bloom_check(&bloom, "hello", 5, fp, &freq));


  bloom_add(&bloom, "303560", 6, fp, &freq);
  //printf("test 303560 = %d\n", bloom_check(&bloom, "303560", 6, fp, &freq));

  //printf("test 3 = %d\n", bloom_check(&bloom, "3", 6, fp, &freq, fp, &freq));
  //printf("test 3000 = %d\n", bloom_check(&bloom, "3000", 6, fp, &freq));
  //printf("test 45324992 = %d\n", bloom_check(&bloom, "45324992", 6, fp, &freq));
  //printf("test 454656 = %d\n", bloom_check(&bloom, "454656", 6, fp, &freq));
  //printf("test 528000 = %d\n", bloom_check(&bloom, "528000", 6, fp, &freq));

  bloom_print(&bloom);
  freq_print(&freq);
  bloom_free(&bloom);
  printf("----- DONE Basic tests with static library -----\n");
}
