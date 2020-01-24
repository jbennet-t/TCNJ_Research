/*******************************************************************************
* File Name: Stepper.h  
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

#if !defined(CY_PINS_Stepper_ALIASES_H) /* Pins Stepper_ALIASES_H */
#define CY_PINS_Stepper_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Stepper_0			(Stepper__0__PC)
#define Stepper_0_INTR	((uint16)((uint16)0x0001u << Stepper__0__SHIFT))

#define Stepper_1			(Stepper__1__PC)
#define Stepper_1_INTR	((uint16)((uint16)0x0001u << Stepper__1__SHIFT))

#define Stepper_2			(Stepper__2__PC)
#define Stepper_2_INTR	((uint16)((uint16)0x0001u << Stepper__2__SHIFT))

#define Stepper_3			(Stepper__3__PC)
#define Stepper_3_INTR	((uint16)((uint16)0x0001u << Stepper__3__SHIFT))

#define Stepper_INTR_ALL	 ((uint16)(Stepper_0_INTR| Stepper_1_INTR| Stepper_2_INTR| Stepper_3_INTR))

#endif /* End Pins Stepper_ALIASES_H */


/* [] END OF FILE */
