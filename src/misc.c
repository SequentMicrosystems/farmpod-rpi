#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"
#include "data.h"
#include "misc.h"


const CliCmdType CMD_WATER_READ = {
	"wldr",
        1,
        &doWaterRead,
        "  wldr             Read water level(as bitmask).\n",
        "  Usage 1:         "PROGRAM_NAME" wldr\n",
        "  Example:         "PROGRAM_NAME" wldr  Get bitmask for the 6 sensors.\n"
};
int doWaterRead(int argc, char *argv[]) {
	(void)argv;
        if(!(argc == 2)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERROR;
        }
	uint8_t buf[1];
	if(OK != i2cMem8Read(dev, I2C_MEM_RELAY_FAN_VAL, buf, 1)) {
		printf("Fail to read!\n");
		return ERROR;
	}
	printf("%d\n", (int)buf[0]);
        return OK;
}

const CliCmdType CMD_FISH_I_READ = {
	"crrd", /* TODO CHANGE NAME*/
	1,
	&doFfIRead,
	"  crrd             Get fish fedders current consumption in mA\n",
	"  Usage:           "PROGRAM_NAME" crrd <channel[1.."STR(CRT_CH_NO)"]>\n",
	"  Example:         "PROGRAM_NAME" crrd 2  Get fish fedder #2 current consumption in mA"
};

int doFfIRead(int argc, char *argv[]) {
	if(argc != 3) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if(dev < 0) {
		return ERROR;
	}
	int ch = atoi(argv[2]);
	if(!(1 <= ch && ch <= CRT_CH_NO)) {
		printf("Current channel out of range!\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[UI_VAL_SIZE];
	if(OK != i2cMem8Read(dev, I2C_MEM_CRT1 + (ch - 1) * UI_VAL_SIZE, buf, UI_VAL_SIZE)) {
		printf("Fail to read current consumption!\n");
		return ERROR;
	}
	uint16_t curr;
	memcpy(&curr, buf, 2);
	printf("%d", (int)curr);
	return OK;
}
