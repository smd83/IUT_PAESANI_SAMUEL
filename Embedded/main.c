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
#include "main.h"
unsigned long avant=0;
unsigned char stateRobot;
static uint8_t OLDSW1=0,OLDSW2=0,OLDSW3=0;

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
    InitADC1();

    /* PWMSetSpeed(0,MOTEUR_DROIT);
     PWMSetSpeed(0,MOTEUR_GAUCHE);*/
    /*PWMSetSpeedConsigne(0,MOTEUR_DROIT);
    PWMSetSpeedConsigne(0,MOTEUR_GAUCHE);
    PWMUpdateSpeed();*/
    



    //**********************************************************************************************
    // Boucle Principale
    //**********************************************************************************************
    while (1) {
        
        while(timestamp <= 59999){
        
            if((!SW1 && OLDSW1 ) || (!SW2 && OLDSW2) || (!SW3 && OLDSW3)){
                InitPWM();
                InitTimer4();
            }
                
                
            
    
          
            

            OLDSW1=SW1;
            OLDSW2=SW2;
            OLDSW3=SW3;
        
        
    
          if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [1])* 3.3 / 4096;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [3])* 3.3 / 4096;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [4])* 3.3 / 4096;
            robotState.distanceTelemetreDroit2 = 34 / volts - 5;
            volts = ((float) result [0])* 3.3 / 4096;
            robotState.distanceTelemetreGauche2 = 34 / volts - 5;
        }
            
        }
                break;
        
  }
}


void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_ATTENTE_EN_COURS;
        case STATE_ATTENTE_EN_COURS:
            if (timestamp > 1000)
                stateRobot = STATE_AVANCE;
            break;
        case STATE_AVANCE:
            PWMSetSpeedConsigne(-25, MOTEUR_DROIT);
            PWMSetSpeedConsigne(25, MOTEUR_GAUCHE);
            stateRobot = STATE_AVANCE_EN_COURS;
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(15, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(-20, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-20, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(20, MOTEUR_DROIT);
            PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        default:
            stateRobot = STATE_ATTENTE;
            break;
    }
}
unsigned char nextStateRobot = 0;

void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;
    //éDtermination de la position des obstacles en fonction des ééètlmtres
    if (robotState.distanceTelemetreDroit < 27 &&
            robotState.distanceTelemetreCentre > 28 &&
            robotState.distanceTelemetreGauche > 27) //Obstacle à droite
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit > 27 &&
            robotState.distanceTelemetreCentre > 28 &&
            robotState.distanceTelemetreGauche < 27) //Obstacle à gauche
        positionObstacle = OBSTACLE_A_GAUCHE;
    else if (robotState.distanceTelemetreDroit2 < 23 &&
            robotState.distanceTelemetreCentre > 28 &&
            (robotState.distanceTelemetreGauche2) > 23)
        positionObstacle = OBSTACLE_A_DROITE2; //obstacle tout a droite
    else if ((robotState.distanceTelemetreDroit2) > 23 &&
            robotState.distanceTelemetreCentre > 28 &&
            robotState.distanceTelemetreGauche2  < 23)
        positionObstacle = OBSTACLE_A_GAUCHE2; //obstacle tout a droite
    else if (robotState.distanceTelemetreCentre < 28)//Obstacle en face
        positionObstacle = OBSTACLE_EN_FACE;
    else if (robotState.distanceTelemetreDroit > 27 &&
            robotState.distanceTelemetreCentre > 28 &&
            robotState.distanceTelemetreGauche > 27 &&
            robotState.distanceTelemetreGauche2 > 23 &&
            robotState.distanceTelemetreDroit2 > 23) //pas d'obstacle
        positionObstacle = PAS_D_OBSTACLE;
    //éDtermination de lé?tat àvenir du robot
    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == OBSTACLE_A_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_A_DROITE2)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_GAUCHE2)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE){
     nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
    }
    //Si l?on n?est pas dans la transition de lé?tape en cours
    if (nextStateRobot != stateRobot - 1) stateRobot = nextStateRobot;
}