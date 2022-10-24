

void updateCapacitive(int pin, int &statusSensor) {
  statusSensor = digitalRead(pin);
  if (statusSensor) {
    // Serial.println("Vino el agua :) !");
  }
  else {
    // Serial.println("No ha venido el agua :( !");
  }

  delay(1000);
}
