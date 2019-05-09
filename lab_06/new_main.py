from math import e, log

a0, a1, a2 = 1, 2, 3
n = 11
h = 1

def f(x):
    return (a0 * x / (a1 + a2 * x))

def f_det(x):
    return (a0 * (a1 + a2 * x) - a0 * a2 * x) / ((a1 + a2 * x) ** 2)

def get_table(x_beg, step, amount):
    x_tbl = [x_beg + step * i for i in range(amount)]
    y_tbl = [f(x) for x in x_tbl]
    return x_tbl, y_tbl

def left_side_diff(y):
    res = [None for i in range(n)]
    for i in range(1, n):
        if not i:
            res[i] = None
        else:
            res[i] = (y[i] - y[i - 1]) / h
    return res

def center_diff(y):
    res = [None for i in range(n)]
    for i in range(1, n - 1):
        res[i] = (y[i + 1] - y[i - 1]) / (2 * h)
    return res

def edge_accuracy(y):
    n = len(y)
    a = [None for i in range(n)]
    a[0] = (-3 * y[0] + 4 * y[1] - y[2]) / (2 * h)
    a[n - 1] = (y[n - 3] - 4 * y[n - 2] + 3 * y[n - 1]) / (2 * h)
    return a

def Runge_left_side(y):
    n = len(y)
    p = 1
    res = [None for i in range(n)]

    yh = left_side_diff(y)
    y2h = [0]*n
    for i in range(0, n):
        if i < 2:
            y2h[i] = 0
        else:
            y2h[i] = (y[i] - y[i - 2]) / (2 * h)

    for i in range (0, n):
        if i < 2:
            res[i] = None
        else:
            res[i] = (yh[i] + (yh[i] - y2h[i]) / (2 ** p - 1))
    return res


def Runge_center(y):
    n = len(y)
    p = 2
    r = 2

    ksi_h = [(y[i + 1] - y[i - 1]) / (2 * h) for i in range(2, n - 2)]
    ksi_rh = [(y[i + r] - y[i - r]) / (2 * h * r) for i in range(2, n - 2)]

    # res = [None for i in range(n)]
    # for i in range(-2, n - 2):
    #     if i >= n - 4 or i < 0:
    #         res[i] = None
    #     else:
    #         res[i] = (ksi_h[i] + (ksi_h[i] - ksi_rh[i]) / (r ** p - 1))
    # return res

    return [None if i >= n - 4 or i < 0
            else (ksi_h[i] + (ksi_h[i] - ksi_rh[i]) / (r ** p - 1))
            for i in range(-2, n - 2)]

def aline(x, y):
    res = [None for i in range(n)]
    for i in range(len(x)):
        if x[i] == 0:
            res[i] = None
        else:
            res[i] = (a1 / a0) * (y[i] * y[i]) * (1 / (x[i] * x[i]))
            # (производная эта по кси) * (производная эта по у) * (производная кси по х)

    return res


def print_res_line(text, res):
    print("{:<20}".format(text), end="")
    for i in res:
        if (i != None):
            print("{: <15.4f}".format(i), end="")
        else:
            print("{: <15}".format("NULL"), end="")
    print()


x_start = 0
x, y = get_table(x_start, h, n)

print_res_line("x", x)
print_res_line("y", y)
print_res_line("y'", [f_det(i) for i in x])
print_res_line("Лев. разность", left_side_diff(y))
print_res_line("Центр. разность", center_diff(y))
print_res_line("Повыш. порядка", edge_accuracy(y))
print_res_line("Рунге (лев.)", Runge_left_side(y))
#print_res_line("Рунге (центр)", Runge_center(y))
print_res_line("Вырав. коэф.", aline(x, y))
