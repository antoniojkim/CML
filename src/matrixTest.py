import numpy as np
import time

m1 = np.array([[1, 2, 3, 4, 5],
               [4, 5, 6, 7, 8],
               [7, 8, 9, 10, 11],
               [12, 13, 14, 15, 16],
               [17, 18, 19, 20, 21]])
m2 = np.array([[2, 7, 9, 3, 7],
               [4, 8, 3, 7, 5],
               [6, 3, 9, 3, 5],
               [3, 7, 3, 7, 4],
               [0, 4, 7, 5, 3]])

print(m1)
print(m2)
print(np.dot(m1, m2))


current_time_milli = lambda: int(round(time.time() * 1000))

start = current_time_milli()
for i in range(10000000):
    m = np.dot(m1, m2)
    # m[0][0] = 0

end = current_time_milli()

print("\nTook", (end-start)/1000.0, " seconds")
# 11.854
