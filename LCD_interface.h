/*
 * LCD_interface.h
 *
 *  Created on: Sep 11, 2021
 *      Author: mwael
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
void LCD_write_cmd(U8 cmd);
void LCD_write_data(U8 data);
void LCD_clear(void);
U8 LCD_clear_pos(U8 y , U8 x);
U8 LCD_string_pos(char* string,U8 y,U8 x);
void LCD_write_no(U32 num,U8 y, U8 x);
void LCD_init(void);


#endif /* LCD_INTERFACE_H_ */
