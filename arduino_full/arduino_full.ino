#include <OneWire.h> 
#include <DallasTemperature.h>

// Temp
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// pH
#define SensorPin A1
#define Offset 0.00
unsigned long int avgValue;
float phhvalue;

void setup(void) {
  Serial.begin(9600);
  sensors.begin();
} 
void loop(void) {

  // Temperature sensor
  sensors.requestTemperatures();
  Serial.print("Temperature:-   ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println("");

  // Turbidity sensor
  int sensorValue = analogRead(A0); // read the input on analog pin 0:
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float turbidityV = (5.0-voltage)*20;
  Serial.print("Turbidity:-  ");
  Serial.print(turbidityV);
  Serial.println("");

  // pH sensor
  int buf[10];                //buffer for read analog
  for(int i=0;i<10;i++) {       //Get 10 sample value from the sensor for smooth the value
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        int temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue+Offset;                      //convert the millivolt into pH value
  Serial.print("pH:-   ");
  Serial.print(phValue,1);
  Serial.println("");

//  
//  Serial.println("");
  delay(5000);
}

