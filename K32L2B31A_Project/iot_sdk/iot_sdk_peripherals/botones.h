/*! @file : botones.h
 * @author  Laura Rodríguez Polo
 * @version 1.0.0
 * @date    11/09/2021
 * @brief   Driver para lectura de botones en la tarjeta FRDM - K32L2B3
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_BOTONES_H_
#define IOT_SDK_PERIPHERALS_BOTONES_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "peripherals.h"
#include "fsl_gpio.h"

/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup BOTONES
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/

bool boton_1LeerEstado();

bool boton_2LeerEstado();

/** @} */ // end of BOTONES
/** @} */ // end of PERIPHERALS

#endif /* IOT_SDK_PERIPHERALS_BOTONES_H_ */
