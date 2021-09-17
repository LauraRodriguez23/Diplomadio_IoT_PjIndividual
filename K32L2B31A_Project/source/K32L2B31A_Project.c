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

#include "irq_lpuart0.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*#define MENSAJE_DEFINE	"define\r\n"

#define CMD_AT_CREG		3*/

#define COMANDOS_DISPONIBLES 	7

enum _ec25_lista_comandos_at{

	kAT = 0,
	kATI,
    kAT_CPIN,
    kAT_CREG,
    kAT_CMGF_1,
    kAT_CMGS,
    kAT_TEXT_MSG_END,

};

enum _lista_comandos_control{

	kLED_VERDE_ON = 0,
	kLED_VERDE_OFF,
	kLED_ROJO_ON,
	kLED_ROJO_OFF,
	kSENSOR_LUZ,
	kSENSOR_TEMPERATURA,
	kENVIAR_COMANDO,

};
/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Local vars
 ******************************************************************************/
/*
 *
 *//*--------------------------------------------------------------------------------------------------------
char mensaje_ram[]="ram\r\n";
const char mensaje_flash[]= "const\r\n";
const char *mensaje_apuntador= "apuntador\r\n";
const char *instrucciones[]={

		"instruccion 1\r\n",
		"instruccion 2\r\n",
		"instruccion 3\r\n",
		"instruccion 4\r\n",
		"instruccion 5\r\n",
		"instruccion 6\r\n",

};
--------------------------------------------------------------------------------------------------------*/
//Listado de comando AT disponibles para ser enviados al modem Quectel
const char *ec25_comandos_at[] = {

		"AT", //comprueba disponibilidad de dispositivo
		"ATI", //consulta información del modem
		"AT+CPIN?", //consulta estado de la simcard
		"AT+CREG?", //consulta estado de la red celular y tecnología usada en red celular
		"AT+CMGF=1", //asigna modo texto para enviar mensajes
		"AT+CMGS=\"300xxxxxxx\"", //envia mensaje de texto a numero definido
		"Mensaje", //MENSAJE & CTRL+Z

    };

const char *ec25_respuestas_at[] = {

		"Quectel:EC25_Revision:EC25EFAR02A09M4G", //Respuesta a comando ATI
    };
/*--------------------------------------------------------------------------------------------------------*/
//Listado de comandos de control disponibles para ser enviados al modem Quectel
const char *comandos_control[] = {

		"LED_VERDE_ON", //Enciende LED verde
		"LED_VERDE_OFF", //Apaga LED verde
		"LED_ROJO_ON", //Enciende LED rojo
		"LED_ROJO_OFF", //Apaga LED rojo
		"SENSOR_LUZ", //Imprime lectura del sensor de luz
		"SENSOR_TEMPERATURA", //Imprime lectura del sensor de temperatura
		"ENVIAR_COMANDO", //Envia comando ATI

		};
/*--------------------------------------------------------------------------------------------------------*/
char buffer_comando_recibido[20];
uint32_t index_buffer_nuevo_comando_recibido = 0;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
void limpiarBufferComando(){
	for(int i=0; i<20; i++){
		buffer_comando_recibido[i]=0;
	}
	index_buffer_nuevo_comando_recibido=0;
}

int main(void) {

	//int i = 0 ;/* Force the counter to be placed into memory. */

	bool boton1, boton2;

	uint8_t nuevo_byte_lpuart0;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    printf("FRDM-K32L2B3 Iniciando...\r\n");

    /*uint8_t index;
    char dato;
    uint32_t size;

    size = sizeof(mensaje_ram);
    for(index=0;index<size;index++){

    	dato=mensaje_ram[index];
    	printf("%c", dato);
    }

    printf("%s", MENSAJE_DEFINE);

    size = sizeof(mensaje_flash);
    for(index=0;index<size;index++){

    	dato=mensaje_flash[index];
    	printf("%c", dato);
    }

    printf("%s", mensaje_flash);

    printf("%s", mensaje_apuntador);

    printf("%s", instrucciones[0]);
    printf("%s", instrucciones[1]);
    printf("%s", instrucciones[2]);
    printf("%s", instrucciones[3]);
    printf("%s", instrucciones[4]);

    for(int i=0;i<4;i++){

    	printf("%s", instrucciones[i]);
    }

    printf("%s\r\n", ec25_comandos_at[CMD_AT_CREG]);*/

    //printf("%s\r\n", ec25_comandos_at[kATI]);

    /* Start counting */
        LPTMR_StartTimer(LPTMR0);

    /*-----------------------------------------------------------------------------*/
    /*!
     * @brief Imprime resultado de la conversion del voltaje ADC a el valor de luxes
     *
     */
      uint32_t imprimirValorDeLux(void){

    	   uint32_t adc_sensor_de_luz;
    	   adc_sensor_de_luz = CalcularValorDeLux();


    	   printf("LUX: %d\r\n", adc_sensor_de_luz);

    	   return (adc_sensor_de_luz);
    	}
     /*-----------------------------------------------------------------------------*/
     /*!
      * @brief Imprime resultado de la conversion del voltaje ADC a el valor de temperatura
      *
      */
       float imprimirValorDeTemperatura(void){

    	   float adc_sensor_de_temperatura;
    	   adc_sensor_de_temperatura = CalcularValorDeTemperatura();

              printf("TEMPERATURA: %f\r\n", adc_sensor_de_temperatura);

              return (adc_sensor_de_temperatura);
         }
      /*-----------------------------------------------------------------------------*/

    /* Enter an infinite loop, just incrementing a counter.*/
    while(1) {

    	/* Pregunta si existe byte dispobible */
    	if(numeroDeByteDisponibleEnBufferRX()!=0){

    		nuevo_byte_lpuart0 = pullByteDesdeBufferCircular();
    		buffer_comando_recibido[index_buffer_nuevo_comando_recibido]=nuevo_byte_lpuart0;
    		index_buffer_nuevo_comando_recibido++;

    		printf("Nuevo Byte: %c\r\n", nuevo_byte_lpuart0);

    		char *puntero_ok;
    		if(nuevo_byte_lpuart0=='\n'){

    			for(int i=0;i<COMANDOS_DISPONIBLES;i++){

    				puntero_ok = (char*)(strstr((char*)(&buffer_comando_recibido[0]),(char*)(comandos_control[i])));
    				if(puntero_ok!=0){

    					switch(i){

    					case kLED_VERDE_ON:
    						encender_led_verde();
    						break;

    					case kLED_VERDE_OFF:
    						apagar_led_verde();
    						break;

    					case kLED_ROJO_ON:
    						encender_led_rojo();
    					    break;

    					case kLED_ROJO_OFF:
    						apagar_led_rojo();
    					    break;

    					case kSENSOR_LUZ:
    						imprimirValorDeLux();
    					    break;

    					case kSENSOR_TEMPERATURA:
    						imprimirValorDeTemperatura();
    					    break;

    					case kENVIAR_COMANDO:
    						printf("%s\r\n", ec25_comandos_at[kATI]);
    					    break;

    					}
    				}
    			}

    			limpiarBufferComando();
    		}

    	}

    	if(lptmr0_irq_counter!=0){

    		//toggle_led_rojo();
    		lptmr0_irq_counter=0;

    		/*i++ ;
    		printf("i:%u\n\r", i);*/

            boton1=boton_1LeerEstado();
            if(boton1==false){
                printf("Boton 1\r\n");
             }

    	    boton2=boton_2LeerEstado();
    	    if(boton2==false){
    	    	printf("Boton 2\r\n");
             }
    	}
    }
    return 0 ;
}
