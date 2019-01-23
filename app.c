#include "flagsrvc.h"

FlagService *fsrvc;

void help() {
  printf("======= Help =======\nThis is example help,\nprinted thanks to FlagService\'s ;)\n======= Help =======\n");
}

void hello_world() {
  printf("Hello Wolrd!\n");
}

void flagservice_list() {
  fsrvc->list(fsrvc);
}

void print(char **argv) {
  int n;
  for (n = 0; n < 3; n++) {
    printf("%s ", argv[n]);
  }
  printf("\n");
}

void say(char **argv) {
  printf("Say: %s\n", argv[0]);
}

int main(int argc, char **argv) {

  // Create new flag service
  fsrvc = flagsrvc_new();

  // Register new flags/services
  fsrvc->reg(fsrvc, flag_new("-h", "-help", &help, 0));
  fsrvc->reg(fsrvc, flag_new("-w", "-helloworld", &hello_world, 0));
  fsrvc->reg(fsrvc, flag_new("-fs", "-flags", &flagservice_list, 0));
  fsrvc->reg(fsrvc, flag_new("-p", "-print", &print, 3));
  fsrvc->reg(fsrvc, flag_new("-n", "-null", NULL, 0));
  fsrvc->reg(fsrvc, flag_new("-s", "-say", &say, 1));

  // List all registered flags/serviecs
  // fsrvc->list(fsrvc);

  // Unregister flags/services
  // fsrvc->unreg_tag(fsrvc, "-help");
  // fsrvc->unreg(fsrvc, fsrvc->find(fsrvc, "-hw"));

  // List all registered flags/services
  // fsrvc->list(fsrvc);

  // Execute flas/services
  fsrvc->exec(fsrvc, argc, argv);

  return 0;
}
