import time
import matplotlib.pyplot as plt
from memory_profiler import memory_usage

# función recursiva para calcular factorial
def facto_r(n):
    if n == 0 or n == 1:
        return 1
    else:
        return n * facto_r(n - 1)

if __name__ == "__main__":
    # pedir número al usuario
    num = int(input("Introduce un número para calcular su factorial: "))

    # medir memoria y tiempo para el número ingresado
    start_time = time.time()
    mem_usage = memory_usage((facto_r, (num,)), max_iterations=1)
    end_time = time.time()

    resultado = facto_r(num)
    tiempo_total = end_time - start_time
    memoria_usada = max(mem_usage) - min(mem_usage)

    # mostrar resultados en consola
    print(f"\nFactorial de {num} = {resultado}")
    print(f"Tiempo de ejecución: {tiempo_total:.6f} segundos")
    print(f"Memoria consumida: {memoria_usada:.6f} MB")

    # --- Gráficas con un solo punto ---
    plt.figure(figsize=(10, 4))

    # gráfico de tiempo
    plt.subplot(1, 2, 1)
    plt.scatter([num], [tiempo_total], color='blue', s=100)
    plt.title("Tiempo de ejecución")
    plt.xlabel("n")
    plt.ylabel("Segundos")
    plt.grid(True)

    # gráfico de memoria
    plt.subplot(1, 2, 2)
    plt.scatter([num], [memoria_usada], color='red', s=100)
    plt.title("Uso de memoria")
    plt.xlabel("n")
    plt.ylabel("MB consumidos")
    plt.grid(True)

    plt.tight_layout()
    plt.show()
