import matplotlib.pyplot as plt
import os
import numpy as np

current_script_directory = os.path.dirname(os.path.abspath(__file__))
project_root_directory = os.path.dirname(current_script_directory)
file_path = os.path.join(project_root_directory, "out.txt")

x_values = []
y_values = []

with open(file_path, 'r') as file:
    for line in file:
        y, x = line.split()
        x_values.append(float(x))
        y_values.append(float(y))


num_bins = 100
max_density = max(x_values)
bin_edges = np.linspace(0, max_density, num_bins+1)
bin_centers = 0.5 * (bin_edges[:-1] + bin_edges[1:])
bin_averages = []

for i in range(num_bins):
    bin_mask = (x_values > bin_edges[i]) & (x_values <= bin_edges[i+1])
    bin_averages.append(np.mean([y for y, m in zip(y_values, bin_mask) if m]))

plt.scatter(x_values, y_values, edgecolors='w', s=6, color='black')
plt.plot(bin_centers, bin_averages, color='red', linewidth=2)

plt.title('Závislost průtoku na hustotě')
plt.xlabel('Hustota [auta na pozici]')
plt.ylabel('Průtok [auta za časový krok]')
plt.grid(True)
plt.show()