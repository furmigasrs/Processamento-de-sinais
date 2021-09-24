
//Biblioteca timer1
#include <TimerOne.h>

//periodo amostragem
#define period 131
//Configuração clock ADC
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

int i=0,t=0,x=0;
bool flag=false,mostrar=false;
long int amostras1[128];
void setup() 
{
  Serial.begin(9600);
  ADCSRA &= ~PS_128;  //limpa configuração da biblioteca do arduino
  ADCSRA |= PS_128;
  ADCSRA|=(1<<ADEN)|(1<<ADSC)|(1<<ADIE);//liga interrupção ADC, liga ADC e inicia conversao.
  ADCSRB=0x00; 
  Timer1.initialize(period);;
  Timer1.attachInterrupt(amostrar_adc);
  amostras1[0]=analogRead(A0);
 //Serial.print("valor inicial:");
  //Serial.println(amostras1[0]);
  delay(100);
  sei();//ativa interrupção global
  delay(100);
}

void amostrar_adc()
{
 //do nothing
 if(flag){
  t+=1;
  if(t<128)
  amostras1[t]=analogRead(A0);

 }
}
void loop()
{
   // put your main code here, to run repeatedly:
  if(Serial.read()=='s'&&!flag)
  {
   //Serial.println("start");
  while(amostras1[0]<320||amostras1[0]>330)
   {
     amostras1[0]=analogRead(A0);
    }
       flag=true; 
    //Serial.print("Flag:");   
    //Serial.println(flag);       
    delay(250);
    //Serial.println("Enviando...");
    for(i=0;i<128;i++)
    {
            Serial.println(amostras1[i]);
     }
  }
}

//interrupção ADC
ISR(ADC_vect)
{

}
