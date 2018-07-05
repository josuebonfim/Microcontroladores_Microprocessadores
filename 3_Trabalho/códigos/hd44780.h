/*
 * hd44780.h
 *
 *  Created on: 28.08.2012
 *      Author: user
 */

#ifndef HD44780_H_
#define HD44780_H_

#define     LCM_DIR               P2DIR
#define     LCM_OUT               P2OUT

//
// Define symbolic LCM - MCU pin mappings

// We've set DATA PIN TO 4,5,6,7 for easy translation
//
#define     LCM_PIN_D4            BIT0          // P1.4
#define     LCM_PIN_D5            BIT1          // P1.5
#define     LCM_PIN_D6            BIT2          // P1.6
#define     LCM_PIN_D7            BIT3          // P1.7
#define     LCM_PIN_RS            BIT4          // P1.0
#define     LCM_PIN_EN            BIT5          // P1.1

#define     LCM_PIN_MASK  ((LCM_PIN_RS | LCM_PIN_EN | LCM_PIN_D7 | LCM_PIN_D6 | LCM_PIN_D5 | LCM_PIN_D4))

#define     FALSE                 0
#define     TRUE                  1

void LcmSetCursorPosition(char Row, char Col);
void ClearLcmScreen();
void InitializeLcm(void);
void PrintStr(char *Text);
void HD44780_outdec(long data, unsigned char ndigits);
void SendByte(char ByteToSend, int IsData);

#endif /* HD44780_H_ */
