#define LED_VERDE_1 2
#define LED_VERDE_2 5 
#define LED_VERDE_3 7
#define LED_BIANCO 9
#define LED_ROSSO 8
#define POTENTIOMETER A0
#define BUTTON_START 12
#define BUTTON_DOWN 13

int livello = 0;

bool gameStart;
int currentBlinkDirection;

void setup() {
  // pin setup:
  pinMode(LED_VERDE_1,OUTPUT);
  pinMode(LED_VERDE_2,OUTPUT);
  pinMode(LED_VERDE_3,OUTPUT);
  pinMode(LED_ROSSO,OUTPUT);
  pinMode(LED_BIANCO,OUTPUT);
  pinMode(POTENTIOMETER,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_DOWN,INPUT);

  // New Game phase setup:
  gameStart = true;
  currentBlinkDirection = 0;
  
  Serial.begin(9600);
  Serial.println("Welcome to Led to Bag. Press Key TS to Start\n");
}

void loop() {
  // NEW GAME PHASE //
  if(gameStart){
   blink();
  }
  
  /*
   * Leggo il potenziometro e scelgo il livello
   */
  livello=scegli_livello(analogRead(POTENTIOMETER));

  
}

void blink(){
  if(currentBlinkDirection==0){
    digitalWrite(LED_VERDE_1, HIGH);
    delay(0);
    digitalWrite(LED_VERDE_1, LOW);
    delay(0);
    digitalWrite(LED_VERDE_2, HIGH);
    delay(0);
    digitalWrite(LED_VERDE_2, LOW);
    delay(0);
    digitalWrite(LED_VERDE_3, HIGH);
    delay(0);
    digitalWrite(LED_VERDE_3, LOW);
    delay(0);
    currentBlinkDirection = 1;
  } else if(currentBlinkDirection==1){
    digitalWrite(LED_VERDE_3, HIGH);
    delay(0);
    digitalWrite(LED_VERDE_3, LOW);
    delay(0);
    digitalWrite(LED_VERDE_2, HIGH);
    delay(0);
    digitalWrite(LED_VERDE_2, LOW);
    delay(0);
    digitalWrite(LED_VERDE_1, HIGH);
    delay(0);
    digitalWrite(LED_VERDE_1, LOW);
    delay(0);
    currentBlinkDirection = 0;   
  }
}

int scegli_livello(int valore){
  return valore/128;
}
