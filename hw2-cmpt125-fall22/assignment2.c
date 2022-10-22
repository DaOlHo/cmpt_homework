#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"

// General format of the DB is as follows:
// <username_len><password_len><username><password>

int add_user_password(const char* file_name, const char* username, const char* password) {
  // Do not continue if user is already in file
  int is_present = check_user_password(file_name, username, password);
  if (is_present == -3 || is_present == 1) return 0;

  FILE* file_ptr = fopen(file_name, "ab");

  int username_len = strlen(username) + 1;
  int password_len = strlen(password) + 1;

  // Append all necessary data sequentially
  fwrite(&username_len, sizeof(int), 1, file_ptr);
  fwrite(&password_len, sizeof(int), 1, file_ptr);
  fwrite(username, username_len, 1, file_ptr);
  fwrite(password, password_len, 1, file_ptr);

  fclose(file_ptr);
  return 1;
}

int check_user_password(const char* file_name, const char* username, const char* password) {
  FILE* file_ptr = fopen(file_name, "rb");

  if (file_ptr == NULL) {
    return -1;
  }

  int return_val = -2;

  while (1) {
    if (feof(file_ptr)) break;

    // Get lengths of entries
    int lengths[2];
    fread(lengths, sizeof(int), 2, file_ptr);
    int username_length = lengths[0];
    int password_length = lengths[1];

    // Get username and password
    char fusername[username_length];
    char fpassword[password_length];
    fread(fusername, username_length, 1, file_ptr);
    fread(fpassword, password_length, 1, file_ptr);
    
    // Compare
    if (strcmp(username, fusername) == 0) {
      if (strcmp(password, fpassword) == 0) {
        return_val = 1;
      } else {
        return_val = -3;
      }

      break;
    }
  }

  // Default is -2 for if user isn't found
  fclose(file_ptr);
  return return_val;
}

int fib3_p(unsigned int n, unsigned int p) {
  // Start at n = 2 because 0<=n<=2 is already defined, making calculation easier
  if (n <= 2) return n;
  unsigned int curr_n = 2, n_min_1 = 2, n_min_2 = 1, n_min_3 = 0;

  // Should be similar speed to recursion, just without risk of stack overflow
  while (curr_n < n) {
    unsigned int curr_val = (n_min_1 + n_min_2 + n_min_3) % p;

    n_min_3 = n_min_2;
    n_min_2 = n_min_1;
    n_min_1 = curr_val;

    curr_n++;
  }

  return n_min_1;
}

char* evolve(const char* state) {
  // -----------------------------------------------
  // Return if rules that end the game are triggered
  // -----------------------------------------------

  int state_len = strlen(state);
  int pebble_count = 0;

  char* state_new = malloc((state_len + 1) * sizeof(char));

  for (int i = 0; i < state_len; i++) {
    if (state[i] == '@') pebble_count++;
  }

  if (pebble_count < 2) {
    strcpy(state_new, state);
    return state_new;
  }; // Rules F + G

  // ------------------
  // Execute move rules
  // ------------------

  int pebble_locs[pebble_count];
  int pebble_locs_prev[pebble_count]; // All operations are on previous state
  int pebble_index = 0;

  for (int i = 0; i < state_len; i++) {
    if (state[i] == '@') {
      pebble_locs[pebble_index] = i;
      pebble_locs_prev[pebble_index] = i;
      pebble_index++;
    }
  }

  // Rules C + D
  pebble_locs[0] += 1;
  pebble_locs[pebble_count - 1] -= 1;

  // Only run if it needs to so it doesn't cause bugs
  if (pebble_count > 2) {
    for (int i = 1; i < pebble_count - 1; i++) {
      int left_distance = pebble_locs_prev[i] - pebble_locs_prev[i - 1];
      int right_distance = pebble_locs_prev[i + 1] - pebble_locs_prev[i];

      if (left_distance == right_distance) pebble_locs[i] = -1; // Rule B
      // Rule A
      else if (left_distance > right_distance) pebble_locs[i]++;
      else pebble_locs[i]--;
    }
  }

  // --------------
  // Remove pebbles
  // --------------

  // Rule E
  for (int i = 1; i < pebble_count; i++) {
    // Catches all matches since movement speed is 1
    if (pebble_locs[i - 1] == pebble_locs[i]) {
      pebble_locs[i - 1] = -1;
      pebble_locs[i] = -1;
    }
  }

  // ---------------
  // Build new state
  // ---------------

  // Clear state with dashes
  for (int i = 0; i < state_len; i++) {
    state_new[i] = '-';
  }
  state_new[state_len] = '\0';
  
  // Fill in pebbles
  for (int i = 0; i < pebble_count; i++) {
    int pebble_index = pebble_locs[i];

    if (pebble_index != -1) {
      state_new[pebble_index] = '@';
    }
  }

  return state_new; // Rule H is implicit
}

char* last_state(const char* state) {
  int state_len = (strlen(state) + 1) * sizeof(char);
  char* state_new = malloc(state_len);
  char* state_prev = malloc(state_len);

  // Populate states for initial frame
  strcpy(state_new, state);
  // printf("%s\n", state_new);

  do {
    strcpy(state_prev, state_new);

    char* state_curr = evolve(state_new);
    strcpy(state_new, state_curr);
    free(state_curr);

    // printf("%s\n", state_new);
  } while(strcmp(state_new, state_prev) != 0); // Rule H

  free(state_prev);
  return state_new;
}