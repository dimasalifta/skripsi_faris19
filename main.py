import paho.mqtt.client as mqtt
import time
import json
import tkinter as tk

ip_broker = "digitalasistensi.com"
port_broker = 1883
topic = "skripsi_faris19"

def generate_color(R,G,B):
    # Convert RGB values to hexadecimal
    hex_color = '#{:02x}{:02x}{:02x}'.format(R, G, B)
    
    # Update label text and background color
    color_label.config(text=hex_color, bg=hex_color)

def print_timestamp():
    print("Timestamps:", time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
    
    
# fungsi callback untuk saat koneksi berhasil
def on_connect(client, userdata, flags, rc):
    print("Connected to broker "+ ip_broker +" with result code "+str(rc))
    client.subscribe(topic)
    
# fungsi callback untuk saat pesan diterima
def on_message(client, userdata, msg):
    # print(msg.topic+" "+str(msg.payload))
    try:
        data = json.loads(msg.payload)
        ## akses nilai tertentu dalam data JSON
        R = data["R"]
        G = data["G"]
        B = data["B"]
        print(str(R),str(G),str(B))
        generate_color(R,G,B)
    except Exception as e:
        print(f"ERROR ON MESSAGE: {e}")
def show_payload():
    payload = "Ini adalah payload"
    payload_label.configure(text=payload)

# Create the main window
window = tk.Tk()
window.title("Generate RGB Color")
window.geometry("200x100")

# Create a label to display the generated color
color_label = tk.Label(window, text="", width=20, height=5)
color_label.pack()
# Membuat label untuk menampilkan payload
payload_label = tk.Label(window, text="Klik tombol untuk menampilkan payload", font=("Helvetica", 14))
payload_label.pack(pady=50)


# Create a button to generate a new color
generate_button = tk.Button(window, text="Generate Color", command=generate_color)
generate_button.pack()


show_payload()
# generate_color(255,0,236    )

# inisialisasi klien MQTT
client = mqtt.Client()

# set fungsi callback
client.on_connect = on_connect

client.on_message = on_message

# koneksi ke broker MQTT pada alamat localhost
client.connect(ip_broker, port_broker)

# loop forever untuk menerima pesan
client.loop_forever()
# Run the Tkinter event loop
window.mainloop()