import serial
import time
import sys
import requests

PUERTO = 'COM3'
VELOCIDAD = 9600
BASE_URL = "http://192.168.1.117:7000/api/temperatura/"

# --- INTERRUPTOR DE ATAQUE ---
MODO_ATAQUE = "--ataque" in sys.argv
# -----------------------------

print("🖥️  INICIANDO PUENTE CENTRAL (PC Windows) 🖥️")
if MODO_ATAQUE:
    print("🔴 MODO ATAQUE ACTIVADO: Manipulando datos...")
else:
    print("🟢 MODO NORMAL: Enviando datos reales...")

ultimo_estado_conexion = True

try:
    arduino = serial.Serial(PUERTO, VELOCIDAD, timeout=1)
    time.sleep(2)
    arduino.reset_input_buffer()

    while True:
        try:
            linea = arduino.readline().decode('utf-8', errors='ignore').strip()
        except (serial.SerialException, OSError):
            print("❌ Arduino desconectado.")
            break

        if not linea:
            continue

        try:
            temp_real = float(linea)
        except ValueError:
            continue

        if MODO_ATAQUE:
            temp_a_enviar = temp_real + 12.0
            print(f"📡 Real: {temp_real:.2f} °C -> 🔥 ATACADO: {temp_a_enviar:.2f} °C")
        else:
            temp_a_enviar = temp_real
            print(f"📡 Real: {temp_real:.2f} °C -> 🟢 Enviado normal")

        url_final = f"{BASE_URL}{temp_a_enviar:.2f}"

        try:
            r = requests.post(url_final, timeout=1)
            if not ultimo_estado_conexion:
                print("✅ UNO Q reconectado. Reanudando envío.")
                ultimo_estado_conexion = True
        except (requests.exceptions.ConnectTimeout,
                requests.exceptions.ConnectionError,
                requests.exceptions.ReadTimeout):
            if ultimo_estado_conexion:
                print("⚠️  Aviso: UNO Q no disponible. Reintentando...")
                ultimo_estado_conexion = False

except serial.SerialException:
    print(f"❌ ERROR: No se pudo abrir el puerto {PUERTO}.")
except KeyboardInterrupt:
    print("\n🛑 Programa detenido por el usuario.")