/*! @file : sensor_de_temperatura.h
 * @author  Laura Rodríguez Polo
 * @version 1.0.0
 * @date    11/09/2021
 * @brief   Driver para lectura de sensor de temperatura interno en la tarjeta FRDM - K32L2B3
 * @details
 *
 */
#ifndef IOT_SDK_PERIPHERALS_SENSOR_DE_TEMPERATURA_H_
#define IOT_SDK_PERIPHERALS_SENSOR_DE_TEMPERATURA_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "peripherals.h"

/*!
 * @addtogroup PERIPHERALS
 * @{
 */
/*!
 * @addtogroup SENSOR_DE_TEMPERATURA
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/

#define SENSOR_DE_TEMPERATURA_ADC0_PERIPHERAL ADC0
#define SENSOR_DE_TEMPERATURA_ADC0_CH0_CONTROL_GROUP 0

#define VTEMP25			(float)(0.716)

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
 * @brief Retorna resultado de la conversion del voltaje ADC a el valor de la temperatura
 *
 */
float CalcularValorDeTemperatura(void);

/*-----------------------------------------------------------------------------*/

/** @} */ // end of SENSOR_DE_TEMPERATURA group
/** @} */ // end of PERIPHERALS group

#endif /* IOT_SDK_PERIPHERALS_SENSOR_DE_TEMPERATURA_H_ */
