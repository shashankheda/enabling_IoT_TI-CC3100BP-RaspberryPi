/*
 * board.c - msp430f5529 launchpad configuration
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include "simplelink.h"
#include "board.h"
#include "wiringPi.h"

#define Pin_IRQ 5
#define nHIB 6

P_EVENT_HANDLER                pIrqEventHandler = 0;

BOOLEAN IntIsMasked;

#ifdef SL_IF_TYPE_UART
#define ASSERT_UART(expr) {  if (!(expr)) { while(1) ;}}

unsigned char error_overrun = FALSE;
_uartFlowctrl uartFlowctrl;
_uartFlowctrl *puartFlowctrl = &uartFlowctrl;
#endif

void Inter_Service_Routine(void)
{
#ifndef SL_IF_TYPE_UART
    if(pIrqEventHandler)
    {
        pIrqEventHandler(0);
    }
#endif
}

int registerInterruptHandler(P_EVENT_HANDLER InterruptHdl , void* pValue)
{
    pIrqEventHandler = InterruptHdl;
    return 0;
}

void CC3100_disable()
{
	digitalWrite(nHIB,LOW);
}


void CC3100_enable()
{
	CC3100_disable();
	delay(10);
	digitalWrite(nHIB,HIGH);
}

void CC3100_InterruptEnable(void)
{
	CC3100_InterruptDisable();
    /* Configure and enable interrupt */
	system ("/usr/local/bin/gpio edge 5 rising");
	wiringPiISR (Pin_IRQ, INT_EDGE_RISING, &Inter_Service_Routine) ;
}

void CC3100_InterruptDisable()
{
	system ("/usr/local/bin/gpio edge 5 none");
}

void MaskIntHdlr()
{
    IntIsMasked = TRUE;
}

void UnMaskIntHdlr()
{
    IntIsMasked = FALSE;
}

void initClk(void)
{
	/* To reset all pins (reset to INPUT Mode) */
	system("/usr/local/bin/gpio reset");
	
	/* Must be removed so that the next instruction can set SPI pin mode to ALT0 */
	system("sudo rmmod spi_bcm2708");
	
	/* To reset SPI Pins to "ALT0" mode from IN mode so as to use them as SPI Pins */
	system("gpio load spi");
	
	/* This initialises the wiringPi system and assumes that the calling program is going to be using the 
	wiringPi pin numbering scheme. This is a simplified numbering scheme which provides a mapping from virtual 
	pin numbers 0 through 16 to the real underlying Broadcom GPIO pin numbers. See the pins page for a table 
	which maps the wiringPi pin number to the Broadcom GPIO pin number to the physical location on the edge connector */
	/* Reference: https://projects.drogon.net/raspberry-pi/wiringpi/pins/ */
	wiringPiSetup() ;

	/* WiringPi pin 6 = BCM GPIO Pin 25 = nHIB; SPI Pins are Pre-configured (after reset) */
	pinMode(nHIB,OUTPUT);
	pinMode(Pin_IRQ,INPUT);
	
    /* Globally enable interrupts */
	CC3100_InterruptEnable();
}

void stopWDT()
{
	/* Watchdog Timer is stopped by default */
}

void initLEDs()
{
    turnLedOff(LED1);
    turnLedOff(LED2);
}

void turnLedOn(char ledNum)
{
}

void turnLedOff(char ledNum)
{
}

void toggleLed(char ledNum)
{
}

unsigned char GetLEDStatus()
{

}

void initAntSelGPIO()
{
}

void SelAntenna(int antenna)
{
}

void Delay(unsigned long interval)
{
    while(interval > 0)
    {
        delay(1000);
        interval--;
    }
}