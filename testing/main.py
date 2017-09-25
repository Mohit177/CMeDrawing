import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('data.txt', header=None)

plt.figure(1)
ax = plt.gca()
ax.plot(df[df.columns[0]], df[df.columns[1]])

plt.figure(2)
ax = plt.gca()
ax.plot(df[df.columns[0]], df[df.columns[2]])

plt.show()