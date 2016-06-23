#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/md5.h>

static const char alphabet[] =
  "abcdefghijklmnopqrstuvwxyz"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "0123456789";

static const int alphabet_size = sizeof(alphabet) - 1;

static const int max_chars = 20;

int current_number_chars = 0;

bool success_decrypt = false;

char* md5_to_decrypt;

char* get_md5(const char *string) {
  unsigned char result[MD5_DIGEST_LENGTH];
  char md5_string[33];
  MD5((unsigned char*)string, strlen(string),  (unsigned char*)&result);
  int i;
  for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
    sprintf(&md5_string[i*2], "%02x", (unsigned int)result[i]);
  }
  return &md5_string;
}

void brute_force_token_matcher(char *str, int index, int max_size){
  for (int i = 0; i < alphabet_size; ++i){
    str[index] = alphabet[i];
    if (index == max_size - 1){
      if(strcmp(get_md5(str), md5_to_decrypt) == 0) {
        printf("\nMD5 '%s' match as '%s'!\n", md5_to_decrypt, str);
        exit(0);
      }
    } else {
      brute_force_token_matcher(str, index + 1, max_size);
    }
  }
}

void brute_sequential(int max_length){
  char* buf = malloc(max_length + 1);
  for (int i = 1; i <= max_length; ++i){
    memset(buf, 0, max_length + 1);
    brute_force_token_matcher(buf, 0, i);
  }
  free(buf);
}

void brute_match_md5() {
  while(current_number_chars <= max_chars) {
    current_number_chars += 1;
    printf("\nTrying match %d sized strings...", current_number_chars);
    brute_sequential(current_number_chars);
  }
}

int main (int argc, char *argv[]) {
  md5_to_decrypt = argv[1];
  printf("\nTrying to decrypt: %s", md5_to_decrypt);
  brute_match_md5();
}
