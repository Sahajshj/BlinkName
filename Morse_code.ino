int led1 = LED_BUILTIN;
int buttonPin = 2;
bool isButtonPressed = false;

const int MAX_MAPPINGS = 10;  // Maximum number of Morse code mappings
int numMappings = 8;          // Initial number of mappings

// Define Morse code mappings as a 2D array [character][Morse code]
const char* morseMappings[MAX_MAPPINGS][2] = {
  {"S", "..."},     // S (...)
  {"A", ".-"},      // a (.-)
  {"H", "...."},    // h (....)
  {"A", ".-"},      // a (.-)
  {"J", ".---"},    // j (.---)
  {"P", ".--."},    // p (.--.)
  {"A", ".-"},      // a (.-)
  {"L", ".-.."},    // l (.-..)
  // Placeholder for additional mappings
};

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), resetName, FALLING);
  
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  if (isButtonPressed) {
    resetName();
    isButtonPressed = false;
  }

  for (int i = 0; i < numMappings; i++) {
    const char* character = morseMappings[i][0];
    const char* morseCode = morseMappings[i][1];

    for (int j = 0; morseCode[j]; j++) {
      if (morseCode[j] == '.')
        blinkDot();
      else if (morseCode[j] == '-')
        blinkDash();

      if (morseCode[j + 1])
        delay(200);
    }

    if (character[0] != ' ')
      delay(600);  // Gap between characters
  }

  delay(2000);  // Gap between words
}

// ... (blinkDot, blinkDash, resetName functions remain unchanged)

void mainFunction() {
  Serial.println("Enter new Morse code mapping (format: Character,MorseCode):");

  while (Serial.available() == 0) {
    ; // Wait for user input
  }

  String input = Serial.readStringUntil('\n'); // Read user input
  input.trim(); // Remove leading and trailing whitespace

  if (input.length() > 0) {
    int commaIndex = input.indexOf(',');
    if (commaIndex != -1) {
      String character = input.substring(0, commaIndex);
      String morseCode = input.substring(commaIndex + 1);

      if (numMappings < MAX_MAPPINGS) {
        morseMappings[numMappings][0] = character.c_str();
        morseMappings[numMappings][1] = morseCode.c_str();
        numMappings++;
        Serial.println("Mapping added: " + character + " -> " + morseCode);
      } else {
        Serial.println("Maximum number of mappings reached.");
      }
    }
  }
}