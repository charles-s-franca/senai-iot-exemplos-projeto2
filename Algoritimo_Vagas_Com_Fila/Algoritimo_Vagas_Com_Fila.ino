#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

int vagas[12] = {};

// Update these with values suitable for your hardware/network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xEE, 0xEE };
IPAddress server(192, 168, 3, 186);

void callback(char* topic, byte* payload, unsigned int length) {
  String vagaString = String(topic[6]) + String(topic[7]);
  int vaga = vagaString.toInt();

  if(vaga > 0 && vaga < 13){
    char* mensagem = payload;
  
    vagas[vaga - 1] = String(mensagem[0]).toInt();
    atualizaStatusVagas();
  }
}

EthernetClient ethClient;
PubSubClient client(ethClient);

long lastReconnectAttempt = 0;

boolean reconnect() {
  Serial.println("Conectando...");
  if (client.connect("arduinoClient")) {
    Serial.println("Conectado");
    client.subscribe("vaga/+");
  }else{
    Serial.println("Erro ao conectar");  
  }
  return client.connected();
}

void setup()
{
  Serial.begin(9600);
  client.setServer(server, 1883);
  client.setCallback(callback);

  Serial.println("Iniciando...");
  Ethernet.begin(mac);
  delay(1500);
  lastReconnectAttempt = 0;
}


void loop()
{
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    client.loop();
  }

}

void atualizaStatusVagas(){
  int totalVagasDisponiveis = 0;
  int totalVagasOcupadas = 0;  
  
  for(int vaga = 0; vaga < 5; vaga++){
      if(vagas[vaga] == 0){
          totalVagasDisponiveis += 1;
      }else{
          totalVagasOcupadas += 1;
      }
  }

  Serial.print("Livres: ");
  Serial.print(totalVagasDisponiveis);

  Serial.println();

  Serial.print("Ocupadas: ");
  Serial.print(totalVagasOcupadas);

  Serial.println();
  Serial.println();
}
