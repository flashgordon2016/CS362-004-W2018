#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    /*Generate random number in the inclusive range 32-126
    of ASCII printable characters*/
    char randomChar = (rand() % (127 - 32)) + 32;
    return randomChar;
}

char *inputString()
{
    int i, stringLength = (rand() % 59) + 5;
    char inputPool[] = {'r', 'e', 's', 't'};
    char* randomString = (char*)malloc((stringLength + 1) * sizeof(char));
    //Generate string of random ASCII characters in the range 97-122
    for (i = 0; i < stringLength; i++) {
      randomString[i] = inputPool[rand() % 4];
    }
    randomString[stringLength] = '\0';
    return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      free(s);
      exit(200);
    }
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
