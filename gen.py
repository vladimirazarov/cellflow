import matplotlib.pyplot as plt
import os
import numpy as np

# Získejte aktuální adresář, ve kterém se nachází skript
current_directory = os.path.dirname(os.path.abspath(__file__))

# Cesta k souboru "out.txt" ve stejném adresáři jako skript
file_path = os.path.join(current_directory, "out.txt")

# Inicializace seznamů pro ukládání x a y hodnot
x_values = []
y_values = []

# Načtení dat ze souboru
with open(file_path, 'r') as file:
    for line in file:
        y, x = line.split()
        x_values.append(float(x))
        y_values.append(float(y))


# Definujeme počet intervalů pro průměrování průtoku
num_bins = 100
max_density = max(x_values)
bin_edges = np.linspace(0, max_density, num_bins+1)
bin_centers = 0.5 * (bin_edges[:-1] + bin_edges[1:])
bin_averages = []

# Vypočítáme průměrný průtok pro každý interval hustoty
for i in range(num_bins):
    bin_mask = (x_values > bin_edges[i]) & (x_values <= bin_edges[i+1])
    bin_averages.append(np.mean([y for y, m in zip(y_values, bin_mask) if m]))

# Vykreslení původních dat
plt.scatter(x_values, y_values, edgecolors='w', s=6, color='black')

# Vykreslení průměrné křivky
plt.plot(bin_centers, bin_averages, color='red', linewidth=2)

# Nastavení grafu
plt.title('Závislost průtoku na hustotě')
plt.xlabel('Hustota [auta na pozici]')
plt.ylabel('Průtok [auta za časový krok]')
plt.grid(True)
plt.show()