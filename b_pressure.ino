#include <Wire.h>
#include "MS5837.h"
#include <Ethernet.h>
#include <PubSubClient.h>

MS5837 sensor;

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};

EthernetClient ethClient;

PubSubClient mqttClient(ethClient);

const char *server = "192.168.0.109";

const int port = 1883;

void setup() {

  Serial.begin(9600);

  Serial.println("Starting");

  Wire.begin();

  // Initialize pressure sensor
  // Returns true if initialization was successful
  // We can't continue with the rest of the program unless we can initialize the sensor
  while (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }

  // .init sets the sensor model for us but we can override it if required.
  // Uncomment the next line to force the sensor model to the MS5837_30BA.
  //sensor.setModel(MS5837::MS5837_30BA);

  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
}

void loop() {
  // Update pressure and temperature readings
  sensor.read();



/** Pressure returned in mbar or mbar*conversion rate.
 */
  Serial.print("Pressure: ");
  Serial.print(sensor.pressure());
  Serial.println(" mbar");


/** Depth returned in meters (valid for operation in incompressible
 *  liquids only. Uses density that is set for fresh or seawater.
 */

  Serial.print("Depth: ");         
  Serial.print(sensor.depth());
  Serial.println(" m");


  delay(1000);
}
