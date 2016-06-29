#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/md5.h>
#include <mpi.h>

#define send_data_tag 2001

static const char alphabet[] =
  "abcdefghijklmnopqrstuvwxyz"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "0123456789";

static const int alphabet_size = sizeof(alphabet) - 1;

int current_number_chars = 0;

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

void *brute_match_md5(int current_size) {
  printf("\nTrying match %d sized strings concurrently...", current_size);
  brute_sequential(current_size);
}

int main (int argc, char *argv[]) {
  int num_procs, my_id, root_proccess;
  md5_to_decrypt = argv[1];
  root_proccess = 0;
  int current_char_size;

  MPI_Init(&argc, &argv);
  MPI_Status status;

  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  if(my_id == root_proccess) {
    int current_char_size;
    for(current_char_size = 1; current_char_size <= num_procs - 1; current_char_size++){
      MPI_Send(&current_char_size, 1 , MPI_INT, current_char_size, send_data_tag, MPI_COMM_WORLD);
    }
  } else {
    MPI_Recv( &current_char_size, 1, MPI_INT, root_proccess,
                send_data_tag, MPI_COMM_WORLD, &status);
    brute_match_md5(current_char_size);
  }
  MPI_Finalize();
}
