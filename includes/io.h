#ifndef _PASSWD_GEN_IO_H
#define _PASSWD_GEN_IO_H

#define MAX_USR_CHARS 32
#define MAIN_MENU_OPTIONS "123"

typedef enum MAIN_OPTIONS
{
  GENERATE,
  HELP,
  EXIT,
  INVALID
} m_options;

typedef struct PROMPTS
{
  char* out;
  char* in;
} prompts_t;

typedef struct MAIN_MENU
{
  char** options;
  short n_of_options;
} mmenu_t;

typedef struct CHAR_SET
{
  char* ucase;
  char* lcase;
  char* digits;
  char* symbols;
} charset_t;

typedef struct PASSWORD
{
  int length;
  char* charset;
  char* value;
} password_t;



prompts_t* prompts_create();
void prompts_free(prompts_t*);



mmenu_t* main_menu_create();
void main_menu_display(mmenu_t*, prompts_t*);
void main_menu_free(mmenu_t*);
void ask_for_input(char*, prompts_t*);
m_options validate_user_input(char, char*);



charset_t* charset_create();
void charset_display(charset_t*, prompts_t*);
void charset_free(charset_t*);



password_t* password_create();
void password_set_length(char*, password_t*, prompts_t*);
void password_set_charset(char*, charset_t*, password_t*, prompts_t*);
void password_free(password_t*);



void help_menu_display(prompts_t*);

#endif