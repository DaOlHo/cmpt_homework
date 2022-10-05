#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "assignment1.h"

bool test_q1_1()  {
  if (count_even(1, 4)==2 && count_even(10, 3)==4)  {
    printf("Q1-1 ok\n");
    return true;
  }
  else  {
    printf("Q1-1 ERROR\n");
    return false;
  }
}

bool test_q1_2()  {
  if (count_even(7, -8)==8 && count_even(-11, -11)==0){
    printf("Q1-2 ok\n");
    return true;
  }
  else  {
    printf("Q1-2 ERROR\n");
    return false;
  }
}


bool test_q2_1()  {
  int ar[6] = {1,7,-3,7,4,7};
  int ans = most_frequent(ar,6);

  if (ans==7) {
    printf("Q2-1 ok\n");
    return true;
  }
  else  {
    printf("Q2-1 ERROR\n");
    return false;
  }
}


#define LEN 101
bool test_q2_2()  {
  int ar[LEN];
  for (int i=0;i<LEN;i++)
    ar[i] = -2 - (i%2);
  int ans = most_frequent(ar,LEN);

  if (ans==-2) {
    printf("Q2-2 ok\n");
    return true;
  }
  else  {
    printf("Q2-2 ERROR\n");
    return false;
  }
}


bool test_q3_1()  {
  if (is_odd_palindrome("a2z@d@z2a")==true && is_odd_palindrome("ae11&edwdccek")==false) {
    printf("Q3-1 ok\n");
    return true;
  }
  else  {
    printf("Q3-1 ERROR\n");
    return false;
  }
}


bool test_q3_2()  {
  if (is_odd_palindrome("a")==true && is_odd_palindrome("abba")==false) {
    printf("Q3-2 ok\n");
    return true;
  }
  else  {
    printf("Q3-2 ERROR\n");
    return false;
  }
}


bool test_q4_1()  {
  if (longest_odd_subpalindrome("aba")==3 && longest_odd_subpalindrome("12321abcba")==5) {
    printf("Q4-1 ok\n");
    return true;
  }
  else  {
    printf("Q4-1 ERROR\n");
    return false;
  }
}

// change STR_LEN3 to 100,000 or 1,000,000 for testing on very long inputs
#define STR_LEN3 1000000
bool test_q4_2()  {
  char* str1 = "abcda@12bcdaK2m_m2Kbcd";
  char* str2 = "Hasta la vista, baby";
  char str3[STR_LEN3+1];
  for (int i=0; i<STR_LEN3/4; i++) {
    str3[4*i] = 'a';
    str3[4*i+1] = 'b';
    str3[4*i+2] = 'c';
    str3[4*i+3] = 'd';
  }
  str3[STR_LEN3] = '\0';
  str3[70] = '0';
  str3[71] = 'k';
  str3[72] = '%';
  str3[73] = 'j';
  str3[74] = 'j';
  str3[75] = 'j';
  str3[76] = '%';
  str3[77] = 'k';
  str3[78] = '0';

  if (longest_odd_subpalindrome(str1)==7
      && longest_odd_subpalindrome(str2)==3
      && longest_odd_subpalindrome(str3)==9
      ) {
    printf("Q4-2 ok\n");
    return true;
  }
  else  {
    printf("Q4-2 ERROR\n");
    return false;
  }
}

// test on a very long string of the form AAAABAAAAAAAAA
// change the length STR_LEN_AAABAA, and see how it affect the running time
#define STR_LEN_AAABAAAAA 10000
bool test_q4_3()  {
  char aabaaaa[STR_LEN_AAABAAAAA];
  memset(aabaaaa,'A',STR_LEN_AAABAAAAA-1);
  aabaaaa[STR_LEN_AAABAAAAA-1] = '\0';
  int pos_B = STR_LEN_AAABAAAAA*0.4; // the mult-factor shuold be between 0.34 and 0.5
  aabaaaa[pos_B] = 'B';

  if (longest_odd_subpalindrome(aabaaaa)==pos_B*2+1) {
    printf("Q4-3 ok\n");
    return true;
  }
  else  {
    printf("Q4-3 ERROR\n");
    return false;
  }
}


bool test_q5_1()  {
  char* num1 = "15";
  int digit1 = 6;

  char* num2 = "15002";
  int digit2 = 5;

  char* ans1 = str_div_by_digit(num1, digit1);
  char* ans2 = str_div_by_digit(num2, digit2);

 
  bool ok = ans1 && strcmp(ans1,"2R3")==0 &&
            ans2 && strcmp(ans2,"3000R2")==0;
  if (ans1)
    free(ans1);
  if (ans2)
    free(ans2);

  if (ok)  {
    printf("Q5-1 ok\n");
    return true;
  }
  else  {
    printf("Q5-1 ERROR\n");
    return false;
  }
}

bool test_q5_2()  {
  char* num1 = "10000000000000000000000000000003";
  int digit1 = 5;

  char* num2 = "1237657129312587312493712539";
  int digit2 = 7;

  char* ans1 = str_div_by_digit(num1, digit1);
  char* ans2 = str_div_by_digit(num2, digit2);

 
  bool ok = ans1 && strcmp(ans1,"2000000000000000000000000000000R3")==0 &&
            ans2 && strcmp(ans2,"176808161330369616070530362R5")==0;
  if (ans1)
    free(ans1);
  if (ans2)
    free(ans2);

  if (ok)  {
    printf("Q5-2 ok\n");
    return true;
  }
  else  {
    printf("Q5-2 ERROR\n");
    return false;
  }
}


// when testing your code, it may be convenient 
// to comment out some of the test cases
// and focus only on the one you are working on right now
int main()  {
  test_q1_1();
  test_q1_2();
  
  test_q2_1();
  test_q2_2();
  
  test_q3_1();
  test_q3_2();

  test_q4_1();
  test_q4_2();
  test_q4_3();
  
  test_q5_1();
  test_q5_2();
  
  return 0;
}