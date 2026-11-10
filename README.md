# ControlTemperatureSCADA
En este proyecto vas a usar un controlador en PYTHON que se conecte a la arduino UNO Rev3 y muestre la temperatura captada por un TMP36. Desde un PC con Arduino UNO Q nos conectaremos a dicha aplicación a modo de monitorización.
Este proyecto lo puedes seguir paso a paso desde las siguientes páginas:
https://mirpas.com/ciberseguridad/projects/3.php
https://mirpas.com/ciberseguridad/projects/3p.php
Necesitarás:
* 1 Arduino UNO Rev3.
* 1 Circuito con control TMP36 y LED RGB de control.
* 1 Arduino UNO Q
* VScode para los dos códigos fuentes (descargas desde aquí).
Desde Arduino UNO REV3 crearemos el .ino de control de temperatura que encenderá el LED con el color correspondiente a la temperatura de la sala.
El programa servidor_meteorologico.py servirá para conectar el circuito de Arduino UNO Rev3 sin necesidad de usar el IDE de Arduino.
Con el archivo mainInMiddle.py, haremos lo propio, pero cuando se conecte la placa Arduino UNO Q a través de Arduino APP Lab, podremos enviar al sistema SCADA un dato falso en lugar del real.
Para activar el dato falso, aplicaremos el programa de la forma:
manInMiddle.py --ataque.
El circuito eléctrico simulado lo puedes encontrar en tinkedcad:
https://www.tinkercad.com/things/0iuJOBnyxTn-control-de-temperaturas
