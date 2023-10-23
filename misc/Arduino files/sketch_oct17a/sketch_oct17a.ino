#include<Math.h>
#include<Servo.h>
//#include<RTClib.h>
//RTCDS3231 rtc;
Servo azimuthServo;
Servo elevationServo;
//const azimuthPin = 9;
//const elevationPin = 10;

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
  int dayOfYear = 291; //october 18th
  float solarDeclination;

  solarDeclination = 23.45 * sin((360.0 / 365.0) * (dayOfYear - 81) * (M_PI / 180));
  float hourAngle = 15 * (hour - 12) + (minute / 4.0);
  float azimuthAngle = atan2(sin(hourAngle * (M_PI / 180)),
                             -cos(latitude * (M_PI / 180)) * tan(solarDeclination * (M_PI / 180)) +
                             sin(latitude * (M_PI / 180)) * cos(hourAngle * (M_PI / 180)));

  azimuthAngle = azimuthAngle * (180 / M_PI);  // Convert from radians to degrees
  azimuthAngle = fmod(azimuthAngle + 360, 360);  // Ensure the angle is between 0 and 360 degrees

  return azimuthAngle;
}

float calculateElevationAngle(float solarZenithAngle) {
  return 90.0 - solarZenithAngle;
}

float mapServo() {

}
void loop() {
  float observerLatitude = 16.4419;
  float observerLongitude = 80.6226;
  // Assuming the current time is 2:30 PM (14:30)
  int currentHour = 16;
  int currentMinute = 30;
  float azimuthAngle = calculateAzimuthAngle(observerLatitude, currentHour, currentMinute);
  int azimuthServoPosition = map(azimuthAngle, 0, 360, 0, 180);

  azimuthServo.write(azimuthServoPosition);

  float solarZenithAngle = 90.0 - azimuthAngle;
  Serial.println(azimuthServoPosition);

  float elevationAngle = calculateElevationAngle(solarZenithAngle);

  int elevationServoPosition = map(elevationAngle, 0, 90, 0, 180);

  elevationServo.write(elevationServoPosition);
}
