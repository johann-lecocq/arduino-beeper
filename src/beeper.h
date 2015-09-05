#ifndef __ecran__
#define __ecran__

struct Commande {
	byte note:4;
	byte octave:4;
	byte lenH;
	byte lenL;
};

void setup();

#endif
