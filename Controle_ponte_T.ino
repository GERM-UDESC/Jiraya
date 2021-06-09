const int PWMA = 11;
const int PWMB = 5;
const int STBY = 6;

const int pin_chR = A5;
const int pin_chP = A4;

int chR, chP;       //R-"Roda"; P-"Pistola"
int PWM_A, PWM_B;
int MRS=110;       //Max rotate speed
int MFS=250;
float max_speed;
float ang;
float rval;
int action=2;        //0->não roda no eixo; 1->roda no eixo; 2->parado

const int chRmax=1970, chRmed=1560, chRmin=1155;     //Coletar em teste val. "Roda"
const int chPmax=1975, chPmed=1560, chPmin=1120;     //Coletar em teste val. "Pist."
const int folga=60;


void setup() {
    pinMode(pin_chR, INPUT);
    pinMode(pin_chP, INPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(STBY, OUTPUT);
    digitalWrite(STBY, HIGH);
    //Serial.begin(9600);
    while(pulseIn(pin_chR, HIGH)==0);
      delay(1);    
}

void loop() {
//------------- Lê os canais
  //chR=analogRead(pin_chR);
  //chP=analogRead(pin_chP);
  
  chR=pulseIn(pin_chR, HIGH);
  chP=pulseIn(pin_chP, HIGH);
  //Serial.println(chR);

//------------- Escolhe acao

  if((chP<chPmed+folga)&&(chP>chPmed-folga)){
      if((chR<chRmed+folga)&&(chR>chRmed-folga))
         action=1;     //PARAR
      else  
         action=0;     //ANDAR

   if(chR<100||chP<100)
         action=1;     //FAIL-SAFE

  }
//------------- Calcula PWM's para a acao
    
  if(action==0){          //andar
    if(chP>chPmed+folga)
      max_speed=1.0*(chP-chPmed-folga)/(chPmax-chPmed-folga);
    if(chP<chPmed-folga)
      max_speed=0;
//***** Aqui realizar operacao com a velocidade frente-tras, de forma a nao ser linear.

    if(chR>chRmed){
      ang=(1.0*(chR-chRmed))/(chRmax-chRmed);
      PWM_A=1.0*(1-ang)*max_speed*MFS;
      PWM_B=1.0*max_speed*MFS;
    }
    if(chR<chRmed){
      ang=(1.0*(chR-chRmed))/(chRmin-chRmed);
      PWM_A=1.0*max_speed*MFS;
      PWM_B=1.0*(1-ang)*max_speed*MFS;
    }
  }
  
  if(action==1){          //desligar os motores
      PWM_A=0;
      PWM_B=0;
  } 
//------------- Setar motores

    if(PWM_A>250)
      PWM_A=250;
    if(PWM_A<0)
      PWM_A=0;

    if(PWM_B>250)
      PWM_B=250;
    if(PWM_B<0)
      PWM_B=0;

  analogWrite(PWMA, PWM_A);
  analogWrite(PWMB, PWM_B);
  

//-------------  Debugger 

/*    Serial.print("PWMA: ");
    Serial.println(PWM_A);
    Serial.print("PWMB: ");
    Serial.println(PWM_B);
    Serial.print("acao: ");
    Serial.println(action);
    Serial.print("maxs: ");
    Serial.println(max_speed);
    Serial.println(ang);
    delay(500);
*/

}
