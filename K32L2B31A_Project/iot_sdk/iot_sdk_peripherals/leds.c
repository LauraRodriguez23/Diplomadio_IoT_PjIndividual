/*! @file : leds.c
 * @author  Laura Rodríguez Polo
 * @version 1.0.0
 * @date    9/09/2021
 * @brief   Driver para controlar LEDs de la tarjeta FRDM - K32L2B3
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "leds.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 
void encender_led_rojo(){

	GPIO_PinWrite(GPIOE,31,0);

	//encender led verde
}

void apagar_led_rojo(){

	GPIO_PinWrite(GPIOE,31,1);

	//encender led verde
}

void encender_led_verde(){

	GPIO_PinWrite(GPIOD,5,0);

	//encender led verde
}

void apagar_led_verde(){

	GPIO_PinWrite(GPIOD,5,1);

	//apagar led verde
}

void toggle_led_rojo(){

	GPIO_PortToggle(GPIOE, 1U << 31U);

}
