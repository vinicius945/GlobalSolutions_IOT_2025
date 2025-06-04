LTAKN - Sistema de Gestão de Abrigos com Notificação de Emergência

📌 Descrição do Projeto

O LTAKN é um sistema inteligente de monitoramento e notificação para situações de risco, como abalos sísmicos ou movimentações incomuns no solo. Utilizando sensores IoT conectados a um drone simulado (ESP32), o sistema detecta alterações físicas e alerta automaticamente os usuários, redirecionando-os para o abrigo mais próximo, com base em um fluxo de decisão em tempo real.

🚀 Tecnologias Utilizadas

ESP32 (via Wokwi)

Sensor de Vibração e Botão (simulados)

Protocolo MQTT (HiveMQ Broker)

ArduinoJson + PubSubClient

Node-RED para dashboard e gateway MQTT

Dashboard UI (node-red-dashboard)

🔧 Funcionalidades

Detecta vibração ou emergência via botão

Publica mensagens MQTT em formato JSON

Alterna automaticamente entre abrigos simulados

Envia status e distância estimada do abrigo

Dashboard simples em tempo real com:

Status

Nome do abrigo

Distância até o local

🔄 Fluxo de Funcionamento

O ESP32 se conecta ao Wi-Fi e broker MQTT

Lê entrada digital (sensor) e botão

Publica um JSON no tópico ltakn/alerta com os dados do evento:

{
  "status": "risco_detectado",
  "drone_id": "drone-01",
  "motivo": "vibracao_detectada",
  "abrigo_proximo": "Abrigo Central",
  "timestamp": 12345678
}

Se o botão for pressionado, o abrigo sugerido muda:

{
  "status": "redirecionado",
  "abrigo_proximo": "Abrigo Zona Norte",
  "distancia_km": 2.4
}

O Node-RED exibe essas informações no painel do usuário

📋 Como Executar

1. Simulador Wokwi (ESP32)

Acesse o projeto: Wokwi Link

Clique em Start Simulation

2. Node-RED (Interface Web)

Importe o JSON ltakn_dashboard_simplificado.json

Execute o flow

Acesse: http://localhost:1880/ui

📦 Requisitos Atendidos (Global Solution)

Requisito

Status

MQTT

✅

JSON estruturado

✅

3 dispositivos (sensor, botão, LED)

✅

Gateway funcional (Node-RED)

✅

Dashboard visual

✅

Tópico personalizado

✅

🎥 Apresentação em Vídeo

Link para o vídeo explicativo

👨‍💻 Integrantes - Grupo LTAKN

Enzo Prado Soddano – RM: 557937
GitHub

Lucas Resende Lima – RM: 556564
GitHub

Vinicius Prates Altafini – RM: 559183
GitHub
