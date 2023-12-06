import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

race_time = 15  # Total time for the race in milliseconds
record_distance = 40  # Record distance in millimeters

# Calculate distances for different hold times
hold_times = np.arange(0, race_time)
distances = hold_times * (race_time - hold_times)

# Set up the figure and axis
fig, ax = plt.subplots()
line, = ax.plot([], [], lw=3)
ax.set_xlim(0, race_time)
ax.set_ylim(0, max(distances) + 10)
ax.set_xlabel('Hold Time (ms)')
ax.set_ylabel('Distance (mm)')
ax.axhline(y=record_distance, color='r', linestyle='--')
ax.text(0.5, record_distance + 2, f'Record Distance: {record_distance} mm', color='r')

def init():
    line.set_data([], [])
    return line,

# Animation function
def animate(i):
    x = hold_times[:i]
    y = distances[:i]
    line.set_data(x, y)
    return line,

# Create animation
ani = FuncAnimation(fig, animate, frames=len(hold_times), init_func=init, blit=True, interval=100)

plt.title('Boat Race Distance vs Hold Time')
plt.show()
