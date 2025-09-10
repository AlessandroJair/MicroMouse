/*******************************************************************************
* File Name: BOTONES.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_BOTONES_H) /* Pins BOTONES_H */
#define CY_PINS_BOTONES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BOTONES_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BOTONES__PORT == 15 && ((BOTONES__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BOTONES_Write(uint8 value);
void    BOTONES_SetDriveMode(uint8 mode);
uint8   BOTONES_ReadDataReg(void);
uint8   BOTONES_Read(void);
void    BOTONES_SetInterruptMode(uint16 position, uint16 mode);
uint8   BOTONES_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BOTONES_SetDriveMode() function.
     *  @{
     */
        #define BOTONES_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BOTONES_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BOTONES_DM_RES_UP          PIN_DM_RES_UP
        #define BOTONES_DM_RES_DWN         PIN_DM_RES_DWN
        #define BOTONES_DM_OD_LO           PIN_DM_OD_LO
        #define BOTONES_DM_OD_HI           PIN_DM_OD_HI
        #define BOTONES_DM_STRONG          PIN_DM_STRONG
        #define BOTONES_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BOTONES_MASK               BOTONES__MASK
#define BOTONES_SHIFT              BOTONES__SHIFT
#define BOTONES_WIDTH              2u

/* Interrupt constants */
#if defined(BOTONES__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BOTONES_SetInterruptMode() function.
     *  @{
     */
        #define BOTONES_INTR_NONE      (uint16)(0x0000u)
        #define BOTONES_INTR_RISING    (uint16)(0x0001u)
        #define BOTONES_INTR_FALLING   (uint16)(0x0002u)
        #define BOTONES_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BOTONES_INTR_MASK      (0x01u) 
#endif /* (BOTONES__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BOTONES_PS                     (* (reg8 *) BOTONES__PS)
/* Data Register */
#define BOTONES_DR                     (* (reg8 *) BOTONES__DR)
/* Port Number */
#define BOTONES_PRT_NUM                (* (reg8 *) BOTONES__PRT) 
/* Connect to Analog Globals */                                                  
#define BOTONES_AG                     (* (reg8 *) BOTONES__AG)                       
/* Analog MUX bux enable */
#define BOTONES_AMUX                   (* (reg8 *) BOTONES__AMUX) 
/* Bidirectional Enable */                                                        
#define BOTONES_BIE                    (* (reg8 *) BOTONES__BIE)
/* Bit-mask for Aliased Register Access */
#define BOTONES_BIT_MASK               (* (reg8 *) BOTONES__BIT_MASK)
/* Bypass Enable */
#define BOTONES_BYP                    (* (reg8 *) BOTONES__BYP)
/* Port wide control signals */                                                   
#define BOTONES_CTL                    (* (reg8 *) BOTONES__CTL)
/* Drive Modes */
#define BOTONES_DM0                    (* (reg8 *) BOTONES__DM0) 
#define BOTONES_DM1                    (* (reg8 *) BOTONES__DM1)
#define BOTONES_DM2                    (* (reg8 *) BOTONES__DM2) 
/* Input Buffer Disable Override */
#define BOTONES_INP_DIS                (* (reg8 *) BOTONES__INP_DIS)
/* LCD Common or Segment Drive */
#define BOTONES_LCD_COM_SEG            (* (reg8 *) BOTONES__LCD_COM_SEG)
/* Enable Segment LCD */
#define BOTONES_LCD_EN                 (* (reg8 *) BOTONES__LCD_EN)
/* Slew Rate Control */
#define BOTONES_SLW                    (* (reg8 *) BOTONES__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BOTONES_PRTDSI__CAPS_SEL       (* (reg8 *) BOTONES__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BOTONES_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BOTONES__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BOTONES_PRTDSI__OE_SEL0        (* (reg8 *) BOTONES__PRTDSI__OE_SEL0) 
#define BOTONES_PRTDSI__OE_SEL1        (* (reg8 *) BOTONES__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BOTONES_PRTDSI__OUT_SEL0       (* (reg8 *) BOTONES__PRTDSI__OUT_SEL0) 
#define BOTONES_PRTDSI__OUT_SEL1       (* (reg8 *) BOTONES__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BOTONES_PRTDSI__SYNC_OUT       (* (reg8 *) BOTONES__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BOTONES__SIO_CFG)
    #define BOTONES_SIO_HYST_EN        (* (reg8 *) BOTONES__SIO_HYST_EN)
    #define BOTONES_SIO_REG_HIFREQ     (* (reg8 *) BOTONES__SIO_REG_HIFREQ)
    #define BOTONES_SIO_CFG            (* (reg8 *) BOTONES__SIO_CFG)
    #define BOTONES_SIO_DIFF           (* (reg8 *) BOTONES__SIO_DIFF)
#endif /* (BOTONES__SIO_CFG) */

/* Interrupt Registers */
#if defined(BOTONES__INTSTAT)
    #define BOTONES_INTSTAT            (* (reg8 *) BOTONES__INTSTAT)
    #define BOTONES_SNAP               (* (reg8 *) BOTONES__SNAP)
    
	#define BOTONES_0_INTTYPE_REG 		(* (reg8 *) BOTONES__0__INTTYPE)
	#define BOTONES_1_INTTYPE_REG 		(* (reg8 *) BOTONES__1__INTTYPE)
#endif /* (BOTONES__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BOTONES_H */


/* [] END OF FILE */
