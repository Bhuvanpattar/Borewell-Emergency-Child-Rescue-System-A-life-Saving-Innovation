#define motor1Pin1 3  // IN1 for Motor 1
#define motor1Pin2 4  // IN2 for Motor 1
#define motor2Pin1 5  // IN3 for Motor 2
#define motor2Pin2 6  // IN4 for Motor 2
#define enablePin1 9  // ENA for Motor 1 (PWM)
#define enablePin2 10 // ENB for Motor 2 (PWM)

#define bluetoothTx 0 // Arduino TX connected to Bluetooth RX
#define bluetoothRx 1 // Arduino RX connected to Bluetooth TX

char command;
int speedValue = 255; // Default speed (max: 255)

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  // Initialize Bluetooth communication
  Serial.begin(9600); // Ensure Bluetooth module's baud rate matches
}

void loop() {
  if (Serial.available()) {
    command = Serial.read(); // Read the command from the app

    switch (command) {
      case 'F': // Forward for Motor 1
        analogWrite(enablePin1, speedValue);
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
        break;

      case 'B': // Backward for Motor 1
        analogWrite(enablePin1, speedValue);
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
        break;

      case 'L': // Backward for Motor 2
        analogWrite(enablePin2, speedValue);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        break;

      case 'R': // Forward for Motor 2
        analogWrite(enablePin2, speedValue);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
        break;

      case 'S': // Stop both motors
        analogWrite(enablePin1, 0);
        analogWrite(enablePin2, 0);
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        break;

      case '+': // Increase speed
        speedValue = min(speedValue + 25, 255);
        break;

      case '-': // Decrease speed
        speedValue = max(speedValue - 25, 0);
        break;

      default:
        // Stop motors if an unknown command is received
        analogWrite(enablePin1, 0);
        analogWrite(enablePin2, 0);
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        break;
    }
  }
}
