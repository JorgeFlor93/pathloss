#### Este documento resume el proyecto a desarrollar
------
### Funcionalidades a lograr

1. Enviar características de una BTS haciendo uso de websockets.
2. Manipular los datos recogidos y usarlos junto a un algoritmo para devolver el cálculo de la propagación.
2. Encapsular la información y devolverla al cliente.
3. modelo Cliente-Servidor.
    1. Mensajes progreso.
    2. Mensajes de datos. Formato JSON.
4. Funcionamiento operativo de la aplicación.

### Funcionalidad actual de la herramienta SignalServer

La aplicación de partida es Cloud-RF. Esta es una herramienta OpenSource para el análisis de Propagación de señales de Radio-Frecuencia, pérdidas y características del terreno. Tiene soporte para multitud de estándares de telecomunicación, como VHF, GMS, UMTS, 5G, WI-Fi y Wi-Max entre otros.

La versión escogida para el proyecto es SignalServer. Se trata de una herramienta de línea de comandos o terminal de textos (shell).
Esta herramienta devuelve a la salida un muestreo de datos 2D en formato PPM Bitmaps. Dicha versión está fundamentada en la herramienta original SPLAT! (Signal Propagation, Loss, And Terrain analysis tool SPLAT!), en ella podemos encontrar [información](https://cloudrf.com/open%20source) mucho más detallada de las bases de este proyecto.

SignalServer provee datos RF de ingeniería del sitio, es decir, parámetros de entrada, y produce reportes en forma de gráficos y mapas topográficos que presentan trayectorias de linea-de-vista, pérdidas por trayectorias regionales y contornos de intensidad de señal a través de los cuales se puede determinar el área de cobertura esperada de sistemas transmisores o repetidores. 

Su forma de uso es:

`signalserver [data options] [input options] [output options] -o outputfile`

Los parámetros de la herramienta se dividen en: 

<details>  
  <summary>1. Parámetros de entrada:</summary> 
  
  ###### Input:
  
     -lat Tx Latitude (decimal degrees) -70/+70
     -lon Tx Longitude (decimal degrees) -180/+180
     -txh Tx Height (above ground)
     -rla (Optional) Rx Latitude for PPA (decimal degrees) -70/+70
     -rlo (Optional) Rx Longitude for PPA (decimal degrees) -180/+180
     -f Tx Frequency (MHz) 20MHz to 100GHz (LOS after 20GHz)
     -erp Tx Effective Radiated Power (Watts) including Tx+Rx gain
     -rxh Rx Height(s) (optional. Default=0.1)
     -rxg Rx gain dBi (optional for text report)
     -hp Horizontal Polarisation (default=vertical)
     -gc Random ground clutter (feet/meters)
     -m Metric units of measurement
     -te Terrain code 1-6 (optional)
     -terdic Terrain dielectric value 2-80 (optional)
     -tercon Terrain conductivity 0.01-0.0001 (optional)
     -cl Climate code 1-6 (optional)
     -rel Reliability for ITM model 50 to 99 (optional)
     -resample Resample Lidar input to specified resolution in meters (optional)
</details>
Características del modelo de telecomunicación que giran en torno a los parámetros de transmisión de la antena, distancia, unidades, tipo de entorno y clima (opcional). Algunos de los parámetros son obligatorios para la ejecución apropiada del programa, mientras que otros son opcionales.

<br/> <details>
  <summary>2. Ficheros de datos</summary>
 
  ###### Data:
  
     -sdf Directory containing SRTM derived .sdf DEM tiles
     -lid ASCII grid tile (LIDAR) with dimensions and resolution defined in header
     -udt User defined point clutter as decimal co-ordinates: 'latitude,longitude,height'
     -clt MODIS 17-class wide area clutter in ASCII grid format
</details>

Ficheros de datos. Adicionalmente se requiere el uso de programas/scripts como opciones de entrada. Los archivos .sdf contienen los modelos digitales del terreno (DEM). Estos existen en diferentes resoluciones, STRM, STRM v2 y STRM-3 (versión 2.1). Estas versiones ofrecen resoluciones en 1 arcosegundo (90m aprox) y 3 arcos (30m). Dichos archivos se pueden obtener en sus diferentes versiones de la [web USGS](https://dds.cr.usgs.gov/srtm/).


<br/> <details>
  <summary>3. Opciones a la salida</summary>
 
  ###### Output:
  
     -dbm Plot Rxd signal power instead of field strength
     -rt Rx Threshold (dB / dBm / dBuV/m)
     -o Filename. Required. 
     -R Radius (miles/kilometers)
     -res Pixels per tile. 300/600/1200/3600 (Optional. LIDAR res is within the tile)
     -pm Propagation model. 1: ITM, 2: LOS, 3: Hata, 4: ECC33,
     	  5: SUI, 6: COST-Hata, 7: FSPL, 8: ITWOM, 9: Ericsson, 10: Plane earth, 11: Egli VHF/UHF
     -pe Propagation model mode: 1=Urban,2=Suburban,3=Rural
     -ked Knife edge diffraction (Already on for ITM)
</details>
Los parámetros a la salida establecen el alcance de nuestra cobertura radiada, el modelo de propagación escogido para el cálculo, el tipo de terreno sobre el que realizamos la propagación (necesario para optimizar el cálculo realizado por los diferentes tipos de modelo) y el nombre del archivo donde se almacenan los resultados.


### Funcionalidad que tendrá cuando finalice el proyecto

Se plantea inicialmente desarrollar un servidor que administre las peticiones de los clientes y devuelva el cálculo de la propagación en una región específica, haciendo uso de los modelos (hata, ITM, LOS, EC33, VHF/UHF...) descritos.

Se va a desplegar haciendo uso de la herramienta [Docker](https://www.docker.com/why-docker) . Esta API permite cierta flexibilidad en cuanto a arquitecturas y el uso de múltiples lenguajes.

Las peticiones de los clientes van a interactuar con el servidor abriendo canales de comunicación bidireccionales y full-duplex sobre un único socket TCP. Para ello se hace uso de la librería [Websockets](https://github.com/facundofarias/awesome-websockets) . Esta herramienta está diseñada para ser implementada en navegadores y servidores web. Estos canales son independientes del lenguaje usado para la comunicación. Estas librerías se van a implementar en C++. Se pretende hacer uso de unas ya existentes para posteriormente adaptarlas a la aplicación.

La aplicación será capaz de levantar una serie de contenedores Docker en los cuales se desarrollarán las funcionalidades descritas. Uno de ellos correra un servidor-web a modo de interfaz que manejará las peticiones Websockets entrantes. Posteriormente enviará las peticiones a los servidores websockets conectados a él. En estos servidores realizan los cálculos pertinentes y responden al servidor web dónde su interfaz mostrará los resultados.

Según lo comentado, esta aplicación pretende funcionar como un modelo cliente-servidor, siendo este capaz de atender múltiples peticiones simultaneamente, y en base a la geolocalización del cliente en forma de vector (latitud y longitud) ser capaz de devolver en un área predefinida un cálculo de la pérdidas por propagación respecto a la antena que le sirva la cobertura radio.

### De la funcionalidad que tendrá el proyecto indicar cuál ya existía cuál es nueva y cuál deja de existir con respecto a lo que ya había

De las funcionalidades comentadas, las encargadas de calcular pérdidas por propagación en base a parámetros RF como pueden ser alturas de las antenas, potencia, ganancia o descripción del terreno, en base a algoritmos heurísticos y empíricos, son pertenecientes a la aplicación SignalServer descrita. Las usaremosen en el servidor-websocket. 

Deja de existir la funcionalidad de la aplicación como herramienta de línea de comando. Se implementará  un modelo cliente-servidor, el cual responderá en base a la geolocalización de las peticiones de los clientes. Estos interactúan con la aplicación a través de un servidor-web.

También vamos a desechar la funcionalidad de devolver la información en forma de Bitmaps. No queremos representar la información mediante una nube de puntos RGB.

Como nueva funcionalidad está la Dockerización de la herramienta. La herramienta va a ser levantada en varios contenedores.

Partimos de un servidor-web, servidores websockets y clientes websockets. Todos ellos han de ser adaptados a la necesidad de la futura aplicación, es decir, necesita modificación para que trabaje con información de geolocalizacón, latitud y longitud, en forma de vector.
