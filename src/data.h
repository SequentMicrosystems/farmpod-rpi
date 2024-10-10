#ifndef DATA_H
#define DATA_H

#define CARD_NAME "Farmpod Controller"
#define PROGRAM_NAME "frpc"
#define VERSION "1.0.3"
#define SLAVE_OWN_ADDRESS_BASE 0x50

#define MIN_CH_NO 1

#define RTD_CH_NO 2
#define RTD_TEMP_DATA_SIZE 4
#define RTD_RES_DATA_SIZE 4

#define CRT_CH_NO 4
#define UI_VAL_SIZE 2
#define OWB_SENS_CNT 16
#define OWB_TEMP_SIZE_B 2

#define RELAY_FAN_CH_NO 6
#define RELAY_LIGHT_CH_NO 8
#define RELAY_PUMP_CH_NO 4
#define RELAY_SPARE_CH_NO 4
#define RELAY_CH_NO 22

#define OD_FISH_CH_NO 4
#define OD_PERI_CH_NO 4

#define VALVE_CH_NO 8

#define FLOW_CH_NO 2

#define CALIBRATION_KEY 0xaa
#define RESET_CALIBRATION_KEY	0x55

#define COUNTER_SIZE 4
#define FREQUENCY_SIZE 2

#define WDT_RESET_SIGNATURE 0xca
#define WDT_RESET_COUNT_SIGNATURE 0xbe

enum
{
	CALIB_IN_PROGRESS = 0,
	CALIB_DONE,
	CALIB_ERROR,
};

enum CALIB_CHANNELS
{
	CAL_NONE_CH = 0,
	CAL_RTD_RES_CH1 = 1,
	CAL_RTD_RES_CH2,
	CAL_CRT1_CH,
	CAL_CRT2_CH,
	CAL_CRT3_CH,
	CAL_CRT4_CH,
	CAL_NO_CH
};

enum
{
	I2C_MEM_RELAY_FAN_VAL = 0,// current state of the relays that controls FAN's [0x00..0x3f](R/W) command options "fanwr" "fanrd"
	I2C_MEM_RELAY_FAN_SET, // turn ON one FAN [1..6] (W)
	I2C_MEM_RELAY_FAN_CLR, // turn OFF one FAN [1..6] (W)
	I2C_MEM_RELAY_LIGHT_VAL, // current state of the relays that controls lights [0x00..0xff](R/W) command option "litwr" "litrd"
	I2C_MEM_RELAY_LIGHT_SET, // turn ON one light [1..8] (W)
	I2C_MEM_RELAY_LIGHT_CLR,// turn OFF one light [1..8] (W)
	I2C_MEM_RELAY_PUMP_VAL,// current state of the relays that controls lights [0x00..0x0f](R/W) "pumpwr" "pumprd"
	I2C_MEM_RELAY_PUMP_SET, // turn on on pump [1..4] (W)
	I2C_MEM_RELAY_PUMP_CLR, // turn OFF one pump [1..4] (W)
	I2C_MEM_RELAY_SPARE_VAL, // current state of spare relays [0x00..0x0f] (R/W) "spwr" "sprd"
	I2C_MEM_RELAY_SPARE_SET, // turn ON one spare relay [1..4] (W)
	I2C_MEM_RELAY_SPARE_CLR, // turn OFF one spare relay [1..4] (W)

	I2C_MEM_OD_FISH_VAL, // current state of OD outputs that controls the fish feeders [0x00..0xff](R/W) "ffwr" "ffrd"
	I2C_MEM_OD_FISH_SET, // turn on one fish feeder [1..4] (W)
	I2C_MEM_OD_FISH_CLR, // turn off one fish feeder [1..4] (W)
	I2C_MEM_OD_PERI_VAL, // current state of OD outputs that controls peristaltic pumps [0x00..0xff](R/W) "ppwr" "pprd"
	I2C_MEM_OD_PERI_SET, // turn on one peri pump [1..4] (W)
	I2C_MEM_OD_PERI_CLR, // turn off one peri pump [1..4] (W)

	I2C_MEM_VALVE_STATE, // State of the  3wires valves position, bitmap 0-close, 1-open [0x00..0xff] (R)  "vstrd" (valve state read)
	I2C_MEM_VALVE_CLOSING, //Clossing in progress for the valves bitmap 1- valve moving to close, 0 valve stopped [0x00..0xff] (R) "vclrd: (valve closing read)
	I2C_MEM_VALVE_OPENING, //Opening in progress for the valves bitmap 1- valve moving to open, 0 valve stopped [0x00..0xff] (R) "voprd: (valve opening read)
	I2C_MEM_VALVE_CMD_OPEN, // Turn one valve to be open [1..8] (W) "vclwr"
	I2C_MEM_VALVE_CMD_CLOSE, // Turn one valve to be close[1..8] (W) "vopwr"

	I2C_MEM_WATER_LEVEL, // bitmap for 6 sensors [0x00..0x3f] (R) "wlrd" (water level read)
	I2C_MEM_FLOW_COUNTER1, // flow metter accumulation counter channel 1 u32 (R)
	I2C_MEM_FLOW_COUNTER2 = I2C_MEM_FLOW_COUNTER1 + COUNTER_SIZE, // flow meter accumulation counter channel 2 u32 (R)
	I2C_MEM_FLOW_FREQ1 = I2C_MEM_FLOW_COUNTER2 + COUNTER_SIZE, // flow meter channel 1 frequency (Hz or pulse per second) u16 (R)
	I2C_MEM_FLOW_FREQ2 = I2C_MEM_FLOW_FREQ1 + FREQUENCY_SIZE, // flow meter channel 2 frequency (Hz or pulse per second) u16 (R)
	I2C_MEM_FLOW_COUNT_RESET_CMD = I2C_MEM_FLOW_FREQ2 +  FREQUENCY_SIZE, // Reset command for  flow meter accumulation counter [1..2] (W)

	I2C_MEM_RTD_TEMP1, //2 channels RTD float as for multiio
	I2C_MEM_RTD_TEMP2 = I2C_MEM_RTD_TEMP1 + 4,
	I2C_MEM_RTD_RES1 = I2C_MEM_RTD_TEMP2 + 4,
	I2C_MEM_RTD_RES2 = I2C_MEM_RTD_RES1 + 4,

	I2C_MEM_CRT1 = I2C_MEM_RTD_RES2 + 4,// 4 x u16 current reading for the fish feeders current consumption in mA

	I2C_MEM_CALIB_CHANNEL = I2C_MEM_CRT1 + CRT_CH_NO * UI_VAL_SIZE,// calibration
	I2C_MEM_CALIB_KEY,
	I2C_MEM_CALIB_VALUE,
	I2C_MEM_CALIB_STATUS = I2C_MEM_CALIB_VALUE + 4,



	I2C_MEM_WDT_RESET_ADD,// watchdog as usual.
	I2C_MEM_WDT_INTERVAL_SET_ADD,
	I2C_MEM_WDT_INTERVAL_GET_ADD = I2C_MEM_WDT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_SET_ADD = I2C_MEM_WDT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_INIT_INTERVAL_GET_ADD = I2C_MEM_WDT_INIT_INTERVAL_SET_ADD + 2,
	I2C_MEM_WDT_RESET_COUNT_ADD = I2C_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
	I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD = I2C_MEM_WDT_RESET_COUNT_ADD + 2,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD
		+ 4,

	I2C_MEM_DIAG_TEMPERATURE = 0x72,
	I2C_MEM_DIAG_12V,
	I2C_MEM_DIAG_12V_1,
	I2C_MEM_DIAG_5V,
	I2C_MEM_DIAG_5V_1,
	I2C_MEM_FAN_POWER,

	I2C_MEM_REVISION_MAJOR = 0x78,
	I2C_MEM_REVISION_MINOR,

	I2C_MEM_DIAG_3V,
	I2C_MEM_DIAG_3V_1,




	I2C_MEM_CPU_RESET = 0xaa,

	SLAVE_BUFF_SIZE = 255
};

#define OK 0
#define ERROR -1
#define ARG_CNT_ERR -2
#define ARG_RANGE_ERROR -3

#define VOLT_TO_MILIVOLT 1000
#define MILIAMP_TO_MICROAMP 1000

#define OK 0
#define ERR -1
#define ARG_CNT_ERR -2
#define ARG_RANGE_ERR -3
#define IO_ERR -4

#define STR_(x) #x
#define STR(x) STR_(x)
#define MASK_1 1
#define MASK_2 3
#define MASK_3 7
#define MASK_4 15
#define MASK_5 31
#define MASK_6 63
#define MASK_7 127
#define MASK_(x) MASK_##x
#define MASK(x) MASK_(x)

typedef enum {
	ON,
	OFF,
	STATE_COUNT,
} State;

#endif /* DATA_H */
