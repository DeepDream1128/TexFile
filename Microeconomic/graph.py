import numpy as np
import matplotlib.pyplot as plt

# Define functions
def budget_line(M, p1, p2, x1):
    return (M - p1 * x1) / p2

def indifference_curve(u, x1):
    return u - np.sqrt(x1)

# Define parameters
x1 = np.linspace(0.01, 2, num=100)
M1, M2 = 1, 2
p1, p2 = 1, 1
u1 = np.sqrt(p1**2 / 4) + M1 - p1**2 / 4
u2 = np.sqrt(p1**2 / 4) + M2 - p1**2 / 4

# Create plot
fig, ax = plt.subplots(figsize=(10,7))
ax.plot(x1, budget_line(M1, p1, p2, x1), label='Budget Line (M=1)')
ax.plot(x1, budget_line(M2, p1, p2, x1), label='Budget Line (M=2)')
ax.plot(x1, indifference_curve(u1, x1), '--', label='Indifference Curve (M=1)')
ax.plot(x1, indifference_curve(u2, x1), '--', label='Indifference Curve (M=2)')
ax.plot(p1**2 / 4, M1 - p1**3 / 4, 'ro', label='Optimal Bundle (M=1)')
ax.plot(p1**2 / 4, M2 - p1**3 / 4, 'bo', label='Optimal Bundle (M=2)')
ax.set_xlabel('Quantity of Good 1')
ax.set_ylabel('Quantity of Good 2')
ax.legend()
ax.grid(True)
plt.title('Budget bundles and indifference curves')
plt.savefig('graph.png')
plt.show()
