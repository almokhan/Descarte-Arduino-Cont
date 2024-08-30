int rele1 = 13;      // Pino do relé
String comando = ""; // Buffer para armazenar a string recebida

void setup() {
  pinMode(rele1, OUTPUT);
  Serial.begin(9600);
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
        Serial.println("Ligado");
        digitalWrite(rele1, HIGH); // Ativa o relé
      } else if (comandoLimpo == "<rele,0") {
        digitalWrite(rele1, LOW);  // Desativa o relé
        Serial.println("Desligado");
      } else {
      }     
      comando = "";
    }
  }
}
