Propósito de la tarea
Comparar dos estrategias para calcular el factorial (n!): recursiva vs iterativa, en C (Windows) y Python. Medir y reportar tiempo de ejecución y uso de memoria, y presentar comparaciones gráficas (tiempo vs n, memoria vs n) para sacar conclusiones prácticas sobre rendimiento y límites.

Cómo implementé las funciones
C recursivo (facto_r)

c
Copiar
Editar
unsigned long long facto_r(int n) {
    if (n==0 || n==1) return 1ULL;
    return (unsigned long long)n * facto_r(n-1);
}
Cada llamada añade un marco en la pila → riesgo de stack overflow para n relativamente bajos.

Usa unsigned long long (64 bits) → exacto solo hasta ~n=20.

C iterativo (facto_i)

c
Copiar
Editar
unsigned long long facto_i(int n) {
    unsigned long long resultado = 1ULL;
    for (int i=1; i<=n; ++i) resultado *= (unsigned long long)i;
    return resultado;
}
Evita consumo adicional de pila; más seguro para n grandes (pero sigue limitado por el tipo numérico).

Python recursivo (facto_r)

python
Copiar
Editar
def facto_r(n):
    if n==0 or n==1: return 1
    return n * facto_r(n-1)
Enteros de precisión arbitraria (no overflow numérico); límite práctico por sys.getrecursionlimit().

Python iterativo (facto_i)

python
Copiar
Editar
def facto_i(n):
    resultado = 1
    for i in range(1, n+1): resultado *= i
    return resultado
Sin riesgo de recursión; eficiente en Python para valores moderados.

Métodos usados para medir tiempo y memoria
C (Windows)

Tiempo: QueryPerformanceCounter() / QueryPerformanceFrequency() (alta resolución).

Memoria: GetProcessMemoryInfo() (Psapi) → PeakWorkingSetSize en KB.

Compilación típica: gcc file.c -o prog.exe -lpsapi.

Python

Tiempo: time.perf_counter() o time.time() (se usó perf_counter cuando se necesitó precisión).

Memoria: paquete memory_profiler — memory_usage((func, (args,)), max_iterations=1) devuelve muestras en MB; se usa max-min para estimar consumo durante la ejecución.

Instalación: pip install memory_profiler matplotlib.

Resumen de hallazgos y comparaciones gráficas
Límites y errores

C recursivo: falla por stack overflow con n relativamente pequeños (depende del tamaño del marco y la pila del proceso).

C (ambas): resultados exactos solo hasta ~n = 20 por el límite de unsigned long long.

Python recursivo: limitado por sys.getrecursionlimit() (por defecto ≈1000) pero admite enteros enormes sin overflow (limitado por RAM).

Rendimiento (tiempo)

Orden típico (menos → más tiempo): C iterativo < C recursivo < Python iterativo < Python recursivo.

En gráficos tiempo vs n: C iterativo muestra la curva más baja; Python recursivo la más alta.

Uso de memoria

C: uso base muy bajo y estable; pico medible en PeakWorkingSet.

Python: mayor uso base (interpreter + objetos) y crecimiento claro con n grande (por enteros arbitrarios).

En gráficos memoria vs n: Python escala más rápido que C.

Conclusión práctica

Para velocidad y consumo: usar C iterativo.

Para factoriales grandes y comodidad (sin librerías extra): usar Python.

Evitar recursión en C para grandes n; usar iterativo o multiprecisión (GMP/boost) si se necesita exactitud para n grandes.

Cómo correr los códigos (resumen)
Compilar C (Windows, usando gcc)

Guardar recursivo_windows.c y iterativo_windows.c.

Compilar en PowerShell (suponiendo gcc en PATH):

powershell
Copiar
Editar
gcc C\recursivo_windows.c -o recursivo.exe -lpsapi
gcc C\iterativo_windows.c -o iterativo.exe -lpsapi
Ejecutar:

powershell
Copiar
Editar
.\recursivo.exe
.\iterativo.exe
Introduce el número cuando el programa lo pida.

Ejecutar Python

Crear y activar un virtualenv (opcional):

powershell
Copiar
Editar
python -m venv venv
.\venv\Scripts\Activate.ps1
Instalar dependencias:

powershell
Copiar
Editar
pip install memory_profiler matplotlib
Ejecutar:

powershell
Copiar
Editar
python python\recursivo_python.py
python python\iterativo_python.py
