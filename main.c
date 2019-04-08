/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system intialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  PIC32MM0256GPM064
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/


#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart1.h" 
#include "string.h" 

#define LedON (PORTDbits.RD3 = 1)
#define LedOFF (PORTDbits.RD3 = 0)

void patternSearch(void);
uint8_t myBuffer[8]; //user buffer
int numBytes = 0;
uint8_t receiveByte;

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    UART1_Enable();
    UART1_WriteBuffer("ON%" , 3); //Send string to UART1
    
    while (1)
    {
      //UART1_Write('A'); //Send the A sign to UART1
      //UART1_WriteBuffer("ON%" , 3); //Send string to UART1
      //  delayMs(100);
     if (UART1_TRANSFER_STATUS_RX_DATA_PRESENT & UART1_TransferStatusGet()) { //check if a byte has arrived
         receiveByte = UART1_Read();
         if(receiveByte){ //if a byte is zero, ignore it
            myBuffer[numBytes++] = receiveByte; //add the received byte to the user buffer
               if(myBuffer[numBytes-1] == '%'){
                  patternSearch();
         }
       }
     }
   }
 }

void patternSearch(void){
      
   if(strstr(myBuffer,"ON")) LedON ;// searches for a string pattern in the user buffer
   		      
   if(strstr(myBuffer,"OFF")) LedOFF ;// searches for a string pattern in the user buffer
	    
}
