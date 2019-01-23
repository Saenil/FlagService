#include "flagsrvc.h"

void flag_tag_normalize(char *tag) {
  int i, j;
  for (i = 0; i < strlen(tag); i++) {
    if (!((tag[i] >= 'a' && tag[i] <= 'z') || (tag[i] >= 'A' && tag[i] <= 'Z'))) {
      for (j = i; j < strlen(tag); j++) {
        tag[j] = tag[j+1];
      }
    }
  }
}

Flag* flag_new(char *short_tag, char *full_tag, void (*action)(char**), int params_count) {
  Flag *f = malloc(sizeof(Flag));

  if (strlen(short_tag) < 4){
    strcpy(f->s_tag, short_tag);
    // flag_tag_normalize(f->s_tag);
  } else {
    strcpy(f->s_tag, "###");
  }

  if (strlen(full_tag) < 15) {
    strcpy(f->f_tag, full_tag);
    // flag_tag_normalize(f->f_tag);
  } else {
    strcpy(f->f_tag, "###");
  }

  f->action = action;
  f->have_params = params_count > 0;
  f->params_count = params_count;
  return f;
}
