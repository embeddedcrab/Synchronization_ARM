/*********************************************************************************************************************
 * @file     sync.c
 * @brief    Synchronization API Source
 * @version  1.0.0
 * @date	 02/23/2021
 *
 * @cond
 *********************************************************************************************************************
 * Copyright (c) 2021, Hemant Sharma - All Rights Reserved
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************************************************************
 *
 * *************************** Change history ********************************
 *
 * @endcond
 */
/******************************************************************************
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/

/** @file:	sync.c
 *  @brief:	This source file contains API function definitions for Sync
 */


/******************************************************************************
* Includes
*******************************************************************************/

/* Include headers */
#include <sync.h>


/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Definitions
*******************************************************************************/

/*------- Locking - Unlocking Functions  -------*/

/**
 * @function	lock_bit
 *
 * @brief		Locks bit of variable using exclusive load-store instruction
 *
 * <i>Imp Note:</i>
 */
long lock_bit( volatile unsigned char * p_varlock )
{
	/* Local Variables */
    unsigned char lock_l = 0;
    unsigned char count_l = 0;

    do
    {
        /* Fetch lock value */
        atomic_load8( &lock_l, p_varlock );
        /* Read lock bit, if not locked then try lock */
        if( !(lock_l & (1<<LOCK_BIT_POSITION)) )
        {
            /* Set Lock */
            lock_l |= 0x01;
            if( 0 == atomic_store8( &lock_l, p_varlock ) )
            {
            	/* Return Success status */
            	return 0;
            }
            else
            {
            	__CLREX();
            	break;
            }
        }
        else
        {
        	/* Counter for iterations */
            if( count_l >= MAX_MUTEX_RETRY_COUNTER )
            {
            	__CLREX();/* Confirm it, because LD is successful and monitors needs to be cleared! */
                break;
            }
            else
            {
            	count_l += 1;
            }
        }
    } while( lock_l & (1<<LOCK_BIT_POSITION) );

    /* Return Failure status */
    return 1;
}


/**
 * @function	unlock_bit
 *
 * @brief
 *
 * <i>Imp Note:</i>
 */
void unlock_bit( volatile unsigned char * p_varlock )
{
	*p_varlock &= ~(1<<LOCK_BIT_POSITION);
}


/********************************** End of File *******************************/
