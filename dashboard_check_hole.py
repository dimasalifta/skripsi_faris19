import tkinter as tk
import paho.mqtt.client as mqtt
import json

ip_broker = "103.150.93.184"
port_broker = 1883
topic = "skripsi_faris19"





# {
#   "R":255,
#   "G":255,
#   "B":255,
#   "Gas":60
# }
# print (defuzzyfikasi(60,60))
# Inisialisasi MQTT client
client = mqtt.Client()

# Fungsi callback ketika terhubung ke broker MQTT
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    # Subscribe ke topik yang diinginkan
    client.subscribe(topic)

# Fungsi callback ketika pesan diterima
def on_message(client, userdata, msg):
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
    # Menampilkan pesan di GUI
    data = json.loads(msg.payload)
    rR = data["R"]
    rG = data["G"]
    rB = data["B"]
    GAS = data["Gas"]
    Amonia = 0.0
    Humidity = 0.0
    
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
        A = 0.00
        B = 0.00
        for i in range(1, 10):
            print("Rule ke", i, "=", Rule[i])
            print("Min ke", i, "=", minr[i])
            A += Rule[i] * minr[i]
            B += minr[i]
        print("Hasil A :", A)
        print("Hasil B :", B)
        return A or B
    
    Amonia = GAS
    Humidity = 90
    
    FUZZY = defuzzyfikasi()
    
    if FUZZY >= 0 and FUZZY < 0.5:
        HASIL = "Belum Matang"
    elif FUZZY >= 0.5 and FUZZY < 0.8:
        HASIL = "Matang"
    elif FUZZY >= 0.8:
        HASIL = "BUSUK"

    labelR.config(text="Nilai R: " + str(rR))
    labelG.config(text="Nilai G: " + str(rG))
    labelB.config(text="Nilai B: " + str(rB))
    labelGas.config(text="Nilai Gas: " + str(GAS) + " ppm")
    labelFuzzy.config(text="Nilai Fuzzy: " + str(FUZZY))
    labelHasil.config(text="Hasil: " + str(HASIL))

    hex_color = '#{:02x}{:02x}{:02x}'.format(rR, rG, rB)
    color_label.config(text=HASIL, bg=hex_color ,fg="white",font=("Arial", 50))

# Membuat GUI menggunakan tkinter
root = tk.Tk()
root.title("Dashboard Faris 2019")
root.geometry("640x480")

# Membuat frame untuk menampilkan nilai R, G, dan B
frameRGB = tk.LabelFrame(root, text="RGB dan Gas", padx=30, pady=10)
frameFUZZY = tk.LabelFrame(root, text="Fuzzy Logic", padx=30, pady=10)
frameRGB.pack(anchor=tk.NW)
frameFUZZY.pack(anchor=tk.NW)


# Membuat label untuk menampilkan pesan
labelR = tk.Label(frameRGB, text="Nilai R: ")
labelG = tk.Label(frameRGB, text="Nilai G: ")
labelB = tk.Label(frameRGB, text="Nilai B: ")
labelGas = tk.Label(frameRGB, text="Nilai Gas: ")
labelFuzzy = tk.Label(frameFUZZY, text="Nilai Fuzzy: ")
labelHasil = tk.Label(frameFUZZY, text="Hasil: ")
color_label = tk.Label(root, text="", width=10, height=10)

labelR.pack(anchor=tk.NW)
labelG.pack(anchor=tk.NW)
labelB.pack(anchor=tk.NW)
labelGas.pack(anchor=tk.NW)
labelFuzzy.pack(anchor=tk.NW, padx=20, pady=10)
labelHasil.pack(anchor=tk.NW, padx=20, pady=10)
color_label.pack(pady=10)


# Menjalankan MQTT client
client.on_connect = on_connect
client.on_message = on_message
client.connect(ip_broker, port_broker, 60)

# Memulai loop MQTT client
client.loop_start()

# Memulai GUI loop
root.mainloop()
