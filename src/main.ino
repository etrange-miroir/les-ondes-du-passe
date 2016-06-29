#include <SoftwareSerial.h>
#include <Somo2.h>
#include <Button.h>

// Rx, Tx to the mp3 player
Somo2 somo(11, 12);
// play reed sensor
Button play = Button(2, INPUT_PULLUP);
// stop reed sensor
Button stop = Button(3, INPUT_PULLUP);
// busy pin to check wether the mp3 player is busy (i.e. playing) or not
int busy = 6;
// relay pin
int relay = 13;

void setup () {
	Serial.begin(9600);
	// init mp3 player
	somo.begin();
	somo.reset();
	delay(1000);
	somo.setVolume(20);
	// init relay pin
	pinMode(relay, OUTPUT);
	digitalWrite(relay, LOW);
}

void loop () {
	// check is the sound has ended, if so turn off the relay
	bool isBusy = digitalRead(busy);
	if (isBusy == HIGH) digitalWrite(relay, LOW);
	if (play.uniquePress()) {
		// play the sound
		somo.playTrack(1, 1);
		// turn on motor by activating the relay
		digitalWrite(relay, HIGH);
	}
	else if (stop.uniquePress()) {
		// stop the sound
		somo.stop();
		// turn off motor by deactivating the relay
		digitalWrite(relay, LOW);
	}
	// keep off bouncing
	delay(100);
}
