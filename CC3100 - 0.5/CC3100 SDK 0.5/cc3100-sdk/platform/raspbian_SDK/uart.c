/*
 * uart.h - msp430f5529 launchpad uart interface implementation
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

//#ifdef SL_IF_TYPE_UART
  
#include "datatypes.h"
#include "simplelink.h"
#include "board.h"
#include "cli_uart.h"

#define CTS_LINE_IS_HIGH        (digitalRead())

extern BOOLEAN IntIsMasked;

int uart_Close(Fd_t fd)
{
    UARTM_Stop();
    
    /* Disable WLAN Interrupt ... */
    CC3100_InterruptDisable();

    return 0;
}


Fd_t uart_Open(char *ifName, unsigned long flags)
{
    UARTM_Start();
    
    /* 1 ms delay */
    CyDelay(1u);

    /* Enable WLAN interrupt */
    CC3100_InterruptEnable();
    
    /* Clear Tx Rx Buffers */
    UARTM_ClearTxBuffer();
    UARTM_ClearRxBuffer();

    return NONOS_RET_OK;
}

int uart_Read(Fd_t fd, unsigned char *pBuff, int len)
{
    int i=0;
    uint8 ch;

    /* Disable Rx Interrupt */
    Rx_ISR_Disable();
    
    /* wait till all remaining bytes are received */
    for(i=0; i < len; )
    {
        //ch = UARTM_GetByte();
        //if(UARTM_ReadRxStatus())    CLI_Write((unsigned char *)"\r\nSays high");
        //else    CLI_Write((unsigned char *)"\r\nSays low");
        //if(0u != ch)
        while(UARTM_ReadRxStatus() == 0);
        //if(UARTM_ReadRxStatus())
        //{
            ch = UARTM_GetByte();
            //CLI_Write((unsigned char *)"\r\nSays high");
            pBuff[i] = ch;
            i++;
            //if(i == 4 || i == 8) UARTM_ClearRxBuffer();
        //}
        //else    CLI_Write((unsigned char *)"\r\nNODATA");
    }
    
    /* Enable Rx Interrupt */
    Rx_ISR_Enable();

    return len;
}


int uart_Write(Fd_t fd, unsigned char *pBuff, int len)
{
    int len_to_return = len;
    CyDelay(10u);
    //CLI_Write((unsigned char *)"\r\nWriting data\r\n");

    while (len)
    {
        UARTM_PutChar(*pBuff);
        len--;
        pBuff++;
    }
    return len_to_return;
}
//#endif /* SL_IF_TYPE_UART */
