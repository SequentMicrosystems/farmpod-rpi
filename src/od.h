#ifndef OD_H
#define OD_H

#include "cli.h"

extern const CliCmdType CMD_OD_FISH_READ;
extern const CliCmdType CMD_OD_PERI_READ;

extern const CliCmdType CMD_OD_FISH_WRITE;
extern const CliCmdType CMD_OD_PERI_WRITE;

int doOdFishRead(int argc, char *argv[]);
int doOdFishWrite(int argc, char *argv[]);

int doOdPeriRead(int argc, char *argv[]);
int doOdPeriWrite(int argc, char *argv[]);

#endif /* OD_H */
