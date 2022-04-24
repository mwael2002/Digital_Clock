/*
 * LCD_program.c

 *
 *  Created on: Sep 11, 2021
 *      Author: mwael
 */
#include"D:/C/bit_calc.h"
#include"D:/C/STD.Types.h"
#define F_CPU 8000000
#include<avr/delay.h>
#include"DIO_interface.h"
#include"LCD_config.h"
#include"LCD_private.h"
#include"LCD_interface.h"

void LCD_write_cmd(U8 cmd){
	DIO_set_pin_value(LCD_control_port,LCD_Rs_pin,LOW);
	LCD_write(cmd);
}
void LCD_write_data(U8 data){
	DIO_set_pin_value(LCD_control_port,LCD_Rs_pin,HIGH);
		LCD_write(data);
}
void LCD_write(U8 value){
	DIO_set_pin_value(LCD_control_port,LCD_Rw_pin,LOW);
	for(U8 i =0;i<8;i++){
		DIO_set_pin_value(LCD_data_port,i,get_bit(value,i));
	}
	DIO_set_pin_value(LCD_control_port,LCD_E_pin,HIGH);
	_delay_ms(1);
	DIO_set_pin_value(LCD_control_port,LCD_E_pin,LOW);
}
void LCD_clear(void){
	LCD_write_cmd(1);
}
U8 LCD_string_pos(char* string,U8 y,U8 x){
	U8 local_address;
	U8 error_state=0;
	U8 i=0;
	if((y<2)&&(x<16)){
		local_address=(x+(y*64));
		set_bit(local_address,7);
		LCD_write_cmd(local_address);
		while(string[i]!='\0'){
			if(local_address==144){
		local_address=192;
		LCD_write_cmd(local_address);
						}
			LCD_write_data(string[i]);
			i++; local_address++;
		}
	}
	else{
		error_state=1;
	}
	return error_state;
}
U8 LCD_clear_pos(U8 y,U8 x){
	U8 local_address;
		U8 error_state=0;
		if((y<2)&&(x<16)){
			local_address=(x+(y*64));
			set_bit(local_address,7);
			LCD_write_cmd(local_address);
			LCD_write_data(254);
		}
		else{
			error_state=1;
		}
		return error_state;

}
void LCD_write_no(U32 num,U8 y, U8 x){
	U8 rem,arr_index=0;
	static U8 str[15];
	static U8 str_2[15];
	if(num==0){
		str_2[arr_index]='0';
		arr_index++;
		str_2[1]='\0';
	}
	else{
		while(num!=0){
	rem=num%10;
	str[arr_index]=rem+'0';
	arr_index++;
	num=num/10;
	}
		str[arr_index]='\0';
		U8 j=0;
		for(S8 i=(arr_index-1);i>=0;i--){
			str_2[j]=str[i];
			j++;
		}
		str_2[j]='\0';
	}
	LCD_string_pos(str_2,y,x);
}
void LCD_init(void){
	DIO_set_port_direction(LCD_data_port,DIO_Max_Port_direction);
	DIO_set_pin_direction(LCD_control_port,LCD_Rs_pin,OUTPUT);
	DIO_set_pin_direction(LCD_control_port,LCD_Rw_pin,OUTPUT);
	DIO_set_pin_direction(LCD_control_port,LCD_E_pin,OUTPUT);
    _delay_ms(40);
    LCD_write_cmd(0b00111000);
    _delay_us(50);
    LCD_write_cmd(0b00001100);
    _delay_us(50);
    LCD_write_cmd(0b00000001);
    _delay_ms(2);
}
