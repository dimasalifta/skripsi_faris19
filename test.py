import tkinter as tk
import paho.mqtt.client as mqtt
import random

# Fungsi yang dipanggil saat koneksi MQTT berhasil
def on_connect(client, userdata, flags, rc):
    print("Terhubung dengan broker MQTT")
    client.subscribe("skripsi/faris19")

# Fungsi yang dipanggil saat ada pesan masuk di topik yang di-subscribe
def on_message(client, userdata, msg):
    payload = msg.payload.decode("utf-8")
    payload_label.configure(text=payload)
    generate_rgb()

# Fungsi untuk menghasilkan warna RGB acak dan memperbarui kotak warna
def generate_rgb():
    r = random.randint(0, 255)
    g = random.randint(0, 255)
    b = random.randint(0, 255)
    rgb_value = f"#{r:02x}{g:02x}{b:02x}"
    color_box.configure(bg=rgb_value)

# Membuat klien MQTT
mqtt_client = mqtt.Client()

# Mengatur callback fungsi
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

# Menghubungkan dengan broker MQTT
mqtt_client.connect("103.150.93.184", 1883, 60)

# Membuat jendela utama
window = tk.Tk()
window.title("Aplikasi Payload MQTT")
window.geometry("400x300")

# Membuat kotak warna
color_box = tk.Label(window, width=100, height=10)
color_box.pack(pady=50)

# Membuat label untuk menampilkan payload
payload_label = tk.Label(window, text="Menunggu payload...", font=("Helvetica", 14))
payload_label.pack()

# Looping untuk menerima pesan MQTT
mqtt_client.loop_start()

# Menjalankan aplikasi
window.mainloop()

# Menghentikan koneksi MQTT setelah aplikasi ditutup
mqtt_client.loop_stop()
mqtt_client.disconnect()
