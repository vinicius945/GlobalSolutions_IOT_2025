// LTAKN IoT - Drone de Alerta Sísmico com Redirecionamento
// ESP32 + Sensor de Vibração + Botão + LED + MQTT

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* topic = "ltakn/alerta";

WiFiClient espClient;
PubSubClient client(espClient);

// Pinos
const int sensorPin = 13;     // Sensor de vibração
const int ledPin = 12;        // LED de alerta
const int buttonPin = 27;     // Botão de emergência

// Abrigos simulados
String abrigos[] = {"Abrigo Central", "Abrigo Zona Norte", "Abrigo Litoral", "Abrigo BH"};
int abrigoIndex = 0;

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("esp32-drone")) {
      Serial.println("conectado!");
    } else {
      Serial.print("erro: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void enviarAlerta(const char* motivo, String abrigo, float distancia = 0.0, const char* status = "risco_detectado") {
  StaticJsonDocument<256> doc;
  doc["status"] = status;
  doc["drone_id"] = "drone-01";
  doc["motivo"] = motivo;
  doc["abrigo_proximo"] = abrigo;
  if (distancia > 0.0) doc["distancia_km"] = distancia;
  doc["timestamp"] = millis();

  char mensagem[256];
  serializeJson(doc, mensagem);
  client.publish(topic, mensagem);
  Serial.println("Mensagem publicada:");
  Serial.println(mensagem);
}

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int sensorValor = digitalRead(sensorPin);
  bool botaoPressionado = digitalRead(buttonPin) == LOW;

  if (sensorValor == HIGH) {
    digitalWrite(ledPin, HIGH);
    enviarAlerta("vibracao_detectada", abrigos[abrigoIndex]);
    delay(3000);
  }
  else if (botaoPressionado) {
    digitalWrite(ledPin, HIGH);
    abrigoIndex = (abrigoIndex + 1) % (sizeof(abrigos) / sizeof(abrigos[0]));
    float distanciaSimulada = random(10, 50) / 10.0; // entre 1.0 e 5.0 km
    enviarAlerta("botao_emergencia", abrigos[abrigoIndex], distanciaSimulada, "redirecionado");
    delay(3000);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
