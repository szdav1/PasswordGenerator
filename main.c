#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "includes/io.h"
#include "includes/generator.h"

int main(void)
{
  short running = 1;
  char* buffer = calloc(MAX_USR_CHARS, sizeof(char));

  prompts_t* prompts = prompts_create();
  mmenu_t* main_menu = main_menu_create();
  charset_t* charset = charset_create();
  password_t* password = password_create();

  while (running)
  {
    main_menu_display(main_menu, prompts);
    memset(buffer, 0, MAX_USR_CHARS);
    ask_for_input(buffer, prompts);
    
    switch (validate_user_input(buffer[0], MAIN_MENU_OPTIONS))
    {
      case GENERATE: 
        password_set_length(buffer, password, prompts);
        password_set_charset(buffer, charset, password, prompts);
        generate_password(password, prompts);
        break;

      case HELP:
        help_menu_display(prompts);
        break;

      case EXIT:
        running = 0;
        break;

      case INVALID:
        printf("\n%s Invalid option (Use 1, 2 or 3).\n", prompts->out);
        break;
    }
  }

  free(buffer);
  prompts_free(prompts);
  main_menu_free(main_menu);
  charset_free(charset);
  password_free(password);

  return 0;
}