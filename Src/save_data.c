#include "include.h"

S_Save_Learned_Device_Data Enocean_Switch;
S_Save_Learned_Device_Data Wireless_Body_Sensor; 
S_Save_Learned_Device_Data Wireless_Windows_Sensor;

void init_learn_space(void)
{
	read_flash(SWITCH_BASE_ADDRESS,(char*)&Enocean_Switch,sizeof(Enocean_Switch));
	read_flash(PIR_BASE_ADDRESS,(char*)&Wireless_Body_Sensor,sizeof(Wireless_Body_Sensor));
	read_flash(WINDOWS_BASE_ADDRESS,(char*)&Wireless_Windows_Sensor,sizeof(Wireless_Windows_Sensor));	
	
	if(Enocean_Switch.this_data_effect != EFFECT)
		{
			erase_flash(SWITCH_BASE_ADDRESS);
			read_flash(SWITCH_BASE_ADDRESS,(char*)&Enocean_Switch,sizeof(Enocean_Switch));
			Enocean_Switch.this_data_effect = EFFECT;
			write_flash(SWITCH_BASE_ADDRESS,(char*)&Enocean_Switch,sizeof(Enocean_Switch));
			
		}

	if(Wireless_Body_Sensor.this_data_effect != EFFECT)
		{
			erase_flash(PIR_BASE_ADDRESS);
			read_flash(PIR_BASE_ADDRESS,(char*)&Wireless_Body_Sensor,sizeof(Wireless_Body_Sensor));
			Wireless_Body_Sensor.this_data_effect = EFFECT;
			write_flash(PIR_BASE_ADDRESS,(char*)&Wireless_Body_Sensor,sizeof(Wireless_Body_Sensor));			
		}

	if(Wireless_Windows_Sensor.this_data_effect != EFFECT)
		{
			erase_flash(WINDOWS_BASE_ADDRESS);
			read_flash(WINDOWS_BASE_ADDRESS,(char*)&Wireless_Windows_Sensor,sizeof(Wireless_Windows_Sensor));
			Wireless_Windows_Sensor.this_data_effect = EFFECT;
			write_flash(WINDOWS_BASE_ADDRESS,(char*)&Wireless_Windows_Sensor,sizeof(Wireless_Windows_Sensor));
		}
	

	check_learn_space(&Enocean_Switch);
	check_learn_space(&Wireless_Body_Sensor);
	check_learn_space(&Wireless_Windows_Sensor);
}

void check_learn_space(P_S_Save_Learned_Device_Data check_space)
{
	unsigned char loop8;
	check_space ->learned_number = 0;
	for(loop8 = 0;loop8<8;loop8++)
		{
			if(check_space->device[loop8].tcm300_ID[4] == EFFECT)
				{
					check_space ->learned_number ++;
				}
		}		
}

void count_device_delay_time(P_S_Save_Learned_Device_Data data)//计算各个学习的设备的延迟时间
{
	unsigned char loop8;
	if(data ->this_devices_effect == EFFECT)
		{
			data ->G_last_time_recv_data ++;
			data ->physical_pressed_time ++;
			for(loop8 = 0; loop8<8 ;loop8++)
				{
					if(data ->device[loop8].tcm300_ID[4] == 0X55)
						{
							if(data ->device[loop8].this_device_effect == EFFECT)
								{
									data->device[loop8].last_time_recv_data ++;
									if(data ->device[loop8].trigger_on == 1)
										{
											data ->device[loop8].count_trigger_on_time ++;
										}
									if(data ->device[loop8].trigger_off == 1)
										{
											data ->device[loop8].count_trigger_off_time ++;
										}
								}
						}
				}
		}
}



