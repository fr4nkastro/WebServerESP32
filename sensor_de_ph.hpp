#include <Arduino.h>
int samples = 10;
float adc_resolution = 1024.0;


float ph (float voltage) {
    return 7 + ((2.5 - voltage) / 0.18);
}

void updatePh()
{
    int measurings=0;

    for (int i = 0; i < samples; i++)
    {
        measurings += analogRead(pPh);
        delay(100);

    }

    float voltage = 5 / adc_resolution * measurings/samples;
    Serial.print("pH= ");
    sPh= ph(voltage);
    Serial.println(sPh);
    delay(100);
}
