/*******************************************************************************
* File Name: DIGITOS.h  
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

#if !defined(CY_PINS_DIGITOS_ALIASES_H) /* Pins DIGITOS_ALIASES_H */
#define CY_PINS_DIGITOS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define DIGITOS_0			(DIGITOS__0__PC)
#define DIGITOS_0_INTR	((uint16)((uint16)0x0001u << DIGITOS__0__SHIFT))

#define DIGITOS_1			(DIGITOS__1__PC)
#define DIGITOS_1_INTR	((uint16)((uint16)0x0001u << DIGITOS__1__SHIFT))

#define DIGITOS_2			(DIGITOS__2__PC)
#define DIGITOS_2_INTR	((uint16)((uint16)0x0001u << DIGITOS__2__SHIFT))

#define DIGITOS_3			(DIGITOS__3__PC)
#define DIGITOS_3_INTR	((uint16)((uint16)0x0001u << DIGITOS__3__SHIFT))

#define DIGITOS_INTR_ALL	 ((uint16)(DIGITOS_0_INTR| DIGITOS_1_INTR| DIGITOS_2_INTR| DIGITOS_3_INTR))

#endif /* End Pins DIGITOS_ALIASES_H */


/* [] END OF FILE */
