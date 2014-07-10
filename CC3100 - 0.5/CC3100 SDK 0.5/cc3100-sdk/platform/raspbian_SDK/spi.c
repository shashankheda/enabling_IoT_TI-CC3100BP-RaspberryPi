/*
 * spi.c - msp430f5529 launchpad spi interface implementation
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
#ifndef SL_IF_TYPE_UART
#include "wiringPiSPI.h"
#include "datatypes.h"
#include "simplelink.h"
#include "spi.h"
#include "board.h"

#define NONOS_RET_OK                            (0)

int spi_Close(Fd_t fd)
{
	/*Stop SPI */
	system("/usr/local/bin/gpio reset");

    /* Disable WLAN Interrupt ... */
    CC3100_InterruptDisable();

    return 0;
}

Fd_t spi_Open(char *ifName, unsigned long flags)
{
	int err = 0;
	
	/* Started SPI at 14MHz speed*/
	err = wiringPiSPISetup(0,14000000);
	if(err == -1)
	{
		while(1);
	}
	
    /* 50 ms delay */
	delay(50);
	
    /* Enable WLAN interrupt */
    CC3100_InterruptEnable();

    return NONOS_RET_OK;
}


int spi_Write(Fd_t fd, unsigned char *pBuff, int len)
{
    int len_to_return = len;

	/* Function used for writing on SPI */
	/* wiringPiSPIDataRW (int channel, unsigned char *data, int len) ; */
	wiringPiSPIDataRW(0,pBuff,len);
	
    return len_to_return;
}


int spi_Read(Fd_t fd, unsigned char *pBuff, int len)
{
    int i = 0;

	/* Function used for reading SPI */
	/* wiringPiSPIDataRW (int channel, unsigned char *data, int len) ; */
	for(i=0; i<len;i++)
	{
		pBuff[i] = 0xFF;
	}
	wiringPiSPIDataRW(0,pBuff,len);
	
    return len;
}
#endif /* SL_IF_TYPE_UART */