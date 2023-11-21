// Physical pinout of arduino board
#define TRIG 2
#define RED 3
#define ECHO 4
#define GREEN 5
#define BLUE 6
#define PROGRAM_BUTTON 7
#define DEBUG

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
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
