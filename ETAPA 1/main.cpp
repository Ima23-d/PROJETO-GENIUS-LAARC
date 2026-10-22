// ============================================================================
// JOGO GENIUS - ESP32 LAARC
// ============================================================================

// ----------------------------------------------------------------------------
// 1. CONFIGURAÇÃO DOS PINOS (Nomeados por cor para facilitar a leitura)
// ----------------------------------------------------------------------------

// LEDs
const int LED_VERDE    = 13;
const int LED_VERMELHO = 14;
const int LED_AMARELO  = 26;
const int LED_AZUL     = 33;

// BOTÕES
const int BOTAO_VERDE    = 12;
const int BOTAO_VERMELHO = 27;
const int BOTAO_AMARELO  = 25;
const int BOTAO_AZUL     = 32;

// BUZZER
const int BUZZER = 23;

// FREQUÊNCIAS DAS NOTAS (Som de cada cor)
const int TOM_VERDE    = 262; // Dó
const int TOM_VERMELHO = 330; // Mi
const int TOM_AMARELO  = 392; // Sol
const int TOM_AZUL     = 523; // Dó alto

// Agrupamos nas listas para o jogo conseguir usar nos laços (loops)
const int leds[4]   = {LED_VERDE, LED_VERMELHO, LED_AMARELO, LED_AZUL};
const int botoes[4] = {BOTAO_VERDE, BOTAO_VERMELHO, BOTAO_AMARELO, BOTAO_AZUL};
const int tons[4]   = {TOM_VERDE, TOM_VERMELHO, TOM_AMARELO, TOM_AZUL};

// ----------------------------------------------------------------------------
// 2. VARIÁVEIS DO JOGO
// ----------------------------------------------------------------------------
#define MAX_SEQUENCIA 100

int sequencia[MAX_SEQUENCIA];
int nivel = 1;

// Declaração das funções
void tocarCor(int indiceCor, int tempo);
void animacaoInicio();
void mostrarSequencia();
bool lerJogadaDoJogador();
int  esperarBotaoSerPressionado();
void animacaoPerdeu();

// ============================================================================
// SETUP
// ============================================================================
void setup() {
  Serial.begin(115200);

  // Configura todos os LEDs como SAÍDA e Botões como ENTRADA
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
    digitalWrite(leds[i], LOW);
  }

  pinMode(BUZZER, OUTPUT);

  // Garante números realmente aleatórios usando a leitura de um pino solto
  randomSeed(analogRead(34));

  // Toca o som de início e sorteia a primeira cor (0 a 3)
  animacaoInicio();
  sequencia[0] = random(0, 4);
}

// ============================================================================
// LOOP PRINCIPAL (Onde o jogo roda)
// ============================================================================
void loop() {
  // 1. O ESP32 pisca e toca a sequência para o jogador
  mostrarSequencia();

  // 2. O jogador tenta repetir a sequência
  if (lerJogadaDoJogador()) {
    
    // SE ACERTOU: Passa de nível e adiciona mais uma cor
    nivel++;
    sequencia[nivel - 1] = random(0, 4);
    delay(500);

  } else {
    
    // SE ERROU: Toca a animação de erro e reinicia o jogo no nível 1
    animacaoPerdeu();
    nivel = 1;
    sequencia[0] = random(0, 4);
    delay(1000);

  }
}

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

// Pisca o LED e toca o som de uma cor específica
void tocarCor(int indiceCor, int tempo) {
  digitalWrite(leds[indiceCor], HIGH);
  tone(BUZZER, tons[indiceCor]);
  delay(tempo);
  digitalWrite(leds[indiceCor], LOW);
  noTone(BUZZER);
}

// Mostra a sequência inteira do nível atual
void mostrarSequencia() {
  delay(600);

  for (int i = 0; i < nivel; i++) {
    int corAtual = sequencia[i];
    tocarCor(corAtual, 500); // Acende por 500ms
    delay(250);               // Pausa entre as cores
  }
}

// Lê todas as respostas que o jogador precisa dar no nível atual
bool lerJogadaDoJogador() {
  for (int i = 0; i < nivel; i++) {
    int botaoApertado = esperarBotaoSerPressionado();

    // Se o botão apertado for diferente do que estava na sequência, errou!
    if (botaoApertado != sequencia[i]) {
      return false;
    }
  }
  return true; // Acertou todos os botões do nível
}

// Fica esperando o jogador apertar qualquer um dos 4 botões
int esperarBotaoSerPressionado() {
  while (true) {
    for (int i = 0; i < 4; i++) {
      
      // Quando o botão é apertado (fica em nível LOW por causa do INPUT_PULLUP)
      if (digitalRead(botoes[i]) == LOW) {
        
        digitalWrite(leds[i], HIGH);
        tone(BUZZER, tons[i]);

        // Fica preso aqui enquanto o jogador segurar o botão
        while (digitalRead(botoes[i]) == LOW);

        // Quando o jogador solta o botão:
        noTone(BUZZER);
        digitalWrite(leds[i], LOW);
        delay(150); // Pequena pausa antes da próxima leitura

        return i; // Retorna qual cor foi apertada (0=Verde, 1=Vermelho, 2=Amarelo, 3=Azul)
      }
    }
  }
}

// Animação rápida ao ligar o jogo
void animacaoInicio() {
  for (int i = 0; i < 4; i++) {
    tocarCor(i, 150);
  }
}

// Animação de quando o jogador perde (pisca tudo 3 vezes com som grave)
void animacaoPerdeu() {
  for (int repeticao = 0; repeticao < 3; repeticao++) {
    
    // Liga todos os LEDs
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], HIGH);
    }
    tone(BUZZER, 150); // Som bem grave de erro
    delay(300);

    // Desliga todos os LEDs
    for (int i = 0; i < 4; i++) {
      digitalWrite(leds[i], LOW);
    }
    noTone(BUZZER);
    delay(300);
  }
}
