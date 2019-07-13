/* Inspirado en El Profe Garcia
  
 
 Conexion del Modulo Bluetooth HC-06 y el Arduino
 ARDUINO    Bluetooth HC-06 
 2 (RX)       TX
 3 (TX)       RX
 5V           VCC
 GND          GND
 
 
 

 */

#include <Servo.h>                // Incluye la libreria Servo                  
#include <SoftwareSerial.h> // Al incluir esta liobrería podemos usar el HC-06 con otros pines que no son el 0 y el 1

SoftwareSerial BT1(2,3); // Crea el objeto BT1. Pines 2 y 3 para RX, TX recordar que se cruzan
Servo servo1;   // Crea el objeto servo1 con las caracteristicas de Servo
Servo servo2;   // Crea el objeto servo2 con las caracteristicas de Servo
int izqA = 13;  
int derA = 12;  
int vel = 255;            // Velocidad de los motores (0-255)
int estado=9;         // inicia detenido

int tx = 2;            // define el pin 2 como tx del HC-06
int rx = 3;            // define el pin 3 como rx del HC-06
int duracion, distancia;  // para Calcular distacia
char dato='o';
int angServo1=90;
int angServo2=90;

void setup()  { 
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  Serial.println("Enter AT commands:");
  BT1.begin(9600);
  pinMode(derA, OUTPUT);
  pinMode(izqA, OUTPUT);
  
  servo1.attach(6,660,1400);    // Asocia el servo1 al pin 11, define el min y max del ancho del pulso  
  servo2.attach(9,660,1400);                              // eso depende del fabricante del servo
} 

void loop()  { 
  int t1=50;
  int t2=20;
  int angulo=1;
  //dato='h';

  if (BT1.available())
    {  
     dato = BT1.read();  //Lee cada carácter uno por uno y se almacena en una variable
     Serial.println(dato);  //Imprimimos en la consola el carácter recibido
    }
  if (dato=='h'){
     digitalWrite(derA, LOW);//Así se para el motor de cc, o con cualquier dato!= de 'a' o 'b'     
     digitalWrite(izqA, LOW);   
    }        
  if (dato=='o'){     //Podríamos decir que los servos van al punto Home de referencia
    servo1.write(90);
    servo2.write(90);
    delay(t2);
    }
  
  if(dato=='a'){              // 1ª Articulación Base o Peana, se mueve en un sentido es la flecha B_1ªArt_Izq de la app Brazorobotbluetooth.
    digitalWrite(derA, HIGH); // Se mueve el motor de cc gracias al LM289
    digitalWrite(izqA, LOW);       
    delay(t1);
    }
  if(dato=='b'){                 // 1ª Articulación Base o Peana, se mueve en el otro sentido es la flecha B_1ªArt_Dcha de la app Brazorobotbluetooth. 
    digitalWrite(derA, LOW);     // Se mueve el motor de cc gracias al LM289
    digitalWrite(izqA, HIGH);      
    delay(t1);
    }
  if(dato=='c'){
     angServo1=angServo1+angulo; 
     servo1.write(angServo1); // 2ª Articulación Hombro, el servo1 se mueve en un sentido, es la flecha B_2ªArt_Izq de la app Brazorobotbluetooth.
     delay(t2);          
     }
  if(dato=='d'){ 
    angServo1=angServo1-angulo; 
    servo1.write(angServo1); // 2ª Articulación Hombro, el servo1 se mueve en el otro sentido, es la flecha B_2ªArt_Dcha de la app Brazorobotbluetooth.
     delay(t2);          
     } 
if(dato=='e'){
     angServo2=angServo2+angulo; 
     servo2.write(angServo2); // 3ª Articulación Codo, el servo2 se mueve en un sentido, es la flecha B_3ªArt_Izq de la app Brazorobotbluetooth.
     delay(t2);          
      }
  if(dato=='f'){ 
    angServo2=angServo2-angulo; 
    servo2.write(angServo2); // 3ª Articulación Codo, el servo2 se mueve en el otro sentido, es la flecha B_3ªArt_Dcha de la app Brazorobotbluetooth.
     delay(t2);          
   }
  
}
