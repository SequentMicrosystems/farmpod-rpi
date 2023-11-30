#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"
#include "data.h"
#include "flow.h"

const CliCmdType CMD_FLOW_CNT_READ = {
	"cntrd",
	1,
	&doFlowCntRead,
	"  cntrd            Get flow counter accumulation\n",
	"  Usage:           "PROGRAM_NAME" cntrd <channel[1.."STR(FLOW_CH_NO)"]>\n",
	"  Example:         "PROGRAM_NAME" cntrd 2  Get flow counter #2 \n"
};

int doFlowCntRead(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	int ch = atoi(argv[2]);
	if (! (1 <= ch && ch <= FLOW_CH_NO))
	{
		printf("Current channel out of range!\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[COUNTER_SIZE];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_FLOW_COUNTER1 + (ch - 1) * COUNTER_SIZE, buf,
			UI_VAL_SIZE))
	{
		printf("Fail to read counter!\n");
		return ERROR ;
	}
	uint32_t count;
	memcpy(&count, buf, COUNTER_SIZE);
	printf("%d\n", (int)count);
	return OK ;
}

const CliCmdType CMD_FLOW_CNT_RESET = {
	"cntrst",
	1,
	&doFlowCntReset,
	"  cntrst            Reset flow counter accumulation\n",
	"  Usage:           "PROGRAM_NAME" cntrst <channel[1.."STR(FLOW_CH_NO)"]>\n",
	"  Example:         "PROGRAM_NAME" cntrst 2  Reset flow counter #2 \n"
};

int doFlowCntReset(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	int ch = atoi(argv[2]);
	if (! (1 <= ch && ch <= FLOW_CH_NO))
	{
		printf("Current channel out of range!\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[UI_VAL_SIZE];
	buf[0] = (uint8_t)ch;
	if (OK != i2cMem8Write(dev, I2C_MEM_FLOW_COUNT_RESET_CMD, buf,1))
	{
		printf("Fail to read counter!\n");
		return ERROR ;
	}
	uint32_t count;
	memcpy(&count, buf, COUNTER_SIZE);
	printf("%d\n", (int)count);
	return OK ;
}

const CliCmdType CMD_FLOW_FREQ_READ = {
	"flowrd",
	1,
	&doFlowFreqRead,
	"  flowrd            Get flow frequency in Hz\n",
	"  Usage:           "PROGRAM_NAME" flowrd <channel[1.."STR(FLOW_CH_NO)"]>\n",
	"  Example:         "PROGRAM_NAME" flowrd 2  Get flow frequency on channel #2 \n"
};

int doFlowFreqRead(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	int ch = atoi(argv[2]);
	if (! (1 <= ch && ch <= FLOW_CH_NO))
	{
		printf("Current channel out of range!\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[COUNTER_SIZE];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_FLOW_FREQ1 + (ch - 1) * UI_VAL_SIZE, buf,
			UI_VAL_SIZE))
	{
		printf("Fail to read frequency!\n");
		return ERROR ;
	}
	uint16_t count;
	memcpy(&count, buf, UI_VAL_SIZE);
	printf("%d\n", (int)count);
	return OK ;
}
