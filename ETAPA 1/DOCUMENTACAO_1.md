
# 🎮 Documentação Técnica Completa: Jogo da Memória "Gênius" - ESP32

**Autores:** Felipe Torres Marinho Barros e Arthur Franco Mendes Gomes  
**Projeto:** Sistema Embarcado Lúdico com ESP32 (LAARC)

---

## 1. Introdução e Contextualização do Problema

O desenvolvimento de habilidades cognitivas, como memória de curto prazo, foco e reflexo rápido, é um desafio constante em um mundo repleto de estímulos dispersos. No âmbito educacional e de entretenimento, há uma demanda contínua por ferramentas que unam o aprendizado prático de eletrônica e programação ao desenvolvimento dessas capacidades de forma lúdica.

O problema central deste projeto consiste em projetar e construir um sistema embarcado de baixo custo, intuitivo e interativo, capaz de desafiar e exercitar a memória sequencial do usuário por meio de estímulos visuais e sonoros coordenados.

---

## 2. A Solução Proposta

A solução desenvolvida é uma versão física e microcontrolada do clássico jogo "Gênius" (conhecido internacionalmente como *Simon*). O sistema utiliza o poder de processamento do microcontrolador **ESP32** montado em uma protoboard para criar um jogo de memorização ativa.

O dispositivo gera sequências aleatórias de cores e sons que aumentam de tamanho progressivamente à medida que o jogador acerta, exigindo que o usuário reproduza exatamente a mesma ordem utilizando os botões físicos correspondentes.

---

## 3. Requisitos do Sistema

### Requisitos Funcionais (O que o sistema faz)

* **Geração de Sequência:** O sistema inicia gerando uma cor/som aleatório e aumenta a sequência em um elemento a cada rodada de acerto.
* **Feedback Visual:** Cada cor gerada acende o LED correspondente (Verde, Vermelho, Amarelo ou Azul) por um intervalo de tempo padrão (500 ms).
* **Feedback Sonoro:** O acionamento de cada LED é acompanhado por uma frequência de som exclusiva emitida pelo buzzer, criando uma assinatura sonora distinta para cada cor (notas Dó, Mi, Sol, Dó alto).
* **Entrada do Usuário:** O sistema aguarda a resposta do jogador por meio de quatro botões de pressão (*push-buttons*).
* **Validação de Jogada:** O sistema compara em tempo real a entrada do usuário com a sequência armazenada na memória.
* **Indicação de Vitória/Derrota:** Há um padrão luminoso e sonoro específico para indicar o acerto da sequência completa (avanço de nível) ou o erro (animação de fim de jogo com pisca-pisca geral e som grave).

### Requisitos Não-Funcionais (Como o sistema se comporta)

* **Tempo de Resposta:** A detecção do pressionamento dos botões é imediata, utilizando travamento em laço `while` para evitar múltiplos disparos indesejados (*debounce* mecânico).
* **Eficiência de Processamento:** O código é estruturado de forma legível e otimizada para rodar de maneira fluida no ESP32 sem sobrecarregar a CPU.
* **Baixo Custo:** O circuito utiliza componentes eletrônicos básicos, acessíveis e reutilizáveis.

---

## 4. Lista Detalhada de Componentes Necessários

Para a montagem física do circuito, foram especificados os seguintes componentes eletrônicos e materiais de apoio:

| Item | Componente | Qtd. | Especificação Técnica | Função Detalhada no Circuito |
| :---: | :--- | :---: | :--- | :--- |
| **1** | **ESP32 DevKit v1** | 1 | Microcontrolador 32-bits, 240MHz, 30 pino GPIOs | Cérebro do sistema: processa a lógica do jogo, lê os botões e controla os LEDs e Buzzer. |
| **2** | **Protoboard (Breadboard)** | 1 | 830 pontos com barramentos de alimentação | Base para montagem do circuito sem necessidade de solda. |
| **3** | **LED Difuso 5mm Verde** | 1 | Tensão de operação: ~2.0V, Corrente: 20mA | Indicador luminoso da cor Verde (Tom Dó / 262 Hz). |
| **4** | **LED Difuso 5mm Vermelho** | 1 | Tensão de operação: ~2.0V, Corrente: 20mA | Indicador luminoso da cor Vermelha (Tom Mi / 330 Hz). |
| **5** | **LED Difuso 5mm Amarelo** | 1 | Tensão de operação: ~2.0V, Corrente: 20mA | Indicador luminoso da cor Amarela (Tom Sol / 392 Hz). |
| **6** | **LED Difuso 5mm Azul** | 1 | Tensão de operação: ~3.0V, Corrente: 20mA | Indicador luminoso da cor Azul (Tom Dó Alto / 523 Hz). |
| **7** | **Resistores de Limitação** | 4 | 220 Ω (ou 330 Ω), 1/4W, Tolerância 5% | Conectados em série com os LEDs para limitar a corrente das GPIOs do ESP32. |
| **8** | **Push-buttons (4 pinos)** | 4 | Chave táctil 6x6x5mm | Entradas digitais do usuário. Operam em modo `INPUT_PULLUP` (acionam em **LOW**). |
| **9** | **Buzzer Passivo** | 1 | Piezoelétrico, 5V, opera via sinal PWM (`tone()`) | Gerador de áudio. Reproduz notas musicais ajustando a frequência enviada pelo pino. |
| **10**| **Cabos Jumper** | ~20 | Macho-Macho / Macho-Fêmea | Realizam as conexões elétricas entre os componentes e as portas do ESP32. |
| **11**| **Cabo Micro-USB / USB-C** | 1 | Comunicação de dados e alimentação 5V | Conecta o ESP32 ao computador para gravação do firmware e energia. |

---

## 5. Mapeamento Atualizado de Pinos e Esquema de Ligação (Hardware)

### Tabela Oficial de Conexões dos Pinos (GPIOs)

| Cor / Canal | Pino LED (Saída) | Resistor do LED | Pino Botão (Entrada) | Modo do Pino | Frequência (Tom) | Nota Musical |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Verde** | GPIO 26 | 220 Ω -> GND | GPIO 25 | `INPUT_PULLUP` | 262 Hz | Dó (C4) |
| **Vermelho** | GPIO 14 | 220 Ω -> GND | GPIO 27 | `INPUT_PULLUP` | 330 Hz | Mi (E4) |
| **Amarelo** | GPIO 33 | 220 Ω -> GND | GPIO 32 | `INPUT_PULLUP` | 392 Hz | Sol (G4) |
| **Azul** | GPIO 13 | 220 Ω -> GND | GPIO 12 | `INPUT_PULLUP` | 523 Hz | Dó Alto (C5) |
| **Buzzer** | GPIO 23 | N/A (GND direto) | - | `OUTPUT` | Variável | Multi-tom |
| **Ruído Aleatório**| - | Solto (Sem conexão) | GPIO 34 | `ANALOG` | N/A | Seed para `random()` |

### Arquitetura de Ligação Elétrica:
1. **LEDs:** O anodo (perna longa) conecta-se à porta GPIO atribuída (26, 14, 33 ou 13). O catodo (perna curta) conecta-se a um resistor de 220 Ω, que vai ligado ao barramento **GND** (Terra).
2. **Botões:** Um terminal do botão conecta-se diretamente à porta GPIO atribuída (25, 27, 32 ou 12). O outro terminal conecta-se ao **GND**. Graças ao modo `INPUT_PULLUP`, quando o botão está solto a porta lê `HIGH`; quando pressionado, lê `LOW`.
3. **Buzzer:** O pino positivo (+) conecta-se na **GPIO 23** e o negativo (-) no barramento **GND**.

---

## 6. Arquitetura do Sistema e Máquina de Estados Finitos (FSM)

O comportamento do jogo é modelado através de uma **Máquina de Estados Finitos (FSM)** composta por 5 estados fundamentais:

```text
               +-------------------+
               |  1. ESTADO_INIT   |
               | (Config / Vinheta)|
               +---------+---------+
                         |
                         v
               +-------------------+
               | 2. MOSTRAR_SEQ    | <-------------------+
               | (ESP32 Pisca/Toca)|                     |
               +---------+---------+                     |
                         |                               |
                         v                               |
               +-------------------+                     |
               | 3. AGUARDAR_JOGADA|                     |
               | (Leitura Botões)  |                     |
               +---------+---------+                     |
                         |                               |
                    [Validar]                            |
                     /     \                             |
               (Correto)  (Incorreto)                    |
                  /           \                          |
                 v             v                         |
       +---------------+  +-------------------+          |
       | 4. PROX_NIVEL |  | 5. GAME_OVER      |          |
       | (Nivel++ /    |  | (Animação Erro /  |          |
       |  Nova Cor)    |  |  Reset p/ Nivel 1)|          |
       +-------+-------+  +---------+---------+          |
               |                    |                    |
               +--------------------+--------------------+

```

### Descrição dos Estados da FSM:

1. **`ESTADO_INIT` (Inicialização):**
* Configura os pinos I/O e inicializa a comunicação Serial (`115200 baud`).
* Lê o ruído do pino analógico 34 para calibrar o gerador de números aleatórios (`randomSeed`).
* Executa a vinheta sonora de abertura (`animacaoInicio()`) e sorteia a primeira cor.


2. **`MOSTRAR_SEQ` (Demonstração da Sequência):**
* O ESP32 varre o vetor `sequencia[]` do índice `0` até `nivel - 1`.
* Acende o LED correspondente e toca o tom da cor por 500ms, com uma pausa de 250ms entre os elementos.


3. **`AGUARDAR_JOGADA` (Aguardando Entrada):**
* O sistema entra em um laço de escuta ativa esperando que o jogador pressione um botão.
* Ao detectar o pressionamento de um botão (nível `LOW`), acende o LED e toca o tom correspondente enquanto o botão estiver pressionado.


4. **`PROX_NIVEL` (Sucesso / Avanço):**
* Se o jogador reproduziu toda a sequência corretamente, o valor de `nivel` é incrementado.
* O sistema sorteia uma nova cor aleatória (entre 0 e 3) e adiciona ao final do vetor da sequência.


5. **`GAME_OVER` (Derrota / Reinício):**
* Se o jogador apertar a cor errada, a execução do nível é interrompida.
* O sistema pisca todos os LEDs 3 vezes simultaneamente e toca um tom grave (150 Hz).
* O nível é resetado para `1` e uma nova sequência é iniciada.



---

## 7. Fluxograma de Execução do Código

```text
[INÍCIO]
   │
   ▼
Setup dos Pinos (LEDs = Output, Botões = Input Pullup)
   │
   ▼
Tocar Animação de Início -> Sortear 1ª Cor da Sequência
   │
   ▼
┌─►[LOOP PRINCIPAL]
│  │
│  ├─► Exibir Sequência do Nível Atual (Piscar LEDs e Tocar Tons)
│  │
│  ├─► Ler Entradas do Jogador (Aguardar cliques até completar a quantidade do Nível)
│  │
│  ├─► [O botão pressionado é IGUAL ao esperado na sequência?]
│  │         │
│  │      (SIM) ──────► Incrementa Nível (Nivel = Nivel + 1)
│  │         │          Adiciona nova cor aleatória à sequência
│  │         │          Pausa de 500ms
│  │         │          └──────────────┐
│  │                                   │
│  └───── (NÃO) ──────► Tocar Animação de Derrota (Pisca tudo + Som Grave)
│                       Resetar Nível = 1
│                       Sortear nova 1ª Cor
│                       Pausa de 1000ms
└──────────────────────────────────────┘

```

---

## 8. Código-Fonte do Projeto (`main.cpp` / `sketch.ino`)

```cpp
// ============================================================================
// JOGO GENIUS - ESP32 LAARC
// Autores: Felipe Torres Marinho Barros e Arthur Franco Mendes Gomes
// ============================================================================

// ----------------------------------------------------------------------------
// 1. CONFIGURAÇÃO DOS PINOS (Atribuição exata de hardware)
// ----------------------------------------------------------------------------

// LEDs
const int LED_VERDE    = 26;
const int LED_VERMELHO = 14;
const int LED_AMARELO  = 33;
const int LED_AZUL     = 13;

// BOTÕES
const int BOTAO_VERDE    = 25;
const int BOTAO_VERMELHO = 27;
const int BOTAO_AMARELO  = 32;
const int BOTAO_AZUL     = 12;

// BUZZER
const int BUZZER = 23;

// FREQUÊNCIAS DAS NOTAS (Som de cada cor em Hz)
const int TOM_VERDE    = 262; // Dó
const int TOM_VERMELHO = 330; // Mi
const int TOM_AMARELO  = 392; // Sol
const int TOM_AZUL     = 523; // Dó alto

// Agrupamos nas listas para o jogo conseguir usar nos laços (loops)
const int leds[4]   = {LED_VERDE, LED_VERMELHO, LED_AMARELO, LED_AZUL};
const int botoes[4] = {BOTAO_VERDE, BOTAO_VERMELHO, BOTAO_AMARELO, BOTAO_AZUL};
const int tons[4]   = {TOM_VERDE, TOM_VERMELHO, TOM_AMARELO, TOM_AZUL};

// ----------------------------------------------------------------------------
// 2. VARIÁVEIS DE ESTADO DO JOGO
// ----------------------------------------------------------------------------
#define MAX_SEQUENCIA 100

int sequencia[MAX_SEQUENCIA];
int nivel = 1;

// Declaração dos protótipos de funções
void tocarCor(int indiceCor, int tempo);
void animacaoInicio();
void mostrarSequencia();
bool lerJogadaDoJogador();
int  esperarBotaoSerPressionado();
void animacaoPerdeu();

// ============================================================================
// SETUP (Configuração inicial de hardware)
// ============================================================================
void setup() {
  Serial.begin(115200);

  // Configura todos os LEDs como SAÍDA e Botões como ENTRADA com PULLUP interno
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
// LOOP PRINCIPAL (Onde a FSM do jogo roda)
// ============================================================================
void loop() {
  // 1. O ESP32 pisca e toca a sequência para o jogador
  mostrarSequencia();

  // 2. O jogador tenta repetir a sequência
  if (lerJogadaDoJogador()) {
    
    // SE ACERTOU: Passa de nível e adiciona mais uma cor
    nivel++;
    
    // Proteção de segurança contra estouro de memória
    if (nivel > MAX_SEQUENCIA) {
      nivel = MAX_SEQUENCIA;
    }

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

// Pisca o LED e toca o som de uma cor específica por um tempo determinado
void tocarCor(int indiceCor, int tempo) {
  digitalWrite(leds[indiceCor], HIGH);
  tone(BUZZER, tons[indiceCor]);
  delay(tempo);
  digitalWrite(leds[indiceCor], LOW);
  noTone(BUZZER);
}

// Mostra a sequência inteira gravada até o nível atual
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
        delay(150); // Pequena pausa antes da próxima leitura (debounce)

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
