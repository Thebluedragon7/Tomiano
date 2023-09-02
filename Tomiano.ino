// Install CapacitiveSensor Library before using this Code
// https://playground.arduino.cc/Main/CapacitiveSensor/

#include <CapacitiveSensor.h>
#include "pitches.h"

#define COMMON_PIN 2  // The common 'send' pin for all keys
#define BUZZER_PIN 11      // The output pin for the piezo buzzer
#define NUM_OF_SAMPLES 10  // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD 50   // 150  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS 8      // Number of keys that are on the keyboard

// This macro creates a capacitance "key" sensor object for each key on the piano keyboard:
#define CS(Y) CapacitiveSensor(COMMON_PIN, Y)

// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
int notes[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };  // C-Major scale
//int notes[]={NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5}; // A-Minor scale
//int notes[]={NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_AS4,NOTE_C5,NOTE_DS5}; // C Blues scale

// Defines the pins that the keys are connected to:
CapacitiveSensor keys[] = { CS(3), CS(4), CS(5), CS(6), CS(7), CS(8), CS(9), CS(10) };

int capData;

void setup() {
  // Turn off autocalibrate on all channels:
  for (int i = 0; i < NUM_OF_KEYS; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  for (int i = 0; i < NUM_OF_KEYS; ++i) {
    capData = keys[i].capacitiveSensor(NUM_OF_SAMPLES);
    if (capData > CAP_THRESHOLD) {
      tone(BUZZER_PIN, notes[i], 10);
    }
  }
}
