
uint16_t sampleRate = 124;  //(in Hz) enter Value b/w 123 and 1025
int rawSignal;              //variable to hold BioAmp adc value
bool b;                     //SAMPLE OR NOT FLAG
int c = 0;                  //just for counting no. of samples

ISR(TIMER1_OVF_vect){
    b = true;
    c++;
   }

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  cli();                       //DISABLE INTERRUPTS
  
//------------------TIMER 1 CONFIG-----------------------//
  TCCR1A = 0b00000011;         //FAST PWM MODE 
  TCCR1B = 0b00011101;         //FAST PWM, PRESCALER OF 1024
  TIMSK1 = 0b00000001;         //OVERFLOW INTERRUPT ENABLE
  TIFR1  = 0b00000001;         //CLEAR OVERFLOW FLAG
  TCNT1  = 0;                  //rst t1
  OCR1A  = ((15625/sampleRate)+1); //SET FREQ OF T1
//------------------------------------------------------//  

  SMCR = bit(SE);              //ENABLE SLEEP MODE
  sei();                       //ENABLE INTURRUPTS
  __asm__("sleep \n");         //SLEEP MODE
  b = false;                   

}

void loop() {
  rawSignal = analogRead(A0);
  //SAMPLE THE SIGNAL
  if (b == true){
    Serial.print(c);
    Serial.print(" - ");
    Serial.println(rawSignal);
    b = false;
  }
}
