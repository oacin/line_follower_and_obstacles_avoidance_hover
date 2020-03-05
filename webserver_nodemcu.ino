#include <Ethernet.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//Nome da sua rede Wifi
const char* ssid = "NomeDaRedeWIFI";
//Senha da rede
const char* password = "senhaDaRedeWIFI";
//IP do ESP (para voce acessar pelo browser)
IPAddress ip(10, 2, 10, 234); //Gateway Padrão. Esse será o valor que vai ser digitado no browser
//IP do roteador da sua rede wifi
IPAddress gateway(10, 2, 10, 62); //Endereço IPv4
//Mascara de rede da sua rede wifi
IPAddress subnet(255, 255, 255, 0); //Máscara de Sub-Rede
//Criando o servidor web na porta 80
WiFiServer server(80);
//Pino do NodeMCU que estara conectado ao LED
const int pin = D2;

void setup() {
  //Preparando o pino, que esta lidgado ao rele
  pinMode(pin, OUTPUT);
  //Isso definirá se a saída começará em HIGH ou LOW quando o sistema for iniciado
  digitalWrite(pin, HIGH);
  //Conectando a rede Wifi
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
  
  //Verificando se esta conectado,
  //caso contrario, espera um pouco e verifica de novo.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  //Iniciando o servidor Web
  server.begin();
}

void loop() {
  //Verificando se o servidor esta pronto
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  //Verificando se o servidor recebeu alguma requisicao
  while (!client.available()) {
    delay(500);
  }
  //Obtendo a requisicao vinda do browser
  String req = client.readStringUntil('\r');
  client.flush();
  //Iniciando o buffer que ira conter a pagina HTML que sera enviada para o browser
  String buf = "";
  buf += "<!DOCTYPE HTML>\r\n<html>\r\n";
  buf += "<head> ";
  buf += "</head> ";
  buf += "<body> ";
  buf += "Controle de Led";
  buf += "</br>";
  buf += "<a href='?ledState=on'>Ligar</a> ";
  buf += "<a href='?ledState=off'>Desligar</a> ";
  buf += "</body> ";
  buf += "</html> ";
  //Enviando para o browser a 'pagina' criada.
  client.print(buf);
  client.flush();
  //Analisando a requisicao recebida para decidir se liga ou desliga a lampada
  if (req.indexOf("on") != -1) {
    Serial.println("Led ligado");
//    digitalWrite(pin, HIGH);
  } else if (req.indexOf("off") != -1) {
    Serial.println("Led desligado");
//    digitalWrite(pin, LOW);
  } else {
    //Requisicao invalida!
    client.stop();
  }
}
