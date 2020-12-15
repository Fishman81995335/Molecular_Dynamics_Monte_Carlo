# Plotter for HW 9 AEP 4830
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

histlist = np.loadtxt("RNG.txt")
plt.hist(histlist, bins=100)
plt.title("RNG Histogram 100,000 points")
plt.ylabel("Number of Points in Bin")
plt.xlabel("Point Value")
plt.savefig("RNG_hist.png", dpi=300)
plt.close()

i=0
q_circ = np.loadtxt("RNG_pairs.txt")
for x in q_circ:
  if x[0]**2 + x[1]**2 <=1:
    i += 1

print(i/10000)

x=np.linspace(0,1)
y=[np.sqrt(1-a**2) for a in x]
plt.plot(x,y,c='r',label='circle r=1')

plt.scatter([q[0] for q in q_circ], [q[1] for q in q_circ], s=2)
plt.title("RNG Distribution in 2D")
plt.ylabel("Y Value")
plt.xlabel("X Value")
plt.legend()
plt.savefig("RNG_circ.png", dpi=300)
plt.close()


# Plot at start of RNG sim
lst = np.loadtxt("start.txt")
x = [val[0] for val in lst]
y = [val[1] for val in lst]
plt.title("Positions at t = 0")
plt.scatter(x,y)
plt.savefig("0.png", dpi = 300)
plt.close()

# Plot at t = 1000 of RNG sim
lst = np.loadtxt("at_e3.txt")
x = [val[0] for val in lst]
y = [val[1] for val in lst]
plt.title("Positions at t = 1,000")
plt.xlabel("Nondimensionalized x Position")
plt.ylabel("Nondimensionalized y Position")
plt.scatter(x,y)
plt.savefig("1000.png", dpi = 300)
plt.close()

# Plot at t = 10000 of RNG sim
lst = np.loadtxt("at_e4.txt")
x = [val[0] for val in lst]
y = [val[1] for val in lst]
plt.title("Positions at t = 10,000")
plt.xlabel("Nondimensionalized x Position")
plt.ylabel("Nondimensionalized y Position")
plt.scatter(x,y)
plt.savefig("10000.png", dpi = 300)
plt.close()

# Plot at t = 100000 of RNG sim
lst = np.loadtxt("at_e5.txt")
x = [val[0] for val in lst]
y = [val[1] for val in lst]
plt.title("Positions at t = 100,000")
plt.xlabel("Nondimensionalized x Position")
plt.ylabel("Nondimensionalized y Position")
plt.scatter(x,y)
plt.savefig("100000.png", dpi = 300)
plt.close()

# Plot at t = 1000000 of RNG sim
lst = np.loadtxt("at_e6.txt")
x = [val[0] for val in lst]
y = [val[1] for val in lst]
plt.title("Positions at t = 1,000,000")
plt.xlabel("Nondimensionalized x Position")
plt.ylabel("Nondimensionalized y Position")
plt.scatter(x,y)
plt.savefig("1000000.png", dpi = 300)
plt.close()

# Plot of E wrt t
lst = np.loadtxt("Evals.txt")
x = [val[0] for val in lst]
y = [val[1] for val in lst]
plt.title("Energy vs steps")
plt.xlabel("Time Steps")
plt.ylabel("E")
plt.plot(x,y)
plt.savefig("E.png", dpi = 300)
plt.close()


# plot the potential
x = np.linspace(.9,2)
y = 4*((1/x)**6)*(((1/x)**6)-1)
plt.plot(x,y)
plt.title("Lennard-Jones Potential")
plt.xlabel("Non-Dimensionalized Length from Atom")
plt.xlabel("Non-Dimensionalized Energy")
plt.savefig("LJ.png", dpi=300)