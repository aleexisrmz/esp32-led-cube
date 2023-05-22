#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char *ssid = "BUAP_Estudiantes";
const char *password = "f85ac21de4";

WiFiClient espClient;
PubSubClient client(espClient);

const char *mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char *mqtt_user = "asdasd";
const char *mqtt_pass = "asdasd";

long lastMsg = 0;
char msg[50];
int value = 0;

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
    digitalWrite(BUILTIN_LED, LOW);
    Serial.print("Led Apagado");
  }
  else
  {
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.print("Led Prendido");
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
  // put your setup code here, to run once:

  pinMode(BUILTIN_LED, OUTPUT);
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