# GamePad BLE Esp32
Libreria requerida: https://github.com/lemmingDev/ESP32-BLE-Gamepad

En mi Instagram estare subiendo videos del funcionamiento en diferentes juegos.

Instagram: @leimerky

El circuito se alimenta con una bateria de 3,7V. 
En la parte trasera se observa dos conectores se puede utilizar cualquiera de los dos  para conectar la bateria.

![GamePad_1](https://user-images.githubusercontent.com/74838411/105619870-d563e900-5dc4-11eb-8aef-cdefa51a9c95.JPG)
![GamePad_2](https://user-images.githubusercontent.com/74838411/105619871-d5fc7f80-5dc4-11eb-99a9-a5abe26f2cb8.JPG)

Se tiene disponible una conexiones para una oled 0.96" y un MPU5060 aun no se a implementado en el codigo.
![GamePad_3](https://user-images.githubusercontent.com/74838411/105619872-d5fc7f80-5dc4-11eb-84b3-0be17c75289b.JPG)

Para la programacion del chip ESP32 es necesario conectar los puntos FTDI que llegaria a ser la R14 en el schematic
esto para alimentar al chip CH340C

Tambien es necesario conectar los pines del regulador en el cual se puede elegir conectar los 5 con el punto medio esto tomara voltaje del puerto usb para alimentar
el circuito o podemos conectar el Bat con el punto medio el cual tomara voltaje de la bateria esto es para evitar soldar el circuito de proteccion y 
carga del circuito y poder realizar pruebas estos puntos equivalen a la R16 y R17 respectivamente en el schematic. (No conectar los 3 puntos ya que se generaria un corto).

![image](https://user-images.githubusercontent.com/74838411/105619867-cbda8100-5dc4-11eb-89b4-bfb1f3ad9f48.png)

El circutio dispone de 2 reguladores es necesario conectar solo uno de estos ya sea el 662k o el ams117 3.3v.(No conectar los 2 reguladores al mismo tiempo).
![image](https://user-images.githubusercontent.com/74838411/105620053-e281d780-5dc6-11eb-9fef-04b8470b3f4e.png)

