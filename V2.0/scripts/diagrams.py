import pandas as pd
import matplotlib.pyplot as plt
import matplotlib


#prints a diagram as a png file for a specific grid size

# Use the Agg backend for non-GUI environments
matplotlib.use('Agg')

# Load data
df = pd.read_csv("/root/Project-1/V2.0/output/execution_times.csv")

# Filter data for a specific grid size
subset = df[df["L_small"] == 160] 
df = pd.read_csv("/root/Project-1/V2.0/Optimized_times.csv")
subset2 = df[df["L_small"] == 160]

# Group by Num_Threads and calculate the mean Execution_Time
summary = subset.groupby("thread_num")["Execution_time"].mean()
summary2 = subset2.groupby("thread_num")["Execution_time"].mean()

# Plot the summarized execution time vs. number of threads
plt.plot(summary.index, summary.values, marker='o', label="Simple_Filtered_Vamana", color = 'blue')
plt.plot(summary2.index, summary2.values, marker='s', label="Optimized_Filtered_Vamana", color='red')
plt.xlabel("Number of Threads")
plt.ylabel("Mean Execution Time (seconds)")
plt.title("Execution Time for Dummy Data (Size=10000)")
plt.grid()
plt.legend()

# Save the plot as a PNG file
plt.savefig("execution_time_plot.png")