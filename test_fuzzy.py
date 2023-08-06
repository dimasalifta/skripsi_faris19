Amonia = 0.0
Humidity = 0.0
A = 0.0
B = 0.0
uNormal = [0, 0, 20, 30]
uSedang = [20, 30, 50, 60]
uTinggi = [50, 60, 80, 80]
uKering = [0, 0, 25, 45]
uLembab = [25, 45, 65, 85]
uBasah = [65, 85, 100, 100]
Aman = 0.0
Waspada = 0.5
Bahaya = 1.0
minr = [0.0] * 10
Rule = [0.0] * 10

def fuNormal():
    if Amonia < uNormal[1]:
        return 1
    elif Amonia >= uNormal[1] and Amonia <= uNormal[2]:
        return (uNormal[2] - Amonia) / (uNormal[2] - uNormal[1])
    elif Amonia > uNormal[2]:
        return 0
    return 0  # Default return when no condition is met

def fuSedang():
    if Amonia <= uSedang[0]:
        return 0
    elif Amonia >= uSedang[0] and Amonia <= uSedang[1]:
        return (Amonia - uSedang[0]) / (uSedang[1] - uSedang[0])
    elif Amonia > uSedang[1] and Amonia <= uSedang[2]:
        return 1
    elif Amonia > uSedang[3]:
        return (uSedang[3] - Amonia) / (uSedang[3] - uSedang[2])
    return 0  # Default return when no condition is met

def fuTinggi():
    if Amonia <= uTinggi[0]:
        return 0
    elif Amonia >= uTinggi[0] and Amonia <= uTinggi[1]:
        return (Amonia - uTinggi[0]) / (uTinggi[1] - uTinggi[0])
    elif Amonia > uTinggi[1]:
        return 1
    return 0  # Default return when no condition is met

def fuKering():
    if Humidity < uKering[1]:
        return 1
    elif Humidity >= uKering[1] and Humidity <= uKering[2]:
        return (uKering[2] - Humidity) / (uKering[2] - uKering[1])
    elif Humidity > uKering[2]:
        return 0
    return 0  # Default return when no condition is met

def fuLembab():
    if Humidity <= uLembab[0]:
        return 0
    elif Humidity >= uLembab[0] and Humidity <= uLembab[1]:
        return (Humidity - uLembab[0]) / (uLembab[1] - uLembab[0])
    elif Humidity >= uLembab[1] and Humidity <= uLembab[2]:
        return 1
    elif Humidity > uLembab[3]:
        return (uLembab[3] - Humidity) / (uLembab[3] - uLembab[2])
    return 0  # Default return when no condition is met

def fuBasah():
    if Humidity <= uBasah[0]:
        return 0
    elif Humidity >= uBasah[0] and Humidity <= uBasah[1]:
        return (Humidity - uBasah[0]) / (uBasah[1] - uBasah[0])
    elif Humidity > uBasah[1]:
        return 1
    return 0  # Default return when no condition is met

def Min(a, b):
    if a < b:
        return a
    elif b < a:
        return b
    else:
        return a

def rule():
    # if Amonia Normal and Humidity Kering then Aman
    minr[1] = Min(fuNormal(), fuKering())
    Rule[1] = Aman
    # if Amonia Normal and Humidity Lembab then Aman
    minr[2] = Min(fuNormal(), fuLembab())
    Rule[2] = Aman
    # if Amonia Sedang and Humidity Kering then Aman
    minr[3] = Min(fuSedang(), fuKering())
    Rule[3] = Aman
    # if Amonia Normal and Humidity Basah then Waspada
    minr[4] = Min(fuNormal(), fuBasah())
    Rule[4] = Waspada
    # if Amonia Sedang and Humidity Lembab then Waspada
    minr[5] = Min(fuSedang(), fuLembab())
    Rule[5] = Waspada
    # if Amonia Tinggi and Humidity Kering then Waspada
    minr[6] = Min(fuTinggi(), fuKering())
    Rule[6] = Waspada
    # if Amonia Sedang and Humidity Basah then Bahaya
    minr[7] = Min(fuSedang(), fuBasah())
    Rule[7] = Bahaya
    # if Amonia Tinggi and Humidity Lembab then Bahaya
    minr[8] = Min(fuTinggi(), fuLembab())
    Rule[8] = Bahaya
    # if Amonia Tinggi and Humidity Lembab then Bahaya
    minr[9] = Min(fuTinggi(), fuLembab())
    Rule[9] = Bahaya

def defuzzyfikasi():
    rule()
    A = 0.0
    B = 0.0
    for i in range(1, 10):
        print("Rule ke", i, "=", Rule[i])
        print("Min ke", i, "=", minr[i])
        A += Rule[i] * minr[i]
        B += minr[i]
    print("Hasil A :", A)
    print("Hasil B :", B)
    return A / B


Amonia = 60
Humidity = 60

print (defuzzyfikasi())