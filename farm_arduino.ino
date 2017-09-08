#define smPin A0
#define lumPin A2
#define tempPin A4
#define light 13
int soil_moisture_level=0;
int light_threshold=700;
int luminosity=0;
float temperature=0;

void setup() {
  Serial.begin(115200);
  pinMode(light,OUTPUT);
  digitalWrite(light,LOW);
}

void soil_moisture_send()
{
  soil_moisture_level=analogRead(smPin);
  Serial.print("s");
  Serial.print("\t");
  Serial.print(soil_moisture_level);  
  Serial.print("\n");
}

void luminosity_check()
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

void temperature_send()
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
  delay(1000);
}
