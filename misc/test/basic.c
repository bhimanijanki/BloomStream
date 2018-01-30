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

int main(int argc, char **argv)
{
  struct bloom BF_i, BF_j, BF_hist;
  struct freq F_ij, F_hist;
  FILE *fp;
  unsigned int curr=1, LBA;
  fp = fopen("/home/janki/Downloads/BloomStream/key_data.txt","w"); 
  //printf("----- Basic tests -----\n");

    /*
  //ALL_UNIQUE - EX-1
  // bloom_init(&BF_i, 10, 0.001);
  // bloom_init(&BF_j, 10, 0.001);
  // bloom_init(&BF_hist, 10, 0.001);
  // freq_init(&F_ij, 10, 0.001);
  // freq_init(&F_hist, 10, 0.001);
  // assert(BF_i.ready == 1);
  // assert(BF_j.ready == 1);
  // assert(BF_hist.ready == 1);

  */

    /*
  // bloom_init(&BF_i, 10, 0.001);
  // bloom_init(&BF_j, 10, 0.001);
  // bloom_init(&BF_hist, 10, 0.001);
  // freq_init(&F_ij, 10, 0.001);
  // freq_init(&F_hist, 10, 0.001);
  // assert(BF_i.ready == 1);
  // assert(BF_j.ready == 1);
  // assert(BF_hist.ready == 1);

  */

    
  //float a=200, b=0.128;  //ALL_UNIQUE - EX-1 (a>50)
  //float a=6, b=0.128; //NO UNIQUE HASH (THE UNUSUAL CASE)- EX-3 (b>0.128)
  float a=6, b=0.001; //NO UNIQUE HASH (THE UNUSUAL CASE)- EX-3 (b>0.128)
   //float a=50, b=0.12;  //SOME COMMON HASH BUT EACH VALUE HAS AT LEAST ONE UNIQUE HASH - EX-2

   bloom_init(&BF_i, a, b);
   bloom_init(&BF_j, a, b);
   bloom_init(&BF_hist, a, b);
   freq_init(&F_ij, a, b);
   freq_init(&F_hist, a, b);
   assert(BF_i.ready == 1);
   assert(BF_j.ready == 1);
   assert(BF_hist.ready == 1);

//decide the # of training entries
//for counter < training entries {
//  LBA = read the trace from file and get LBA to be added
  /*
  //TEST_CASE-1
    // LBA = 5654678;
    // //printf("the number of digits = %d\n", GetNumberOfDigits(&LBA));
    // bloom_add_to_pair(&BF_i, &BF_j, &LBA , GetNumberOfDigits(&LBA), fp, &F_ij, &curr);
    // //printf("freq = %d\n", bloom_check_in_pair(&BF_i, &BF_j, &LBA , GetNumberOfDigits(&LBA), fp, &F_ij));
    // bloom_add_to_pair(&BF_i, &BF_j, &LBA , GetNumberOfDigits(&LBA), fp, &F_ij, &curr);
    // //printf("freq = %d\n", bloom_check_in_pair(&BF_i, &BF_j, &LBA , GetNumberOfDigits(&LBA), fp, &F_ij));
    // bloom_add_to_pair(&BF_i, &BF_j, &LBA , GetNumberOfDigits(&LBA), fp, &F_ij, &curr);
    // //printf("freq = %d\n", bloom_check_in_pair(&BF_i, &BF_j, &LBA , GetNumberOfDigits(&LBA), fp, &F_ij));
  //blooms_to_bloomhist(&BF_i, &BF_j, &BF_hist, &F_ij, &F_hist);
  //printf("freq_hist = %d\n", bloom_check_in_hist(&BF_hist, &LBA , GetNumberOfDigits(&LBA), fp, &F_hist));
  //printf("freq_hist = %d\n", bloom_check_in_hist(&BF_hist, "654343241" , GetNumberOfDigits("654343241"), fp, &F_hist));

  */

  //TEST_CASE-2
  bloom_add_to_pair(&BF_i, &BF_j, "a" , GetNumberOfDigits("a"), fp, &F_ij, &curr);
  bloom_add_to_pair(&BF_i, &BF_j, "a" , GetNumberOfDigits("a"), fp, &F_ij, &curr);
  bloom_add_to_pair(&BF_i, &BF_j, "a" , GetNumberOfDigits("a"), fp, &F_ij, &curr);
  bloom_add_to_pair(&BF_i, &BF_j, "b" , GetNumberOfDigits("b"), fp, &F_ij, &curr);
  bloom_add_to_pair(&BF_i, &BF_j, "b" , GetNumberOfDigits("b"), fp, &F_ij, &curr);
  bloom_add_to_pair(&BF_i, &BF_j, "c" , GetNumberOfDigits("c"), fp, &F_ij, &curr);
  bloom_add_to_pair(&BF_i, &BF_j, "a" , GetNumberOfDigits("a"), fp, &F_ij, &curr);
  bloom_add_to_pair(&BF_i, &BF_j, "b" , GetNumberOfDigits("b"), fp, &F_ij, &curr);
//}

  blooms_to_bloomhist(&BF_i, &BF_j, &BF_hist, &F_ij, &F_hist);
  printf("freq_hist a = %d\n", bloom_check_in_hist(&BF_hist, "a" , GetNumberOfDigits("a"), fp, &F_hist));
  printf("freq_hist b = %d\n", bloom_check_in_hist(&BF_hist, "b" , GetNumberOfDigits("b"), fp, &F_hist));
  printf("freq_hist c = %d\n", bloom_check_in_hist(&BF_hist, "c" , GetNumberOfDigits("c"), fp, &F_hist));
  printf("freq_hist 654343241 = %d\n", bloom_check_in_hist(&BF_hist, "654343241" , GetNumberOfDigits("654343241"), fp, &F_hist));








/*

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
  // assert(bloom_add(&bloom, "hello world", 11, fp, &freq) == 0);
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
*/
  bloom_print(&BF_i);
  bloom_print(&BF_j);
  freq_print(&F_ij);
  bloom_free(&BF_i);
  bloom_free(&BF_j);
  printf("----- DONE Basic tests with static library -----\n");
}
