/*******************************************************************************
* File Name: LED_ORANGE.h  
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

#if !defined(CY_PINS_LED_ORANGE_H) /* Pins LED_ORANGE_H */
#define CY_PINS_LED_ORANGE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LED_ORANGE_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LED_ORANGE__PORT == 15 && ((LED_ORANGE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LED_ORANGE_Write(uint8 value);
void    LED_ORANGE_SetDriveMode(uint8 mode);
uint8   LED_ORANGE_ReadDataReg(void);
uint8   LED_ORANGE_Read(void);
void    LED_ORANGE_SetInterruptMode(uint16 position, uint16 mode);
uint8   LED_ORANGE_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LED_ORANGE_SetDriveMode() function.
     *  @{
     */
        #define LED_ORANGE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LED_ORANGE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LED_ORANGE_DM_RES_UP          PIN_DM_RES_UP
        #define LED_ORANGE_DM_RES_DWN         PIN_DM_RES_DWN
        #define LED_ORANGE_DM_OD_LO           PIN_DM_OD_LO
        #define LED_ORANGE_DM_OD_HI           PIN_DM_OD_HI
        #define LED_ORANGE_DM_STRONG          PIN_DM_STRONG
        #define LED_ORANGE_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LED_ORANGE_MASK               LED_ORANGE__MASK
#define LED_ORANGE_SHIFT              LED_ORANGE__SHIFT
#define LED_ORANGE_WIDTH              1u

/* Interrupt constants */
#if defined(LED_ORANGE__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LED_ORANGE_SetInterruptMode() function.
     *  @{
     */
        #define LED_ORANGE_INTR_NONE      (uint16)(0x0000u)
        #define LED_ORANGE_INTR_RISING    (uint16)(0x0001u)
        #define LED_ORANGE_INTR_FALLING   (uint16)(0x0002u)
        #define LED_ORANGE_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LED_ORANGE_INTR_MASK      (0x01u) 
#endif /* (LED_ORANGE__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_ORANGE_PS                     (* (reg8 *) LED_ORANGE__PS)
/* Data Register */
#define LED_ORANGE_DR                     (* (reg8 *) LED_ORANGE__DR)
/* Port Number */
#define LED_ORANGE_PRT_NUM                (* (reg8 *) LED_ORANGE__PRT) 
/* Connect to Analog Globals */                                                  
#define LED_ORANGE_AG                     (* (reg8 *) LED_ORANGE__AG)                       
/* Analog MUX bux enable */
#define LED_ORANGE_AMUX                   (* (reg8 *) LED_ORANGE__AMUX) 
/* Bidirectional Enable */                                                        
#define LED_ORANGE_BIE                    (* (reg8 *) LED_ORANGE__BIE)
/* Bit-mask for Aliased Register Access */
#define LED_ORANGE_BIT_MASK               (* (reg8 *) LED_ORANGE__BIT_MASK)
/* Bypass Enable */
#define LED_ORANGE_BYP                    (* (reg8 *) LED_ORANGE__BYP)
/* Port wide control signals */                                                   
#define LED_ORANGE_CTL                    (* (reg8 *) LED_ORANGE__CTL)
/* Drive Modes */
#define LED_ORANGE_DM0                    (* (reg8 *) LED_ORANGE__DM0) 
#define LED_ORANGE_DM1                    (* (reg8 *) LED_ORANGE__DM1)
#define LED_ORANGE_DM2                    (* (reg8 *) LED_ORANGE__DM2) 
/* Input Buffer Disable Override */
#define LED_ORANGE_INP_DIS                (* (reg8 *) LED_ORANGE__INP_DIS)
/* LCD Common or Segment Drive */
#define LED_ORANGE_LCD_COM_SEG            (* (reg8 *) LED_ORANGE__LCD_COM_SEG)
/* Enable Segment LCD */
#define LED_ORANGE_LCD_EN                 (* (reg8 *) LED_ORANGE__LCD_EN)
/* Slew Rate Control */
#define LED_ORANGE_SLW                    (* (reg8 *) LED_ORANGE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LED_ORANGE_PRTDSI__CAPS_SEL       (* (reg8 *) LED_ORANGE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LED_ORANGE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LED_ORANGE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LED_ORANGE_PRTDSI__OE_SEL0        (* (reg8 *) LED_ORANGE__PRTDSI__OE_SEL0) 
#define LED_ORANGE_PRTDSI__OE_SEL1        (* (reg8 *) LED_ORANGE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LED_ORANGE_PRTDSI__OUT_SEL0       (* (reg8 *) LED_ORANGE__PRTDSI__OUT_SEL0) 
#define LED_ORANGE_PRTDSI__OUT_SEL1       (* (reg8 *) LED_ORANGE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LED_ORANGE_PRTDSI__SYNC_OUT       (* (reg8 *) LED_ORANGE__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LED_ORANGE__SIO_CFG)
    #define LED_ORANGE_SIO_HYST_EN        (* (reg8 *) LED_ORANGE__SIO_HYST_EN)
    #define LED_ORANGE_SIO_REG_HIFREQ     (* (reg8 *) LED_ORANGE__SIO_REG_HIFREQ)
    #define LED_ORANGE_SIO_CFG            (* (reg8 *) LED_ORANGE__SIO_CFG)
    #define LED_ORANGE_SIO_DIFF           (* (reg8 *) LED_ORANGE__SIO_DIFF)
#endif /* (LED_ORANGE__SIO_CFG) */

/* Interrupt Registers */
#if defined(LED_ORANGE__INTSTAT)
    #define LED_ORANGE_INTSTAT            (* (reg8 *) LED_ORANGE__INTSTAT)
    #define LED_ORANGE_SNAP               (* (reg8 *) LED_ORANGE__SNAP)
    
	#define LED_ORANGE_0_INTTYPE_REG 		(* (reg8 *) LED_ORANGE__0__INTTYPE)
#endif /* (LED_ORANGE__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LED_ORANGE_H */


/* [] END OF FILE */
