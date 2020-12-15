# Plotter for Final Project AEP 4830

# This import registers the 3D projection, but is otherwise unused.
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
import numpy as np
import matplotlib as mpl
mpl.use ( 'TkAgg') # must be written both in import intermediate
import matplotlib.pyplot as plt 


# Allow for latex in plots
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "serif",
    "font.serif": ["Palatino"],
})


# Plot at t = 100000000 of RNG sim
x = [0.198428662, 1.84925079, 1.12557956, 0.812247018, 0.147942166, 1.05098303, 2.0, 1.27868577, 1.89394466, 0.714537125]
y = [1.27358432, 0.744005761, 0.952379302, 2.0, 1.2690655, 1.57998393, 1.65448919, 0.925126634, 1.79518417, 0.411780287]
z=[0.29026051, 1.04748701, 1.85070098, 1.96743296, 1.45636894, 0.93630141, 0.4635193, 0.0483312264, 1.61432701, 1.00712861]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
plt.title("Positions at t = 100,000,000")
ax.scatter(x,y,z)
ax.set_xlabel("Nondimensionalized x Position")
ax.set_ylabel("Nondimensionalized y Position")
ax.set_zlabel("Nondimensionalized z Position")
plt.savefig("100000000.png", dpi = 300)
plt.show()
plt.close()