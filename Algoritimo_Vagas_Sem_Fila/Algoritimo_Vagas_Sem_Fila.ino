// Inicializa o vetor de vagas
int vagas[5] = {};

void setup() {
    Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
      // Recupera o valor digitado na serial e o converte
      // para int
      int vaga = Serial.parseInt();
      if(vagas[vaga] == 0){
          vagas[vaga] = 1;
      }else{
        vagas[vaga] = 0;  
      }
      
      atualizaStatusVagas();
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
