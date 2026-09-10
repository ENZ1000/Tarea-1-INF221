# Documentación

## Entrega

La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

## Multiplicación de matrices

### Programa principal

El programa principal `matrix_multiplication.cpp` se encarga de cargar los pares de matrices desde el directorio `data/matrix_input/`, ejecutar las mediciones temporales para los algoritmos Naive y Strassen, guardar las matrices resultantes en `data/matrix_output/` y registrar los tiempos de ejecución en `data/measurements/matrix_measurements.csv`.

> **Nota:** Antes de compilar y ejecutar el programa principal, es necesario crear las matrices de prueba con `matrix_generator.py` para que existan en `data/matrix_input/`.

* **Compilación:**
    (en un terminal powershell en visual studio code)
    cd code/matrix_multiplication
    g++ -std=c++17 -O3 -Wall matrix_multiplication.cpp -o matrix_multiplication.exe

* **Ejecución:**
    .\matrix_multiplication.exe

Luego de ejecutar el programa principal, ejecutamos el plot_generator.py, el cual procesa el archivo CSV con las mediciones y exporta los gráficos PNG a data/plots/.

### Scripts

* scripts/matrix_generator.py: Genera los 144 pares de archivos de matrices en data/matrix_input/ según su dimensión (N = {16, 64, 256, 1024}), estructura (dispersa, diagonal, densa) y dominio de valores (D_0, D_10).

py scripts/matrix_generator.py


* scripts/plot_generator.py: Procesa los datos de data/measurements/matrix_measurements.csv y genera los gráficos comparativos de tiempo de ejecución versus dimensión en formato PNG dentro de data/plots/.

py scripts/plot_generator.py

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, PatienceSort, std::sort.

### Programa principal

El programa principal sorting.cpp lee las instancias de arreglos desde data/array_input/, ejecuta las pruebas para los cuatro algoritmos de ordenamiento, almacena los arreglos resultantes en data/array_output/ y exporta los tiempos medidos a data/measurements/sorting_measurements.csv.

> **Nota:** Antes de compilar y ejecutar el programa de ordenamiento, se deben crear los archivos de arreglos en data/array_input/ ejecutando array_generator.py.

* **Compilación:**
    (en un terminal powershell en visual studio)
    cd code/sorting
    g++ -std=c++17 -O3 -Wall -pthread sorting.cpp -o sorting.exe

* **Ejecución:**
    .\sorting.exe

Para generar los gráficos, plot_generator.py(el de la sección de sorting) lee el archivo CSV de mediciones y produce las curvas de rendimiento en formato PNG en data/plots/.

### Scripts

* scripts/array_generator.py: Crea los archivos de arreglos en data/array_input/ según el tamaño (N = {10, 10^3, 10^5, 10^7}), tipo de orden inicial (ascendente, descendente, aleatorio) y dominio (D_1, D_7).

py scripts/array_generator.py


* scripts/plot_generator.py: Lee data/measurements/sorting_measurements.csv y genera los gráficos comparativos de tiempo versus tamaño de arreglo en formato PNG dentro de data/plots/.

py scripts/plot_generator.py