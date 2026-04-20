#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// GPS module connected to pins 4 (RX) and 3 (TX)
SoftwareSerial gpsSerial(4, 3);
TinyGPSPlus gps;

// GSM module connected to pins 7 (RX) and 8 (TX)
SoftwareSerial gsmSerial(7, 8);

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);

  // Initialize GSM module
  gsmSerial.println("AT"); // Check GSM
  delay(1000);
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode
  delay(1000);
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated()) {
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();

      // Example accident trigger (replace with sensor logic)
      bool accidentDetected = true; 

      if (accidentDetected) {
        sendAlert(latitude, longitude);
        delay(10000); // Prevent spamming
      }
    }
  }
}

void sendAlert(double lat, double lng) {
  gsmSerial.println("AT+CMGS=\"+911234567890\""); // Replace with emergency contact
  delay(1000);
  gsmSerial.print("Accident detected! Location: ");
  gsmSerial.print("Lat: ");
  gsmSerial.print(lat, 6);
  gsmSerial.print(", Lng: ");
  gsmSerial.print(lng, 6);
  gsmSerial.write(26); // End SMS with Ctrl+Z
}

