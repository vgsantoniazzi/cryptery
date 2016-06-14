#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const char alphabet[] =
  "abcdefghijklmnopqrstuvwxyz"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
  "0123456789";

static const int alphabet_size = sizeof(alphabet) - 1;

bool success_decrypt = false;

char* md5_to_decrypt;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void brute_force_token_matcher(char *str, int index, int max_size){
  for (int i = 0; i < alphabet_size; ++i){
    if(success_decrypt) {
      pthread_exit(&success_decrypt);
    }
    str[index] = alphabet[i];
    if (index == max_size - 1){
      if(strcmp(md5_to_decrypt, str) == 0) {
        pthread_mutex_lock(&lock);
        printf("\nMD5 '%s' match as '%s'!\n", md5_to_decrypt, str);
        success_decrypt = true;
        pthread_mutex_unlock(&lock);
        pthread_exit(&success_decrypt);
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

void *brute_match_md5(void *thread_id) {
  brute_sequential(3);
  pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
  int num_cpus = sysconf(_SC_NPROCESSORS_CONF);
  int threads_number = num_cpus * 2;
  md5_to_decrypt = argv[1];
  pthread_t threads[threads_number];
  printf("Number of cores: %d", num_cpus);
  printf("\nNumber of threads: %d", threads_number);
  int thread_id;
  for(thread_id = 0; thread_id < threads_number; thread_id++){
    pthread_create(&threads[thread_id], NULL, brute_match_md5,
        (void *) &thread_id);
  }
  pthread_exit(NULL);
}
