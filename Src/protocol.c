#include "include.h"

S_Protocol_Info g_protocol_info;

void motor_goto_angle(P_S_Motor_Info motor_info,float angle)
{	
	float operat_angle;
	operat_angle = angle - motor_info->current_angle;
	if(operat_angle > 0)
		{
			operat_motor(1, 220.0,operat_angle, motor_info);
		}
	if(operat_angle < 0)
		{
			operat_motor(0, 220.0,operat_angle, motor_info);
		}
}

unsigned char adjust_protocol(unsigned char* protocol)
{
	unsigned char data_length = 0;
	data_length = *(protocol + 3);
	if(VerifyCRC8Sub(protocol,data_length))
		{
			return 1;
		}
	else
		{
			return 0;
		}
	
}

void pretreatment_protocol(unsigned char* protocol,P_S_Protocol_Info protocol_info)//预处理通信帧
{
	protocol_info->address = *(protocol + 2);
	protocol_info->this_protocol_length= *(protocol + 3);
	protocol_info->command= (E_Motor_Ctrl_Command)*(protocol + 4);
	protocol_info->parameter= (protocol + 5);	
}

void execute_protocol(P_S_Protocol_Info protocol_info)
{
	float parameter= 0.0;
	int int_parameter = 0;
	unsigned char recv_parameter[10]={0};
	if((machine_info.this_machime_adress != protocol_info->address)&&(0XFF != protocol_info->address))
		{
			return;
		}
	switch(protocol_info->command)
		{
			case motor_reset:
				adjust_motor(&motor_1_info);
				adjust_motor(&motor_2_info);
				break;
				
			case motor_goto_start_position:
				break;
				
			case motor_set_mod:
				break;

			case motor_start_show:
				break;

			case motor_pause_show:
				break;

			case motor_stop_show:
				break;

			case motor1_goto_angle:
				recv_parameter[0] = *(protocol_info->parameter);
				recv_parameter[1] = *(protocol_info->parameter+1);
				int_parameter = (((int)recv_parameter[0])<<8) + recv_parameter[1];
				parameter = (float)int_parameter;
				parameter = parameter/10;
				motor_goto_angle(&motor_1_info,parameter);
				break;

			case motor2_goto_angle:
				recv_parameter[0] = *(protocol_info->parameter);
				recv_parameter[1] = *(protocol_info->parameter+1);
				int_parameter = (((int)recv_parameter[0])<<8) + recv_parameter[1];
				parameter = (float)int_parameter;
				parameter = parameter/10;
				motor_goto_angle(&motor_2_info,parameter);
				break;

			case motor_goto_posiation:
				break;

			case save_motor_posiation_info:
				break;

			case save_motor_end_posiation_info:
				break;

			case delete_all_motor_posiation_info:
				break;
				
			case polling_all_motor_posiation_info:
				break;

			case polling_motor_rs485_info:
				break;

			case test_motor_driver:
				recv_parameter[0] = *(protocol_info->parameter);
				recv_parameter[1] = *(protocol_info->parameter+1);
				int_parameter = (((int)recv_parameter[0])<<8) + recv_parameter[1];
				parameter = (float)int_parameter;
				operat_motor(1,parameter,2000.0,&motor_1_info);
				operat_motor(1,parameter,2000.0,&motor_2_info);
				break;
				



			default :
				break;
		}
}

void deal_protocol(unsigned char* protocol)
{
	if(0 == adjust_protocol(protocol))
		{
			return;
		}
	pretreatment_protocol(protocol,&g_protocol_info);
	execute_protocol(&g_protocol_info);
}


