# Integración de Contenedores en el Portenta X8 para IoT: Mosquitto, Node-RED, InfluxDB y Grafana

## Resumen

Este proyecto describe la implementación de entornos en contenedores en **Portenta X8** para integrar herramientas esenciales de IoT como **Mosquitto**, **Node-RED**, **InfluxDB**, y **Grafana**. El proceso implica la instalación y configuración de contenedores individuales y la integración de un módulo **ESP32** para una transmisión de datos sin interrupción. 

El sistema implementado muestra una solución escalable y eficiente para aplicaciones de IoT, que permite la visualización de datos en tiempo real y el almacenamiento seguro de datos. Los resultados clave demuestran la capacidad de **Portenta X8** como una plataforma robusta y versátil para el desarrollo avanzado de IoT.

## Introducción

El **Internet de las Cosas (IoT)** ha transformado la forma en que interactuamos con el mundo digital, permitiendo la interconexión de dispositivos a través de Internet para la recolección y análisis de datos en tiempo real. Este avance ha generado una necesidad creciente de soluciones tecnológicas que permitan la integración eficiente y la gestión de múltiples sistemas y dispositivos.

En este contexto, los **contenedores** han emergido como una herramienta clave para la implementación de aplicaciones modulares y escalables. El uso de contenedores permite que diferentes aplicaciones y servicios se ejecuten de forma aislada, simplificando su administración, actualización y despliegue. Además, estos ofrecen una gran flexibilidad y eficiencia en entornos de IoT, donde la conectividad y el procesamiento de datos en tiempo real son cruciales.

Este informe detalla el proceso de implementación de contenedores en el microcontrolador **Portenta X8**, una plataforma robusta diseñada para aplicaciones avanzadas de IoT. A través de la utilización de herramientas como **Mosquitto** para la comunicación MQTT, **Node-RED** para la automatización, **InfluxDB** para el almacenamiento de series temporales y **Grafana** para la visualización, se construye una arquitectura eficiente que permite gestionar y monitorear datos provenientes de dispositivos IoT. El **Portenta X8**, con su capacidad de procesamiento y soporte para Docker, proporciona una base ideal para ejecutar y coordinar estos contenedores, logrando una integración eficaz y escalable.

El objetivo principal de este trabajo es presentar paso a paso cómo se realizó la configuración de los contenedores, describiendo los comandos utilizados y las herramientas implementadas, para finalmente demostrar cómo esta solución puede facilitar el desarrollo de aplicaciones IoT de alto rendimiento.

## Metodología

La implementación de los contenedores en el **Portenta X8** se llevó a cabo siguiendo un enfoque sistemático que involucró varios pasos clave. A continuación, se describen las etapas del proceso de instalación y configuración de los contenedores, así como las herramientas utilizadas. Cabe aclarar que este proceso se realizó en un entorno **Windows**. Los comandos pueden variar si se utilizan otros sistemas operativos.
## Actualización del Portenta X8

Antes de continuar, es altamente recomendable **actualizar el sistema operativo** del **Portenta X8**. Las versiones antiguas suelen presentar errores que pueden afectar el desempeño general del dispositivo, especialmente en la ejecución y gestión de contenedores.

Para realizar la actualización a la versión más reciente, visite el siguiente enlace oficial [https://docs.arduino.cc/tutorials/portenta-x8/image-flashing/](https://docs.arduino.cc/tutorials/portenta-x8/image-flashing/) (Marquínez, 2024), donde encontrará diversos métodos para actualizar su dispositivo.

Mantener el **Portenta X8** actualizado es esencial para asegurar un funcionamiento óptimo, aprovechar las últimas mejoras y aplicar correcciones de errores.

## 1. Descarga de la librería del Portenta X8 en Arduino IDE

El primer paso en la configuración del entorno para trabajar con el **Portenta X8** fue la instalación de la librería adecuada en el **Arduino IDE**. Esta librería proporciona las herramientas necesarias para programar y utilizar el **Portenta X8**, asegurando que el entorno de desarrollo reconozca y sea compatible con este dispositivo. Además de la librería específica, el proceso de instalación incluye la herramienta **ADB (Android Debug Bridge)**, que se utiliza para establecer una comunicación con el **Portenta X8**. Esta herramienta es esencial para la transferencia de datos y la gestión de la configuración del dispositivo desde el entorno de desarrollo.

Para realizar la descarga y configuración, sigue los siguientes pasos:

- Abra el **Arduino IDE**.
- **Herramientas > Gestor de Placas > Portenta X8 > Arduino Mbed OS Portenta Boards**.

Este proceso instala las librerías necesarias junto con la herramienta **ADB**, lo que facilita la comunicación con el dispositivo.

Este proceso se ilustra en la siguiente imagen:

![Instalación de la librería para el Portenta X8 en el Gestor de Placas de Arduino IDE](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/1.facility_of__adb.png)

*Instalación de la librería para el Portenta X8 en el Gestor de Placas de Arduino IDE.*


## 2. Acceder a la herramienta ADB

Para acceder a la herramienta **ADB**, es necesario navegar al directorio donde se encuentra la instalación de la herramienta. Esto se logra mediante el siguiente comando en la terminal de **PowerShell** de **Windows**:


```bash
cd C:\Users\USER\AppData\Local\Arduino15\packages\arduino\tools\adb\32.0.0
```

El comando anterior permite acceder a la carpeta donde se encuentra la herramienta **ADB**. Es importante tener en cuenta que el nombre de usuario (**USER** en este caso) debe ser reemplazado por el correspondiente en cada computadora, así como la ubicación de **Arduino IDE**, que puede variar según el directorio de instalación.

Este proceso está basado en el sistema operativo **Windows**, por lo que los comandos podrían diferir si se utiliza otro sistema operativo.

Este proceso se ilustra en la siguiente imagen:

![Ruta para acceder a la herramienta ADB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/2.terminal_with_adb_directory.png)

*Ruta para acceder a la herramienta ADB.*

## 3. Uso de los comandos `.\adb shell` y `sudo su -`

Para acceder a la terminal del dispositivo y obtener privilegios de superusuario, se utilizan los siguientes comandos:

1. **Acceso a la terminal del dispositivo**: Para iniciar una sesión interactiva de ADB en el dispositivo, se utiliza el comando:

 
```bash   
.\adb shell
 ```  

Este comando te permite acceder al sistema operativo del **Portenta X8** de manera remota, desde donde puedes ejecutar varios comandos.

2. **Obtener privilegios de superusuario**: Una vez dentro del dispositivo, para obtener privilegios de administrador, se ejecuta el siguiente comando:


```bash  
sudo su -
```    

Este comando cambia el usuario a superusuario, otorgando acceso completo a todas las funciones del sistema. Es importante tener en cuenta que, por defecto, la contraseña del usuario es (`fio`). Este es el valor predeterminado en el **Portenta X8** y debe ser utilizado para autenticar el acceso de superusuario.

Este proceso se ilustra en la siguiente imagen:

![Uso de los comandos `.\adb shell` y `sudo su -` para acceder a la terminal y obtener privilegios de superusuario](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/3.connection_super_user_portentax8.png)

*Uso de los comandos `.\adb shell` y `sudo su -` para acceder a la terminal y obtener privilegios de superusuario.*

## 4. Verificación del estado de Docker

Para verificar si Docker está en ejecución en el sistema, se utiliza el siguiente comando:


```bash
systemctl status docker
```

Este comando muestra el estado actual del servicio Docker en el dispositivo, indicando si está activo y funcionando correctamente. Si el servicio está corriendo, aparecerá un mensaje que indica su estado como `active (running)`.

En caso de que Docker no esté en ejecución, se puede iniciar el servicio con el siguiente comando:


```bash
systemctl start docker
```

Este proceso se ilustra en la siguiente imagen:

![Verificación del estado de Docker con el comando `systemctl status docker`](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/4.verify_docker.png)

*Verificación del estado de Docker con el comando `systemctl status docker`.*

## 5. Creación de la red interna para los Contenedores

Para crear una red de conexión interna para los contenedores Docker, se utiliza el siguiente comando:


```bash
docker network create --driver bridge --subnet=172.22.0.0/16 iot-network
```

Este comando crea una nueva red interna llamada `iot-network` utilizando el controlador `bridge`, que es el controlador por defecto para redes aisladas en Docker. Además, se especifica un rango de direcciones IP para la red, con la opción `--subnet=172.22.0.0/16`, lo que garantiza que los contenedores conectados a esta red tengan direcciones IP dentro de ese rango.

Para verificar que la red se ha creado correctamente, se puede utilizar el siguiente comando:


```bash
docker network ls
```

Este comando lista todas las redes existentes en Docker, incluyendo la recién creada `iot-network`. Si la red está correctamente configurada, debería aparecer en la lista.

Este proceso se ilustra en la siguiente imagen:

![Creación y verificación de la red interna de contenedores con `docker network create` y `docker network ls`](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/5.red_created.png)

*Creación y verificación de la red interna de contenedores con `docker network create` y `docker network ls`.*

## 6. Conexión a la red Wi-Fi

Para conectar el dispositivo a una red Wi-Fi, se utiliza el siguiente comando:


```bash
nmcli device wifi connect "SSID" password "CONTRASEÑA"
```

En este comando, se debe reemplazar `SSID` por el nombre de la red Wi-Fi a la que deseas conectarte y `CONTRASEÑA` por la contraseña correspondiente.

Es importante recordar que el `SSID` y la `CONTRASEÑA` son valores específicos de cada red, por lo que deberás adaptarlos a tu configuración.

Posteriormente, puedes utilizar el siguiente comando para verificar el estado de los dispositivos de red:

```bash
nmcli device status
```

Este comando muestra el estado actual de los dispositivos de red en el sistema, permitiendo verificar si la conexión Wi-Fi se ha establecido correctamente.

Este proceso se ilustra en la siguiente imagen:

![Conexión a la red Wi-Fi utilizando `nmcli`](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/6.Connect_wifi.png)

*Conexión a la red Wi-Fi utilizando `nmcli`.*

## 7. Verificación de la dirección IP asignada

Para verificar la dirección IP asignada por defecto a la interfaz de red, se utiliza el siguiente comando:


```bash
nmcli dev show wlan0
```

Este comando muestra la configuración actual de la interfaz de red `wlan0`, incluyendo la dirección IP asignada al dispositivo. En la línea (`IP4.address [1]`), observe la dirección IP asignada al dispositivo. Es importante verificar qué clase de red tiene configurada (en este caso, es una red de clase C), ya que esta información será útil para configurar una IP estática dentro del mismo rango de red.

Además, revise la línea (`IP4.GATEWAY`), ya que el gateway es necesario para configurar una IP estática, ya que establece el punto de acceso para la comunicación con otras redes.

Una vez identificada la (`IP4.address [1]`) y (`IP4.GATEWAY`), se puede proceder a configurar una IP estática en el dispositivo.

Este proceso se ilustra en la siguiente imagen:

![Verificación de la dirección IP asignada al dispositivo](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/7.%20assigned_ip.png)

*Verificación de la dirección IP asignada al dispositivo.*

## 8. Asignación de una IP estática

Para asignar una IP estática al dispositivo, se utilizan los siguientes comandos:


```bash
nmcli con mod SSID ipv4.addresses 192.168.1.100/24
```
```bash    
nmcli con mod SSID ipv4.gateway 192.168.1.1
```
```bash    
nmcli con mod SSID ipv4.dns "8.8.8.8 8.8.4.4"
```
```bash    
nmcli con mod SSID ipv4.method manual
```

En estos comandos, el valor `SSID` debe ser reemplazado por el nombre de la red Wi-Fi a la que está conectado el dispositivo. El primer comando asigna la dirección IP `192.168.1.100` con la máscara de subred `/24`. Esta dirección IP se seleccionó modificando el último número de la dirección IP asignada por defecto previamente, que en la sección anterior se mostró como `192.168.1.7`. Se cambió el número final a `100`, lo cual está dentro del rango de direcciones permitido por la red, según la máscara de subred `/24`.

El segundo comando establece la puerta de enlace (`gateway`) como `192.168.1.1`, valor que fue obtenido previamente al ejecutar el comando (`nmcli device show wlan0`) en la sección anterior, donde se identificó el `IP4.GATEWAY`.

El tercer comando configura los servidores DNS como `8.8.8.8` y `8.8.4.4`, y el cuarto comando establece el método de IP como `manual`, lo que significa que la IP será configurada de forma estática y no dinámica.

Después de configurar la IP estática, es necesario reiniciar la conexión para que los cambios surtan efecto. Esto se puede hacer con los siguientes comandos:

```bash
nmcli con down SSID
```
```bash
nmcli con up SSID
```

Es importante tener en cuenta que, aunque la asignación de una IP estática en el dispositivo puede prevenir conflictos de IP al reiniciar, esto no garantiza que no haya problemas con las IPs asignadas por el `Access Point`. Si se desea una IP estática real de punto a punto, debe asignarse la IP directamente desde el `Access Point`, ya que el `Access Point` es el que gestiona las direcciones IP dentro de la red.

La asignación de una IP estática ofrece varios beneficios, como evitar conflictos de IP cuando el dispositivo se reinicia, asegurando que la dirección IP no cambie y evitando tener que reconfigurar la conexión después de un reinicio. Además, mejora la estabilidad de la conexión y facilita el acceso al dispositivo en una red local.

Este proceso se ilustra en la siguiente imagen:

![Asignación de una IP estática utilizando `nmcli`](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/8.new_ip.png)

*Asignación de una IP estática utilizando `nmcli`.*

**NOTA: Si deseas revertir los cambios y configurar la IP de manera automática nuevamente, puedes utilizar los siguientes comandos:**


```bash
nmcli con mod SSID ipv4.method auto
```
```bash
nmcli con up SSID
```


## 9. Verificación de la configuración de la IP estática

Para verificar que la configuración de la IP estática se haya realizado correctamente, puedes usar el siguiente comando:


```bash
nmcli dev show wlan0
```

Este comando muestra la configuración de la interfaz de red `wlan0`, donde podrás verificar si la IP estática que asignaste aparece correctamente. Si la configuración fue exitosa, deberías ver la dirección IP que asignaste previamente en la sección anterior.

Este proceso se ilustra en la siguiente imagen:

![Verificación de la configuración de la IP estática utilizando `nmcli dev show wlan0`](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/9.new_assigned_ip.png)

*Verificación de la configuración de la IP estática utilizando `nmcli dev show wlan0`.*

## 10. Configuración de Mosquitto

En esta sección se detalla el proceso para configurar Mosquitto como un contenedor Docker en el sistema.

### Creación de directorios para Mosquitto

Para almacenar los archivos de configuración, datos y registros de Mosquitto, es necesario crear los directorios correspondientes utilizando los siguientes comandos:


```bash
mkdir -p /home/usuario/mosquitto/config
```
```bash
mkdir -p /home/usuario/mosquitto/data
```
```bash
mkdir -p /home/usuario/mosquitto/log
```

Estos comandos crean las carpetas necesarias dentro del directorio `/home/usuario`.

Este proceso se ilustra en la siguiente imagen:

![Creación de directorios para Mosquitto](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/10.permissions_installation_mosquitto.png)

*Creación de directorios para Mosquitto.*

### Edición del archivo de configuración

Para modificar el archivo de configuración de Mosquitto, utiliza los siguientes comandos:

1. Accede al contenedor de Mosquitto:

```bash
docker exec -it mosquitto sh
```

Este comando abre un shell dentro del contenedor.

2. Edita el archivo de configuración con el siguiente comando:

```bash      
vi /mosquitto/config/mosquitto.conf
  ```
  
Este comando abre el archivo de configuración de Mosquitto en el editor `vi`. Dentro del editor, presiona la tecla `i` para habilitar el modo de inserción y pega las siguientes líneas de configuración:

```bash
pid_file /mosquitto/mosquitto.pid
user mosquitto
listener 1883
persistence true
allow_anonymous true
persistence_location /mosquitto/data/
log_dest file /mosquitto/log/mosquitto.log
  ```

Una vez editado, presiona la tecla `Esc`, escribe `:wq` y presiona `Enter` para guardar y salir.

Los parámetros `pid_file` definen el archivo donde se almacenará el ID de proceso, `user` establece el usuario, `listener 1883` configura el puerto, `persistence` habilita la persistencia de mensajes, `allow_anonymous` permite conexiones sin autenticación, `persistence_location` especifica el directorio para los archivos persistentes, y `log_dest` define el archivo de registros.

Este proceso se ilustra en la siguiente imagen:

![Edición del archivo de configuración de Mosquitto](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/11.permissions_installation_mosquitto.png)

*Edición del archivo de configuración de Mosquitto.*

### Creación y ejecución del contenedor de Mosquitto

Para ejecutar Mosquitto como un contenedor Docker, utiliza el siguiente comando:

```bash
docker run -d --name mosquitto --network iot-network --ip 172.22.0.2 -p 1883:1883 -v /home/usuario/mosquitto/config:/mosquitto/config -v /home/usuario/mosquitto/data:/mosquitto/data -v /home/usuario/mosquitto/log:/mosquitto/log eclipse-mosquitto
```

Este comando crea y ejecuta el contenedor `mosquitto` en segundo plano `-d` en la red `iot-network` con una IP estática `172.22.0.2`. Además, mapea el puerto `1883` para que Mosquitto pueda ser accesible desde fuera del contenedor y monta los volúmenes locales para la configuración, los datos y los registros.

Para verificar que el contenedor se está ejecutando correctamente, utiliza el siguiente comando:

```bash
docker logs mosquitto
```

Este comando muestra los registros del contenedor y te ayudará a comprobar que todo está funcionando como se espera.

Si al ejecutar el comando anterior no se genera salida alguna, significa que todo está configurado correctamente.

Este proceso se ilustra en la siguiente imagen:

![Creación y ejecución del contenedor de Mosquitto](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/12.permissions_installation_mosquitto.png)

*Creación y ejecución del contenedor de Mosquitto.*

## 11. Configuración de InfluxDB

En esta sección se detallará el proceso para configurar InfluxDB como un contenedor Docker dentro de la red `iot-network`.

### Creación y ejecución del contenedor de InfluxDB

Para crear y ejecutar un contenedor Docker para InfluxDB, utiliza el siguiente comando:

```bash
docker run -d --name influxdb --network iot-network --ip 172.22.0.3 -p 8086:8086 influxdb
```

Este comando crea y ejecuta el contenedor de InfluxDB en segundo plano `-d`, lo conecta a la red `iot-network` y le asigna la dirección IP estática `172.22.0.3`. Además, mapea el puerto `8086` para permitir que el contenedor sea accesible y reciba solicitudes a través de dicho puerto.

Este proceso se ilustra en la siguiente imagen:

![Creación y ejecución del contenedor de InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/13.influxdb_installation.png)

*Creación y ejecución del contenedor de InfluxDB.*

## 12. Configuración de Grafana

En esta sección se describen los pasos necesarios para configurar y ejecutar Grafana como un contenedor Docker dentro de la red `iot-network`.

### Creación y ejecución del contenedor

Para crear y ejecutar el contenedor de Grafana, utiliza el siguiente comando:
``` bash
docker run -d --name grafana --network iot-network --ip 172.22.0.4 -p 3000:3000 grafana/grafana
```
Este comando crea y ejecuta el contenedor de Grafana en segundo plano `-d`, lo conecta a la red `iot-network`, y le asigna la dirección IP estática `172.22.0.4`. Además, mapea el puerto `3000` para permitir que el contenedor sea accesible y reciba solicitudes a través de dicho puerto.

Este proceso se ilustra en la siguiente imagen:

![Creación y ejecución del contenedor de Grafana](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/14.Grafana_installation.png)

*Creación y ejecución del contenedor de Grafana.*

## 13. Configuración de Node-RED

En esta sección se describen los pasos necesarios para configurar y ejecutar Node-RED como un contenedor Docker dentro de la red `iot-network`.

### Creación y ejecución del contenedor

Para crear y ejecutar el contenedor de Node-RED, utiliza el siguiente comando:

```bash
docker run -d --name node-red --network iot-network --ip 172.22.0.5 -p 1880:1880 nodered/node-red
```

Este comando crea y ejecuta el contenedor de Node-RED en segundo plano `-d`, lo conecta a la red `iot-network`, y le asigna la dirección IP estática `172.22.0.5`. Además, mapea el puerto `1880` del contenedor al host para que la interfaz web de Node-RED sea accesible desde el navegador.

Este proceso se ilustra en la siguiente imagen:

![Ejecución del contenedor de Node-RED](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/15.node-red_installation.png)

*Ejecución del contenedor de Node-RED.*

## 14. Comando para verificar contenedores activos

Este comando permite verificar que los contenedores Docker que acabamos de configurar estén corriendo con normalidad. Utiliza el siguiente comando para obtener los nombres de los contenedores que se están ejecutando:


```bash
docker ps --format '{{.Names}}'
```

Este comando muestra los nombres de los contenedores activos en el sistema, sin mostrar información adicional como el ID del contenedor, puertos o tiempo de actividad. La opción `--format` permite personalizar la salida, y en este caso, se utiliza `'{{.Names}}'` para mostrar solo los nombres de los contenedores. Así, puedes confirmar que los contenedores que configuraste están en ejecución.

Este proceso se ilustra en la siguiente imagen:

![Listado de contenedores activos utilizando `docker ps`](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/16.container_list.png)

*Listado de contenedores activos utilizando `docker ps`.*

## 15. Comando para activar el inicio automático de contenedores

Este comando permite configurar los contenedores Docker para que se reinicien automáticamente si el sistema se reinicia, si falla la electricidad al dispositivo o en cualquier otro caso en el que el contenedor se detenga inesperadamente.

```bash
docker update --restart unless-stopped mosquitto influxdb node-red grafana
```

Este comando actualiza la política de reinicio de los contenedores especificados para que se reinicien automáticamente, excepto si el contenedor es detenido manualmente. La opción `--restart unless-stopped` asegura que los contenedores se reinicien automáticamente después de un reinicio del sistema o un corte de electricidad, garantizando que los servicios continúen funcionando sin necesidad de intervención manual.

Este proceso se ilustra en la siguiente imagen:

![Configuración de reinicio automático de contenedores](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/17.start_containers_with_portnetax8.png)

*Configuración de reinicio automático de contenedores.*

## 16. Comando para inspeccionar la red y obtener direcciones IP de los contenedores

Este comando permite inspeccionar la red Docker `iot-network` y listar los nombres de los contenedores junto con sus direcciones IP. Utiliza el siguiente comando para obtener la información:

```bash
docker network inspect --format '{{range .Containers}}{{.Name}} - {{.IPv4Address}}{{"\n"}}{{end}}' iot-network | sort -t'_' -k2
```

Este comando inspecciona la red Docker `iot-network` y recorre todos los contenedores conectados a la red y muestra su nombre seguido de su dirección IPv4.

Además, para obtener una lista de los contenedores junto con sus puertos asociados, puedes ejecutar el siguiente comando:

```bash
docker ps --format "table {{.Names}}\t{{.Ports}}"
```

Este comando muestra una tabla con los nombres de los contenedores y sus puertos asociados.

Es fundamental verificar que cada contenedor tenga la dirección IP correctamente configurada y sus puertos asociados previamente antes de proceder con las configuraciones en Node-RED, InfluxDB y Grafana. Esta información es esencial para asegurar que los contenedores puedan comunicarse correctamente entre sí y con los dispositivos conectados a la red.

Este proceso se ilustra en la siguiente imagen:

![Listado de contenedores y sus direcciones IP en la red `iot-network`](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/36.ip_and_ports.png)

*Listado de contenedores y sus direcciones IP en la red `iot-network`.*

## 17. Configuración de InfluxDB

Para comenzar con la configuración de InfluxDB, primero abra su navegador de preferencia y ejecute el siguiente enlace:

```bash
http://192.168.1.100:8086
```

En este caso, `192.168.1.100` es la dirección IP estática que le asignamos al Portenta X8 y `8086` es el puerto asignado a InfluxDB en los pasos anteriores.

Al acceder a la URL, verás la pantalla de inicio de InfluxDB. Aquí puedes empezar a configurar tu base de datos.

Este proceso se ilustra en la siguiente imagen:

![Pantalla de inicio de InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/19.influxdb.png)

*Pantalla de inicio de InfluxDB.*

Para continuar con el registro, sigue estos pasos:

En la sección de registro, se te pedirá el `Initial Organization Name`. En este campo, coloca una referencia a tu proyecto o alguna organización en particular. En mi caso, utilicé `MyIoTSystem`.

En el campo `Initial Bucket Name`, coloca un nombre para el bucket. En este caso, utilicé `Date`, pero puedes elegir otro nombre o dejarlo vacío si lo prefieres.

Este proceso se ilustra en la siguiente imagen:

![Pantalla de registro de InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/20.register_influxdb.png)

*Pantalla de registro de InfluxDB.*

Una vez registrado, verás el `Token`. No es necesario copiarlo en este momento, ya que el token inicial no es recomendable para la conexión entre contenedores. Posteriormente, crearemos otro token dedicado a la conexión de contenedores.

Haz clic en el botón `Configure Later` para continuar.

Este proceso se ilustra en la siguiente imagen:

![Pantalla de configuración de token de InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/21.influxdb_Token.png)

*Pantalla de configuración de token de InfluxDB.*

A continuación, estarás en la página principal de InfluxDB. Para crear una base de datos, sigue estos pasos: haz clic en la opción `Load Data` y selecciona `Buckets`. Luego, presiona el botón `+ Create Bucket`.

Este proceso se ilustra en la siguiente imagen:

![Pantalla para crear un bucket en InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/23.create_database_1.png)

*Pantalla para crear un bucket en InfluxDB.*

Posteriormente asigna un nombre a tu base de datos. En mi caso, `IoT_Database`. Asegúrate de configurar la opción `Delete Data` en `Never` para evitar que los datos se borren periódicamente. Luego, haz clic en el botón `Create` para crear el bucket.

Este proceso se ilustra en la siguiente imagen:

![Configuración del bucket en InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/24.create_database_2.png)

*Configuración del bucket en InfluxDB.*

De esta manera, habrás creado y configurado correctamente tu base de datos en InfluxDB. Ahora podrás empezar a almacenar y gestionar los datos de tu sistema IoT.

## 18. Inicio en Node-RED

Para comenzar a trabajar en Node-RED, abre tu navegador de preferencia y accede al siguiente enlace:

```bash
http://192.168.1.100:1880
```
En este caso, `192.168.1.100` corresponde a la dirección IP estática asignada al dispositivo, y `1880` es el puerto de Node-RED.

Al ingresar a la URL, se mostrará la pantalla principal de Node-RED, donde puedes iniciar la configuración.

Este proceso se ilustra en la siguiente imagen:

![Pantalla de inicio de Node-RED](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/25.node_red.png)

*Pantalla de inicio de Node-RED.*

1. Acceda a Node-RED. En la esquina superior derecha, haga clic en las tres líneas para abrir el menú desplegable y seleccione `Manage Palette`.

Este proceso se ilustra en la siguiente imagen:

![Acceso a la opción Manage Palette](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/26.Node_RED_Manage_palette_1.png)

*Acceso a la opción Manage Palette.*

2. En la pestaña `Install`, busque el paquete escribiendo únicamente `influxdb`: `@rcomanne/node-red-contrib-influxdb`, e instálelo. Por último, presione `Close`.

Este proceso se ilustra en la siguiente imagen:

![Búsqueda e instalación del paquete InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/28.Node_RED_Manage_palette_3.png)

*Búsqueda e instalación del paquete InfluxDB.*

3. En el menú izquierdo, arrastre los nodos `InfluxDB Out`, `MQTT In` y `Debug` al campo de trabajo, y conéctelos tal como se muestra en la siguiente imagen:

![Selección de nodos: InfluxDB Out, MQTT In y Debug](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/34.Node_RED_Influx_Out_6.png)

*Selección de nodos: InfluxDB Out, MQTT In y Debug.*

`InfluxDB Out`: Permite enviar datos a la base de datos en InfluxDB.
   
`MQTT In`: Recibe mensajes desde un servidor MQTT.
   
`Debug`: Muestra mensajes de depuración en el panel derecho, confirmando la conexión con Mosquitto.

 Configure el nodo `MQTT In` haciendo clic sobre él y luego en el botón `+` para añadir un nuevo servidor MQTT.

Este proceso se ilustra en la siguiente imagen:

![Configuración del servidor MQTT](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/35.Node_RED_Influx_Out_7.png)

*Configuración del servidor MQTT.*

4. En la configuración del servidor MQTT, complete los siguientes campos:

`Name`: Asigne un nombre de su preferencia.

`Server`: Introduzca la IP del contenedor Mosquitto `172.22.0.2`.

`Port`: Introduzca el puerto del servidor Mosquitto `1883`.

`Protocol`: Seleccione `MQTT V3.1.1`.

Mantenga los demás campos con la configuración predeterminada.

Haga clic en `Update` para guardar los cambios.

Este proceso se ilustra en la siguiente imagen:

![Configuración del servidor MQTT en Node-RED](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/37.Node_RED_Influx_Out_8.png)

*Configuración del servidor MQTT en Node-RED.*

5. En el nodo `MQTT In`, configure las siguientes opciones:

`Server`: Seleccione el servidor configurado previamente.

`Action`: Elija `Subscribe to single topic`.

`Topic`: Especifique el tópico donde desea almacenar los datos. Por ejemplo, `Sensor_data`.

`QoS`: Seleccione `2`.

`Output`: Establezca `Auto_detect (parsed JSON object, string or buffer)`.

`Name`: Asigne un nombre a su preferencia, por ejemplo, `mqtt broker`.

Haga clic en `Done` para guardar los cambios.

Este proceso se ilustra en la siguiente imagen:

![Configuración del nodo MQTT In](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/38.Node_RED_Influx_Out_9.png)

*Configuración del nodo MQTT In.*

6. Haga clic en `Deploy` para guardar la configuración. Si todo está correctamente configurado, debería aparecer el estado `connected`.

Este proceso se ilustra en la siguiente imagen:

![Confirmación de conexión exitosa en Node-RED](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/39.Node_RED_Influx_Out_10.png)

*Confirmación de conexión exitosa en Node-RED.*

Para configurar el nodo de InfluxDB necesitamos un token de acceso. Para ello, redirígete a InfluxDB. Abre su interfaz, accede al menú `API Tokens`, y haz clic en `+GENERATE API TOKEN`. Selecciona `All Access API Token`, asigna un nombre y guarda el token.

Este proceso se ilustra en las siguientes imágenes: 

![Generación de un token en InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/44.Influxdb_creation_Token_2.png)

*Generación de un token en InfluxDB.*

![Generación de un token en InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/45.Influxdb_creation_Token_3.png)

*Generación de un token en InfluxDB.*

Copie el token manualmente, ya que el botón `COPY TO CLIPBOARD` puede no funcionar correctamente.

Este proceso se ilustra en la siguiente imagen:

![Copia manual del token en InfluxDB](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/46.Influxdb_creation_Token_4.png)

*Copia manual del token en InfluxDB.*

7. Configure el nodo `InfluxDB Out` en Node-RED:

`Name`: Asigne un nombre a su preferencia, por ejemplo, `InfluxDB_Database`.

`Version`: Seleccione `2.0`.

`URL`: Introduzca la IP de InfluxDB con su puerto `http://172.22.0.3:8086`.

`Token`: Pegue el token creado anteriormente.

`Verify Server Certificate`: Desmarque esta opción.

Haga clic en `Update` para guardar los cambios.

Este proceso se ilustra en la siguiente imagen:

![Configuración del nodo InfluxDB Out](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/47.Node_RED_Influx_Out_14.png)

*Configuración del nodo InfluxDB Out.*

8. Después realice los siguientes pasos:

`Name`: Asigne un nombre a su preferencia, por ejemplo, `InfluxDB_Database`.

`Server`: Seleccione el servidor configurado previamente.

`Organization`: Introduzca el nombre de la organización creada durante el registro en InfluxDB, el cual puede verificar ingresando a InfluxDB en la parte superior izquierda, debajo de su usuario. En mi caso, es `MyIoTSystem`.

`Bucket`: Especifique el nombre de la base de datos creada anteriormente.

`Measurement`: Introduzca el `topic` que creo anteriormente.

`Time Precision`: Seleccione `milliseconds (ms)`.

Haga clic en `Done` para guardar los cambios.

Este proceso se ilustra en la siguiente imagen:

![Configuración del nodo InfluxDB Out](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/48.Node_RED_Influx_Out_15.png)

*Configuración del nodo InfluxDB Out.*

Si todo está configurado correctamente, Node-RED podrá recibir y almacenar datos en InfluxDB.

9. Haga clic nuevamente en `Deploy` para guardar todo. Si todo fue configurado correctamente, el flujo debería funcionar sin problemas.

## 19. Configuración del ESP32

Para configurar el ESP32 y conectarlo con Node-RED y el Portenta X8, siga los pasos:

`Librería`: Instale `ArduinoMqttClient` desarrollada por Arduino desde el gestor de librerías del IDE de Arduino. 

`Código`: El código para el ESP32 está disponible en: https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Sending_MQTT_data_to_Portentax8/Sending_MQTT_data_to_Portentax8.ino.

`Configuración`: En el archivo de código, localice y modifique las siguientes variables según su configuración: 

`SECRET_SSID`: Introduzca el nombre de su red Wi-Fi.

`SECRET_PASS`: Introduzca la contraseña de su red Wi-Fi.

`MQTT_BROKER`: Cambie la dirección IP al valor estático asignado al Portenta X8 si es diferente. 

`TOPIC`: Cambie el tópico al creado previamente en Node-RED.

Es importante que el ESP32 esté conectado a la misma red Wi-Fi que el Portenta X8.

Este proceso se ilustra en la siguiente imagen:

![Descarga de la librería MQTT y el código cargado al ESP32](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/50.code_esp32.png)

*Descarga de la librería MQTT y el código cargado al ESP32.*

`Serial Monitor`: Una vez cargado el código al ESP32, abra el `Serial Monitor` en el IDE de Arduino. Debería visualizar los mensajes `Connected to Wi-Fi` y `Connected to MQTT broker`, lo que confirmará que todo el proceso anterior se realizó con éxito.

Puede regresar a Node-RED y observar el nodo `Debug` configurado previamente para verificar los datos enviados por el ESP32.

Este proceso se ilustra en las siguientes imágenes: 

![Resultados del monitor serial del ESP32](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/51.ESP32.CONNECTET.png)

*Resultados del monitor serial del ESP32.*

![Verificación de datos enviados por el ESP32 en Node-RED](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/52.Node_RED_Influx_Out_17.png)

*Verificación de datos enviados por el ESP32 en Node-RED.*

## 20. Configuración de Grafana

Para comenzar a trabajar en Grafana, abre tu navegador de preferencia y accede al siguiente enlace:

```bash
http://192.168.1.100:3000
```

En este caso, `192.168.1.100` corresponde a la dirección IP estática asignada al dispositivo, y `3000` es el puerto predeterminado configurado anteriormente para Grafana.

Al ingresar a la URL, se mostrará la pantalla principal de Grafana, donde deberás ingresar tu nombre de usuario y contraseña para acceder. De forma predeterminada, el usuario es `admin` y la contraseña es `admin`.

Es recomendable cambiar estas credenciales en la primera sesión para asegurar una mayor seguridad en el acceso al sistema. Una vez introducidas las credenciales, podrás iniciar la configuración y personalización de tu instancia de Grafana para crear y gestionar los dashboards y visualizaciones de tus datos.

Este proceso se ilustra en la siguiente imagen:

![Pantalla de inicio de Grafana](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/54.Influxdb_to_Grafana_2.png)

*Pantalla de inicio de Grafana.*

1. Acceder a las conexiones en Grafana:

Abra el menú en la parte derecha y seleccione `Connections > Add New Connection`, tal como se muestra en la siguiente imagen:

![Agregar una nueva conexión en Grafana](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/55.Influxdb_to_Grafana_3.png)

*Agregar una nueva conexión en Grafana.*

2. Selección de InfluxDB:

Busque y seleccione la opción `InfluxDB`, tal como se muestra en la siguiente imagen:

![Selección de InfluxDB en Grafana.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/56.Influxdb_to_Grafana_4.png)

*Selección de InfluxDB en Grafana.*

A continuación, haga clic en `Add New Data Source`, tal como se muestra en la siguiente imagen:

![Selección de InfluxDB en Grafana.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/57.Influxdb_to_Grafana_5.png)

*Selección de InfluxDB en Grafana.*

3. Configuración de la conexión:

`Name:` Introduzca un nombre a su elección.

`Query Language:` Seleccione `Flux`. 

A continuación, configure los siguientes campos en la sección `HTTP`:

`URL:` Introduzca `http://172.22.0.3:8086`

`Auth:` Marque `With Credentials`.

En la sección `InfluxDB Details:`

`Organization:` Introduzca el nombre que usó al registrarse en InfluxDB.  

`Token:` Pegue el token utilizado en Node-RED.  

Por último, haga clic en `Save & Test`.

Este proceso se ilustra en las siguientes Imágenes:

![Configuración inicial de la conexión.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/58.Influxdb_to_Grafana_6.png)

*Configuración inicial de la conexión.*

![Configuración HTTP de la conexión.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/59.Influxdb_to_Grafana_7.png)

*Configuración HTTP de la conexión.*

![Prueba exitosa de la conexión en Grafana.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/60.Influxdb_to_Grafana_8.png)

*Prueba exitosa de la conexión en Grafana.*

4. Crear un nuevo Dashboard: 

En el menú principal de Grafana, haga clic en `+` y seleccione `New Dashboard`. Luego, haga clic en `+ Add Visualization` y elija la conexión configurada previamente con InfluxDB.  

Una vez seleccionada la conexión, podrá personalizar el gráfico eligiendo el tipo que mejor se ajuste a sus necesidades, como líneas o barras. Además, podrá configurar detalles como el rango de tiempo, el intervalo de actualización y los colores. Finalmente, haga clic en `Save Dashboard` para guardar el panel, asignándole un nombre representativo.

Este proceso se ilustra en las siguientes Imágenes:

![Crear un nuevo Dashboard en Grafana.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/61.Influxdb_to_Grafana_9.png)

*Crear un nuevo Dashboard en Grafana.*

![Agregar una visualización en Grafana.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/62.Influxdb_to_Grafana_10.png)

*Agregar una visualización en Grafana.*

![Seleccionar la base de datos configurada.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/63.Influxdb_to_Grafana_11.png)

*Seleccionar la base de datos configurada.*

5. Introducir la consulta Flux:

En la parte inferior, ingrese la siguiente consulta, asegurándose de reemplazar `IoT_Database` con el nombre del bucket que creó previamente:

```bash
from(bucket: "IoT_Database")
  |> range(start: 0)
```
Haga clic en `Refresh`. Si la configuración es correcta, los datos enviados por el ESP32 se visualizarán, tal como se aprecia en la siguiente imagen. Finalmente, haga clic en `Save Dashboard` y asígnele un nombre de su preferencia.


![Consulta Flux para visualizar los datos.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/64.Influxdb_to_Grafana_12.png)

*Consulta Flux para visualizar los datos.*

6. Opciones de visualización: 
 
En `Visualization`, puede cambiar el tipo de gráfico y, junto al botón `Refresh`, ajustar el intervalo de actualización de los datos, tal como se muestra en la siguiente imagen:

![Opciones de visualización y actualización en Grafana.](https://github.com/StevenRangels/Integracion_de_Contenedores_en_el_Portenta_X8_para_IoT_Mosquitto_Node-RED_InfluxDB_y_Grafana/blob/main/Images/66.Influxdb_to_Grafana_14.png)

*Opciones de visualización y actualización en Grafana.*

## Resultados y Discusión

### Resultados Obtenidos

En esta sección se presentan los resultados esperados al seguir el tutorial, junto con una interpretación detallada para validar la configuración y conexión del entorno.

1. Configuración del ESP32 y Node-RED:

   - Al ejecutar el código en el ESP32, el `Serial Monitor` muestra la conexión exitosa al Wi-Fi y al broker MQTT. Esto confirma que los parámetros configurados (`SSID, contraseña, broker, y topic`) son correctos.
   
   - En Node-RED, el nodo `Debug` muestra los datos enviados desde el ESP32, permitiendo validar el flujo de datos en tiempo real.

2. Configuración en Grafana:

   - El tablero personalizado permite seleccionar diferentes formas de representación gráfica, ajustar el intervalo de actualización y analizar las tendencias de los datos en tiempo real.

   - La visualización en Grafana muestra los datos almacenados en InfluxDB. Esto incluye las métricas enviadas por el ESP32, como se observa al ejecutar la consulta Flux:

```bash
from(bucket: "IoT\_Database")
  |> range(start: 0)
```

### Discusión

El entorno creado destaca por su facilidad de implementación, gracias al uso de herramientas de código abierto como Node-RED, InfluxDB y Grafana, que ofrecen una integración fluida.

### Eficiencia:

   - La conexión entre el ESP32 y los demás servicios se realiza de forma confiable, demostrando un bajo nivel de latencia en la transmisión y visualización de datos.
   
   - Grafana permite personalizar la visualización, lo que facilita el análisis de datos en tiempo real.

### Facilidad de Uso:

   - Las instrucciones detalladas garantizan que cualquier usuario, independientemente de su nivel técnico, pueda replicar el entorno.

   - La posibilidad de actualizar y escalar las configuraciones hace que este sistema sea altamente adaptable a diferentes proyectos IoT.

## Conclusiones

En este tutorial se logró establecer un entorno integrado para la captura, transmisión y visualización de datos IoT utilizando el ESP32, Node-RED, InfluxDB y Grafana. A continuación, se destacan los principales logros, posibles mejoras y aplicaciones futuras:

### Logros alcanzados:

   - Se implementó con éxito una conexión fiable entre el ESP32 y Node-RED mediante el protocolo MQTT, demostrando la capacidad del sistema para transmitir datos en tiempo real.
   
   - La integración con InfluxDB permitió almacenar los datos generados de manera estructurada, facilitando su consulta y análisis posterior.
   
   - Grafana proporcionó una visualización efectiva y personalizable de los datos, lo que permite monitorear el sistema de forma intuitiva.

   - El entorno completo fue documentado con un enfoque paso a paso, garantizando su replicabilidad por parte de otros usuarios.

### Posibles mejoras:  

   - Implementar métodos de autenticación más robustos, como el uso de certificados SSL/TLS, para mejorar la seguridad en la transmisión de datos.
     
   - Automatizar parcialmente la configuración inicial mediante scripts que reduzcan el esfuerzo manual necesario para integrar los diferentes componentes.

   - Ampliar las funcionalidades del sistema para incluir alertas automáticas en tiempo real ante eventos definidos, como umbrales críticos en las variables monitoreadas.

### Aplicaciones futuras: 

   - Este entorno puede ser utilizado en aplicaciones industriales para monitorear procesos en tiempo real y tomar decisiones basadas en datos.
 
   - En el campo educativo, el sistema puede ser utilizado como herramienta didáctica para enseñar conceptos de IoT, bases de datos y visualización de datos.

   - En proyectos de investigación, este sistema puede servir como base para analizar tendencias y patrones en datos provenientes de sensores en experimentos complejos.

## Bibliografía

- **Arduino Software**  
  Autor: Arduino  
  Año: 2024  
  [Enlace: Arduino Software](https://www.arduino.cc/en/software)  
  Última revisión: 2024  

- **How To Update Your Portenta X8**  
  Autor: Marquínez, Pablo  
  Año: 2024  
  [Enlace: How To Update Your Portenta X8](https://docs.arduino.cc/tutorials/portenta-x8/image-flashing/)  
  Última revisión: 29/11/2024  

