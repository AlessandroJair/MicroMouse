/*******************************************************************************
* File Name: VALORES.h  
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

#if !defined(CY_PINS_VALORES_ALIASES_H) /* Pins VALORES_ALIASES_H */
#define CY_PINS_VALORES_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define VALORES_0			(VALORES__0__PC)
#define VALORES_0_INTR	((uint16)((uint16)0x0001u << VALORES__0__SHIFT))

#define VALORES_1			(VALORES__1__PC)
#define VALORES_1_INTR	((uint16)((uint16)0x0001u << VALORES__1__SHIFT))

#define VALORES_2			(VALORES__2__PC)
#define VALORES_2_INTR	((uint16)((uint16)0x0001u << VALORES__2__SHIFT))

#define VALORES_3			(VALORES__3__PC)
#define VALORES_3_INTR	((uint16)((uint16)0x0001u << VALORES__3__SHIFT))

#define VALORES_4			(VALORES__4__PC)
#define VALORES_4_INTR	((uint16)((uint16)0x0001u << VALORES__4__SHIFT))

#define VALORES_5			(VALORES__5__PC)
#define VALORES_5_INTR	((uint16)((uint16)0x0001u << VALORES__5__SHIFT))

#define VALORES_6			(VALORES__6__PC)
#define VALORES_6_INTR	((uint16)((uint16)0x0001u << VALORES__6__SHIFT))

#define VALORES_7			(VALORES__7__PC)
#define VALORES_7_INTR	((uint16)((uint16)0x0001u << VALORES__7__SHIFT))

#define VALORES_INTR_ALL	 ((uint16)(VALORES_0_INTR| VALORES_1_INTR| VALORES_2_INTR| VALORES_3_INTR| VALORES_4_INTR| VALORES_5_INTR| VALORES_6_INTR| VALORES_7_INTR))

#endif /* End Pins VALORES_ALIASES_H */


/* [] END OF FILE */
