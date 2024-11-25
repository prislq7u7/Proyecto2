Proyecto #2: Simulador de Planificador de Procesos con C++

Integrantes:

-Melissa Garita Chacón C23186
-Priscilla López Quesada C14301
-Stephanie Monge Ortiz C35035

Este proyecto es un simulador de planificador de procesos que implementa dos algoritmos clásicos de planificación de CPU:
1. Round Robin: Cada proceso recibe un tiempo fijo (`quantum`) para ejecutarse antes de ser interrumpido.  
2. Planificación por Prioridad: Los procesos se ejecutan en orden de prioridad, de mayor a menor.

El programa permite cargar procesos desde un archivo de texto, ejecutarlos según el algoritmo seleccionado y comparar el resultado con una salida esperada. 
Los tiempos de ejecución y retardo se simulan para representar el comportamiento real de un sistema operativo.


El proyecto está organizado en varias carpetas.

Proyecto2/
├── src/
│   ├── archivo.cpp
│   ├── main.cpp
│   ├── procesos.cpp
│   ├── simulador.cpp
├── include/
│   ├── archivo.h
│   ├── cola.h
│   ├── planificador.h
│   ├── procesos.h
│   ├── simulador.h
├── bin/
│   └── Proyecto2.exe
├── tests/
│   └── (vacío)
├── lib/
│   └── (vacío)


Instrucciones:
1. Nos ubicamos en ..\Proyecto2
2. Ejecuto el comando para compilar el proyecto: "g++ -I include -o bin/Proyecto2 src/main.cpp src/archivo.cpp src/procesos.cpp src/simulador.cpp"
3. El ejecutable se crea en ../Proyecto2/bin, entonces escribo -> "./bin/Proyecto2" o "bin\Proyecto2.exe"
4. Se va a imprimir lo siguiente: "Ingrese el nombre del archivo a abrir (con extensión):" el archivo.txt debe estar en ..\Proyecto2
5. Vamos a recibir: "Cola cargada desde archivo:" junto a los procesos que va a ejecutar.
6. Debemos seleccionar el algoritmo de planificación, 1 para Round Robin, y 2 para ejecutarlo por prioridad.
7. Los procesos van a comenzar a ejecutarse por el algoritmo de planificación escogido, a su vez irá imprimiendo las iteraciones para llevar un orden sobre el estado de dichos procesos.
8. Una vez que todos los procesos indiquen el estado "Finalizado", el estado de la cola se actualizará a vacía e indicará que todos los procesos han sido gestionados.
9. Para los casos de prueba, el programa pedirá lo siguiente: "Ingrese el nombre del archivo con la salida esperada:", debe indicarse el archivo.txt (indicar la extensión) que contenga la salida esperada para el archivo que se procesó anteriormente, este al igual que los otros, debe estar en ..\Proyecto2
10. Si el procesamiento del archivo es igual al archivo de salida esperado, el programa indicará "La salida es igual a la esperada.", sino, se indicará el número de línea donde está la diferencia y lo que esperaba comparado con lo que recibió.

