# FlagService
Simple and small library - I want it to be library - (uncompiled, WIP) made for fun and as a part of learning process. It's for dealing with terminal parameters passed to an application

# TODO
- [ ] Finish this README
- [x] Parameters controll - secure the scope of pointers in `services_execute` method
- [ ] If possible, remove requirenment for FlagService pointer from it's methods
- [ ] ... (I don't know right now, but for sure I'll figure out something)
- [ ] Compile and pack it into library

# Usage(Step by step)
## 1. First of all you need to create new FlagService, do it with:
```c
FlagService *fsrvc = flagsrvc_new();
```
## 2. Register some flags/services:
```c
<FlagService>->reg(<FlagService>, <Flag>);
```
* `<FlagService>` is pointer to FlagService created in first step
* `<Flag>` is pointer to Flag, which we can create with:
```c
flag_new(<short_tag>, <full_tag>, <action>, <nr_of_parameters>).
```
* `<short_tag>`  it's self-descriptive(ex.: -h)
* `<full_tag>`  it's self-descriptive(ex.: -help)
* `<action>` is pointer to function/method that should be triggered when we use `<short_tag>` or `<full_tag>`
* `<nr_of_parameters>` is integer number of parameters that should be passed to `<action>` after trigger was enabled
> **IMPORTANT** parameters are passed into `<action>` as array of character arrays or in other words, as array of "strings"
### Example:
```c
fsrvc->reg(fsrvc, flag_new("-h", "-help", &help, 0)); // I assume that help() is allready implemented
```
## 3. Execute flags/services:
```c
<FlagService>->exec(<FlagService>, <parameters_count>, <array_of_parameters>);
```
* `<parameters_count>` is simply an integer number of entered parameters(ex.: argc)
* `<array_of_parameters>` is char array of parameters(ex.: argv)
### Example:
```c
fsrvc->exec(fsrvc, argc, argv); // argc and argv are from main(int argc, char **argv)
```
## Complete Example:
```c
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

int main(int argc, char **argv) {

  // Create new flag service
  fsrvc = flagsrvc_new();

  // Register new flags/services
  fsrvc->reg(fsrvc, flag_new("-h", "-help", &help, 0));
  fsrvc->reg(fsrvc, flag_new("-w", "-helloworld", &hello_world, 0));
  fsrvc->reg(fsrvc, flag_new("-fs", "-flags", &flagservice_list, 0));
  fsrvc->reg(fsrvc, flag_new("-p", "-print", &print, 3));

  // Execute flags/services
  fsrvc->exec(fsrvc, argc, argv);

  return 0;
}

```

# Other
## Unregister flag/service:
Both do the same, but first is able to find index of `<Tag>` by it self, second one need index passed as an argument.
```c
<FlagService>->unreg_tag(<FlagService>, <Tag>);
```
or
```c
<FlagService>->unreg(<FlagService>, <index_of_flag>);
```
* `<Tag>` can be `<short_tag>` or `<full_tag>`
* `<index_of_flag>` integer representing index of flag/service we want to unregister. We can find it with `find(<Tag>)` method.
```c
<FlagService>->find(<FlagService>, <Tag>);
```
### Example 1.
```c
fsrvc->unreg_tag(fsrvc, "-help"); // Of course you can pass "-h" if you want to
```
### Example 2.
```c
fsrvc->unreg(fsrvc, fsrvc->find(fsrvc, "-help")); // Same
```
