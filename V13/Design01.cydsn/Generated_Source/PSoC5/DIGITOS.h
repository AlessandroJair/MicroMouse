/*******************************************************************************
* File Name: DIGITOS.h  
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

#if !defined(CY_PINS_DIGITOS_H) /* Pins DIGITOS_H */
#define CY_PINS_DIGITOS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIGITOS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIGITOS__PORT == 15 && ((DIGITOS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIGITOS_Write(uint8 value);
void    DIGITOS_SetDriveMode(uint8 mode);
uint8   DIGITOS_ReadDataReg(void);
uint8   DIGITOS_Read(void);
void    DIGITOS_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIGITOS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIGITOS_SetDriveMode() function.
     *  @{
     */
        #define DIGITOS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIGITOS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIGITOS_DM_RES_UP          PIN_DM_RES_UP
        #define DIGITOS_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIGITOS_DM_OD_LO           PIN_DM_OD_LO
        #define DIGITOS_DM_OD_HI           PIN_DM_OD_HI
        #define DIGITOS_DM_STRONG          PIN_DM_STRONG
        #define DIGITOS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIGITOS_MASK               DIGITOS__MASK
#define DIGITOS_SHIFT              DIGITOS__SHIFT
#define DIGITOS_WIDTH              4u

/* Interrupt constants */
#if defined(DIGITOS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIGITOS_SetInterruptMode() function.
     *  @{
     */
        #define DIGITOS_INTR_NONE      (uint16)(0x0000u)
        #define DIGITOS_INTR_RISING    (uint16)(0x0001u)
        #define DIGITOS_INTR_FALLING   (uint16)(0x0002u)
        #define DIGITOS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIGITOS_INTR_MASK      (0x01u) 
#endif /* (DIGITOS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIGITOS_PS                     (* (reg8 *) DIGITOS__PS)
/* Data Register */
#define DIGITOS_DR                     (* (reg8 *) DIGITOS__DR)
/* Port Number */
#define DIGITOS_PRT_NUM                (* (reg8 *) DIGITOS__PRT) 
/* Connect to Analog Globals */                                                  
#define DIGITOS_AG                     (* (reg8 *) DIGITOS__AG)                       
/* Analog MUX bux enable */
#define DIGITOS_AMUX                   (* (reg8 *) DIGITOS__AMUX) 
/* Bidirectional Enable */                                                        
#define DIGITOS_BIE                    (* (reg8 *) DIGITOS__BIE)
/* Bit-mask for Aliased Register Access */
#define DIGITOS_BIT_MASK               (* (reg8 *) DIGITOS__BIT_MASK)
/* Bypass Enable */
#define DIGITOS_BYP                    (* (reg8 *) DIGITOS__BYP)
/* Port wide control signals */                                                   
#define DIGITOS_CTL                    (* (reg8 *) DIGITOS__CTL)
/* Drive Modes */
#define DIGITOS_DM0                    (* (reg8 *) DIGITOS__DM0) 
#define DIGITOS_DM1                    (* (reg8 *) DIGITOS__DM1)
#define DIGITOS_DM2                    (* (reg8 *) DIGITOS__DM2) 
/* Input Buffer Disable Override */
#define DIGITOS_INP_DIS                (* (reg8 *) DIGITOS__INP_DIS)
/* LCD Common or Segment Drive */
#define DIGITOS_LCD_COM_SEG            (* (reg8 *) DIGITOS__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIGITOS_LCD_EN                 (* (reg8 *) DIGITOS__LCD_EN)
/* Slew Rate Control */
#define DIGITOS_SLW                    (* (reg8 *) DIGITOS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIGITOS_PRTDSI__CAPS_SEL       (* (reg8 *) DIGITOS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIGITOS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIGITOS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIGITOS_PRTDSI__OE_SEL0        (* (reg8 *) DIGITOS__PRTDSI__OE_SEL0) 
#define DIGITOS_PRTDSI__OE_SEL1        (* (reg8 *) DIGITOS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIGITOS_PRTDSI__OUT_SEL0       (* (reg8 *) DIGITOS__PRTDSI__OUT_SEL0) 
#define DIGITOS_PRTDSI__OUT_SEL1       (* (reg8 *) DIGITOS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIGITOS_PRTDSI__SYNC_OUT       (* (reg8 *) DIGITOS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIGITOS__SIO_CFG)
    #define DIGITOS_SIO_HYST_EN        (* (reg8 *) DIGITOS__SIO_HYST_EN)
    #define DIGITOS_SIO_REG_HIFREQ     (* (reg8 *) DIGITOS__SIO_REG_HIFREQ)
    #define DIGITOS_SIO_CFG            (* (reg8 *) DIGITOS__SIO_CFG)
    #define DIGITOS_SIO_DIFF           (* (reg8 *) DIGITOS__SIO_DIFF)
#endif /* (DIGITOS__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIGITOS__INTSTAT)
    #define DIGITOS_INTSTAT            (* (reg8 *) DIGITOS__INTSTAT)
    #define DIGITOS_SNAP               (* (reg8 *) DIGITOS__SNAP)
    
	#define DIGITOS_0_INTTYPE_REG 		(* (reg8 *) DIGITOS__0__INTTYPE)
	#define DIGITOS_1_INTTYPE_REG 		(* (reg8 *) DIGITOS__1__INTTYPE)
	#define DIGITOS_2_INTTYPE_REG 		(* (reg8 *) DIGITOS__2__INTTYPE)
	#define DIGITOS_3_INTTYPE_REG 		(* (reg8 *) DIGITOS__3__INTTYPE)
#endif /* (DIGITOS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIGITOS_H */


/* [] END OF FILE */
