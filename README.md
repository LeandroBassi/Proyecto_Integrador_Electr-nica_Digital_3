# Proyecto_Integrador_Electronica_Digital_3

# Nombre del Proyecto: SENSOR DE ESTACIONAMIENTO

## Descripción:
El proyecto consiste en el desarrollo de un sistema de asistencia al estacionamiento basado en el microcontrolador LPC1769. Mediante una combinación de dos sensores de distancia se mide en tiempo real la proximidad entre el vehículo y un obstáculo: un sensor ultrasónico HC-SR04 para distancias largas (80 cm a 400 cm) y un sensor infrarrojo Sharp GP2Y0A21YK0F para distancias cortas (10 cm a 80 cm). La información de ambos sensores es procesada por el microcontrolador para brindar retroalimentación visual, sonora y digital al usuario mediante tres rangos.

El sistema cuenta con tres LEDs indicadores (verde, amarillo y rojo) que se activan progresivamente a medida que el vehículo se aproxima al obstáculo. Simultáneamente, un buzzer pasivo de alta potencia emite señales sonoras cuya frecuencia aumenta proporcionalmente a la reducción de la distancia, alertando al conductor de forma intuitiva, con la posibilidad de silenciar mediante un pulsador. Con el fin de proteger al microcontrolador y manejar la corriente necesaria para el buzzer, se utilizará un optoacoplador como etapa de aislamiento y un transistor como etapa de potencia. 

Adicionalmente, la distancia medida es transmitida en tiempo real a una PC mediante comunicación UART, permitiendo su monitoreo desde una terminal serie. Por último,  el teclado nos permitirá sobreescribir el valor umbral de activación del buzzer o silenciar la alarma.

## Integrantes:
- BASSI Leandro Dante
- PEREZ CADIBONI Lautaro Ezequiel
- BASTIDA Lucas Ramiro

## Profesor:
- Ing. Migliore Emiliano
  
## Hardware utilizado
- Placa de desarrollo LPC1769
- Sensor Sharp GP2Y0A21YK0F
- Sensor HC-SR04
- Buzzer piezoelectrico Activo 12V
- Optoacoplador DC (PC817)
- MOSFET IRLZ44N
- 1 pulsador
- 3 LEDs (Verde / Amarrilo / Rojo)
- 4 displays 7 segmentos
- 4 transistores NPN
- Resistencias
- CP2102

## Requisitos
- MCUXpresso IDE
- Driver LPC1769

## Estado del proyecto
En desarrollo

## Materia
Electrónica Digital 3 - Año 2026
