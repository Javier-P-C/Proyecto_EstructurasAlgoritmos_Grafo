DOCUMENTACIÓN 
  1.-Explicación general del código 
  2.-Explicación por Función 
  3.-Complejidades de los algoritmos 
  4.-Casos de Prueba

--------------------------------------------
EXPLICACIÓN GENERAL DEL CÓDIGO
Al iniciar el programa se cargan por medio de dos archivos los nodos del grafo. El primer archivo continene las uniones y el segundo es para darle nombre a los grafos.
El objetivo del programa es mostrar una ruta corta entre dos nodos seleccionados por el usuario en el metro. Se tomo como referencia el Metro de CDMX pero solo con las estaciones donde había más conexiones.
El menú te permite elegir entre tres opciones del programa. Busqueda de ruta, ver las estaciones vecinas y ver todos las estaciones del metro. 

-----------------------------------------------------
EXPLICACIÓN POR FUNCIÓN
El programa cuenta con cuatro tipos de funciones. Las que cargan la información, la que ayudan a realizar la búsqueda, las que ayudan a imprimir información y las de apoyo para las anteriores.

Carga:
-void loadGraphList(std::string,int)
  Recibe el nombre del archivo donde se encuentran las conexiones de los nodos y el número de vértices. Con esta función se meten los nodos a adjList y se establece la forma del grafo.
-void loadNodeNames(std::string)
  Recibe el nombre de un archivo con los nombres ordenados de cada nodo. En este caso los nodos son las estaciones.

Búsqueda:
-std::string BFS(int,int)
  Recibe el nodo de origen y el destino. Está función hace el recorrido del grafo y va guardando su paso en una cola. Le pide el camino más corto a pathBFS() y devuelve el resultado.
-void pathBFS(int,int,std::queue<int>&,std::stringstream&)
  Una vez que el recorrido fue realizado la cola se le pasa a esta nueva función para poder sacar el recorrido con menos nodos. Por medio de las coordenadas guardadas se va metiendo el recorrido en un stringstream.

Impresiones:
-std::string printAdjList()
  Recorre el vector de nodos adyacentes para devolver un string con todos los nodos y sus adyacentes.
-void showInfo()
  Imprime el número de nodos y arcos del grafo.
-void neighborNodes(int)
  Recibe el número de un nodo para imprimir las estaciones adyacentes
-void showAllNodes()
  Imprime los nombres de cada nodo
-void neighborNodesString(std::string)
  Recibe el nombre de un nodo para imprimir las estaciones adyacentes

Auxiliares:
-std::string number2string(int)
  Por medio de número del nodo recibido busca el nombre del nodo en el vector names. El resultado lo devuelve en forma de string.
-int string2number(std::string)
  Recorre el vector de names buscando una coincidencia con el vector nombre recibido. Devuelve un entero correspondiente al nodo buscado.
-std::string searchByNameBFS(std::string,std::string)
  Recibe el nombre de las estaciones buscadas y las transforma en enteros para poder hacer la búsqueda del camino.
-template <class T> void swap(std::vector<T>&,int,int)
  Intercambia dos valores en un mismo vector

--------------------------------------------------------
COMPLEJIDAD DE LOS ALGORITMOS
-void loadGraphList(std::string,int)
-void loadNodeNames(std::string)
  Ambas funciones leen documentos y repiten el guardado de datos el mismo número de veces que el número de líneas en los archivos. Por eso ambos son O(n).

-void showInfo()
  Solo imprime dos atribrutos, su complejidad es constante, O(1)

-std::string printAdjList()
  Recorre el vector pero también recorre los vectores dentro de cada índice. En el peor de los casos todos los nodos se conectan con todos. Su complejidad es O(n^2)

-void neighborNodes(int)
-void showAllNodes()
  Ambos recorren un solo vector para imprimir los elementos dentro de él. Como solo lo hace una vez su complejidad se queda en lineal, O(n).

-----------------------------------------------------------------
CASOS DE PRUEBA

----Lectura de datos-----
-INDICACIONES
Verifique la cantidad de datos en estaciones.txt (28)
-INPUT
2
-OUTPUT
Se deben desplegar todas las estaciones con su nombre

----Busqueda----
-INPUT
1
1
SALTO DEL AGUA
PANTITLAN
-OUTPUT
Un recorrido de 4 nodos que contenga el nodo de origen y el nodo de salida
*Se puede comprobar por medio de la imagen CDMX_mapa_metro.jpg que se encuentra en el proyecto

-INPUT
1
1
TACUBA
MORELOS
-OUTPUT
Un recorrido de 5 nodos que contenga el nodo de origen y el nodo de salida
*Se puede comprobar por medio de la imagen CDMX_mapa_metro.jpg que se encuentra en el proyecto

-INPUT
1
2
21
10
-OUTPUT
Un recorrido de 5 nodos que incluya el origen y destino
*Se puede comprobar por medio de la imagen CDMX_mapa_metro.jpg que se encuentra en el proyecto

-INPUT
1
2
4
27
-OUTPUT
Un recorrido de 8 nodos que incluya el origen y destino
*Se puede comprobar por medio de la imagen CDMX_mapa_metro.jpg que se encuentra en el proyecto

----Lista de Adyacencia----
-INPUT
3
1
BALDERAS
-OUTPUT
Se despliegan las tres estacionas que conectan con Balderas: Hidalgo, Salto del Agua, centro médico
*Se puede comprobar por medio de la imagen CDMX_mapa_metro.jpg que se encuentra en el proyecto

-INPUT
3
2
22
-OUTPUT
Se despliegan las 4 estacionas que conectan con el nodo 22(Jamaica): Candelaria, Pantitlan, Chabacano, Santa Anita
*Se puede comprobar por medio de la imagen CDMX_mapa_metro.jpg que se encuentra en el proyecto