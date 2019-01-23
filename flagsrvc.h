#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct FlagService FlagService;
typedef struct Flag Flag;

struct FlagService {
  Flag **services;
  int services_count;
  void (*reg)(FlagService*, Flag*);
  void (*unreg)(FlagService*, int);
  void (*unreg_tag)(FlagService*, char*);
  int (*find)(FlagService*, char*);
  Flag* (*get)(FlagService*, int);
  Flag* (*get_tag)(FlagService*, char*);
  void (*list)(FlagService*);
  void (*exec)(FlagService*, int, char**);
};

struct Flag {
  char s_tag[4];
  char f_tag[10];
  void (*action)(char**);
  int have_params;
  int params_count;
};

Flag* flag_new(char*, char*, void (*)(char**), int);
void flag_tag_normalize(char*);

FlagService* flagsrvc_new();
