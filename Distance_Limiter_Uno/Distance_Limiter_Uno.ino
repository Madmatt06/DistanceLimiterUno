#include <EEPROM.h>

// Physical pinout of arduino board
#define TRIG 2
#define RED 3
#define ECHO 4
#define GREEN 5
#define BLUE 6
#define PROGRAM_BUTTON 7
#define DEBUG

// Other constants.
#define EEPROMSTARTADDRESS 0
#define USEEEPROM false

// Distance is stored as milliseconds for trigger to go high.
// Change this to set default for first flash.
float defaultDistance = 30;

// Will blink faster on yellow as object gets closer if true.
// If false, will instead fade from green to yellow and then red.
// Change this to set default for first flash.
boolean defaultBlink = true;

// Keeps track of what mode the arduino is currently in.
// 0 = Normal operation
// 1 = Setting distance threshold
// 2 = Toggle is flashing settings
short int operation = 0;

// This is how the settings will be stored in EEPROM.
// Pass -U flag to avrdude to reset all settings while flashing to arduino.
struct settings_t {
  float distance;
  boolean doBlink;
};

// This stores the settings which will be used in the whole program.
settings_t Settings;

void setupSettings() {
  #if USEEEEPROM
  Serial.println("Reading EEPROM for settings");
  EEPROM.get(EEPROMSTARTADDRESS, Settings);
  #ifdef DEBUG
  Serial.println("DEBUG START");
  Serial.println("EEPROM returned struct Settings with distance = " + String(Settings.distance) + " and blink = " + String(Settings.doBlink));
  Serial.println("DEBUG END");
  #endif
  Serial.println(Settings.doBlink);
  if(isnan(Settings.distance)) {
    Serial.println("Writing Default settings to EEPROM due to invalid data");
    #ifdef DEBUG
    Serial.println("DEBUG START");
    Serial.println("defaultDistance = " + String(defaultDistance) + " defaultBlink = " + String(defaultBlink));
    #endif
    Settings.distance = defaultDistance;
    Settings.doBlink = defaultBlink;
    #ifdef DEBUG
    Serial.println("Writing Settings Object to EEPROM.");
    Serial.println("distance = " + String(Settings.distance) + " and blink = " + String(Settings.doBlink));
    #endif
    //EEPROM.put(EEPROMSTARTADDRESS, Settings);
    Serial.println("Would have used EEPROM");
    #ifdef DEBUG
    EEPROM.get(EEPROMSTARTADDRESS, Settings);
    Serial.println("DEBUG START");
    Serial.println("EEPROM returned struct Settings with distance = " + String(Settings.distance) + " and blink = " + String(Settings.doBlink));
    Serial.println("DEBUG END");
    #endif
  } else {
    Serial.println("EEPROM Data Valid");
  }
  #else
  Serial.println("EEPROM disabled. Using default values");
  Settings.distance = defaultDistance;
  Settings.doBlink = defaultBlink;
  #ifdef DEBUG
  Serial.println("DEBUG START");
  Serial.println("Default values are set");
  Serial.println("distance = " + String(Settings.distance) + " and blink = " + String(Settings.doBlink));
  Serial.println("DEBUG STOP");
  #endif
  #endif
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  #ifdef DEBUG
  Serial.println("DEBUG START");
  Serial.println("Trigger Output Pin #" + String(TRIG) + "\nEcho Input Pin #" + String(ECHO) + "\nRGB LED Output pins R #" + String(RED) + " G #" + String(GREEN) + " B #" + String(BLUE) + "\nProgram Button input pin #" + String(PROGRAM_BUTTON) + "\nLED_BUILTIN Output pin #" + String(LED_BUILTIN));
  Serial.println("DEBUG END");
  #endif
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PROGRAM_BUTTON, INPUT_PULLUP);
  setupSettings();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
