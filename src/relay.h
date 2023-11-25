#ifndef RELAY_H
#define RELAY_H

#include "cli.h"

extern const CliCmdType CMD_RELAY_FAN_READ;
extern const CliCmdType CMD_RELAY_FAN_WRITE;

extern const CliCmdType CMD_RELAY_LIGHT_WRITE;
extern const CliCmdType CMD_RELAY_LIGHT_READ;

extern const CliCmdType CMD_RELAY_PUMP_WRITE;
extern const CliCmdType CMD_RELAY_PUMP_READ;

extern const CliCmdType CMD_RELAY_SPARE_WRITE;
extern const CliCmdType CMD_RELAY_SPARE_READ;

int doRelayFanRead(int argc, char *argv[]);
int doRelayFanWrite(int argc, char *argv[]);

int doRelayLightRead(int argc, char *argv[]);
int doRelayLightWrite(int argc, char *argv[]);

int doRelayPumpRead(int argc, char *argv[]);
int doRelayPumpWrite(int argc, char *argv[]);

int doRelaySpareRead(int argc, char *argv[]);
int doRelaySpareWrite(int argc, char *argv[]);
#endif /* RELAY_H */
