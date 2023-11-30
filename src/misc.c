#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"
#include "data.h"
#include "misc.h"


const CliCmdType CMD_WATER_READ = {
	"wlrd",
	1,
	&doWaterRead,
	"  wlrd             Read water level(as bitmask).\n",
	"  Usage 1:         "PROGRAM_NAME" wlrd\n",
	"  Example:         "PROGRAM_NAME" wlrd  Get bitmask for the 6 sensors.\n"
};
int doWaterRead(int argc, char *argv[])
{
	(void)argv;
	if (! (argc == 2))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	uint8_t buf[1];
	if (OK != i2cMem8Read(dev, I2C_MEM_WATER_LEVEL, buf, 1))
	{
		printf("Fail to read!\n");
		return ERROR ;
	}
	printf("%d\n", (int)buf[0]);
	return OK ;
}

const CliCmdType CMD_FISH_I_READ = {
	"crtrd",
	1,
	&doFfIRead,
	"  crtrd            Get fish fedders current consumption in mA\n",
	"  Usage:           "PROGRAM_NAME" crtrd <channel[1.."STR(CRT_CH_NO)"]>\n",
	"  Example:         "PROGRAM_NAME" crtrd 2  Get fish fedder #2 current consumption in mA\n"
};

int doFfIRead(int argc, char *argv[])
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
	if (! (1 <= ch && ch <= CRT_CH_NO))
	{
		printf("Current channel out of range!\n");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[UI_VAL_SIZE];
	if (OK
		!= i2cMem8Read(dev, I2C_MEM_CRT1 + (ch - 1) * UI_VAL_SIZE, buf,
			UI_VAL_SIZE))
	{
		printf("Fail to read current consumption!\n");
		return ERROR ;
	}
	uint16_t curr;
	memcpy(&curr, buf, 2);
	printf("%d\n", (int)curr);
	return OK ;
}

const CliCmdType CMD_COOL_WRITE = {
	"coolwr",
	1,
	&doCoolWrite,
	"  coolwr           Set the colling fan power [0..100]\n",
	"  Usage:           "PROGRAM_NAME" coolwr <power[0..100]>\n",
	"  Example:         "PROGRAM_NAME" coolwr 50  Set the cooling fan to half power\n"
};

int doCoolWrite(int argc, char *argv[])
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
	int power = atoi(argv[2]);
	if (! (0 <= power && power <= 100))
	{
		printf("Fan power out of range!\n");
		return ARG_RANGE_ERROR;
	}

	uint8_t pwm = (uint8_t)power;
	if (OK
		!= i2cMem8Write(dev, I2C_MEM_FAN_POWER , &pwm,
			1))
	{
		printf("Fail to set cooling power!\n");
		return ERROR ;
	}
	return OK ;
}


