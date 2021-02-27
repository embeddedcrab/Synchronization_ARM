/*********************************************************************************************************************
 * @file     sync.h
 * @brief    Syncronization API Header
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

/** @file:	sync.h
 *  @brief:	This file contains API functions for synchronization.
 */
#ifndef SYNC_H_
#define SYNC_H_


#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/

/* CMSIS headers inclusion */
#include <cmsis_gcc.h>


/******************************************************************************
* Preprocessor Constants
******************************************************************************/


/******************************************************************************
* Configuration Constants
******************************************************************************/

#define MAX_MUTEX_RETRY_COUNTER		10


/******************************************************************************
* Macros
******************************************************************************/

#define LOCK_BIT_POSITION			0
#define SYNC_BIT_POSITION			1
#define WRITE_BIT_POSITION			2
#define READ_BIT_POSITION			3


/******************************************************************************
* Typedefs
******************************************************************************/

/**
 * @brief
 */
typedef struct sync_mutex_t_
{
    union
    {
    	struct
		{
            unsigned char lock	: 1;
            unsigned char sync	: 1;/* Can be used for sequencing or anything */
            unsigned char write	: 1;
            unsigned char read	: 1;
            unsigned char		: 4;/* Can add more variables as per usage */
		};
        unsigned char byte;
    };
} sync_mutex_t;


/******************************************************************************
* Variables
******************************************************************************/


/******************************************************************************
* Static Functions
******************************************************************************/

/*------- Atomic Load and Store Functions  -------*/

/**
 * @function	atomic_load8
 *
 * @brief		Load variable value from memory
 *
 * @param[in]	p_addr	-	Memory address of variable
 *
 * @param[out]	p_out	-	Value at memory address
 *
 * @param[inout]NA
 *
 * @return		NA
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 * 				Uses CMSIS instruction
 *
 */
static inline void atomic_load8( volatile unsigned char *p_out, volatile unsigned char * p_addr )
{
	*p_out = __LDREXB( p_addr );
}


/**
 * @function	atomic_store8
 *
 * @brief		Store Value to memory using variable
 *
 * @param[in]	p_value	-	pointer to value to be stored
 * 				p_addr	-	pointer to address of memory variable
 *
 * @param[out]	NA
 *
 * @param[inout]NA
 *
 * @return		Status of Completion of instruction
 * 				0 - Success
 * 				1 - Failure
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 * 					Uses CMSIS instruction
 *
 */
static inline unsigned long atomic_store8( volatile unsigned char *p_value, volatile unsigned char * p_addr )
{
	return __STREXB( *p_value, p_addr );
}


/******************************************************************************
* Function Prototypes
******************************************************************************/

/*------- Bit lock Functions  -------*/

/**
 * @function	lock_bit
 *
 * @brief		Locks bit of variable using exclusive load-store instruction
 *
 * @param[in]
 *
 * @param[out]
 *
 * @param[inout]pointer to lock variable
 *
 * @return		return status of operations
 * 				0 - Success
 * 				1 - Failed
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 * 				Disabled optimization to discard changes done by compiler
 *
 */
long lock_bit( volatile unsigned char * p_varlock ) __attribute__((optimize("0")));


/**
 * @function	unlock_bit
 *
 * @brief		Unlocks bit of variable
 *
 * @param[in]
 *
 * @param[out]
 *
 * @param[inout]pointer to lock variable
 *
 * @return		NA
 *
 * \par<b>Description:</b><br>
 *
 * <i>Imp Note:</i>
 * 				Disabled optimization to discard changes done by compiler
 * 				Uses Atomic operation by Entering Critical Section
 *
 */
void unlock_bit( volatile unsigned char * p_varlock ) __attribute__((optimize("0")));


#ifdef __cplusplus
}
#endif	/* extern "C" linkage */


#endif /* SYNC_H_ */

/********************************** End of File ******************************/

