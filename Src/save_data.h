#ifndef __SAVE_DATA_H__
#define __SAVE_DATA_H__
#include "include.h"


#define PRIORITY_SAVE_ADDR 		((FLASH_BASE)+(31*FLASH_PAGE_SIZE))
#define SWITCH_BASE_ADDRESS 	((FLASH_BASE)+(30*FLASH_PAGE_SIZE))
#define WINDOWS_BASE_ADDRESS 	((FLASH_BASE)+(29*FLASH_PAGE_SIZE))
#define PIR_BASE_ADDRESS 		((FLASH_BASE)+(28*FLASH_PAGE_SIZE))
#define APP_INFOR_SAVE_ADDR 	((FLASH_BASE)+(27*FLASH_PAGE_SIZE))


#define RTC_SAVE_ADDR			((FLASH_BASE)+(26*FLASH_PAGE_SIZE))

typedef struct
{
	unsigned char enble_turn_on_this_machine;
	unsigned char tcm300_ID[5];
	unsigned char this_device_effect;
	unsigned char trigger_data;
	
	unsigned char trigger_on;
	unsigned char trigger_off;
	
	unsigned char set_trigger_on_stat;
	unsigned char set_trigger_off_stat;
	
	unsigned char trigger_stat;
	
	unsigned int set_trigger_on_delay_time;
	unsigned int set_trigger_off_delay_time;
	unsigned int count_trigger_on_time;
	unsigned int count_trigger_off_time;
	unsigned int last_time_recv_data;
}S_Wireless_Device,*P_S_Wireless_Device;

typedef struct
{
	unsigned char find_point;
	unsigned char learned_number;
	unsigned int G_last_time_recv_data;
	unsigned int physical_pressed_time;
	unsigned char this_data_effect;
	unsigned char this_devices_effect;
	S_Wireless_Device device[8];
}S_Save_Learned_Device_Data,*P_S_Save_Learned_Device_Data;

extern S_Save_Learned_Device_Data Enocean_Switch;
extern S_Save_Learned_Device_Data Wireless_Body_Sensor; 
extern S_Save_Learned_Device_Data Wireless_Windows_Sensor;


void init_learn_space(void);
void check_learn_space(P_S_Save_Learned_Device_Data check_space);
void count_device_delay_time(P_S_Save_Learned_Device_Data data);

#endif

