#include<Math.h>
#include<Servo.h>
//#include<RTClib.h>
//RTCDS3231 rtc;


Servo azimuthServo;
Servo elevationServo;
//const azimuthPin = 9;
//const elevationPin = 10;
float EoT = 14.47;
float IST = 82.5;
float observerLongitude = 80.4585;
int dayOfYear = 320; //november 20th

String actualAzimuth;
String actualElevation;
String actualVoltage;
int counter = 1;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //  if(!rtc.begin()){
  //    Serial.write("rtc dint start properly");
  //  }
  azimuthServo.attach(9);
  elevationServo.attach(10);
  
}

float calculateAzimuthAngle(float latitude, int hour, int minute) {
  float solarDeclination;
  float LocalSolarTime = 12 + (4*(IST- observerLongitude)+EoT/60);
  solarDeclination = 23.45 * sin((360.0 / 365.0) * (dayOfYear - 81) * (M_PI / 180));
  float hourAngle = 15 * (LocalSolarTime - 12);
  float azimuthAngle = atan2(sin(hourAngle * (M_PI / 180)),
                             -cos(latitude * (M_PI / 180)) * tan(solarDeclination * (M_PI / 180)) +
                             sin(latitude * (M_PI / 180)) * cos(hourAngle * (M_PI / 180)));

  azimuthAngle = azimuthAngle * (180 / M_PI);  // Convert from radians to degrees
  azimuthAngle = fmod(azimuthAngle + 360, 360);  // Ensure the angle is between 0 and 360 degrees

  return azimuthAngle;
}

float calculateElevationAngle(float latitude) {
  float solarDeclination;
  float LocalSolarTime = 12 + (4*(IST- observerLongitude)+EoT/60);
  float hourAngle = 15 * (LocalSolarTime - 12);
  solarDeclination = 23.45 * sin((360.0 / 365.0) * (dayOfYear - 81) * (M_PI / 180));
  float incidenceAngle = acos(sin(solarDeclination)*sin(latitude) +(cos(solarDeclination)*cos(latitude)*cos(hourAngle)));
  return 90- incidenceAngle;
}

float mapServo() {

}
void delayFunction(int seconds){
  for(int i=1; i<=seconds; i++){
    delay(1000);

  }
}
void loop() {
  if(counter == 1){
      azimuthServo.write(0);
      elevationServo.write(0);
   }
   counter++;
  float observerLatitude = 16.4419;
  // As 
  
  float azimuthAngle = calculateAzimuthAngle(observerLatitude, currentHour, currentMinute);
  actualAzimuth = (String)azimuthAngle;
  //write next 2 for elevation and voltage
  int azimuthServoPosition = map(azimuthAngle, 0, 360, 0, 180);
  int sensorValue = analogRead(A0); // Solar Panel Positive PIN connect to A0  
  float voltage = sensorValue * (5.0 / 1023.0);
  azimuthServo.write(azimuthAngle);
  
  float solarZenithAngle = 90.0 - azimuthAngle;
  //Serial.println(azimuthServoPosition);

  float elevationAngle = calculateElevationAngle(solarZenithAngle);
  
  int elevationServoPosition = map(elevationAngle, 0, 90, 0, 180);
  actualElevation = (String)elevationAngle;
  actualVoltage = (String)voltage;
  elevationServo.write(elevationServoPosition);
  String combinedString = actualAzimuth +" "+actualElevation +" "+voltage;
  Serial.println(combinedString);
  delayFunction(60);
}
