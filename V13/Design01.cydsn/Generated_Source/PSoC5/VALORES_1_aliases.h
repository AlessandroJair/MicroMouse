/*******************************************************************************
* File Name: VALORES_1.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_VALORES_1_ALIASES_H) /* Pins VALORES_1_ALIASES_H */
#define CY_PINS_VALORES_1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define VALORES_1_0			(VALORES_1__0__PC)
#define VALORES_1_0_INTR	((uint16)((uint16)0x0001u << VALORES_1__0__SHIFT))

#define VALORES_1_1			(VALORES_1__1__PC)
#define VALORES_1_1_INTR	((uint16)((uint16)0x0001u << VALORES_1__1__SHIFT))

#define VALORES_1_2			(VALORES_1__2__PC)
#define VALORES_1_2_INTR	((uint16)((uint16)0x0001u << VALORES_1__2__SHIFT))

#define VALORES_1_3			(VALORES_1__3__PC)
#define VALORES_1_3_INTR	((uint16)((uint16)0x0001u << VALORES_1__3__SHIFT))

#define VALORES_1_INTR_ALL	 ((uint16)(VALORES_1_0_INTR| VALORES_1_1_INTR| VALORES_1_2_INTR| VALORES_1_3_INTR))

#endif /* End Pins VALORES_1_ALIASES_H */


/* [] END OF FILE */
