/*
 * Final Line following.c
 *
 * Created: 02-02-2016 10:31:32 PM
 * Author : Rishabh Sheth
			Team eYRC#1263-HD
 *			Dharmsinh Desai University, Nadiad
 
 */ 


#include "setup.h"


int node=0;
unsigned char sharp;
unsigned int dis_value;


void find_node ()
{
	while (1)
	{
		Left_white_line = ADC_Conversion(3);	//Getting data of Left WL Sensor
		Center_white_line = ADC_Conversion(2);	//Getting data of Center WL Sensor
		Right_white_line = ADC_Conversion(1);	//Getting data of Right WL Sensor

		flag=0;
		
		if ((Center_white_line>0x10 && Left_white_line>0x10)|| (Center_white_line>0x10 && Right_white_line>0x10) )
		{
			forward();
			velocity(0,0);
			break;
		}
		
		else if(Center_white_line>0x10)
		{
			flag=1;
			forward();
			velocity(150,150);
		}

		else if ((Center_white_line>0x10 && Left_white_line>0x10)|| (Center_white_line>0x10 && Right_white_line>0x10) )
		{
			forward();
			velocity(0,0);
		}
		
		else if((Left_white_line>0x10) && (flag==0))
		{
			flag=1;
			forward();
			velocity(0,100);
		}

		else if((Right_white_line>0x10) && (flag==0))
		{
			flag=1;
			forward();
			velocity(100,0);
		}	
	}
	node++;
}

void turn()
{
	switch(node)
	{
		case 1:
		{
			forward();
			velocity(0,100);
			_delay_ms(3000);
			break;
		}
		case 2:
		{
			forward();
			velocity(100,0);
			_delay_ms(4000);
			break;
		}
		default:
		{
			forward();
			velocity(0,0);
			break;
		}
	}
}

void find_distance()
{
	sharp = ADC_Conversion(11);						//Stores the Analog value of front sharp connected to ADC channel 11 into variable "sharp"
	dis_value = Sharp_GP2D12_estimation(sharp);
}

int main(void)
{
    init_devices();
	/*lcd_set_4bit();
	lcd_init();
	*/

    find_node();
	find_distance();
	/*lcd_print(1,5,dis_value,3); */							//Prints Value Of Distanc in MM measured by Sharp Sensor.

	if(dis_value>450)
	{
		
		forward();
		velocity(0,250);
		_delay_ms(500);
		find_node();
	}
	else
	{
		forward();
		velocity(100,100);
		_delay_ms(500);
		find_node();
		velocity(100,100);
		_delay_ms(250);
		find_node();
	}

	/*turn();
	find_node();
	turn(); 
	find_node();*/   
	
	
}

