# FlagService
Simple and small library(uncompiled, WIP) for dealing with terminal parameters passed to an application

# TODO
* Parameters controll - secure the scope of pointers in `services_execute` method
* If possible, remove requirenment for FlagService pointer from it's methods
* ... (I don't know right now, but for sure I'll figure out something)
* Compile and pack it into library

# Usage(Step by step)
## 1. First of all you need to create new FlagService, do it with:
```c
FlagService *fsrvc = flagsrvc_new();
```
## 2. Register some flags/services:
```c
fsrvc->reg(<FlagService>, <Flag>);
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
### Example:
```c
fsrvc->reg(fsrvc, flag_new("-h", "-help", &help, 0)); // I assume that help() is implemented
```
## 3. Execute flags/services:
```c
fsrvc->exec(<FlagService>, <parameters_count>, <array_of_parameters>);
```
* `<parameters_count>` is simply an integer number of entered parameters(ex.: argc)
* `<array_of_parameters>` is char array of parameters(ex.: argv)
### Example:
```c
fsrvc->exec(fsrvc, argc, argv); // argc and argv are from main(int argc, char **argv)
```
