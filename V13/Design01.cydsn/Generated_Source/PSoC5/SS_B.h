/*******************************************************************************
* File Name: SS_B.h  
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

#if !defined(CY_PINS_SS_B_H) /* Pins SS_B_H */
#define CY_PINS_SS_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SS_B_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SS_B__PORT == 15 && ((SS_B__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SS_B_Write(uint8 value);
void    SS_B_SetDriveMode(uint8 mode);
uint8   SS_B_ReadDataReg(void);
uint8   SS_B_Read(void);
void    SS_B_SetInterruptMode(uint16 position, uint16 mode);
uint8   SS_B_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SS_B_SetDriveMode() function.
     *  @{
     */
        #define SS_B_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SS_B_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SS_B_DM_RES_UP          PIN_DM_RES_UP
        #define SS_B_DM_RES_DWN         PIN_DM_RES_DWN
        #define SS_B_DM_OD_LO           PIN_DM_OD_LO
        #define SS_B_DM_OD_HI           PIN_DM_OD_HI
        #define SS_B_DM_STRONG          PIN_DM_STRONG
        #define SS_B_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SS_B_MASK               SS_B__MASK
#define SS_B_SHIFT              SS_B__SHIFT
#define SS_B_WIDTH              1u

/* Interrupt constants */
#if defined(SS_B__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SS_B_SetInterruptMode() function.
     *  @{
     */
        #define SS_B_INTR_NONE      (uint16)(0x0000u)
        #define SS_B_INTR_RISING    (uint16)(0x0001u)
        #define SS_B_INTR_FALLING   (uint16)(0x0002u)
        #define SS_B_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SS_B_INTR_MASK      (0x01u) 
#endif /* (SS_B__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SS_B_PS                     (* (reg8 *) SS_B__PS)
/* Data Register */
#define SS_B_DR                     (* (reg8 *) SS_B__DR)
/* Port Number */
#define SS_B_PRT_NUM                (* (reg8 *) SS_B__PRT) 
/* Connect to Analog Globals */                                                  
#define SS_B_AG                     (* (reg8 *) SS_B__AG)                       
/* Analog MUX bux enable */
#define SS_B_AMUX                   (* (reg8 *) SS_B__AMUX) 
/* Bidirectional Enable */                                                        
#define SS_B_BIE                    (* (reg8 *) SS_B__BIE)
/* Bit-mask for Aliased Register Access */
#define SS_B_BIT_MASK               (* (reg8 *) SS_B__BIT_MASK)
/* Bypass Enable */
#define SS_B_BYP                    (* (reg8 *) SS_B__BYP)
/* Port wide control signals */                                                   
#define SS_B_CTL                    (* (reg8 *) SS_B__CTL)
/* Drive Modes */
#define SS_B_DM0                    (* (reg8 *) SS_B__DM0) 
#define SS_B_DM1                    (* (reg8 *) SS_B__DM1)
#define SS_B_DM2                    (* (reg8 *) SS_B__DM2) 
/* Input Buffer Disable Override */
#define SS_B_INP_DIS                (* (reg8 *) SS_B__INP_DIS)
/* LCD Common or Segment Drive */
#define SS_B_LCD_COM_SEG            (* (reg8 *) SS_B__LCD_COM_SEG)
/* Enable Segment LCD */
#define SS_B_LCD_EN                 (* (reg8 *) SS_B__LCD_EN)
/* Slew Rate Control */
#define SS_B_SLW                    (* (reg8 *) SS_B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SS_B_PRTDSI__CAPS_SEL       (* (reg8 *) SS_B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SS_B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SS_B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SS_B_PRTDSI__OE_SEL0        (* (reg8 *) SS_B__PRTDSI__OE_SEL0) 
#define SS_B_PRTDSI__OE_SEL1        (* (reg8 *) SS_B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SS_B_PRTDSI__OUT_SEL0       (* (reg8 *) SS_B__PRTDSI__OUT_SEL0) 
#define SS_B_PRTDSI__OUT_SEL1       (* (reg8 *) SS_B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SS_B_PRTDSI__SYNC_OUT       (* (reg8 *) SS_B__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SS_B__SIO_CFG)
    #define SS_B_SIO_HYST_EN        (* (reg8 *) SS_B__SIO_HYST_EN)
    #define SS_B_SIO_REG_HIFREQ     (* (reg8 *) SS_B__SIO_REG_HIFREQ)
    #define SS_B_SIO_CFG            (* (reg8 *) SS_B__SIO_CFG)
    #define SS_B_SIO_DIFF           (* (reg8 *) SS_B__SIO_DIFF)
#endif /* (SS_B__SIO_CFG) */

/* Interrupt Registers */
#if defined(SS_B__INTSTAT)
    #define SS_B_INTSTAT            (* (reg8 *) SS_B__INTSTAT)
    #define SS_B_SNAP               (* (reg8 *) SS_B__SNAP)
    
	#define SS_B_0_INTTYPE_REG 		(* (reg8 *) SS_B__0__INTTYPE)
#endif /* (SS_B__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SS_B_H */


/* [] END OF FILE */
