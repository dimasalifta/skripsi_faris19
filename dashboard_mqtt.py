import tkinter as tk
import paho.mqtt.client as mqtt

# Fungsi untuk mengirim pesan
def publish_message():
    topic = topic_entry.get()
    message = message_entry.get()
    client.publish(topic, message)

# Fungsi untuk menerima pesan
def on_message(client, userdata, msg):
    received_message.config(text=msg.payload.decode())

# Inisialisasi klien MQTT
client = mqtt.Client()

# Konfigurasi callback untuk menerima pesan
client.on_message = on_message

# Konfigurasi broker MQTT
broker_address = "103.150.93.184"
broker_port = 1883

# Koneksi ke broker MQTT
client.connect(broker_address, broker_port)

# Membuat GUI menggunakan Tkinter
window = tk.Tk()
window.title("MQTT Dashboard")

# Label dan Entry untuk memasukkan topik
topic_label = tk.Label(window, text="Topic:")
topic_label.pack()
topic_entry = tk.Entry(window)
topic_entry.pack()

# Label dan Entry untuk memasukkan pesan
message_label = tk.Label(window, text="Message:")
message_label.pack()
message_entry = tk.Entry(window)
message_entry.pack()

# Tombol untuk mengirim pesan
send_button = tk.Button(window, text="Publish", command=publish_message)
send_button.pack()

# Label untuk menampilkan pesan yang diterima
received_message = tk.Label(window, text="")
received_message.pack()

# Mengatur agar klien MQTT menerima pesan secara asinkron
client.loop_start()

# Menjalankan aplikasi GUI
window.mainloop()

# Saat aplikasi ditutup, menghentikan klien MQTT
client.loop_stop()
client.disconnect()
