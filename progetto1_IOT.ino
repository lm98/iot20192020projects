#define LED_VERDE_1 2
#define LED_VERDE_2 5 
#define LED_VERDE_3 7
#define LED_BIANCO 9
#define LED_ROSSO 8
#define POTENTIOMETER A0
#define BUTTON_START 12
#define BUTTON_DOWN 13

int livello = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_VERDE_1,OUTPUT);
  pinMode(LED_VERDE_2,OUTPUT);
  pinMode(LED_VERDE_3,OUTPUT);
  pinMode(LED_ROSSO,OUTPUT);
  pinMode(LED_BIANCO,OUTPUT);
  pinMode(POTENTIOMETER,INPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_DOWN,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  /*
   * Leggo il potenziometro e scelgo il livello
   */
  livello=scegli_livello(analogRead(POTENTIOMETER));

  
}

int scegli_livello(int valore){
  return valore/128;
}
