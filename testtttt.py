import tkinter as tk
import paho.mqtt.client as mqtt
import json
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

ip_broker = "103.150.93.184"
port_broker = 1883
topic = "skripsi_faris19"


# Inisialisasi MQTT client
client = mqtt.Client()

# Fungsi callback ketika terhubung ke broker MQTT
def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    # Subscribe ke topik yang diinginkan
    client.subscribe(topic)

# Fungsi callback ketika pesan diterima
def on_message(client, userdata, msg):
    # Menampilkan pesan di GUI
    data = json.loads(msg.payload)
    ## akses nilai tertentu dalam data JSON
    R = data["R"]
    G = data["G"]
    B = data["B"]
    GAS = data["Gas"]
   
    FUZZY = 0.5
    HASIL = "matang"
    
     # Convert RGB values to hexadecimal
    hex_color = '#{:02x}{:02x}{:02x}'.format(R, G, B)
    print(hex_color)
    # pesan = msg.payload.decode()
    labelR.config(text="Nilai R: " + str(R))
    labelG.config(text="Nilai G: " + str(G))
    labelB.config(text="Nilai B: " + str(B))
    labelGas.config(text="Nilai Gas: " + str(GAS) +" ppm")
    labelFuzzy.config(text="Nilai Fuzzy: " + str(FUZZY))
    labelHasil.config(text="Hasil: " + HASIL)
    # Update label text and background color
    color_label.config(text=hex_color, bg=hex_color, font=("Arial", 20))
    
    

# Membuat GUI menggunakan tkinter
root = tk.Tk()
root.title("Dashboard Faris 2019")
root.geometry("640x480")

# Membuat label untuk menampilkan pesan
labelR = tk.Label(root, text="Nilai R: ",bg="red", fg="white")
labelG = tk.Label(root, text="Nilai G: ",bg="green", fg="white")
labelB = tk.Label(root, text="Nilai B: ",bg="blue", fg="white")
labelGas = tk.Label(root, text="Nilai Gas: ")
labelFuzzy = tk.Label(root, text="Nilai Fuzzy: ")
labelHasil = tk.Label(root, text="Hasil: ")
color_label = tk.Label(root, text="", width=50, height=50)
labelR.config(font=("Arial", 20)) 
labelG.config(font=("Arial", 20)) 
labelB.config(font=("Arial", 20)) 
labelGas.config(font=("Arial", 20)) 
labelFuzzy.config(font=("Arial", 20)) 
labelHasil.config(font=("Arial", 20)) 

labelR.pack(anchor=tk.NW, padx = 20, pady = 20)
labelG.pack(anchor=tk.NW, padx = 20, pady = 20)
labelB.pack(anchor=tk.NW, padx = 20, pady = 20)
labelGas.pack(anchor=tk.NW, padx = 20, pady = 20)
labelFuzzy.pack(anchor=tk.NW, padx = 20, pady = 20)
labelHasil.pack(anchor=tk.CENTER, padx = 20, pady = 0)
color_label.pack()


# Menjalankan MQTT client
client.on_connect = on_connect



client.on_message = on_message
client.connect(ip_broker, port_broker, 60)

# Memulai loop MQTT client
client.loop_start()

# Memulai GUI loop
root.mainloop()