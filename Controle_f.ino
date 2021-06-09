const int PWMA = 10;
const int PWMB = 11;

const int pin_chR = A5;

int leitura;       //R-"Roda"; P-"Pistola"
float PWM;

const float chRmax=1960, chRmed=1550, chRmin=1105;     //Coletar em teste val. "Roda"     - ATUALIZADOS
//const int chPmax=1975, chPmed=1560, chPmin=1120;     //Coletar em teste val. "Pist."

void setup() {
    pinMode(pin_chR, INPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
   // Serial.begin(9600);
    while(pulseIn(pin_chR, HIGH)==0);
      delay(1);    
   //   Serial.begin(9600);
}

void loop() {
//------------- Lê os canais
  
  leitura=pulseIn(pin_chR, HIGH);

//------------- Executa saidas para as acoes

    if(leitura>chRmed){       //  =>>
      PWM=250.0*((leitura-chRmed)/(chRmax-chRmed));
      
      analogWrite(PWMA, 127+PWM/2);
      analogWrite(PWMB, 127-PWM/2); 
    }
    else{                     //    <<=
      PWM=250.0*((leitura-chRmed)/(chRmin-chRmed));
      
      analogWrite(PWMA, 127-PWM/2);
      analogWrite(PWMB, 127+PWM/2); 
    }

}
