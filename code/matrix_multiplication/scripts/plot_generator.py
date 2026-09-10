import os
import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams.update({
    'font.family': 'serif',
    'font.size': 18,
    'axes.labelsize': 22,
    'axes.titlesize': 24,
    'xtick.labelsize': 18,
    'ytick.labelsize': 18,
    'legend.fontsize': 18,
    'figure.titlesize': 24
})

COLORES = {
    'naive': '#ff598f',      # Rosa brillante
    'strassen': '#00d2ff'    # Cian
}

def generar_graficos():
    base_dir = os.path.dirname(os.path.abspath(__file__))
    csv_path = os.path.join(base_dir, "../data/measurements/matrix_measurements.csv")
    output_dir = os.path.join(base_dir, "../data/plots")

    if not os.path.exists(csv_path):
        print(f"Error: No se encontró {csv_path}")
        return

    os.makedirs(output_dir, exist_ok=True)
    df = pd.read_csv(csv_path)
    df = df[df["tiempo_ms"] >= 0]

    resumen = df.groupby(["n", "tipo", "dominio", "algoritmo"])["tiempo_ms"].mean().reset_index()

    for t in df["tipo"].unique():
        for d in df["dominio"].unique():
            sub = resumen[(resumen["tipo"] == t) & (resumen["dominio"] == d)]
            if sub.empty:
                continue

            fig, ax = plt.subplots(figsize=(10, 10))

            for alg, datos in sub.groupby("algoritmo"):
                datos = datos.sort_values("n")
                c = COLORES.get(alg.lower(), '#333333')
                ax.plot(datos["n"], datos["tiempo_ms"],
                        linestyle='-', linewidth=2, color=c, alpha=0.85)
                ax.plot(datos["n"], datos["tiempo_ms"],
                        marker='s', markersize=14, markeredgecolor='black',
                        markeredgewidth=1.8, markerfacecolor=c, linestyle='None',
                        label=alg)

            ax.set_xscale("log", base=2)
            ax.set_yscale("log")

            # Estilo despojado sin bordes superior y derecho
            ax.spines['top'].set_visible(False)
            ax.spines['right'].set_visible(False)
            ax.spines['left'].set_linewidth(1.2)
            ax.spines['bottom'].set_linewidth(1.2)

            ax.tick_params(direction='out', length=8, width=1.2)
            ax.set_xlabel("Dimensión (N × N)", labelpad=15)
            ax.set_ylabel("Tiempo promedio (ms)", labelpad=15)
            ax.set_title(f"Tiempo vs Dimensión ({t} - {d})", pad=25)

            ax.legend(title="Algoritmo", frameon=False, loc="upper left")
            plt.tight_layout()

            nombre = f"matrix_{t}_{d}.png"
            plt.savefig(os.path.join(output_dir, nombre), dpi=300)
            plt.close()
            print(f"Gráfico generado: {nombre}")

if __name__ == "__main__":
    generar_graficos()