#ifndef FLOW_H
#define FLOW_H

#include "cli.h"

extern const CliCmdType CMD_FLOW_CNT_READ;
extern const CliCmdType CMD_FLOW_CNT_RESET;
extern const CliCmdType CMD_FLOW_FREQ_READ;

int doFlowCntRead(int argc, char *argv[]);
int doFlowCntReset(int argc, char *argv[]);
int doFlowFreqRead(int argc, char *argv[]);

#endif /* FLOW_H */
