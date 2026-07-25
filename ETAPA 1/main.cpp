// ======================
// JOGO GENIUS - ESP32
// ======================

// LEDs
const int leds[4] = {13, 14, 26, 33};

// Botões
const int botoes[4] = {12, 27, 25, 32};

// Buzzer (GPIO 35 NÃO FUNCIONA como saída)
const int buzzer = 23;

// Frequências
const int tons[4] = {262, 330, 392, 523};

#define MAX_SEQ 100

int sequencia[MAX_SEQ];
int nivel = 1;

// ------------------------

void setup() {

  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }

  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(34));

  sequencia[0] = random(0, 4);

  inicio();
}

// ------------------------

void loop() {

  mostrarSequencia();

  if (lerJogador()) {

    nivel++;

    sequencia[nivel - 1] = random(0, 4);

    delay(500);

  } else {

    perdeu();

    nivel = 1;

    sequencia[0] = random(0, 4);

    delay(1000);

  }

}

// =========================

void inicio() {

  for (int i = 0; i < 4; i++) {

    digitalWrite(leds[i], HIGH);
    tone(buzzer, tons[i]);
    delay(150);
    digitalWrite(leds[i], LOW);
    noTone(buzzer);

  }

}

// =========================

void mostrarSequencia() {

  delay(600);

  for (int i = 0; i < nivel; i++) {

    int led = sequencia[i];

    digitalWrite(leds[led], HIGH);

    tone(buzzer, tons[led]);

    delay(500);

    digitalWrite(leds[led], LOW);

    noTone(buzzer);

    delay(250);

  }

}

// =========================

bool lerJogador() {

  for (int i = 0; i < nivel; i++) {

    int botao = esperarBotao();

    if (botao != sequencia[i]) {

      return false;

    }

  }

  return true;

}

// =========================

int esperarBotao() {

  while (true) {

    for (int i = 0; i < 4; i++) {

      if (digitalRead(botoes[i]) == LOW) {

        digitalWrite(leds[i], HIGH);

        tone(buzzer, tons[i]);

        while (digitalRead(botoes[i]) == LOW);

        noTone(buzzer);

        digitalWrite(leds[i], LOW);

        delay(150);

        return i;

      }

    }

  }

}

// =========================

void perdeu() {

  for (int j = 0; j < 3; j++) {

    for (int i = 0; i < 4; i++) {

      digitalWrite(leds[i], HIGH);

    }

    tone(buzzer, 150);

    delay(300);

    for (int i = 0; i < 4; i++) {

      digitalWrite(leds[i], LOW);

    }

    noTone(buzzer);

    delay(300);

  }

}