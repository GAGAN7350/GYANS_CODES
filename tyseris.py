from numpy import array, zeros, exp

def taylor(deriv, x, y, xStop, h):
    X = []
    Y = []
    X.append(x)
    Y.append(y[0])  # Assuming scalar y

    while x < xStop:
        D = deriv(x, y) 
        H = 1.0
        for j in range(3):  # Build Taylor series up to 3rd order
            H = H * h / (j + 1)
            y[0] = y[0] + D[j][0] * H  # y is updated in-place

        x = x + h
        X.append(x)
        Y.append(y[0])

    return array(X), array(Y)

def deriv(x, y):
    D = zeros((4, 1))  # Derivatives y', y'', y''', y''''
    D[0][0] = 2 * y[0] + 3 * exp(x)
    D[1][0] = 4 * y[0] + 9 * exp(x)
    D[2][0] = 8 * y[0] + 21 * exp(x)
    D[3][0] = 16 * y[0] + 45 * exp(x)
    return D

# Initial conditions
x = 0.0
xStop = 0.3
y = array([0.0])  # Initial y
h = 0.1  # Step size

X, Y = taylor(deriv, x, y, xStop, h)

# Print results
print("The required values are:")
for i in range(len(X)):
    print(f"x = {X[i]:.2f}, y = {Y[i]:.5f}") 