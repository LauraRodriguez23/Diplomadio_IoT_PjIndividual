/*! @file : K32L2B31A_Project.c
 * @author  Laura Rodríguez Polo
 * @version 0.0.000
 * @date    09/09/2021
 * @brief   Funcion principal main
 * @details
 *			v0.0.000	Proyecto base creado usando MCUXpresso
 *
 *
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"

#include "leds.h"

#include "sensor_de_luz.h"

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

unsigned int test_global_var = 100;
float dato_float = 3.1416;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/

/*-----------------------------------------------------------------------------*/

/*!
 * @brief Genera bloqueo de microcontrolador por tiempo fijo
 *
 */
void delay_block(void){

	uint32_t i;
	for(i=0;i<0xFFFF;i++){

	}
}

/*-----------------------------------------------------------------------------*/

int main(void) {

	int i = 0 ;/* Force the counter to be placed into memory. */

	uint32_t adc_sensor_de_luz;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    printf("Hello World\n\r");
    printf("test_global_var: %d\n\r", test_global_var);
    printf("dato_float: %g\n\r", dato_float);

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
       i++ ;
       printf("i:%u\n\r", i);


       adc_sensor_de_luz = SensorDeLuzObtenerResultadoADC();

       printf("ADC SENSOR DE LUZ: %u\r\n", adc_sensor_de_luz);

    }
    return 0 ;
}
