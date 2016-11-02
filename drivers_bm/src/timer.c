/* Copyright 2016, 
 * Federico Pinna
 * fpinna@unsl.edu.ar
 * Eduardo Filomena
 * efilomena@bioingenieria.edu.ar
 * Juan Manuel Reta
 * jmrera@bioingenieria.edu.ar
 * Facultad de Ingeniería
 * Universidad Nacional de Entre Ríos
 * Argentina
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Bare Metal driver for RIT timer in the EDU-CIAA board.
 **
 **/

/*
 * Initials     Name
 * ---------------------------
 *  FP         Federico Pinna
 *  EF			Eduardo Filomena
 *  JMR			Juan Manuel Reta
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160602 v0.1 initial version Federico Pinna
 * 20160807 v0.2 modifications and improvements made by Eduardo Filomena
 * 20160808 v0.3 modifications and improvements made by Juan Manuel Reta
 */

/*==================[inclusions]=============================================*/

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#else
#endif

#include "timer.h"


/*==================[macros and definitions]=================================*/



/*==================[internal data declaration]==============================*/

/** \brief Function pointer declaration
 **
 **/
void (*pIsrTimer)();
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

void TimerInit(uint32_t time_ms,void *pfunc)
{
   /*receive pointer to the app function that execute every elpased timer interval*/
	pIsrTimer = pfunc;

	Chip_RIT_Init(LPC_RITIMER);
	Chip_RIT_SetTimerInterval(LPC_RITIMER,time_ms);
	NVIC_EnableIRQ(RITIMER_IRQn);
}

 void Isr_RIT(void)
{
    /*Clear interrupt flag*/
	Chip_RIT_ClearInt(LPC_RITIMER);
	pIsrTimer();
}

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

