import customtkinter as ctk
import paho.mqtt.client as mqtt

# Fungsi callback ketika terhubung ke broker
def on_connect(client, userdata, flags, rc):
    print("Terhubung dengan kode hasil: " + str(rc))
    client.subscribe("skripsi_faris19")  # Ganti dengan topik yang Anda inginkan

# Fungsi callback ketika pesan diterima
def on_message(client, userdata, msg):
    payload = msg.payload.decode('utf-8')
    print(f"Pesan diterima: {payload}")
    # Memperbarui label dengan payload yang diterima
    label.config(text=f"Pesan: {payload}")

# Inisialisasi client MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Hubungkan ke broker MQTT
client.connect("digitalasistensi.com", 1883, 60)  # Ganti dengan alamat broker Anda

# Inisialisasi aplikasi customtkinter
app = ctk.CTk()
app.title("MQTT Receiver")
app.geometry("400x200")

# Label untuk menampilkan pesan
label = ctk.CTkLabel(app, text="Menunggu pesan...")
label.pack(pady=20)

# Fungsi untuk menjalankan loop MQTT
def run_mqtt():
    client.loop_start()

# Tombol untuk memulai menerima pesan
start_button = ctk.CTkButton(app, text="Mulai", command=run_mqtt)
start_button.pack(pady=10)

# Menjalankan aplikasi
app.mainloop()
