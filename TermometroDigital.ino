/*const int sensorPin = A0;

// Asignamos los pines según la última prueba que te funcionó
const int redPin = 9;    // Pin 9
const int greenPin = 11; // Pin 10 (este es el que hacía el verde)
const int bluePin = 10;  // Pin 11 (este es el que hacía el azul)

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int lectura = analogRead(sensorPin);
  float voltaje = lectura * (5.0 / 1023.0);
  float temperaturaC = (voltaje - 0.5) * 100.0;

  Serial.println(temperaturaC);

  // Lógica de colores
  if (temperaturaC < 18.0) {
    // Frío: AZUL puro
    setColor(0, 0, 255);   
  } 
  else if (temperaturaC >= 18.0 && temperaturaC <= 28.0) {
    // Templado: VERDE puro
    setColor(0, 255, 0);   
  } 
  else {
    // Calor: ROJO puro
    setColor(255, 0, 0);   
  }

  delay(1000);
}

// FUNCIÓN CORREGIDA
void setColor(int r, int g, int b) {
  // Si el valor es 0, apagamos el pin de forma absoluta. Si no, usamos PWM.
  if (r == 0) { digitalWrite(redPin, LOW); } else { analogWrite(redPin, r); }
  if (g == 0) { digitalWrite(greenPin, LOW); } else { analogWrite(greenPin, g); }
  if (b == 0) { digitalWrite(bluePin, LOW); } else { analogWrite(bluePin, b); }
}*/

//VERSION 2
const int sensorPin = A0;

// Pines confirmados
// Pines corregidos según tu conexión física real:
const int redPin = 9;    
const int bluePin = 10;    // El azul está en el pin 10 
const int greenPin = 11;   // El verde está en el pin 11


void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  float temperaturaC;

  // ==========================================
  // MODO SIMULACIÓN (Para probar sin esperar cambios de temperatura)
  // Cambia el número (ej: 14.0, 19.0, 24.0) para probar cada color.
  // Para volver a la lectura del sensor poner el valor en negativo (-1)
  float temperaturaSimulada = -1; 
  // ==========================================

  // Si la simulación está activa, usamos ese valor. Si no, leemos el sensor.
  if (temperaturaSimulada >= 0) { // Usamos esto como interruptor rápido
    temperaturaC = temperaturaSimulada;
    Serial.print("[MODO PRUEBA] Temperatura forzada: ");
  } else {
    // Lectura normal del sensor con promedio (por si vuelves al sensor real)
    float sumaLecturas = 0;
    int muestras = 15;
    for (int i = 0; i < muestras; i++) {
      sumaLecturas += analogRead(sensorPin);
      delay(3);
    }
    float lecturaPromedio = sumaLecturas / muestras;
    float voltaje = lecturaPromedio * (5.0 / 1023.0);
    temperaturaC = (voltaje - 0.5) * 100.0;
    //Serial.print("Temperatura real sensor: "); //Descomentar cuando no se conecte a PYTHON por problemas con Pyserial
  }
  Serial.println(temperaturaC); //Solo para la comunicación con pyserial
  //Serial.print(temperaturaC);  //Descomentar cuando no se conecte a python por problemas con Pyserial
  //Serial.println(" °C");       //Descomentar cuando no se conecte a python por problemas con Pyserial

  // --- LÓGICA DE RANGOS Y COLORES ---
  if (temperaturaC < 12.0) {
    setColor(0, 150, 255); // Azul claro (< 12°C)
  } 
  else if (temperaturaC >= 12.0 && temperaturaC < 16.0) {
    setColor(255, 255, 255);  // blanco
  } 
  else if (temperaturaC >= 16.0 && temperaturaC < 22.0) {
    setColor(0, 255, 0);   // Verde (16°C a 22°C)
  } 
  else if (temperaturaC >= 22.0 && temperaturaC < 26.0) {
    setColor(15, 250, 0); // Naranja claro (22°C a 26°C)
  } 
  else {
    setColor(255, 0, 0);   // Rojo intenso (>= 26°C)
  }

  delay(1000);
}

// Función para Cátodo Común (0 = apagado, 255 = encendido)
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}