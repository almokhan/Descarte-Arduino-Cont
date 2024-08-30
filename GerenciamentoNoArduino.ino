int rele1 = 13;      // Pino do relé
int sensorObj = 12;      //Pino do sensor de Objetos
int sensorPort = 11;      //Pino do sensor da porta
String comando = ""; // Buffer para armazenar a string recebida

void setup() {
  pinMode(rele1, OUTPUT);
  pinMode(sensorObj, INPUT);
  pinMode(sensorPort, INPUT);
  Serial.begin(9600);
}

void descarte(){  //Responsavel por um descarte seguro
  digitalWrite(rele1, HIGH);
  while (digitalRead(sensorPort) == LOW){ //Trava o programa até a Portinhola abrir
    digitalWrite(rele1, HIGH);
  }
  while(digitalRead(sensorObj) == LOW){  //Trava o programa até o sensor registra algo
    delay(8);  //Serve para evitar um possivel bouncing
  }
  while(digitalRead(sensorObj) == HIGH){  //Trava o programa até o sensor ser liberado
    delay(8);
  }
  delay(2000); //Tempo de segurança para a portinhola fechar
  digitalWrite(rele1, LOW);
  while(digitalRead(sensorPort) == HIGH){ //Trava o programa até a portinhola ser fechada
    digitalWrite(rele1, LOW);
  Serial.write(1);
  }

}

void loop() {
 
  if (Serial.available() > 0) {
    // Lê o próximo caractere
    char recebido = Serial.read();
    
    comando += recebido;
    
    // Verifica se o comando é completo
    if (comando.endsWith(">")) {
      String comandoLimpo = comando;
      comandoLimpo.remove(comandoLimpo.length() - 1); // Remove '>'
      if (comandoLimpo == "<rele,1") {
        descarte();
      } else if (comandoLimpo == "<rele,0") {
      } else {
      }     
      comando = "";
    }
  }
}
