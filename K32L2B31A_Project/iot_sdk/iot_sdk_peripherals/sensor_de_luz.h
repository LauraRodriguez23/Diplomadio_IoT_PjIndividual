/*! @file : sensor_de_luz.h
 * @author  Laura Rodríguez Polo
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para 
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_SENSOR_DE_LUZ_H_
#define IOT_SDK_PERIPHERALS_SENSOR_DE_LUZ_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"

/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup SENSOR_DE_LUZ
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/

#define SENSOR_DE_LUZ_ADC16_BASE          ADC0
#define SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP 0U
#define SENSOR_DE_LUZ_ADC16_USER_CHANNEL  3U /* PTE22, ADC0_SE3 */

#define Vref			(float)(3.3)
#define Vr              (uint32_t)(10000)
/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/

/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/

/*-----------------------------------------------------------------------------*/
/*!
 * @brief Retorna resultado de la conversion del voltaje ADC a el valor de luxes
 *
 */
uint32_t CalcularValorDeLux(void);

/*-----------------------------------------------------------------------------*/

/** @} */ // end of SENSOR_DE_LUZ
/** @} */ // end of PERIPHERALS

#endif /* IOT_SDK_PERIPHERALS_SENSOR_DE_LUZ_H_ */
