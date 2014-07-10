/*
 * cli_uart.c - msp430f5529 launchpad application uart interface implementation
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


//*****************************************************************************
//
//! \addtogroup CLI_UART
//! @{
//
//*****************************************************************************

#include "cli_uart.h"
#include <string.h>
#include <stdio.h>

#ifdef _USE_CLI_
unsigned char *g_ucUARTBuffer;
//using standard input-output stdio for CLI_Read and CLI_Write
int cli_have_cmd = 0;
#endif

int
CLI_Read(unsigned char *pBuff)
{
    if(pBuff == NULL)
        return -1;
#ifdef _USE_CLI_
//using standard input-output stdio for CLI_Read and CLI_Write
    cli_have_cmd = 0;
	scanf("%s",pBuff); 

    return strlen((const char *)pBuff);
#else
    return 0;
#endif
}


int
CLI_Write(unsigned char *inBuff)
{
	FILE *F1;
	F1 = fopen("database.txt","a");
    
	if(inBuff == NULL)
        return -1;
#ifdef _USE_CLI_
//using standard input-output stdio for CLI_Read and CLI_Write
    unsigned short ret,usLength = strlen((const char *)inBuff);
    ret = usLength;
    
	fprintf(F1,"%s",inBuff);
	fclose(F1);        
    return (int)ret;
#else
	fclose(F1);
    return 0;
#endif
}


void
CLI_Configure(void)
{
#ifdef _USE_CLI_
//using standard input-output stdio for CLI_Read and CLI_Write
	FILE *F1;
	F1 = fopen("database.txt","w");
	fclose(F1);
#endif
}


//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
