/*! @file : sensor_de_luz.c
 * @author  Laura Rodríguez Polo
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sensor_de_luz.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/

/*-----------------------------------------------------------------------------*/

/*!
 * @brief Inicia captura por ADC de voltaje generado por sensor de luz
 *
 */
void SensorDeLuzIniciarCaptura(void);

/*-----------------------------------------------------------------------------*/

/*!
 * @brief Espera a que finalice el trabajo del ADC
 *
 */
void SensorDeLuzEsperarResultado(void);

/*-----------------------------------------------------------------------------*/

/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/

/*-----------------------------------------------------------------------------*/
 
void SensorDeLuzIniciarCaptura(void){

	ADC16_SetChannelConfig(SENSOR_DE_LUZ_ADC16_BASE, SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[0]);

}

/*-----------------------------------------------------------------------------*/

void SensorDeLuzEsperarResultado(void){

	while (0U == (kADC16_ChannelConversionDoneFlag &
	                      ADC16_GetChannelStatusFlags(
	                    		  SENSOR_DE_LUZ_ADC16_BASE,
								  SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP)))
    {
	}

}

/*-----------------------------------------------------------------------------*/

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/

/*-----------------------------------------------------------------------------*/

uint32_t SensorDeLuzObtenerResultadoADC(void){

	uint32_t resultadoADC;

	SensorDeLuzIniciarCaptura();
    SensorDeLuzEsperarResultado();

	resultadoADC = ADC16_GetChannelConversionValue(SENSOR_DE_LUZ_ADC16_BASE, SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP);

	return(resultadoADC);

}

/*-----------------------------------------------------------------------------*/

uint32_t CalcularValorDeLux(void){

	uint32_t adc_Voltaje_del_Sensor;

	adc_Voltaje_del_Sensor = SensorDeLuzObtenerResultadoADC();
	adc_Voltaje_del_Sensor = (2*(Vref-(Vref/adc_Voltaje_del_Sensor)))*Vr;

	return (adc_Voltaje_del_Sensor);

}
/*-----------------------------------------------------------------------------*/
