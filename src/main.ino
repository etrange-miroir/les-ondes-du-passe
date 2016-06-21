#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#include <Button.h>

// Rx, Tx to the mp3 player
SoftwareSerial mySerial(10, 11);
// play reed sensor
Button play = Button(2, INPUT_PULLUP);
// stop reed sensor
Button stop = Button(3, INPUT_PULLUP);
// relay pin
int relay = 4;

void setup () {
	Serial.begin(9600);
	// init mp3 player
	mySerial.begin(9600);
	mp3_set_serial(mySerial);
	mp3_set_volume(20);
	delay(2000);
	// init relay pin
	pinMode(relay, OUTPUT);
	digitalWrite(relay, LOW);
}

void loop () {
	if (play.uniquePress()) {
		// play the sound
		mp3_play(1);
		// turn on motor by activating the relay
		digitalWrite(relay, HIGH);
	}
	else if (stop.uniquePress()) {
		// stop the sound
		mp3_stop();
		// turn off motor by deactivating the relay
		digitalWrite(relay, LOW);
	}
	// keep off bouncing
	delay(100);
}
