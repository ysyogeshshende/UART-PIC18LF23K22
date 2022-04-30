/*
 * File:   newmain.c
 * Author: INAVIT
 *
 * Created on December 2, 2021, 4:03 PM
 */
// PIC18LF23K22 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1H
#pragma config FOSC = LP        // Oscillator Selection bits (LP oscillator)
#pragma config PLLCFG = ON      // 4X PLL Enable (Oscillator multiplied by 4)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = ON       // Watchdog Timer Enable bits (WDT is always enabled. SWDTEN bit has no effect)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<5:0> pins are configured as analog input channels on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTB5   // ECCP2 B output mux bit (P2B is on RB5)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000200-000FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (001000-001FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0001FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000200-000FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (001000-001FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000200-000FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (001000-001FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 32768

//This function initialize UART module
void UART_Initial()
{
TRISCbits.RC6=1;
TRISCbits.RC7=1;
//SPBRG=0x00; // store value for 9600 baud rate
///BAUDCON1-=0x0A;
SPBRGH1 =0x00;
SPBRG1 =0x00;
TXSTAbits.CSRC = 1; // Don't care for asynchronous mode
TXSTAbits.TX9 = 0; // Selects 8-bit data transmission
TXSTAbits.TXEN = 1; // Enable Data tranmission on RC6 pin
TXSTAbits.SYNC = 0; // Selects Asynchronous Serial Communication Mode
TXSTAbits.BRGH = 0; // Default Baud rate speed 
BAUDCONbits.BRG16 = 0; // selects only 8 bit register for baud rate 
RCSTA = 0x90; // Enables UART Communication PORT

}

void UART_Write( char data )
{
while (TXIF == 0); 
TXREG = data; 
//while(TXIF==0); // wait until transmit register not empty
}
void main(void) 
{
//OSCCON=0x72; // Select internal oscillator with frequency = 8MHz
UART_Initial();
while(1)
{
UART_Write('U'); // Send character A
UART_Write('A'); // Send character A
UART_Write('R'); // Send carriage return for new line
UART_Write('A'); // Send character A
UART_Write('T'); // Send carriage return for new line

UART_Write('\r'); // Send carriage return for new line
__delay_ms(10); // adds delay of one second
}
return;
}