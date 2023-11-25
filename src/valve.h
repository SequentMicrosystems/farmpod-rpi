#ifndef VALVE_H
#define VALVE_H

#include "cli.h"

extern const CliCmdType CMD_VALVE_STATE_READ;

extern const CliCmdType CMD_VALVE_CLOSING_READ;
extern const CliCmdType CMD_VALVE_OPENING_READ;

extern const CliCmdType CMD_VALVE_OPEN_WRITE;
extern const CliCmdType CMD_VALVE_CLOSE_WRITE;


int doValveStateRead(int argc, char *argv[]);

int doValveClosingRead(int argc, char *argv[]);
int doValveOpeningRead(int argc, char *argv[]);

int doValveOpenWrite(int argc, char *argv[]);
int doValveCloseWrite(int argc, char *argv[]);

#endif /* VALVE_H */
