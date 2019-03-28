import matplotlib.pyplot as plt
import numpy as np


def calculate_rms(x, y, p, n):
    sum_x_n = []
    t = 0
    for j in range (n * 2 - 1):
        for i in range (len(x)):
            t += x[i] ** j * p[i]
        sum_x_n.append(t)
        t = 0

    sum_y_x_n = []
    t = 0
    for j in range (n):
        for i in range (len(x)):
            t += x[i] ** j * p[i] * y[i]
        sum_y_x_n.append(t)
        t = 0

    mtrx = []
    for i in range(n):
        mtrx.append(sum_x_n[i:i + n])

    for i in range(n):
        mtrx[i].append(sum_y_x_n[i])

    for i in mtrx:
        print(i)

    a = Gauss(mtrx)
    return a

def Gauss(mtrx):
    n = len(mtrx)
    # приводим к треугольному виду
    for k in range(n):
        for i in range(k + 1, n):
            coeff = -(mtrx[i][k] / mtrx[k][k])
            for j in range(k, n + 1):
                mtrx[i][j] += coeff * mtrx[k][j]
    print("\ntriangled:")
    for i in mtrx:
        print(i)
    # находим неизвестные
    a = [0 for i in range(n)]
    for i in range(n - 1, -1, -1):
        for j in range(n - 1, i, -1):
            mtrx[i][n] -= a[j] * mtrx[i][j]
        a[i] = mtrx[i][n] / mtrx[i][i]
    return a


# def f(x_arr, coeff):
#     res = np.zeros(len(x_arr))
#     for i in range(len(coeff)):
#         res += coeff[i] * (x_arr ** i)
#     return res


def show(a):
    t = np.arange(-1.0, 5.0, 0.02)
    plt.figure(1)
    plt.ylabel("y")
    plt.xlabel("x")
    res = np.zeros(len(t))
    for i in range(len(a)):
        res += a[i] * (t ** i)
    plt.plot(t, res, 'k')
    for i in range(len(x)):
        plt.plot(x[i], y[i], 'ro')
    plt.show()


f = open("data2.txt", "r")
x, y, ro = [], [], []
for arr in f:
    arr = arr.split(" ")
    x.append(float(arr[0]))
    y.append(float(arr[1]))
    ro.append(float(arr[2]))

n = 0

length = len(x)
print("x    y    p")
for i in range(length):
    print("%.2f %.2f %.2f" % (x[i], y[i], ro[i]))

a = calculate_rms(x, y, ro, n + 1)

print("\na:", a)

show(a)

