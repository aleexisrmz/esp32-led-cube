#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

/* const char *ssid = "BUAP_Estudiantes";
const char *password = "f85ac21de4"; */

const char* ssid = "Totalplay-F3AA";
const char* password = "F3AAF735FutJQBFp";


WiFiClient espClient;
PubSubClient client(espClient);

const char *mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char *mqtt_user = "asdasd";
const char *mqtt_pass = "asdasd";

long lastMsg = 0;
char msg[50];
int value = 0;

int led[] = {16,17,18,20,36,39,42,38,35,34,27,25,24,22,21,41}; // <-- Salida de las columnas
int lvl[] = {12,13,14,15}; // <-- Salida de las filas
/* int led[] = {15,2,1,4,16,17,5,18,19,21,22,23,13,12,14,27}; // <-- Salida de las columnas */
/* int lvl[] = {26,25,33,32}; // <-- Salida de las filas */
int y; // <-- Variables para encender las filas


// FUNCIONES DE LAS FASES DEL CUBO

void LED(int h, int i, int j, int k, int l, int m, int n, int o, int p, int q, int r, int s, int t, int u, int v, int w)
{
digitalWrite(led[0], h);
digitalWrite(led[1], i);
digitalWrite(led[2], j);
digitalWrite(led[3], k);
digitalWrite(led[4], l);
digitalWrite(led[5], m);
digitalWrite(led[6], n);
digitalWrite(led[7], o);
digitalWrite(led[8], p);
digitalWrite(led[9], q);
digitalWrite(led[10], r);
digitalWrite(led[11], s);
digitalWrite(led[12], t);
digitalWrite(led[13], u);
digitalWrite(led[14], v);
digitalWrite(led[15], w);
}
 
void LVL(int h, int i, int j, int k)
{
digitalWrite(led[0], h);
digitalWrite(led[1], i);
digitalWrite(led[2], j);
digitalWrite(led[3], k);
}

void level()
{ // En esta función se establecen los valores para las filas donde con un 1 los leds no encienden y con 0 encienden
switch (y)
{
case 0:
LVL(0, 1, 1, 1);
break; // La primera fila encendida
case 1:
LVL(1, 0, 1, 1);
break; // La segunda fila encendida
case 2:
LVL(1, 1, 0, 1);
break; // La tercera fila encendida
case 3:
LVL(1, 1, 1, 0);
break; // La cuarta fila encendida
case 4:
LVL(0, 1, 1, 0);
break; // Las filas exteriores encendidas
case 5:
LVL(1, 0, 0, 1);
break; // Las filas interiores encendidas
case 6:
LVL(0, 0, 0, 0);
break; // Todas las filas encendidas
case 7:
LVL(0, 0, 0, 1);
break; // Todas excepto la última
case 8:
LVL(0, 0, 1, 1);
break; // Las primeras dos
case 9:
LVL(1, 1, 0, 0);
break; // Las últimas dos
}
}

// En esta animación prende led por led
void uxu()
{
int t = 100; // Esta variable determina el tiempo que espera el Arduino pararealizar la siguiente acción
for (int j = 0; j < 4; j++)
{ // Este for se utiliza para pasar de una fila a otra
y = j;
level();
LED(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
delay(t);
}
}

// En esta animación prende fila por placa
void pxp()
{
int t = 500; // Esta variable determina el tiempo que espera el Arduino para realizar la siguiente acción
for (int j = 0; j < 4; j++)
{ // Este for se utiliza para pasar de una fila a otra
y = j;
level();
LED(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
delay(t);
}
}

// En esta animación prende un cubo en el centro y después prende un cubo en el exterior
void cubito()
{
int t = 500; // Esta variable determina el tiempo que espera el Arduino para realizar la siguiente acción
int a = 50; // Esta variable determina las veces que se repetirá una secuencia para formar una imagen que no vibre
for (int x = 0; x < a; x++)
{ // este for se utiliza para crear una imagen que no vibre
y = 4;
level();
LED(1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1);
delay(5);
y = 5;
level();
LED(1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1);
delay(5);
}
y = 5;
level();
LED(0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0);
delay(t);
for (int x = 0; x < a; x++)
{
y = 4;
level();
LED(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
delay(5);
y = 5;
level();
LED(1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1);
delay(5);
}
y = 5;
level();
LED(0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0);
delay(t);
}

// En esta animación prende fila por fila hasta formar un cubo en el exterior
void cubote()
{ // Prende una fila a la vez para formar un cubo sin centro
int t = 500;
int a = 50;
y = 6;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
delay(t);
LED(1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1);
delay(t);
LED(1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1);
delay(t);
for (int x = 0; x < a; x++)
{
y = 3;
level();
LED(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
delay(5);
y = 7;
level();
LED(1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 4;
level();
LED(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
delay(5);
y = 5;
level();
LED(1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1);
delay(5);
}
}

// En esta animación prende una serie de tres leds que recorren todo el cubo
void ser()
{
int t = 100;
int a = 10;
int b = 6.5;
for (int x = 0; x < b; x++)
{
y = 0;
level();
LED(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 1;
level();
LED(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < b; x++)
{
y = 0;
level();
LED(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 1;
level();
LED(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
y = 0;
level();
LED(1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
delay(t);
for (int x = 0; x < a; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1);
delay(5);
}
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1);
delay(t);
LED(0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0);
delay(t);
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0);
delay(5);
}
y = 2;
level();
LED(0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0);
delay(t);
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0);
delay(5);
}
for (int x = 0; x < b; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(5);
}
for (int x = 0; x < b; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(5);
}
for (int x = 0; x < b; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0);
delay(5);
}
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1);
delay(t);
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1);
delay(5);
}
for (int x = 0; x < b; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
delay(5);
}
y = 0;
level();
LED(0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0);
delay(t);
for (int x = 0; x < a; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 0;
level();
LED(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 1;
level();
LED(0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < b; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0);
delay(5);
}
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0);
delay(t);
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < b; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
delay(5);
}
y = 1;
level();
LED(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0);
delay(t);
LED(0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
y = 2;
level();
LED(0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
y = 3;
level();
LED(0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
LED(1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(t);
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 3;
level();
LED(1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 2;
level();
LED(1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 3;
level();
LED(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
for (int x = 0; x < a; x++)
{
y = 1;
level();
LED(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
y = 2;
level();
LED(1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
delay(5);
}
}



void setup_wifi()
{
  Serial.println("");
  Serial.println("");
  Serial.print("Conectando a ->");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(250);
  }

  Serial.println("");
  Serial.println("Conexión exitosa!");

  Serial.print("Mi ip es ->");
  Serial.println(WiFi.localIP());
}


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Mensaje recibido bajo el topico ->");
  Serial.print(topic);
  Serial.println("Longitud del payload ->" + String(length));

  for (int i = 0; i > length; i++)
  {
    Serial.print((char)payload[i]);
  }
  // Serial.println();

  if ((char)payload[0] == '0')
  {
    ser();
    Serial.print("Primer modo");
  }
  else if ((char)payload[0] == '1')
  {
    cubote();
    Serial.print("Segundo modo");
  }
  else if ((char)payload[0] == '2')
  {
    cubito();
    Serial.print("Tercero modo");
  }
  else if ((char)payload[0] == '3')
  {
    pxp();
    Serial.print("Cuarto modo");
  }
  else if ((char)payload[0] == '4')
  {
    uxu();
    Serial.print("Quinto modo");
  }
}


void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Intentando conexión MQTT");
    String clientId = "iot_1";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Conexión a MQTT exitosa!!!");
      client.publish("salidaYellow", "primer mensaje");
      client.subscribe("entrada");
    }
    else
    {
      Serial.println("Falló la conexión");
      Serial.print(client.state());
      Serial.print("Se intentará de nuevo en 5 segundos");
      delay(5000);
    }
  }
}
void setup()
{
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(led[4], OUTPUT);
  pinMode(led[5], OUTPUT);
  pinMode(led[6], OUTPUT);
  pinMode(led[7], OUTPUT);
  pinMode(led[8], OUTPUT);
  pinMode(led[9], OUTPUT);
  pinMode(led[10], OUTPUT);
  pinMode(led[11], OUTPUT);
  pinMode(led[12], OUTPUT);
  pinMode(led[13], OUTPUT);
  pinMode(led[14], OUTPUT);
  pinMode(led[15], OUTPUT);
  pinMode(lvl[0], OUTPUT);
  pinMode(lvl[1], OUTPUT);
  pinMode(lvl[2], OUTPUT);
  pinMode(lvl[3], OUTPUT);


  // pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Entro a la conexión");
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}
void loop()
{
  // put your main code here, to run repeatedly:

  if (client.connected() == false)
  {
    reconnect();
  }

  client.loop();

  if (millis() - lastMsg > 2000)
  {
    lastMsg = millis();
    value++;
    String mes = "Valor ->" + String(value);
    mes.toCharArray(msg, 50);
    client.publish("salidaYellow", msg);
    Serial.println("Mensaje enviado ->" + String(value));
  }
}