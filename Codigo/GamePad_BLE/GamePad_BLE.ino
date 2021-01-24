//Ref Botones: https://fccid.io/S8DGGE917-D/User-Manual/User-Manual-548661
//Libreria: https://github.com/lemmingDev/ESP32-BLE-Gamepad
#include <BleGamepad.h>
#include "pines.h"

BleGamepad bleGamepad("ESP GamePad", "Leimer G.", 100);

const int threshold = 20;
int touchValueL2;
int touchValueR2;
int touchValueT2;
bool stateLed = 0;
int stateConnection = 0;
bool stateBattery = false;
int period = 2000;
unsigned long time_now = 0;

const int numberOfPotSamples = 5;     // Number of pot samples to take (to smooth the values)
const int delayBetweenSamples = 2;    // Delay in milliseconds between pot samples
const int delayBetweenHIDReports = 5; // Additional delay in milliseconds between HID reports
const int debounceDelay = 10;        // Delay in milliseconds between button press

int previousButton1State = HIGH;
int previousButton2State = HIGH;
int previousButton3State = HIGH;
int previousButton4State = HIGH;

TaskHandle_t Task1;

int R1 = 6800;
int R2 = 2000;
float Vin = 3.7;
float divisor;

void setup() {
      
  Serial.begin(115200);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(L_Up, INPUT_PULLUP);
  pinMode(L_Down, INPUT_PULLUP);
  pinMode(R_Up, INPUT_PULLUP);
  pinMode(R_Down, INPUT_PULLUP);
  pinMode(R_Right, INPUT_PULLUP);
  pinMode(R_Left, INPUT_PULLUP);
  pinMode(LT, INPUT_PULLUP);
  pinMode(RT, INPUT_PULLUP);
  pinMode(LS, INPUT_PULLUP);
  pinMode(RS, INPUT_PULLUP);
  pinMode(L_Right, INPUT);
  pinMode(L_Left, INPUT);
  
  bleGamepad.begin();
  xTaskCreatePinnedToCore(
      Task1code, /* Funcion de la tarea1 */
      "Task1", /* Nombre de la tarea */
      10000,  /* Tamaño de la pila */
      NULL,  /* Task input parameter */
      1,  /* Prioridad de la tarea */
      &Task1,  /* objeto TaskHandle_t. */
      0); /* Nucleo donde se correra */
     
  ledAction(0);
  divisor = 0.91;//((Vin*R2)/(R1+R2))-0.01;
  Serial.println(divisor);
  Serial.println("Starting BLE work!");

}

void loop() {
  if (bleGamepad.isConnected()) {
    stateConnection = 1;

/**********************D PAD RIGTH********************************/
    int currentButton1State = digitalRead(R_Up); //Triangulo B1
    int currentButton2State = digitalRead(R_Left); //Circulo B2
    int currentButton3State = digitalRead(R_Down); //X B3
    int currentButton4State = digitalRead(R_Right);//cuadrado B4
    
    if (currentButton1State != previousButton1State) {
      if (currentButton1State == LOW)
        bleGamepad.press(BUTTON_1);
      else
        bleGamepad.release(BUTTON_1);
    }
    previousButton1State = currentButton1State;

    if (currentButton2State != previousButton2State) {
      if (currentButton2State == LOW)
        bleGamepad.press(BUTTON_2);
      else
        bleGamepad.release(BUTTON_2);
    }
    previousButton2State = currentButton2State;

    if (currentButton3State != previousButton3State) {
      if (currentButton3State == LOW)
        bleGamepad.press(BUTTON_3);
      else
        bleGamepad.release(BUTTON_3);
    }
    previousButton3State = currentButton3State;

    if (currentButton4State != previousButton4State) {
      if (currentButton4State == LOW)
        bleGamepad.press(BUTTON_4);
      else
        bleGamepad.release(BUTTON_4);
    }
    previousButton4State = currentButton4State;
/**********************Gatillos********************************/
    if (digitalRead(LT) == LOW) { //L1 B5
      Serial.println("L1");
      bleGamepad.press(BUTTON_5);
      delay(debounceDelay);
      bleGamepad.release(BUTTON_5);
    }
    
    if (digitalRead(RT) == LOW) { //R1 B6
      Serial.println("R1");
      bleGamepad.press(BUTTON_6);
      delay(debounceDelay);
      bleGamepad.release(BUTTON_6);
    }
    
    touchValueL2 = touchRead(LT2); //L2 B7
    if(touchValueL2 > 1 && touchValueL2 < threshold){
      int touchValuesLT2[numberOfPotSamples];
      for (int i = 0 ; i < numberOfPotSamples ; i++) {
        touchValuesLT2[i] = touchRead(LT2);
        delay(delayBetweenSamples);
      }
      int touchValueLT2 = 0;
      for (int i = 0 ; i < numberOfPotSamples ; i++) {
        touchValueLT2 += touchValuesLT2[i];
      }
      touchValueLT2 = touchValueLT2 / numberOfPotSamples;
      
      if(touchValueLT2 > 3 && touchValueLT2 < 10){
        Serial.print("LT2: ");
        Serial.println(touchValueR2);
        bleGamepad.press(BUTTON_7);
        delay(debounceDelay);
        bleGamepad.release(BUTTON_7);
      }
    }
    
    touchValueR2 = touchRead(RT2); //R2 B8
    if(touchValueR2 > 1 && touchValueR2 < threshold){
      int touchValuesRT2[numberOfPotSamples];
      for (int i = 0 ; i < numberOfPotSamples ; i++) {
        touchValuesRT2[i] = touchRead(RT2);
        delay(delayBetweenSamples);
      }
      int touchValueRT2 = 0;
      for (int i = 0 ; i < numberOfPotSamples ; i++) {
        touchValueRT2 += touchValuesRT2[i];
      }
      touchValueRT2 = touchValueRT2 / numberOfPotSamples;
      
      if(touchValueRT2 > 3 && touchValueRT2 < 10){
        Serial.print("RT2: ");
        Serial.println(touchValueR2);
        bleGamepad.press(BUTTON_8);
        delay(debounceDelay);
        bleGamepad.release(BUTTON_8);
      }
    }
/*****************************************************/
    touchValueT2 = touchRead(Touch2); //B10 start
    if(touchValueT2 > 1 && touchValueT2 < threshold){
      int touchValuesT2[numberOfPotSamples];
      for (int i = 0 ; i < numberOfPotSamples ; i++) {
        touchValuesT2[i] = touchRead(Touch2);
        delay(delayBetweenSamples);
      }
      int touchValueT2 = 0;
      for (int i = 0 ; i < numberOfPotSamples ; i++) {
        touchValueT2 += touchValuesT2[i];
      }
      touchValueT2 = touchValueT2 / numberOfPotSamples;
      
      if(touchValueT2 > 3 && touchValueT2 < 10){
        Serial.print("Touch2: ");
        Serial.println(touchValueT2);
        bleGamepad.press(BUTTON_10);
        delay(debounceDelay);
        bleGamepad.release(BUTTON_10);
      }
    }

/**********************Joystick********************************/
    if (digitalRead(LS) == LOW) {
      Serial.println("Left Joystick");
      bleGamepad.press(BUTTON_11);
      delay(debounceDelay);
      bleGamepad.release(BUTTON_11);
    }
    if (digitalRead(RS) == LOW) {
      Serial.println("Right Joystick");
      bleGamepad.press(BUTTON_12);
      delay(debounceDelay);
      bleGamepad.release(BUTTON_12);
    }

    //---------------------Left--------------------------
    int potValues[numberOfPotSamples];
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValues[i] = analogRead(LH);
      delay(delayBetweenSamples);
    }
    int potValue = 0;
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValue += potValues[i];
    }
    potValue = potValue / numberOfPotSamples;
    if(potValue > 1780 && potValue < 1830) potValue = 2047;
    int adjustedValue = map(potValue, 0, 4095, 32737, -32737);

    //--------------------------------------------------
    int potValues2[numberOfPotSamples];
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValues2[i] = analogRead(LV);
      delay(delayBetweenSamples);
    }
    int potValue2 = 0;
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValue2 += potValues2[i];
    }
    potValue2 = potValue2 / numberOfPotSamples;
    if(potValue2 > 1730 && potValue2 < 1770) potValue2 = 2047;
    int adjustedValue2 = map(potValue2, 0, 4095, 32737, -32737);

    //----------------------------Rigth-----------------
    int potValues3[numberOfPotSamples];
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValues3[i] = analogRead(RH);
      delay(delayBetweenSamples);
    }
    int potValue3 = 0;
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValue3 += potValues3[i];
    }
    potValue3 = potValue3 / numberOfPotSamples;
    if(potValue3 > 1760 && potValue3 < 1790) potValue3 = 2047;
    int adjustedValue3 = map(potValue3, 0, 4095, 32737, -32737);

    //--------------------------------------------------
    int potValues4[numberOfPotSamples];
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValues4[i] = analogRead(RV);
      delay(delayBetweenSamples);
    }
    int potValue4 = 0;
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValue4 += potValues4[i];
    }
    potValue4 = potValue4 / numberOfPotSamples;
    if(potValue4 > 1710 && potValue4 < 1790) potValue4 = 2047;
    int adjustedValue4 = map(potValue4, 0, 4095, 32737, -32737);

    bleGamepad.setAxes(adjustedValue, adjustedValue2,  adjustedValue3, adjustedValue4, 0, 0,DPAD_CENTERED);
    delay(delayBetweenHIDReports);
/**********************D PAD Left********************************/
    if (digitalRead(L_Up) == LOW){
      bleGamepad.setAxes(adjustedValue, adjustedValue2,  adjustedValue3, adjustedValue4, 0, 0, DPAD_UP);
    }
    if (digitalRead(L_Left) == LOW){
      bleGamepad.setAxes(adjustedValue, adjustedValue2,  adjustedValue3, adjustedValue4, 0, 0, DPAD_LEFT);
    }
    if (digitalRead(L_Down) == LOW){
      bleGamepad.setAxes(adjustedValue, adjustedValue2,  adjustedValue3, adjustedValue4, 0, 0, DPAD_DOWN);
    }
    if (digitalRead(L_Right) == LOW){
      bleGamepad.setAxes(adjustedValue, adjustedValue2,  adjustedValue3, adjustedValue4, 0, 0, DPAD_RIGHT);
    }
  }else stateConnection = 0;
}

void batteryLevel() {
  int sensorValue = analogRead(ADC);
  //Serial.println(sensorValue);
  float voltage = sensorValue * (3.3 / 4095.0);
  Serial.print(voltage);
  Serial.print("V ||");
  int porcentaje = (voltage / divisor) * 100;
  Serial.print(porcentaje);
  Serial.println("%");
  bleGamepad.setBatteryLevel(porcentaje);
  if (porcentaje < 60) {
    stateBattery = true;
  }else stateBattery = false;
}


void ledAction(int estado){
  switch(estado){
    case 0: //encendido
      for(int i = 0; i<6;i++){
        digitalWrite(Led1, stateLed);
        digitalWrite(Led2, stateLed);
        stateLed =! stateLed;
        delay(500);
      }
    break;
    case 1://en juego
      stateLed =! stateLed;
      digitalWrite(Led1, stateLed);
      digitalWrite(Led2, !stateLed);
      delay(500);
    break;
    case 2://bateria baja
      for (int i = 0; i<8; i++){
        digitalWrite(Led1, stateLed);
        digitalWrite(Led2, stateLed);
        stateLed =! stateLed;
        delay(200);
      } 
      delay(1000);
    break; 
    case 3:
      digitalWrite(Led1, stateLed);
      digitalWrite(Led2, stateLed);
      stateLed =! stateLed;
      delay(200);
    break; 
  }
}

void Task1code( void * parameter) {
  for(;;){
    while(stateConnection){
      while (millis() > time_now + period) {
        Serial.println("Verificando Nivel Bateria");
        batteryLevel();
        time_now = millis();
      }
      if(!stateBattery) ledAction(1);
      else ledAction(2);
    }
    if(!stateConnection) ledAction(3);
    delay(100);
  }
  vTaskDelay(10);
}
