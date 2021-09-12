/*! @file : sensor_de_temperatura.c
 * @author  Laura Rodríguez Polo
 * @version 1.0.0
 * @date    11/09/2021
 * @brief   Driver para lectura de sensor de temperatura interno en la tarjeta FRDM - K32L2B3
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "sensor_de_temperatura.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/

/*-----------------------------------------------------------------------------*/

/*!
 * @brief Inicia captura por ADC de voltaje generado por sensor de temperatura
 *
 */
void SensorDeTemperaturauzIniciarCaptura(void);

/*-----------------------------------------------------------------------------*/
/*!
 * @brief Espera a que finalice el trabajo del ADC
 *
 */
void SensorDeTemperaturaEsperarResultado(void);

/*-----------------------------------------------------------------------------*/
/*!
 * @brief Inicia captura por ADC de voltaje generado por BandGap
 *
 */
void IniciarCapturaVoltajeDeIntervaloDeBanda(void);

/*-----------------------------------------------------------------------------*/
/*!
 * @brief Espera a que finalice el trabajo del ADC
 *
 */
void EsperarResultadoVoltajeDeIntervaloDeBanda(void);

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

void SensorDeTemperaturaIniciarCaptura(void){

	ADC16_SetChannelConfig(SENSOR_DE_TEMPERATURA_ADC0_PERIPHERAL,
			SENSOR_DE_TEMPERATURA_ADC0_CH0_CONTROL_GROUP,
			&ADC0_channelsConfig[1]);

}

/*-----------------------------------------------------------------------------*/

void SensorDeTemperaturaEsperarResultado(void){

	while (0U== (kADC16_ChannelConversionDoneFlag&
			ADC16_GetChannelStatusFlags(
					SENSOR_DE_TEMPERATURA_ADC0_PERIPHERAL,
					SENSOR_DE_TEMPERATURA_ADC0_CH0_CONTROL_GROUP)))
	{
	}

}

/*-----------------------------------------------------------------------------*/

void IniciarCapturaVoltajeDeIntervaloDeBanda(void){

	ADC16_SetChannelConfig(SENSOR_DE_TEMPERATURA_ADC0_PERIPHERAL,
			SENSOR_DE_TEMPERATURA_ADC0_CH0_CONTROL_GROUP,
			&ADC0_channelsConfig[2]);

}

/*-----------------------------------------------------------------------------*/

void EsperarResultadoVoltajeDeIntervaloDeBanda(void){

	while (0U== (kADC16_ChannelConversionDoneFlag&
			ADC16_GetChannelStatusFlags(
					SENSOR_DE_TEMPERATURA_ADC0_PERIPHERAL,
					SENSOR_DE_TEMPERATURA_ADC0_CH0_CONTROL_GROUP)))
	{
	}

}

/*-----------------------------------------------------------------------------*/

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 
/*-----------------------------------------------------------------------------*/

uint32_t SensorDeTemperaturaObtenerResultadoADC(void){

	uint32_t adc_valor_de_temperatura;

	SensorDeTemperaturaIniciarCaptura();
	SensorDeTemperaturaEsperarResultado();

	adc_valor_de_temperatura = ADC16_GetChannelConversionValue(
			SENSOR_DE_TEMPERATURA_ADC0_PERIPHERAL,
			SENSOR_DE_TEMPERATURA_ADC0_CH0_CONTROL_GROUP);

	return (adc_valor_de_temperatura);

}

/*-----------------------------------------------------------------------------*/

uint32_t VoltajeDeIntervaloDeBandaObtenerResultadoADC(void){

	uint32_t adc_valor_de_voltaje_de_banda;

	IniciarCapturaVoltajeDeIntervaloDeBanda();
	EsperarResultadoVoltajeDeIntervaloDeBanda();

	adc_valor_de_voltaje_de_banda = ADC16_GetChannelConversionValue(
			SENSOR_DE_TEMPERATURA_ADC0_PERIPHERAL,
			SENSOR_DE_TEMPERATURA_ADC0_CH0_CONTROL_GROUP);

	return (adc_valor_de_voltaje_de_banda);

}

/*-----------------------------------------------------------------------------*/

float CalcularValorDeTemperatura(void){
	float Vref;
	float Temperatura;
	float Valor_Temperatura;
	float Valor_Pendiente;

	uint32_t adc_valor_temperatura;
	uint32_t adc_valor_voltaje_de_intervalo_de_banda;

	adc_valor_voltaje_de_intervalo_de_banda = VoltajeDeIntervaloDeBandaObtenerResultadoADC();
	//Captura ADC para obtener valor de referencia bandgap
	Vref = (float)((float)4095*1.2/adc_valor_voltaje_de_intervalo_de_banda);
	//Convierte ADC a Voltaje para obtener Vref

	adc_valor_temperatura = SensorDeTemperaturaObtenerResultadoADC();
	//Captura ADC del sensor de temperatura
	Valor_Temperatura = (float)((adc_valor_temperatura)*(Vref)/ (float)(4095));
	//Convierte ADC a voltaje para obtener Vtemp

	if(Valor_Temperatura>=VTEMP25){

		Valor_Pendiente=(float)1.646;	//Pendiente Fria

	}
	else{

		Valor_Pendiente=(float)1.769;	//Pendiente Caliente

	}

	Temperatura = (float)(((float)(Valor_Temperatura)-(float)(VTEMP25))/(float)(Valor_Pendiente));
	//Convierte voltaje a temperatura
	Temperatura = (float)(25-Temperatura);

	return(Temperatura);
}

/*-----------------------------------------------------------------------------*/
