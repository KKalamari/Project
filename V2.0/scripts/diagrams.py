import pandas as pd
import matplotlib.pyplot as plt
import matplotlib


#prints a diagram as a png file for a specific grid size

# Use the Agg backend for non-GUI environments
matplotlib.use('Agg')

# Load data
df = pd.read_csv("/root/Project-1/V2.0/output/execution_times.csv")

# Filter data for a specific grid size
subset = df[df["Data_Dimensions"] == 40000] 

# Group by Num_Threads and calculate the mean Execution_Time
summary = subset.groupby("thread_num")["Execution_time"].mean()

# Plot the summarized execution time vs. number of threads
plt.plot(summary.index, summary.values, marker='o', label="Data Size = 40000")
plt.xlabel("Number of Threads")
plt.ylabel("Mean Execution Time (seconds)")
plt.title("Execution Time for Dummy Data (Size=40000)")
plt.grid()
plt.legend()

# Save the plot as a PNG file
plt.savefig("execution_time_plot.png")