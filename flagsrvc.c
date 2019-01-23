#include "flagsrvc.h"

void services_register(FlagService *flagservice, Flag *flag) {
  if (flagservice->services_count > 0) {
    flagservice->services[flagservice->services_count] = flag;
    flagservice->services_count++;
  } else {
    flagservice->services = malloc(sizeof(Flag *));
    flagservice->services[flagservice->services_count] = flag;
    flagservice->services_count++;
  }
}

void services_unregister(FlagService *flagservice, int index) {
  if (index > -1) {
    for (index; index < flagservice->services_count - 1; index++) {
      flagservice->services[index] = flagservice->services[index + 1];
    }
    flagservice->services_count--;
  } else {
    printf("Exception: Index is %d\n", index);
  }
}

void services_unregister_tag(FlagService *flagservice, char *tag) {
  int index = flagservice->find(flagservice, tag);
  flagservice->unreg(flagservice, index);
}

int services_find(FlagService *flagservice, char *tag) {
  int i;
  for (i = 0; i < flagservice->services_count; i++) {
    if (strcmp(flagservice->services[i]->s_tag, tag) == 0 || strcmp(flagservice->services[i]->f_tag, tag) == 0) {
      return i;
    }
  }
  printf("\'%s\' is probably an unregistered flag/service. Register it using \'<FlagService>->reg(<FlagService>, <Flag>)\'.\n", tag);
  return -1;
}

Flag* services_get(FlagService *flagservice, int index) {
  return flagservice->services[index];
}

Flag* services_get_tag(FlagService *flagservice, char *tag) {
  int index = flagservice->find(flagservice, tag);
  return flagservice->services[index];
}

void services_list(FlagService *flagservice) {
  int i;
  printf("============================== Registered Services ===============================\n", i);
  for (i = 0; i < flagservice->services_count; i++) {
    printf("| %d | Short Tag: %-3s | Full Tag: %-11s | Have Params: %-1s | No. of Params: %-1d |\n", i, flagservice->services[i]->s_tag, flagservice->services[i]->f_tag, flagservice->services[i]->have_params ? "T" : "F", flagservice->services[i]->params_count);
  }
  printf("============================== Printed %d services ================================\n", i);
}

void services_execute(FlagService *flagservice, int count, char **argv) {
  int i;
  for (i = 1; i < count; i++) {
    int index = flagservice->find(flagservice, argv[i]);
    if (index > -1) {
      Flag *f = flagservice->get(flagservice, index);
      if (f->have_params) {
        char *params[f->params_count];
        int j;
        for (j = 0; j < f->params_count; j++) {
          params[j] = argv[++i]; //TODO: Kontrola strumienia -> Sprawdzanie czy aby przypadkowo nie weszliśmy na coś innego niż oczekiwane parametry
        }
        f->action(params);
      } else {
        f->action(NULL);
      }
    }
  }
}

FlagService* flagsrvc_new() {
  FlagService *fs = malloc(sizeof(FlagService));
  fs->services_count = 0;
  fs->reg = &services_register;
  fs->unreg = &services_unregister;
  fs->unreg_tag = &services_unregister_tag;
  fs->list = &services_list;
  fs->find = &services_find;
  fs->get = &services_get;
  fs->get_tag = &services_get_tag;
  fs->exec = &services_execute;
  return fs;
}
