#define smPin A0     //soil moisture input pin
#define lumPin A2    //ldr sensor input pin
#define tempPin A4   //temperature sensor input pin
#define light 13     //light output
int soil_moisture_level=0;
int light_threshold=700;
int luminosity=0;
float temperature=0;

void setup() {
  Serial.begin(115200);
  pinMode(light,OUTPUT);
  digitalWrite(light,LOW);
}

void soil_moisture_send()  //sending soil moisture data serially
{
  soil_moisture_level=analogRead(smPin);
  Serial.print("s");
  Serial.print("\t");
  Serial.print(soil_moisture_level);  
  Serial.print("\n");
}

void luminosity_check()  // checking ambient lighting conditions
{
  luminosity=analogRead(lumPin);
  if (luminosity>light_threshold){
    digitalWrite(light,HIGH);
  }
  else{
    digitalWrite(light,LOW);
  }
  Serial.print("l");
  Serial.print("\t");
  Serial.print(luminosity);
  Serial.print("\n");
}

void temperature_send()  //sending temperature of the environment serially
{
  temperature=(analogRead(tempPin)*500)/1023;
  Serial.print("t");
  Serial.print("\t");
  Serial.print(temperature);
  Serial.print("\n");
}
void loop() {
  soil_moisture_send();
  luminosity_check();
  temperature_send();
}
