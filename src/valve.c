#include <stdio.h>
#include <stdlib.h>

#include "comm.h"
#include "data.h"
#include "valve.h"

const CliCmdType CMD_VALVE_STATE_READ = {
	"vstrd",
        1,
        &doValveStateRead,
        "  vstrd            Read valve state\n",
        "  Usage 1:         "PROGRAM_NAME" vstrd <channel[1.."STR(VALVE_CH_NO)"]>\n"
        "  Usage 2:         "PROGRAM_NAME" vstrd\n",
        "  Example:         "PROGRAM_NAME" vstrd 2  Get the state valve #2\n"
};
int doValveStateRead(int argc, char *argv[]) {
        if(!(argc == 2 || argc == 3)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 2) {
		uint8_t buf[1];
                if(OK != i2cMem8Read(dev, I2C_MEM_VALVE_STATE, buf, 1)) {
                        printf("Fail to read!\n");
                        return ERROR;
                }
		for(int rel = 1; rel <= VALVE_CH_NO; ++rel) {
			if(buf[0] & (1 << (rel - 1))) {
				printf("1 ");
			} else {
				printf("0 ");
			}
		}
		printf("\n");
        }
        else if(argc == 3) {
		uint8_t buf[1];
		if(OK != i2cMem8Read(dev, I2C_MEM_VALVE_STATE, buf, 1)) {
			printf("Fail to read!\n");
			return ERROR;
		}
		int rel = atoi(argv[2]);
                if(!(1 <= rel && rel <= VALVE_CH_NO)) {
			printf("Led number out of range");
                        return ARG_RANGE_ERROR;
                }
		if(buf[0] & (1 << (rel - 1))) {
			printf("1\n"); /* rel ON */
		} else {
			printf("0\n");
		}
        }
        return OK;
} 

const CliCmdType CMD_VALVE_CLOSING_READ = {
	"vclrd",
        1,
        &doValveClosingRead,
        "  vclrd            Check if closing in progress for valve\n",
        "  Usage 1:         "PROGRAM_NAME" vclrd <channel[1.."STR(VALVE_CH_NO)"]>\n"
        "  Usage 2:         "PROGRAM_NAME" vclrd\n",
        "  Example:         "PROGRAM_NAME" vclrd 2  Get whether valve #2 is in closing process or not\n"
};
int doValveClosingRead(int argc, char *argv[]) {
        if(!(argc == 2 || argc == 3)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 2) {
		uint8_t buf[1];
                if(OK != i2cMem8Read(dev, I2C_MEM_VALVE_CLOSING, buf, 1)) {
                        printf("Fail to read!\n");
                        return ERROR;
                }
		for(int rel = 1; rel <= VALVE_CH_NO; ++rel) {
			if(buf[0] & (1 << (rel - 1))) {
				printf("1 ");
			} else {
				printf("0 ");
			}
		}
		printf("\n");
        }
        else if(argc == 3) {
		uint8_t buf[1];
		if(OK != i2cMem8Read(dev, I2C_MEM_VALVE_CLOSING, buf, 1)) {
			printf("Fail to read!\n");
			return ERROR;
		}
		int rel = atoi(argv[2]);
                if(!(1 <= rel && rel <= VALVE_CH_NO)) {
			printf("Valve number out of range");
                        return ARG_RANGE_ERROR;
                }
		if(buf[0] & (1 << (rel - 1))) {
			printf("1\n"); /* rel ON */
		} else {
			printf("0\n");
		}
        }
        return OK;
} 

const CliCmdType CMD_VALVE_OPENING_READ = {
	"voprd",
        1,
        &doValveOpeningRead,
        "  voprd            Check if opening in progress for valve\n",
        "  Usage 1:         "PROGRAM_NAME" voprd <channel[1.."STR(VALVE_CH_NO)"]>\n"
        "  Usage 2:         "PROGRAM_NAME" voprd\n",
        "  Example:         "PROGRAM_NAME" voprd 2  Get whether valve #2 is in opening process or not\n"
};
int doValveOpeningRead(int argc, char *argv[]) {
        if(!(argc == 2 || argc == 3)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 2) {
		uint8_t buf[1];
                if(OK != i2cMem8Read(dev, I2C_MEM_VALVE_OPENING, buf, 1)) {
                        printf("Fail to read!\n");
                        return ERROR;
                }
		for(int rel = 1; rel <= VALVE_CH_NO; ++rel) {
			if(buf[0] & (1 << (rel - 1))) {
				printf("1 ");
			} else {
				printf("0 ");
			}
		}
		printf("\n");
        }
        else if(argc == 3) {
		uint8_t buf[1];
		if(OK != i2cMem8Read(dev, I2C_MEM_VALVE_OPENING, buf, 1)) {
			printf("Fail to read!\n");
			return ERROR;
		}
		int rel = atoi(argv[2]);
                if(!(1 <= rel && rel <= VALVE_CH_NO)) {
			printf("Valve number out of range");
                        return ARG_RANGE_ERROR;
                }
		if(buf[0] & (1 << (rel - 1))) {
			printf("1\n"); /* rel ON */
		} else {
			printf("0\n");
		}
        }
        return OK;
} 

const CliCmdType CMD_VALVE_OPEN_WRITE = {
	"vopwr",
        2,
        &doValveOpenWrite,
        "  vopwr            Open valve.\n",
        "  Usage 1:         "PROGRAM_NAME" vopwr <channel[1.."STR(VALVE_CH_NO)"]>\n",
        "  Example:         "PROGRAM_NAME" vopwr 2  Open valve #2\n"
};
int doValveOpenWrite(int argc, char *argv[]) {
        if(argc != 3) {
		return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERROR;
        }
	int rel = atoi(argv[2]);
	if(!(1 <= rel && rel <= VALVE_CH_NO)) {
		printf("Valve number out of range");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[1];
	buf[0] = 0xff & rel;
	if(OK != i2cMem8Write(dev, I2C_MEM_VALVE_CMD_OPEN, buf, 1)) {
		printf("Fail to write!\n");
		return ERROR;
	}
        return OK;
}

const CliCmdType CMD_VALVE_CLOSE_WRITE = {
	"vclwr",
        2,
        &doValveCloseWrite,
        "  vclwr            Close valve.\n",
        "  Usage 1:         "PROGRAM_NAME" vclwr <channel[1.."STR(VALVE_CH_NO)"]>\n",
        "  Example:         "PROGRAM_NAME" vclwr 2  Close valve #2\n"
};
int doValveCloseWrite(int argc, char *argv[]) {
        if(argc != 3) {
		return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERROR;
        }
	int rel = atoi(argv[2]);
	if(!(1 <= rel && rel <= VALVE_CH_NO)) {
		printf("Valve number out of range");
		return ARG_RANGE_ERROR;
	}
	uint8_t buf[1];
	buf[0] = 0xff & rel;
	if(OK != i2cMem8Write(dev, I2C_MEM_VALVE_CMD_CLOSE, buf, 1)) {
		printf("Fail to write!\n");
		return ERROR;
	}
        return OK;
}
