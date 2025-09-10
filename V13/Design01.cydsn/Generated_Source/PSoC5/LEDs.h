/*******************************************************************************
* File Name: LEDs.h  
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

#if !defined(CY_PINS_LEDs_H) /* Pins LEDs_H */
#define CY_PINS_LEDs_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LEDs_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LEDs__PORT == 15 && ((LEDs__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LEDs_Write(uint8 value);
void    LEDs_SetDriveMode(uint8 mode);
uint8   LEDs_ReadDataReg(void);
uint8   LEDs_Read(void);
void    LEDs_SetInterruptMode(uint16 position, uint16 mode);
uint8   LEDs_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LEDs_SetDriveMode() function.
     *  @{
     */
        #define LEDs_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LEDs_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LEDs_DM_RES_UP          PIN_DM_RES_UP
        #define LEDs_DM_RES_DWN         PIN_DM_RES_DWN
        #define LEDs_DM_OD_LO           PIN_DM_OD_LO
        #define LEDs_DM_OD_HI           PIN_DM_OD_HI
        #define LEDs_DM_STRONG          PIN_DM_STRONG
        #define LEDs_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LEDs_MASK               LEDs__MASK
#define LEDs_SHIFT              LEDs__SHIFT
#define LEDs_WIDTH              2u

/* Interrupt constants */
#if defined(LEDs__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LEDs_SetInterruptMode() function.
     *  @{
     */
        #define LEDs_INTR_NONE      (uint16)(0x0000u)
        #define LEDs_INTR_RISING    (uint16)(0x0001u)
        #define LEDs_INTR_FALLING   (uint16)(0x0002u)
        #define LEDs_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LEDs_INTR_MASK      (0x01u) 
#endif /* (LEDs__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LEDs_PS                     (* (reg8 *) LEDs__PS)
/* Data Register */
#define LEDs_DR                     (* (reg8 *) LEDs__DR)
/* Port Number */
#define LEDs_PRT_NUM                (* (reg8 *) LEDs__PRT) 
/* Connect to Analog Globals */                                                  
#define LEDs_AG                     (* (reg8 *) LEDs__AG)                       
/* Analog MUX bux enable */
#define LEDs_AMUX                   (* (reg8 *) LEDs__AMUX) 
/* Bidirectional Enable */                                                        
#define LEDs_BIE                    (* (reg8 *) LEDs__BIE)
/* Bit-mask for Aliased Register Access */
#define LEDs_BIT_MASK               (* (reg8 *) LEDs__BIT_MASK)
/* Bypass Enable */
#define LEDs_BYP                    (* (reg8 *) LEDs__BYP)
/* Port wide control signals */                                                   
#define LEDs_CTL                    (* (reg8 *) LEDs__CTL)
/* Drive Modes */
#define LEDs_DM0                    (* (reg8 *) LEDs__DM0) 
#define LEDs_DM1                    (* (reg8 *) LEDs__DM1)
#define LEDs_DM2                    (* (reg8 *) LEDs__DM2) 
/* Input Buffer Disable Override */
#define LEDs_INP_DIS                (* (reg8 *) LEDs__INP_DIS)
/* LCD Common or Segment Drive */
#define LEDs_LCD_COM_SEG            (* (reg8 *) LEDs__LCD_COM_SEG)
/* Enable Segment LCD */
#define LEDs_LCD_EN                 (* (reg8 *) LEDs__LCD_EN)
/* Slew Rate Control */
#define LEDs_SLW                    (* (reg8 *) LEDs__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LEDs_PRTDSI__CAPS_SEL       (* (reg8 *) LEDs__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LEDs_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LEDs__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LEDs_PRTDSI__OE_SEL0        (* (reg8 *) LEDs__PRTDSI__OE_SEL0) 
#define LEDs_PRTDSI__OE_SEL1        (* (reg8 *) LEDs__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LEDs_PRTDSI__OUT_SEL0       (* (reg8 *) LEDs__PRTDSI__OUT_SEL0) 
#define LEDs_PRTDSI__OUT_SEL1       (* (reg8 *) LEDs__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LEDs_PRTDSI__SYNC_OUT       (* (reg8 *) LEDs__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LEDs__SIO_CFG)
    #define LEDs_SIO_HYST_EN        (* (reg8 *) LEDs__SIO_HYST_EN)
    #define LEDs_SIO_REG_HIFREQ     (* (reg8 *) LEDs__SIO_REG_HIFREQ)
    #define LEDs_SIO_CFG            (* (reg8 *) LEDs__SIO_CFG)
    #define LEDs_SIO_DIFF           (* (reg8 *) LEDs__SIO_DIFF)
#endif /* (LEDs__SIO_CFG) */

/* Interrupt Registers */
#if defined(LEDs__INTSTAT)
    #define LEDs_INTSTAT            (* (reg8 *) LEDs__INTSTAT)
    #define LEDs_SNAP               (* (reg8 *) LEDs__SNAP)
    
	#define LEDs_0_INTTYPE_REG 		(* (reg8 *) LEDs__0__INTTYPE)
	#define LEDs_1_INTTYPE_REG 		(* (reg8 *) LEDs__1__INTTYPE)
#endif /* (LEDs__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LEDs_H */


/* [] END OF FILE */
