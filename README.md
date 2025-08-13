
# Cómo correr los códigos (resumen)

- Ejecutar Python
  1. Instalar dependencias:
     powershell
     pip install memory_profiler matplotlib
     
  2. Ejecutar:
     powershell
     python python
    recursivo_python.py
     python python\iterativo_python.py
     
- Compilar C (Windows, usando `gcc`)
  1. Guardar `recursivo_windows.c` y `iterativo_windows.c`.
  2. Compilar en PowerShell (si `gcc` está en PATH):
     powershell
     gcc C
ecursivo_windows.c -o recursivo.exe -lpsapi
     gcc C\iterativo_windows.c -o iterativo.exe -lpsapi
     
  3. Ejecutar:
     powershell
     
ecursivo.exe
     .\iterativo.exe
     
  4. Introduce el número cuando el programa lo pida.

#Propósito de la tarea
Comparar algoritmos recursivos e iterativos usando el calculo de factoriales en C y Python. Medir el tiempo de ejecucion y el uso de la memoria para despues mostrarlo en graficas
para comparar rendimiento y limites de cada codigo.

#Cómo implementé las funciones
- C recursivo (`facto_r`)
c
unsigned long long facto_r(int n) {
    if (n==0 || n==1) return 1ULL;
    return (unsigned long long)n * facto_r(n-1);
}

Riesgo: cada llamada usa pila → *stack overflow* para n relativamente bajos.

- C iterativo (`facto_i`)
unsigned long long facto_i(int n) {
    unsigned long long resultado = 1ULL;
    for (int i=1; i<=n; ++i) resultado *= (unsigned long long)i;
    return resultado;
}

- Python recursivo (`facto_r`)

def facto_r(n):
    if n==0 or n==1: return 1
    return n * facto_r(n-1)

- Python iterativo (`facto_i`)

def facto_i(n):
    resultado = 1
    for i in range(1, n+1): resultado *= i
    return resultado

Sin riesgo de recursión; eficiente para valores moderados.

# Métodos usados para medir tiempo y memoria

- Python
  - Tiempo: `time.perf_counter()` o `time.time()`.
  - Memoria: `memory_profiler.memory_usage
  - Instalar: `pip install memory_profiler matplotlib`.

- C (Windows)
  - Tiempo: `QueryPerformanceCounter()` / `QueryPerformanceFrequency()` (alta resolución).
  - Memoria: `GetProcessMemoryInfo()` (Psapi) → `PeakWorkingSetSize` (KB).
  - Compilación: `gcc file.c -o prog.exe -lpsapi`.

# Resumen comparaciones gráficas
- Límites y errores
  - C: falla por stack overflow con n relativamente pequeños.
  - Python recursivo: limitado por `sys.getrecursionlimit()` (≈1000 por defecto) pero sin overflow numérico (limitado por RAM).

- Rendimiento (tiempo) 
  Orden típico (menos → más tiempo): C iterativo < C recursivo < Python iterativo < Python recursivo.  
  En `tiempo vs n`: C iterativo la curva más baja; Python recursivo la más alta.

- Uso de memoria 
  - C: uso base bajo y estable.  
  - Python: mayor uso base (intérprete + objetos) y crecimiento con n grande.  
  En `memoria vs n`: Python escala más rápido que C.

- Conclusión práctica
  - Para velocidad vs eficiencia: C iterativo.  
  - Para factoriales grandes sin librerías externas: Python.  
  - Evitar recursión en C para n grandes; usar iterativo o multiprecisión si se necesita exactitud para n grandes.
