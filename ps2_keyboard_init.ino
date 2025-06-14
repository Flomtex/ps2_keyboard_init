#define PS2_DATA 2
#define PS2_CLK 3

void sendBit(bool bit) {
  digitalWrite(PS2_DATA, bit);
  delayMicroseconds(30);
  digitalWrite(PS2_CLK, LOW);
  delayMicroseconds(30);
  digitalWrite(PS2_CLK, HIGH);
  delayMicroseconds(30);
}

void sendByte(byte value) {
  pinMode(PS2_DATA, OUTPUT);
  pinMode(PS2_CLK, OUTPUT);

  digitalWrite(PS2_DATA, LOW);
  digitalWrite(PS2_CLK, HIGH);
  delayMicroseconds(100);
  digitalWrite(PS2_CLK, LOW);
  delayMicroseconds(30);

  byte parity = 1;
  for (int i = 0; i < 8; i++) {
    bool bit = (value >> i) & 1;
    sendBit(bit);
    parity ^= bit;
  }

  sendBit(parity);         // parity bit
  digitalWrite(PS2_DATA, HIGH); // stop bit
  delayMicroseconds(30);
  digitalWrite(PS2_CLK, LOW);
  delayMicroseconds(30);
  digitalWrite(PS2_CLK, HIGH);
  delayMicroseconds(30);

  pinMode(PS2_DATA, INPUT_PULLUP);
  pinMode(PS2_CLK, INPUT_PULLUP);
}

void setup() {
  delay(1000); // Wait for keyboard to power up
  sendByte(0xF4); // Send "enable scanning" command
}

void loop() {
  // Nothing here — monitor with scope
}
