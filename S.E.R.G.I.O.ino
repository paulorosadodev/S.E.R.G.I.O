#include <Wire.h> // Importa a biblioteca Wire.h

// Declaração das variáveis do Sensor de Fluxo //
const int INTERRUPCAO_SENSOR = 0;
const int PINO_SENSOR = 2;
float fluxo = 0;
float volume = 0;
float volume_total = 0;
unsigned long contador = 0; // Definicao da variavel de contagem de voltas
const float FATOR_CALIBRACAO = 4.5; // Definicao do fator de calibracao para conversao do valor lido
unsigned long tempo_antes = 0; // Definicao da variavel de intervalo de tempo

// Declaração das variáveis do Acelerometro //
const int MPU_addr = 0x68; // Endereço do sensor
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;  // Variáveis para pegar os valores medidos
const int limiarMovimento = 18000; 

// Declaração das Variáveis da LED //
const int led = 4;
int led_estado = LOW;
unsigned long tempo_anterior = 0;
const long intervalo = 1000;
String furtado;

// Declaração das variáveis para resetar o Arduino //
const unsigned long tempoParaReset = 60000; // Resetará a cada 60 segundos
unsigned long ultimoReset = 0; // Variável para armazenar o tempo do último reset

void setup() {
  Serial.begin(9600); // Inicializacao do monitor serial

  Wire.begin();                      // Inicia a comunicação I2C
  Wire.beginTransmission(MPU_addr);  // Começa a transmissao de dados para o sensor
  Wire.write(0x6B);                  // registrador PWR_MGMT_1
  Wire.write(0);                     // Manda 0 e "acorda" o MPU 6050 (Acelerometro)
  Wire.endTransmission(true);

  // Configuração dos pinos da LED e do Sensor de Fluxo
  pinMode(PINO_SENSOR, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
   // Obtém o tempo atual em milissegundos
  unsigned long tempoAtual = millis();

  // Verifica se o tempo desde o último reset é maior que o tempo desejado
  if (tempoAtual - ultimoReset >= tempoParaReset) {
    ultimoReset = tempoAtual;

      Serial.println(volume_total); // Envia o volume total de água para o monitor serial
      
      delay(1000);
    
    // Aguarda um curto período de tempo para a mensagem ser enviada
    delay(100);

    // Reinicia o Arduino
    asm volatile ("  jmp 0");
  }

  // Executa a contagem de pulsos uma vez por segundo
  if ((millis() - tempo_antes) > 1000) {

    // Desabilita a interrupcao para realizar a conversao do valor de pulsos
    detachInterrupt(INTERRUPCAO_SENSOR);

    // Conversao do valor de pulsos para L/min
    fluxo = ((1000.0 / (millis() - tempo_antes)) * contador) / FATOR_CALIBRACAO;

    // Calculo do volume em L passado pelo sensor
    volume = fluxo / 60;

    // Armazenamento do volume
    volume_total += volume;
    
    // Reinicializacao do contador de pulsos
    contador = 0;

    // Atualizacao da variavel tempo_antes
    tempo_antes = millis();

    // Contagem de pulsos do sensor
    attachInterrupt(INTERRUPCAO_SENSOR, contador_pulso, FALLING);

    unsigned long tempo_atual = millis();

    Wire.beginTransmission(MPU_addr);  // Começa a transmissao de dados para o sensor
    Wire.write(0x3B);                  // registrador dos dados medidos (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 12, true);

    // Armazenamento dos dados medidos pelo acelerômetro
    AcX = Wire.read() << 8 | Wire.read();  
    AcY = Wire.read() << 8 | Wire.read();  
    AcZ = Wire.read() << 8 | Wire.read(); 
    GyX = Wire.read() << 8 | Wire.read();  
    GyY = Wire.read() << 8 | Wire.read();  
    GyZ = Wire.read() << 8 | Wire.read();  

    // Verifica o movimento usando os valores do acelerômetro e envia um alerta se uma movimentaçaõ suspeita for detectada
    if (abs(AcX) > limiarMovimento || abs(AcY) > limiarMovimento || abs(AcZ) > limiarMovimento) {
      furtado = "sim";
      Serial.println("ALERTA! MOVIMENTAÇÃO SUSPEITA DETECTADA!");
    }

    if (fluxo > 0) { // Comportamento da LED se for detectado fluxo de água (Ficará acesa constantemente)
      digitalWrite(led, HIGH);
      led_estado = HIGH;
    } else { // Comportamento da LED em funcionamento padrão do dispositivo (Piscará com um intervalo mediano)
      if (tempo_atual - tempo_anterior >= intervalo) {
        if (led_estado == LOW) {
          digitalWrite(led, HIGH);
          led_estado = HIGH;
        } else { 
          digitalWrite(led, LOW);
          led_estado = LOW;
        }
        tempo_anterior = tempo_atual;
      }
    }
    if (furtado == "sim") { // Comportamento da LED se for detectada movimentação suspeita (Piscará rapidamente)
      digitalWrite(led, HIGH);
      delay(50);
      digitalWrite(led, LOW);
      delay(50);
    }
  }
}
//Funcao chamada pela interrupcao para contagem de pulsos
void contador_pulso() {
  contador++;
}