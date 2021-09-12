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
#include "irq_lptmr0.h"
#include "botones.h"
#include "sensor_de_temperatura.h"

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

int main(void) {

	int i = 0 ;/* Force the counter to be placed into memory. */

	uint32_t adc_sensor_de_luz;

	float adc_sensor_de_temperatura;

	bool boton1, boton2;

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

    /* Start counting */
        LPTMR_StartTimer(LPTMR0);

    /* Enter an infinite loop, just incrementing a counter.*/
    while(1) {

    	if(lptmr0_irq_counter!=0){

    		toggle_led_rojo();
    		lptmr0_irq_counter=0;

    		i++ ;
    		printf("i:%u\n\r", i);

            boton1=boton_1LeerEstado();
            adc_sensor_de_temperatura = CalcularValorDeTemperatura();
            if(boton1==false){

                printf("TEMPERATURA: %f\r\n", adc_sensor_de_temperatura);

             }
    	    boton2=boton_2LeerEstado();
    	    adc_sensor_de_luz = CalcularValorDeLux();
    	    if(boton2==false){

    	       printf("LUX: %d\r\n", adc_sensor_de_luz);

             }

    	}

    }
    return 0 ;
}
