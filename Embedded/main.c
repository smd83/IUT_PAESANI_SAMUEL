/* 
 * File:   main.c
 * Author: E306-PC4
 *
 * Created on September 2, 2026, 11:56 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "Robot.h"

int main(void) {
    //***********************************************************************************************
    //Initialisation oscillateur
    //**********************************************************************************************
    InitOscillator();
    //**********************************************************************************************
    // Configuration des input et output (IO)
    //**********************************************************************************************
    InitIO();
    LED_BLANCHE_1 = 0;
    LED_BLEUE_1 = 0;
    LED_ORANGE_1 = 0;
    LED_ROUGE_1 = 1;
    LED_VERTE_1 = 0;

    LED_BLANCHE_2 = 1;
    LED_BLEUE_2 = 1;
    LED_ORANGE_2 = 1;
    LED_ROUGE_2 = 1;
    LED_VERTE_2 = 1;
    InitTimer23();
    InitTimer1();
    //***********************************************************************************************
    //apppel des fonctions PWM
    //**********************************************************************************************
    InitPWM();

    /* PWMSetSpeed(0,MOTEUR_DROIT);
     PWMSetSpeed(0,MOTEUR_GAUCHE);*/
    /*PWMSetSpeedConsigne(0,MOTEUR_DROIT);
    PWMSetSpeedConsigne(0,MOTEUR_GAUCHE);
    PWMUpdateSpeed();*/
    InitADC1();
    
    //**********************************************************************************************
    // Boucle Principale
    //**********************************************************************************************
    while (1) {
        if (ADCIsConversionFinished() == 1)
    {
        ADCClearConversionFinishedFlag();
        unsigned int * result = ADCGetResult();
        float volts = ((float) result [0])* 3.3 / 4096;
        robotState.distanceTelemetreGauche = 34 / volts - 5;
        volts = ((float) result [1])* 3.3 / 4096;
        robotState.distanceTelemetreCentre = 34 / volts - 5;
        volts = ((float) result [2])* 3.3 / 4096;
        robotState.distanceTelemetreDroit = 34 / volts - 5;
}

    }
}