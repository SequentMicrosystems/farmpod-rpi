#include <stdio.h>
#include <stdlib.h>

#include "comm.h"
#include "data.h"
#include "relay.h"

const CliCmdType CMD_RELAY_FAN_READ =
{
	"fanrd",
	1,
	&doRelayFanRead,
	"  fanrd            Read fan relay state\n",
	"  Usage 1:         "PROGRAM_NAME" fanrd <channel[1.."STR(RELAY_FAN_CH_NO)"]>\n"
	"  Usage 2:         "PROGRAM_NAME" fanrd\n",
	"  Example:         "PROGRAM_NAME" fanrd 2  Get the state of fan relay #2\n"
};
int doRelayFanRead(int argc, char *argv[])
{
	if (! (argc == 2 || argc == 3))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 2)
	{
		uint8_t buf[1];
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_FAN_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		for (int fan = 1; fan <= RELAY_FAN_CH_NO; ++fan)
		{
			if (buf[0] & (1 << (fan - 1)))
			{
				printf("1 ");
			}
			else
			{
				printf("0 ");
			}
		}
		printf("\n");
	}
	else if (argc == 3)
	{
		uint8_t buf[1];
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_FAN_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		int fan = atoi(argv[2]);
		if (! (1 <= fan && fan <= RELAY_FAN_CH_NO))
		{
			printf("Led number out of range");
			return ARG_RANGE_ERROR;
		}
		if (buf[0] & (1 << (fan - 1)))
		{
			printf("1\n"); /* fan ON */
		}
		else
		{
			printf("0\n");
		}
	}
	return OK ;
}

const CliCmdType CMD_RELAY_FAN_WRITE =
{
	"fanwr",
	1,
	&doRelayFanWrite,
	"  fanwr            Change fan relay state\n",
	"  Usage 1:         "PROGRAM_NAME" fanwSr <channel[1.."STR(RELAY_FAN_CH_NO)"]> <state(0/1)>\n"
	"  Usage 2:         "PROGRAM_NAME" fanwr <mask[0.."STR(MASK(RELAY_FAN_CH_NO))"]>\n",
	"  Example:         "PROGRAM_NAME" fanwr 2 1  Set the state of fan relay #2 to ON\n"
};
int doRelayFanWrite(int argc, char *argv[])
{
	if (! (argc == 3 || argc == 4))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 3)
	{
		int state = 0;
		state = atoi(argv[2]);
		if (! (0 <= state && state <= (1 << RELAY_FAN_CH_NO) - 1))
		{
			return ARG_RANGE_ERROR;
		}
		uint8_t buf[1];
		buf[0] = 0xff & state;
		if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_FAN_VAL, buf, 1))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
	}
	else if (argc == 4)
	{
		int state = 0;
		int fan = atoi(argv[2]);
		if (! (1 <= fan && fan <= RELAY_FAN_CH_NO))
		{
			printf("Led number out of range");
			return ARG_RANGE_ERROR;
		}
		state = atoi(argv[3]);
		uint8_t buf[1];
		buf[0] = 0xff & fan;
		if (state > 0)
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_FAN_SET, buf, 1))
			{
				printf("Fail to write!\n");
				return ERROR ;
			}
		}
		else
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_FAN_CLR, buf, 1))
			{
				printf("Fail to write!\n");
				return ERROR ;
			}
		}
	}
	return OK ;
}

const CliCmdType CMD_RELAY_LIGHT_READ =
{
	"litrd",
	1,
	&doRelayLightRead,
	"  litrd            Read light relay state\n",
	"  Usage 1:         "PROGRAM_NAME" litrd <channel[1.."STR(RELAY_LIGHT_CH_NO)"]>\n"
	"  Usage 2:         "PROGRAM_NAME" litrd\n",
	"  Example:         "PROGRAM_NAME" litrd 2  Get the state of light relay #2\n"
};
int doRelayLightRead(int argc, char *argv[])
{
	if (! (argc == 2 || argc == 3))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 2)
	{
		uint8_t buf[1];
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_LIGHT_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		for (int rel = 1; rel <= RELAY_LIGHT_CH_NO; ++rel)
		{
			if (buf[0] & (1 << (rel - 1)))
			{
				printf("1 ");
			}
			else
			{
				printf("0 ");
			}
		}
		printf("\n");
	}
	else if (argc == 3)
	{
		uint8_t buf[1];
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_LIGHT_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		int rel = atoi(argv[2]);
		if (! (1 <= rel && rel <= RELAY_LIGHT_CH_NO))
		{
			printf("Led number out of range");
			return ARG_RANGE_ERROR;
		}
		if (buf[0] & (1 << (rel - 1)))
		{
			printf("1\n"); /* rel ON */
		}
		else
		{
			printf("0\n");
		}
	}
	return OK ;
}

const CliCmdType CMD_RELAY_LIGHT_WRITE =
{
	"litwr",
	1,
	&doRelayLightWrite,
	"  litwr            Change light relay state\n",
	"  Usage 1:         "PROGRAM_NAME" litwr <channel[1.."STR(RELAY_LIGHT_CH_NO)"]> <state(0/1)>\n"
	"  Usage 2:         "PROGRAM_NAME" litwr <mask[0.."STR(MASK(RELAY_LIGHT_CH_NO))"]>\n",
	"  Example:         "PROGRAM_NAME" litwr 2 1  Set the state of light relay #2 to ON\n"
};
int doRelayLightWrite(int argc, char *argv[])
{
	if (! (argc == 3 || argc == 4))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 3)
	{
		int state = 0;
		state = atoi(argv[2]);
		if (! (0 <= state && state <= (1 << RELAY_LIGHT_CH_NO) - 1))
		{
			return ARG_RANGE_ERROR;
		}
		uint8_t buf[1];
		buf[0] = 0xff & state;
		if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_LIGHT_VAL, buf, 1))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
	}
	else if (argc == 4)
	{
		int state = 0;
		int rel = atoi(argv[2]);
		if (! (1 <= rel && rel <= RELAY_LIGHT_CH_NO))
		{
			printf("Channel number out of range\n");
			return ARG_RANGE_ERROR;
		}
		state = atoi(argv[3]);
		uint8_t buf[1];
		buf[0] = 0xff & rel;
		if (state > 0)
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_LIGHT_SET, buf, 1))
			{
				printf("Fail to write!\n");
				return ERROR ;
			}
		}
		else
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_LIGHT_CLR, buf, 1))
			{
				printf("Fail to write!\n");
				return ERROR ;
			}
		}
	}
	return OK ;
}

const CliCmdType CMD_RELAY_PUMP_READ =
{
	"pumprd",
	1,
	&doRelayPumpRead,
	"  pumprd           Read pump relay state\n",
	"  Usage 1:         "PROGRAM_NAME" pumprd <channel[1.."STR(RELAY_PUMP_CH_NO)"]>\n"
	"  Usage 2:         "PROGRAM_NAME" pumprd\n",
	"  Example:         "PROGRAM_NAME" pumprd 2  Get the state of relay pump #2\n"
};
int doRelayPumpRead(int argc, char *argv[])
{
	if (! (argc == 2 || argc == 3))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 2)
	{
		uint8_t buf[1];
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_PUMP_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		for (int rel = 1; rel <= RELAY_PUMP_CH_NO; ++rel)
		{
			if (buf[0] & (1 << (rel - 1)))
			{
				printf("1 ");
			}
			else
			{
				printf("0 ");
			}
		}
		printf("\n");
	}
	else if (argc == 3)
	{
		uint8_t buf[1];
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_PUMP_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		int rel = atoi(argv[2]);
		if (! (1 <= rel && rel <= RELAY_PUMP_CH_NO))
		{
			printf("Led number out of range");
			return ARG_RANGE_ERROR;
		}
		if (buf[0] & (1 << (rel - 1)))
		{
			printf("1\n"); /* rel ON */
		}
		else
		{
			printf("0\n");
		}
	}
	return OK ;
}

const CliCmdType CMD_RELAY_PUMP_WRITE =
{
	"pumpwr",
	1,
	&doRelayPumpWrite,
	"  pumpwr           Change pump relay state\n",
	"  Usage 1:         "PROGRAM_NAME" pumpwr <channel[1.."STR(RELAY_PUMP_CH_NO)"]> <state(0/1)>\n"
	"  Usage 2:         "PROGRAM_NAME" pumpwr <mask[0.."STR(MASK(RELAY_PUMP_CH_NO))"]>\n",
	"  Example:         "PROGRAM_NAME" pumpwr 2 1  Set the state of pump relay #2 to ON\n"
};
int doRelayPumpWrite(int argc, char *argv[])
{
	if (! (argc == 3 || argc == 4))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 3)
	{
		int state = 0;
		state = atoi(argv[2]);
		if (! (0 <= state && state <= (1 << RELAY_PUMP_CH_NO) - 1))
		{
			return ARG_RANGE_ERROR;
		}
		uint8_t buf[1];
		buf[0] = 0xff & state;
		if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_PUMP_VAL, buf, 1))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
	}
	else if (argc == 4)
	{
		int state = 0;
		int rel = atoi(argv[2]);
		if (! (1 <= rel && rel <= RELAY_PUMP_CH_NO))
		{
			printf("Channel number out of range\n");
			return ARG_RANGE_ERROR;
		}
		state = atoi(argv[3]);
		uint8_t buf[1];
		buf[0] = 0xff & rel;
		if (state > 0)
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_PUMP_SET, buf, 1))
			{
				printf("Fail to write!\n");
				return ERROR ;
			}
		}
		else
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_PUMP_CLR, buf, 1))
			{
				printf("Fail to write!\n");
				return ERROR ;
			}
		}
	}
	return OK ;
}

const CliCmdType CMD_RELAY_SPARE_READ =
{
	"sprd",
	1,
	&doRelaySpareRead,
	"  sprd            Read spare relay state\n",
	"  Usage 1:         "PROGRAM_NAME" sprd <channel[1.."STR(RELAY_SPARE_CH_NO)"]>\n"
	"  Usage 2:         "PROGRAM_NAME" sprd\n",
	"  Example:         "PROGRAM_NAME" sprd 2  Get the state of relay spare #2\n"
};
int doRelaySpareRead(int argc, char *argv[])
{
	if (! (argc == 2 || argc == 3))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 2)
	{
		uint8_t buf[1];
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_SPARE_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		for (int rel = 1; rel <= RELAY_SPARE_CH_NO; ++rel)
		{
			if (buf[0] & (1 << (rel - 1)))
			{
				printf("1 ");
			}
			else
			{
				printf("0 ");
			}
		}
		printf("\n");
	}
	else if (argc == 3)
	{
		uint8_t buf[1];
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_SPARE_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		int rel = atoi(argv[2]);
		if (! (1 <= rel && rel <= RELAY_SPARE_CH_NO))
		{
			printf("Channel number out of range\n");
			return ARG_RANGE_ERROR;
		}
		if (buf[0] & (1 << (rel - 1)))
		{
			printf("1\n"); /* rel ON */
		}
		else
		{
			printf("0\n");
		}
	}
	return OK ;
}

const CliCmdType CMD_RELAY_SPARE_WRITE =
{
	"spwr",
	1,
	&doRelaySpareWrite,
	"  spwr             Change spare relay state\n",
	"  Usage 1:         "PROGRAM_NAME" spwr <channel[1.."STR(RELAY_SPARE_CH_NO)"]> <state(0/1)>\n"
	"  Usage 2:         "PROGRAM_NAME" spwr <mask[0.."STR(MASK(RELAY_SPARE_CH_NO))"]>\n",
	"  Example:         "PROGRAM_NAME" spwr 2 1  Set the state of spare relay #2 to ON\n"
};
int doRelaySpareWrite(int argc, char *argv[])
{
	if (! (argc == 3 || argc == 4))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}
	if (argc == 3)
	{
		int state = 0;
		state = atoi(argv[2]);
		if (! (0 <= state && state <= (1 << RELAY_SPARE_CH_NO) - 1))
		{
			return ARG_RANGE_ERROR;
		}
		uint8_t buf[1];
		buf[0] = 0xff & state;
		if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_SPARE_VAL, buf, 1))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
	}
	else if (argc == 4)
	{
		int state = 0;
		int rel = atoi(argv[2]);
		if (! (1 <= rel && rel <= RELAY_SPARE_CH_NO))
		{
			printf("Channel number out of range\n");
			return ARG_RANGE_ERROR;
		}
		state = atoi(argv[3]);
		uint8_t buf[1];
		buf[0] = 0xff & rel;
		if (state > 0)
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_SPARE_SET, buf, 1))
			{
				printf("Fail to write!\n");
				return ERROR ;
			}
		}
		else
		{
			if (OK != i2cMem8Write(dev, I2C_MEM_RELAY_SPARE_CLR, buf, 1))
			{
				printf("Fail to write!\n");
				return ERROR ;
			}
		}
	}
	return OK ;
}

// All relays --------------------------------------------------

const CliCmdType CMD_RELAY_READ =
{
	"relrd",
	1,
	&doRelayRead,
	"  relrd            Read one of 22 relay state\n",
	"  Usage :         "PROGRAM_NAME" relrd <channel[1.."STR(RELAY_CH_NO)"]>\n"
	"",
	"  Example:         "PROGRAM_NAME" relrd 2  Get the state of relay #2\n"
};
int doRelayRead(int argc, char *argv[])
{
	if (! (argc == 3))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}

	int relay = atoi(argv[2]);
	if (! (1 <= relay && relay <= RELAY_CH_NO))
	{
		printf("Relay number out of range");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[1];
	uint8_t shift = 0;
	if (relay <= RELAY_FAN_CH_NO)
	{
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_FAN_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		shift = relay - 1;
	}
	else if (relay <= RELAY_FAN_CH_NO + RELAY_LIGHT_CH_NO)
	{
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_LIGHT_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		shift = relay - RELAY_FAN_CH_NO - 1;

	}
	else if (relay <= RELAY_FAN_CH_NO + RELAY_LIGHT_CH_NO + RELAY_PUMP_CH_NO)
	{
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_PUMP_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		shift = relay - RELAY_FAN_CH_NO - RELAY_LIGHT_CH_NO - 1;
	}
	else
	{
		if (OK != i2cMem8Read(dev, I2C_MEM_RELAY_SPARE_VAL, buf, 1))
		{
			printf("Fail to read!\n");
			return ERROR ;
		}
		shift = relay - RELAY_FAN_CH_NO - RELAY_LIGHT_CH_NO - RELAY_PUMP_CH_NO
			- 1;
	}

	if (buf[0] & (1 << shift))
	{
		printf("1\n"); /* relay ON */
	}
	else
	{
		printf("0\n");
	}

	return OK ;
}

const CliCmdType CMD_RELAY_WRITE =
{
	"relwr",
	1,
	&doRelayWrite,
	"  relwr            Change relay state\n",
	"  Usage :         "PROGRAM_NAME" relwr <channel[1.."STR(RELAY_CH_NO)"]> <state(0/1)>\n"
	"",
	"  Example:         "PROGRAM_NAME" relwr 2 1  Set the state of relay #2 to ON\n"
};
int doRelayWrite(int argc, char *argv[])
{
	if (! (argc == 4))
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(0);
	if (dev < 0)
	{
		return ERROR ;
	}

	int state = 0;
	int relay = atoi(argv[2]);
	if (! (1 <= relay && relay <= RELAY_CH_NO))
	{
		printf("Relay number out of range");
		return ARG_RANGE_ERROR;
	}
	state = atoi(argv[3]);

	uint8_t add = I2C_MEM_RELAY_FAN_SET;
	uint8_t count = 0;
	if(relay <= RELAY_FAN_CH_NO)
	{
		count = relay;
		add = I2C_MEM_RELAY_FAN_SET;
	}
	else if(relay <= RELAY_FAN_CH_NO + RELAY_LIGHT_CH_NO)
	{
		count = relay - RELAY_FAN_CH_NO;
		add = I2C_MEM_RELAY_LIGHT_SET;
	}
	else if(relay <= RELAY_FAN_CH_NO + RELAY_LIGHT_CH_NO + RELAY_PUMP_CH_NO)
	{
		count = relay - RELAY_FAN_CH_NO - RELAY_LIGHT_CH_NO;
		add = I2C_MEM_RELAY_PUMP_SET;
	}
	else
	{
		count = relay - RELAY_FAN_CH_NO - RELAY_LIGHT_CH_NO - RELAY_PUMP_CH_NO;
		add = I2C_MEM_RELAY_SPARE_SET;
	}
	uint8_t buf[1];
	buf[0] = 0xff & count;
	if (state > 0)
	{
		if (OK != i2cMem8Write(dev, add, buf, 1))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
	}
	else
	{
		if (OK != i2cMem8Write(dev, add + 1, buf, 1))
		{
			printf("Fail to write!\n");
			return ERROR ;
		}
	}

	return OK ;
}
