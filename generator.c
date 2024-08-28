#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "includes/generator.h"

void generate_password(password_t* passwd, prompts_t* prompts)
{
  int i;
  passwd->value = realloc(passwd->value, passwd->length*sizeof(char));

  memset(passwd->value, 0, passwd->length+1);

  for (i = 0; i < passwd->length; i++)
    passwd->value[i] = passwd->charset[rand()%strlen(passwd->charset)];

  printf("\n%s Your password is: %s\n", prompts->out, passwd->value);
}