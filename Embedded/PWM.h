/*void PWMSetSpeed(float vitesseEnPourcents,int motor);*/
void InitPWM(void);
void PWMUpdateSpeed();
void PWMSetSpeedConsigne(float vitesseEnPourcents, char moteur);
#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1
