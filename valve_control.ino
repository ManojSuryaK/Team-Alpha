//trial code , implemeted as a part of remote_farm_controller.ino
 const int A = 8 ;
const int B = 9 ;

void setup()
{
pinMode(A,OUTPUT) ;
pinMode(B,OUTPUT) ;
}

void loop()
{
delay(3000) ;     
digitalWrite(A,HIGH) ;
digitalWrite(B,LOW) ;

 }
