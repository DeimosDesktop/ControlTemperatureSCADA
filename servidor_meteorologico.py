import serial
import time

PUERTO = 'COM3' 
VELOCIDAD = 9600

print(f"Abriendo puerto {PUERTO}...")
try:
    arduino = serial.Serial(PUERTO, VELOCIDAD, timeout=1)
    time.sleep(2) # Esperamos a que el Arduino reinicie
    arduino.reset_input_buffer() # Limpiamos cualquier basura inicial
    print("¡Conectado! Leyendo temperaturas...\n")
    
    while True:
        if arduino.in_waiting > 0:
            # Leemos la línea y quitamos espacios en blanco
            linea = arduino.readline().decode('utf-8', errors='ignore').strip()
            
            if linea:
                try:
                    # Convertimos a número
                    temperatura = float(linea)
                    print(f"✅ Temperatura recibida: {temperatura} °C")
                except ValueError:
                    # Si llega basura, la ignoramos (no hace nada)
                    pass

except serial.SerialException:
    print(f"ERROR: No se pudo abrir el puerto {PUERTO}. ¿Está abierto el IDE de Arduino?")
except KeyboardInterrupt:
    print("\nServidor detenido.")