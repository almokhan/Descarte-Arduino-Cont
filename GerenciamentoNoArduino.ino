int seletorPeca = 12;
int portinhola = 10;//Define em que porta a portinhola estara conectada
int sensor = 13; //Define em que porta o sensor sera instaldo (Por enquanto ele é considerado um botão)
int time = 0;//Variavel usada para fazer os TimeOut
int atvSeletor = 11;

void setup() {
 pinMode(sensor, INPUT); //Declara a porta do sensor como de entrada de dados
 pinMode(seletorPeca,INPUT);//Declara a porta do seletor de peça
 pinMode(portinhola, OUTPUT);//Declara a porta da portinhola
 Serial.begin(9600); //Configura a taxa de Bauds entre o Arduino e o PC
}

void loop() {
 Serial.println("Tentando comunicação com PC...");
 Serial.println(1);// O Arduino envia o numero 1, e se recebe-lo de volta, ele confirma a comunicação

  if (Serial.parseInt() == 1){//Recebe o resultado da tentativa de comunicação

  time = millis();

    digitalWrite(portinhola, HIGH);//Abre a portinhola

    Serial.println("Testando sensor, aproxime algo do sensor...");
    while(digitalRead(sensor) != HIGH){//Executa o teste do sensor
      if (millis() - time > 30000){//Se o sensor não for detectado em menos de 30 segundos o Arduino reinicia

        Serial.println("Não foi possivel efetuar comunicação com o sensor, fechando portinhola");
        delay(5000);//Tempo de segurança para o operador
        digitalWrite(portinhola, LOW);//Fecha a portinhola
        Serial.println(5);//Avisa o PC que o Arduino sera reiniciado
        Serial.print("Reiniciando o Arduino em 5 segundos");
        delay(5000);
         asm volatile ("  jmp 0");//Reinicia o Arduino
      }
    }
    time = millis();
    while(digitalRead(sensor) != LOW){// Verifica se nada esta obstruindo o sensor
        if(millis() - time == 12000){
          Serial.println("Por favor desobstrua o sensor");
          delay(1);
        }
    }
    Serial.println("Sensor detectado, tudo Ok");
    delay(5000);
      digitalWrite(portinhola, LOW);
    while(1 < 2){//Loop eterno para manter o Arduino executando apenas esse escopo
    while(Serial.parseInt() != 2){//Loop até o PC enviar pedido para verificar o sensor
    }
    digitalWrite(portinhola, HIGH);//Abre a portinhola
    Serial.println("Aguradando descarte..");

    time = millis();
    while(digitalRead(sensor) != HIGH){//Agurada o cabo passar na frente do sensor
      if(millis() - time == 20000){
        Serial.println("Descarte não foi feito, verifique o sensor");
        delay(1);
        }
    }
    time = millis();
    while(digitalRead(sensor) != LOW){
      if(millis() - time == 20000){
        Serial.println("Descarte não foi feito, verifique se algo obstrui o sensor");
        delay(1);
        }
    }
    Serial.println("Descarte feito");
    Serial.println(2);//Envia sinal para o PC após o descarte ser feito
    delay(5000);//Tempo de segurança para o operador
    digitalWrite(portinhola, LOW);//Fecha a portinhola
  }
  }
  else{
    Serial.println("Erro, não foi possivel efetuar a comunicação com o PC, verifique se o Baud Rate é 9600");
  }
}
