#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "includes/io.h"

prompts_t* prompts_create()
{
  prompts_t* p = calloc(1, sizeof(prompts_t));
  p->out = calloc(3, sizeof(char));
  p->in = calloc(3, sizeof(char));

  strcpy(p->out, ">>");
  strcpy(p->in, "<<");

  return p;
}

void prompts_free(prompts_t* p)
{
  free(p->out);
  free(p->in);
  free(p);
}

mmenu_t* main_menu_create()
{
  int i;
  const char* opts[] = {"Generate", "Help", "Exit"};
  mmenu_t* m = calloc(1, sizeof(mmenu_t));
  m->n_of_options = 3;
  m->options = calloc(m->n_of_options, sizeof(char*));

  for (i = 0; i < m->n_of_options; i++)
  {
    m->options[i] = calloc(strlen(opts[i])+1, sizeof(char));
    strcpy(m->options[i], opts[i]);
  }

  return m;
}

void main_menu_display(mmenu_t* main_menu, prompts_t* prompts)
{
  int i;

  printf("\n%s Please select the desired procedure:\n", prompts->out);

  for (i = 0; i < main_menu->n_of_options; i++)
    printf("\t%s %d %s\n", prompts->out, i+1, main_menu->options[i]);
}

void main_menu_free(mmenu_t* main_menu)
{
  int i;
  for (i = 0; i < main_menu->n_of_options; i++)
    free(main_menu->options[i]);

  free(main_menu->options);
  free(main_menu);
}

void ask_for_input(char* buffer, prompts_t* prompts)
{
  printf("%s ", prompts->in);
  fgets(buffer, MAX_USR_CHARS, stdin);
}

m_options validate_user_input(char user_input, char* valid_inputs)
{
  int i;
  for (i = 0; i < strlen(valid_inputs); i++)
  {
    if (user_input == valid_inputs[i])
    {
      switch (i+1)
      {
        case 1:
          return GENERATE;
          break;

        case 2:
          return HELP;
          break;

        case 3:
          return EXIT;
          break;

        default:
          return INVALID;
      }
    }
  }

  return INVALID;
}

charset_t* charset_create()
{
  charset_t* charset = calloc(1, sizeof(charset_t));
  charset->ucase = calloc(27, sizeof(char));
  charset->lcase = calloc(27, sizeof(char));
  charset->digits = calloc(10, sizeof(char));
  charset->symbols = calloc(34, sizeof(char));

  strcpy(charset->ucase, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  strcpy(charset->lcase, "abcdefghijklmnopqrstuvwxyz");
  strcpy(charset->digits, "0123456789");
  strcpy(charset->symbols, "!\"#$%&'()*+,-./:;<=>?@[\\]^_{|}~");

  return charset;
}

void charset_display(charset_t* charset, prompts_t* prompts)
{
  printf("\n%s Select what characters your password should contain:\n", prompts->out);
  printf("\t%s %d %s\n", prompts->out, 1, charset->ucase);
  printf("\t%s %d %s\n", prompts->out, 2, charset->lcase);
  printf("\t%s %d %s\n", prompts->out, 3, charset->digits);
  printf("\t%s %d %s\n", prompts->out, 4, charset->symbols);
}

void charset_free(charset_t* charset)
{
  free(charset->ucase);
  free(charset->lcase);
  free(charset->digits);
  free(charset->symbols);
  free(charset);
}

password_t* password_create()
{
  password_t* passwd = calloc(1, sizeof(password_t));
  passwd->length = 1;
  passwd->charset = calloc(1, sizeof(char));
  passwd->value = calloc(passwd->length, sizeof(char));

  return passwd;
}

void password_set_length(char* buffer, password_t* passwd, prompts_t* prompts)
{
  int i = 0;

  while (i <= 0)
  {
    printf("\n%s Length of password: ", prompts->out);
    memset(buffer, 0, MAX_USR_CHARS);
    fgets(buffer, MAX_USR_CHARS, stdin);
    i = atoi(buffer);
  }

  passwd->length = i;
}

void password_set_charset(char* buffer, charset_t* charset, password_t* passwd, prompts_t* prompts)
{
  int size = 0;
  char chars[95];

  memset(chars, 0, 95);

  while (size == 0)
  {
    charset_display(charset, prompts);
    ask_for_input(buffer, prompts);

    if (strstr(buffer, "1"))
    {
      size += 26;
      strncat(chars, charset->ucase, 26);
    }

    if (strstr(buffer, "2"))
    {
      size += 26;
      strncat(chars, charset->lcase, 26);
    }

    if (strstr(buffer, "3"))
    {
      size += 9;
      strncat(chars, charset->digits, 9);
    }

    if (strstr(buffer, "4"))
    {
      size += 33;
      strncat(chars, charset->symbols, 33);
    }
  }

  size++;
  passwd->charset = realloc(passwd->charset, size*sizeof(char));
  strcpy(passwd->charset, chars);
}

void password_free(password_t* passwd)
{
  free(passwd->charset);
  free(passwd->value);
  free(passwd);
}

void help_menu_display(prompts_t* prompts)
{
  printf("\n%s Password Generator V.1.0.0\n", prompts->out);
  printf("%s You can navigate inside menus by typing the number in front of the desired option.\n", prompts->out);
  printf("%s The \"Generate\" menu will start the generation process.\n", prompts->out);
  printf("%s When you need to specify the desired character sets, you don't have to type the numbers in order.\n", prompts->out);
  printf("%3sDuring generation the order is anyways ignored.\n", " ");
}
