#include <Arduino.h>

#include "beeper.h"

#define PIN_BUZZER 8
#define DUREE_PREMIERE_NOTE 200
#define HAUTEUR_PREMIERE_NOTE 440
#define SERIAL_SPEED 9600
#define DELAY_ATTENTE_SERIAL 100

#define NOTE_MUETTE 12 // ou soupir pour les musiciens
int NOTES[12][8] = {
  { 33,  65, 131, 262, 523, 1046, 2093, 4186 },
  { 35,  69, 139, 277, 554, 1109, 2217, 4435 },
  { 37,  73, 147, 294, 587, 1175, 2349, 4699 },
  { 39,  78, 155, 311, 622, 1244, 2489, 4978 },
  { 41,  82, 165, 330, 659, 1328, 2637, 5274 },
  { 44,  87, 175, 349, 698, 1397, 2794, 5588 },
  { 46,  92, 185, 370, 740, 1480, 2960, 5920 },
  { 49,  98, 196, 392, 784, 1568, 3136, 6271 },
  { 52, 104, 208, 415, 831, 1661, 3322, 6645 },
  { 55, 110, 220, 440, 880, 1760, 3520, 7040 },
  { 58, 116, 233, 466, 932, 1865, 3729, 7459 },
  { 62, 123, 245, 494, 988, 1975, 3951, 7902 }
};


int main() {
	short int longueur;
	Commande commande;
	init();
	setup();
	for(;;){
		if(Serial.available() < 3) {
			delay(DELAY_ATTENTE_SERIAL);
			continue;
		}
		Serial.readBytes((char *)(&commande), 3);
		longueur = ((commande.lenH & 0xFF) << 8) | (commande.lenL & 0xFF);
		if (commande.note != NOTE_MUETTE) {
			tone(PIN_BUZZER, NOTES[commande.note][commande.octave - 1], longueur);
		}
		delay(longueur);
	}
	return 0;
}

void setup() {
	Serial.begin(SERIAL_SPEED);
	delay(500);
	tone(PIN_BUZZER, HAUTEUR_PREMIERE_NOTE, DUREE_PREMIERE_NOTE);
}

