#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"
#include "data.h"
#include "flow.h"

const CliCmdType CMD_FLOW_CNT_READ = {
	"fcntrd",
	2,
	&doFlowCntRead,
	"  fcntrd           Get accumultaion counter.\n",
	"  Usage:           "PROGRAM_NAME" fcntrd <channel[1.."STR(FLOW_CH_NO)"]>\n",
	"  Example:         "PROGRAM_NAME" fcntrd 2; Get accumulation counter for channel #2\n"
};
int doFlowCntRead(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	int ch = atoi(argv[2]);
	if(!(1 <= ch && ch <= FLOW_CH_NO)) {
		printf("Flow channel number out of range!");
		return ARG_RANGE_ERR;
	}
	uint8_t buf[COUNTER_SIZE];
	if (OK != i2cMem8Read(dev, I2C_MEM_FLOW_COUNTER1 + (ch - 1) * COUNTER_SIZE, buf, COUNTER_SIZE))
	{
		printf("Fail to read watchdog reset count!\n");
		return ERROR;
	}
	uint32_t cnt;
	memcpy(&cnt, buf, COUNTER_SIZE);
	printf("%d\n", (int)cnt);
	return OK;
}

const CliCmdType CMD_FLOW_FREQ_READ = {
	"ffeqrd",
	2,
	&doFlowFreqRead,
	"  ffeqrd           Get frequency(Hz).\n",
	"  Usage:           "PROGRAM_NAME" ffeqrd <channel[1.."STR(FLOW_CH_NO)"]>\n",
	"  Example:         "PROGRAM_NAME" ffeqrd 2; Get frequency for channel #2\n"
};
int doFlowFreqRead(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0) {
		return ERROR;
	}
	int ch = atoi(argv[2]);
	if(!(1 <= ch && ch <= FLOW_CH_NO)) {
		printf("Flow channel number out of range!");
		return ARG_RANGE_ERR;
	}
	uint8_t buf[FREQUENCY_SIZE];
	if (OK != i2cMem8Read(dev, I2C_MEM_FLOW_COUNTER1 + (ch - 1) * FREQUENCY_SIZE, buf, FREQUENCY_SIZE))
	{
		printf("Fail to read watchdog reset count!\n");
		return ERROR;
	}
	uint16_t freq;
	memcpy(&freq, buf, FREQUENCY_SIZE);
	printf("%d\n", (int)freq);
	return OK;
}

const CliCmdType CMD_FLOW_CNT_RESET = {
	"fcntrst",
	2,
	&doFlowCntReset,
	"  fcntrst          Reset flow meter accumulation counter\n",
	"  Usage:           "PROGRAM_NAME" fcntrst <channel[1.."STR(FLOW_CH_NO)"\n",
	"  Example:         "PROGRAM_NAME" fcntrst 2  Reset flow meter accumulation counter for channel #2\n"
};
int doFlowCntReset(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev <= 0) {
		return ERROR;
	}
	int ch = atoi(argv[2]);
	if(!(1 <= ch && ch <= FLOW_CH_NO)) {
		printf("Flow channel number out of range\n");
		return ARG_RANGE_ERR;
	}
	uint8_t buf[1] = { ch };
	if (OK != i2cMem8Write(dev, I2C_MEM_FLOW_COUNT_RESET_CMD, buf, 1)) {
		printf("Fail to reset flow meter accumulation counter!\n");
		return ERROR;
	}
	return OK;
}
