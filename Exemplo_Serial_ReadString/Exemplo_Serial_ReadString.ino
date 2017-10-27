void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    String mensagem = Serial.readString();
    Serial.print("Mensagem recebida: ");
    Serial.print(mensagem);
    Serial.println();
  }
}
