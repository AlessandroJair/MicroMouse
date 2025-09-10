/*******************************************************************************
* File Name: VALORES.h  
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

#if !defined(CY_PINS_VALORES_H) /* Pins VALORES_H */
#define CY_PINS_VALORES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VALORES_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 VALORES__PORT == 15 && ((VALORES__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VALORES_Write(uint8 value);
void    VALORES_SetDriveMode(uint8 mode);
uint8   VALORES_ReadDataReg(void);
uint8   VALORES_Read(void);
void    VALORES_SetInterruptMode(uint16 position, uint16 mode);
uint8   VALORES_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VALORES_SetDriveMode() function.
     *  @{
     */
        #define VALORES_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define VALORES_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define VALORES_DM_RES_UP          PIN_DM_RES_UP
        #define VALORES_DM_RES_DWN         PIN_DM_RES_DWN
        #define VALORES_DM_OD_LO           PIN_DM_OD_LO
        #define VALORES_DM_OD_HI           PIN_DM_OD_HI
        #define VALORES_DM_STRONG          PIN_DM_STRONG
        #define VALORES_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VALORES_MASK               VALORES__MASK
#define VALORES_SHIFT              VALORES__SHIFT
#define VALORES_WIDTH              8u

/* Interrupt constants */
#if defined(VALORES__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VALORES_SetInterruptMode() function.
     *  @{
     */
        #define VALORES_INTR_NONE      (uint16)(0x0000u)
        #define VALORES_INTR_RISING    (uint16)(0x0001u)
        #define VALORES_INTR_FALLING   (uint16)(0x0002u)
        #define VALORES_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define VALORES_INTR_MASK      (0x01u) 
#endif /* (VALORES__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VALORES_PS                     (* (reg8 *) VALORES__PS)
/* Data Register */
#define VALORES_DR                     (* (reg8 *) VALORES__DR)
/* Port Number */
#define VALORES_PRT_NUM                (* (reg8 *) VALORES__PRT) 
/* Connect to Analog Globals */                                                  
#define VALORES_AG                     (* (reg8 *) VALORES__AG)                       
/* Analog MUX bux enable */
#define VALORES_AMUX                   (* (reg8 *) VALORES__AMUX) 
/* Bidirectional Enable */                                                        
#define VALORES_BIE                    (* (reg8 *) VALORES__BIE)
/* Bit-mask for Aliased Register Access */
#define VALORES_BIT_MASK               (* (reg8 *) VALORES__BIT_MASK)
/* Bypass Enable */
#define VALORES_BYP                    (* (reg8 *) VALORES__BYP)
/* Port wide control signals */                                                   
#define VALORES_CTL                    (* (reg8 *) VALORES__CTL)
/* Drive Modes */
#define VALORES_DM0                    (* (reg8 *) VALORES__DM0) 
#define VALORES_DM1                    (* (reg8 *) VALORES__DM1)
#define VALORES_DM2                    (* (reg8 *) VALORES__DM2) 
/* Input Buffer Disable Override */
#define VALORES_INP_DIS                (* (reg8 *) VALORES__INP_DIS)
/* LCD Common or Segment Drive */
#define VALORES_LCD_COM_SEG            (* (reg8 *) VALORES__LCD_COM_SEG)
/* Enable Segment LCD */
#define VALORES_LCD_EN                 (* (reg8 *) VALORES__LCD_EN)
/* Slew Rate Control */
#define VALORES_SLW                    (* (reg8 *) VALORES__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VALORES_PRTDSI__CAPS_SEL       (* (reg8 *) VALORES__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VALORES_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VALORES__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VALORES_PRTDSI__OE_SEL0        (* (reg8 *) VALORES__PRTDSI__OE_SEL0) 
#define VALORES_PRTDSI__OE_SEL1        (* (reg8 *) VALORES__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VALORES_PRTDSI__OUT_SEL0       (* (reg8 *) VALORES__PRTDSI__OUT_SEL0) 
#define VALORES_PRTDSI__OUT_SEL1       (* (reg8 *) VALORES__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VALORES_PRTDSI__SYNC_OUT       (* (reg8 *) VALORES__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VALORES__SIO_CFG)
    #define VALORES_SIO_HYST_EN        (* (reg8 *) VALORES__SIO_HYST_EN)
    #define VALORES_SIO_REG_HIFREQ     (* (reg8 *) VALORES__SIO_REG_HIFREQ)
    #define VALORES_SIO_CFG            (* (reg8 *) VALORES__SIO_CFG)
    #define VALORES_SIO_DIFF           (* (reg8 *) VALORES__SIO_DIFF)
#endif /* (VALORES__SIO_CFG) */

/* Interrupt Registers */
#if defined(VALORES__INTSTAT)
    #define VALORES_INTSTAT            (* (reg8 *) VALORES__INTSTAT)
    #define VALORES_SNAP               (* (reg8 *) VALORES__SNAP)
    
	#define VALORES_0_INTTYPE_REG 		(* (reg8 *) VALORES__0__INTTYPE)
	#define VALORES_1_INTTYPE_REG 		(* (reg8 *) VALORES__1__INTTYPE)
	#define VALORES_2_INTTYPE_REG 		(* (reg8 *) VALORES__2__INTTYPE)
	#define VALORES_3_INTTYPE_REG 		(* (reg8 *) VALORES__3__INTTYPE)
	#define VALORES_4_INTTYPE_REG 		(* (reg8 *) VALORES__4__INTTYPE)
	#define VALORES_5_INTTYPE_REG 		(* (reg8 *) VALORES__5__INTTYPE)
	#define VALORES_6_INTTYPE_REG 		(* (reg8 *) VALORES__6__INTTYPE)
	#define VALORES_7_INTTYPE_REG 		(* (reg8 *) VALORES__7__INTTYPE)
#endif /* (VALORES__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_VALORES_H */


/* [] END OF FILE */
