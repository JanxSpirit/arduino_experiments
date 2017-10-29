int PIEZZO = 8;
int minToneCal = 10000;
int maxToneCal = 0;
int PAUSE_BTN = 13;
int TONE_LED_1 = 2;
int TONE_LED_2 = 3;
int TONE_LED_3 = 4;
int TONE_LED_4 = 5;
int toneLeds[] = {TONE_LED_1, TONE_LED_2, TONE_LED_3, TONE_LED_4};

boolean paused = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(PAUSE_BTN, INPUT);
  pinMode(PIEZZO, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TONE_LED_1, OUTPUT);
  pinMode(TONE_LED_2, OUTPUT);
  pinMode(TONE_LED_3, OUTPUT);
  pinMode(TONE_LED_4, OUTPUT);

  Serial.begin(9600);

  //calibration time
  digitalWrite(LED_BUILTIN, HIGH);
  while (millis() < 5000) {
    int ao = analogRead(A0);
    if (ao > maxToneCal) {
      maxToneCal = ao;
    }
    if (ao < minToneCal) {
      minToneCal = ao;
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  //read potentiometer
  int potVal = analogRead(A1);
  int toneDialLedValue = map(potVal, 0, 1023, 1, 5) - 1;
  //power indicator LEDs
  for (int i = 0; i < 4; i++) {
    if (toneDialLedValue > i) {
      digitalWrite(toneLeds[i], HIGH);
    } else {
      digitalWrite(toneLeds[i], LOW);
    }
  }
  

  //puase btn
  if (digitalRead(PAUSE_BTN) == HIGH) {
    paused = !paused;
    delay(500);
  }

  //Serial.println("not paused");
  int sensorValue = analogRead(A0);

  //serial ouput
  int aonorm = map(sensorValue, 100, 750, 1, 100);
  for (int i = 0; i < aonorm; i++) {
    Serial.print(".");
  }
  Serial.println();

  if (paused) {
    delay(50);
  } else {
    //sound output
    int adjustedMaxTone = map(potVal, 0, 1023, 2000, 4000);
    int atone = map(sensorValue, minToneCal, maxToneCal, 50, adjustedMaxTone);
    tone (PIEZZO, atone, 40);
  }
}
