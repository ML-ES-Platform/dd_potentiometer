/*
 * dd_pot_demo.cpp
 *
 *  Created on: May 8, 2020
 *      Author: Andrei Bragarenco
 */

#include <MCAL/mcal_adc/mcal_adc.h>
#include <ESW/dd_pot/dd_pot.h>
#include <ESW/dd_pot/dd_pot_demo.h>


//The setup function is called once at startup of the sketch
void dd_pot_demo_setup() {
// Add your initialization code here
	Serial.begin(9600);
	Serial.println("MCAL ADC demo !");
	Std_ReturnType error = E_OK;

	error+= MCAL_ADC_ChannelSetup(ADC_1, A3);
	error+= MCAL_ADC_ChannelSetup(ADC_2, A4);
	error+= MCAL_ADC_ChannelSetup(ADC_3, A5);

	error+= DD_POT_ChannelSetup(POT_1, ADC_3);
	error+= DD_POT_ChannelSetup(POT_2, ADC_2);
	error+= DD_POT_ChannelSetup(POT_3, ADC_1);

	error+= DD_POT_SetPullMethod(POT_1, ADC_ReadChannel);
	error+= DD_POT_SetPullMethod(POT_2, ADC_ReadChannel);
	error+= DD_POT_SetPullMethod(POT_3, ADC_ReadChannel);


	Serial.print("Errors: ");
	Serial.println(error);


}

// The loop function is called in an endless loop
void dd_pot_demo_loop() {
//Add your repeated code here
	for (int i = 0; i < MCAL_ADC_CHANNEL_NR_OF; i++) {

		Std_RawDataType adcVal = ADC_ReadChannel(i);
		Serial.print(" : ");
		Serial.print(adcVal);
	}
	Serial.print(" : <--->");

	for (int i = 0; i < MCAL_ADC_CHANNEL_NR_OF; i++) {

		Std_PhyDataType potVal = POT_GetPosition(i);
		Serial.print(" : ");
		Serial.print(potVal);
	}

	Serial.println();
	delay(100);
}
