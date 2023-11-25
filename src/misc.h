#ifndef MISC_H
#define MISC_H

#include "cli.h"

extern const CliCmdType CMD_WATER_READ;

extern const CliCmdType CMD_FISH_I_READ;

int doWaterRead(int argc, char *argv[]);
int doFfIRead(int argc, char *argv[]);

#endif /* MISC_H */

