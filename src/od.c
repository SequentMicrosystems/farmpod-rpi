#include <stdio.h>
#include <stdlib.h>

#include "comm.h"
#include "data.h"
#include "od.h"

const CliCmdType CMD_OD_FISH_READ = {
	"ffrd",
        1,
        &doOdFishRead,
        "  ffrd             Read od fish feeder state\n",
        "  Usage 1:         "PROGRAM_NAME" ffrd <channel[1.."STR(OD_FISH_CH_NO)"]>\n"
        "  Usage 2:         "PROGRAM_NAME" ffrd\n",
        "  Example:         "PROGRAM_NAME" ffrd 2  Get the state of fish feeder od #2\n"
};
int doOdFishRead(int argc, char *argv[]) {
        if(!(argc == 2 || argc == 3)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 2) {
		uint8_t buf[1];
                if(OK != i2cMem8Read(dev, I2C_MEM_OD_FISH_VAL, buf, 1)) {
                        printf("Fail to read!\n");
                        return ERROR;
                }
		for(int rel = 1; rel <= OD_FISH_CH_NO; ++rel) {
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
		if(OK != i2cMem8Read(dev, I2C_MEM_OD_FISH_VAL, buf, 1)) {
			printf("Fail to read!\n");
			return ERROR;
		}
		int rel = atoi(argv[2]);
                if(!(1 <= rel && rel <= OD_FISH_CH_NO)) {
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

const CliCmdType CMD_OD_FISH_WRITE = {
	"ffwr",
        2,
        &doOdFishWrite,
        "  ffwr             Change od fish feeder state\n",
        "  Usage 1:         "PROGRAM_NAME" ffwr <channel[1.."STR(OD_FISH_CH_NO)"]> <state(0/1)>\n"
        "  Usage 2:         "PROGRAM_NAME" ffwr <mask[0.."STR(MASK(OD_FISH_CH_NO))"]>\n",
        "  Example:         "PROGRAM_NAME" ffwr 2 1  Set the state of od fish feeder #2 to ON\n"
};
int doOdFishWrite(int argc, char *argv[]) {
        if(!(argc == 3 || argc == 4)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(0);
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 3) {
                int state = 0;
                state = atoi(argv[2]);
                if(!(0 <= state && state <= (1 << OD_FISH_CH_NO) - 1)) {
                        return ARG_RANGE_ERROR;
                }
                uint8_t buf[1];
                buf[0] = 0xff & state;
                if(OK != i2cMem8Write(dev, I2C_MEM_OD_FISH_VAL, buf, 1)) {
                        printf("Fail to write!\n");
                        return ERROR;
                }
        }
        else if(argc == 4) {
                int state = 0;
                int rel = atoi(argv[2]);
                if(!(1 <= rel && rel <= OD_FISH_CH_NO)) {
			printf("Led number out of range");
                        return ARG_RANGE_ERROR;
                }
                state = atoi(argv[3]);
                uint8_t buf[1];
                buf[0] = 0xff & rel;
                if(state > 0) {
                        if(OK != i2cMem8Write(dev, I2C_MEM_OD_FISH_SET, buf, 1)) {
                                printf("Fail to write!\n");
                                return ERROR;
                        }
                }
                else {
                        if(OK != i2cMem8Write(dev, I2C_MEM_OD_FISH_CLR, buf, 1)) {
                                printf("Fail to write!\n");
                                return ERROR;
                        }
                }
        }
        return OK;
}


const CliCmdType CMD_OD_PERI_READ = {
	"pprd",
        1,
        &doOdPeriRead,
        "  pprd             Read od peri state\n",
        "  Usage 1:         "PROGRAM_NAME" pprd <channel[1.."STR(OD_PERI_CH_NO)"]>\n"
        "  Usage 2:         "PROGRAM_NAME" pprd\n",
        "  Example:         "PROGRAM_NAME" pprd 2  Get the state of peri od #2\n"
};
int doOdPeriRead(int argc, char *argv[]) {
        if(!(argc == 3 || argc == 4)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 3) {
		uint8_t buf[1];
                if(OK != i2cMem8Read(dev, I2C_MEM_OD_PERI_VAL, buf, 1)) {
                        printf("Fail to read!\n");
                        return ERROR;
                }
		for(int rel = 1; rel <= OD_PERI_CH_NO; ++rel) {
			if(buf[0] & (1 << (rel - 1))) {
				printf("1 ");
			} else {
				printf("0 ");
			}
		}
		printf("\n");
        }
        else if(argc == 4) {
		uint8_t buf[1];
		if(OK != i2cMem8Read(dev, I2C_MEM_OD_PERI_VAL, buf, 1)) {
			printf("Fail to read!\n");
			return ERROR;
		}
		int rel = atoi(argv[3]);
                if(!(1 <= rel && rel <= OD_PERI_CH_NO)) {
			printf("Fish feeder number out of range");
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

const CliCmdType CMD_OD_PERI_WRITE = {
	"ppwr",
        2,
        &doOdPeriWrite,
        "  ppwr             Set od peri state\n",
        "  Usage 1:         "PROGRAM_NAME" ppwr <channel[1.."STR(OD_PERI_CH_NO)"]> <state(0/1)>\n"
        "  Usage 2:         "PROGRAM_NAME" ppwr <mask[0.."STR(MASK(OD_PERI_CH_NO))"]>\n",
        "  Example:         "PROGRAM_NAME" ppwr 2 1  Set the state of od peri #2 to ON\n"
};
int doOdPeriWrite(int argc, char *argv[]) {
        if(!(argc == 4 || argc == 5)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if(dev < 0) {
                return ERROR;
        }
        if(argc == 4) {
                int state = 0;
                state = atoi(argv[3]);
                if(!(0 <= state && state <= (1 << OD_PERI_CH_NO) - 1)) {
                        return ARG_RANGE_ERROR;
                }
                uint8_t buf[1];
                buf[0] = 0xff & state;
                if(OK != i2cMem8Write(dev, I2C_MEM_OD_PERI_VAL, buf, 1)) {
                        printf("Fail to write!\n");
                        return ERROR;
                }
        }
        else if(argc == 5) {
                int state = 0;
                int rel = atoi(argv[3]);
                if(!(1 <= rel && rel <= OD_PERI_CH_NO)) {
			printf("Peristaltic pump number out of range");
                        return ARG_RANGE_ERROR;
                }
                state = atoi(argv[4]);
                uint8_t buf[1];
                buf[0] = 0xff & rel;
                if(state > 0) {
                        if(OK != i2cMem8Write(dev, I2C_MEM_OD_PERI_SET, buf, 1)) {
                                printf("Fail to write!\n");
                                return ERROR;
                        }
                }
                else {
                        if(OK != i2cMem8Write(dev, I2C_MEM_OD_PERI_CLR, buf, 1)) {
                                printf("Fail to write!\n");
                                return ERROR;
                        }
                }
        }
        return OK;
}
