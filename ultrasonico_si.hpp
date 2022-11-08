#include <NewPing.h> // Librería necesaria para trabajar con el sensor ultrasónico impermeable JSN-SR04T.


void updateUltrasonic()
{

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(pUltraSonicTriger, HIGH);
  delayMicroseconds(500);          //Enviamos un pulso de 500us
  digitalWrite(pUltraSonicTriger, LOW);
  
  t = pulseIn(pUltraSonicEcho, HIGH); //obtenemos el ancho del pulso
  d = t/59;             //escalamos el tiempo a una distancia en cm
  
  // Serial.print("Distancia: ");
  // Serial.print(d);      //Enviamos serialmente el valor de la distancia
  // Serial.print("cm");
  sUltrasonic= d;
   Serial.println(t);
  delay(800);          //Hacemos una pausa de 800ms
}
