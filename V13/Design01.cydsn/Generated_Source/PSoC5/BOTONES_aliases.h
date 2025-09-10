/*******************************************************************************
* File Name: BOTONES.h  
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

#if !defined(CY_PINS_BOTONES_ALIASES_H) /* Pins BOTONES_ALIASES_H */
#define CY_PINS_BOTONES_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define BOTONES_0			(BOTONES__0__PC)
#define BOTONES_0_INTR	((uint16)((uint16)0x0001u << BOTONES__0__SHIFT))

#define BOTONES_1			(BOTONES__1__PC)
#define BOTONES_1_INTR	((uint16)((uint16)0x0001u << BOTONES__1__SHIFT))

#define BOTONES_INTR_ALL	 ((uint16)(BOTONES_0_INTR| BOTONES_1_INTR))

#endif /* End Pins BOTONES_ALIASES_H */


/* [] END OF FILE */
