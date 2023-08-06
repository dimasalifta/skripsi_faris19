import tkinter as tk
import random

def generate_color():
    # Generate random RGB values
    red = random.randint(0, 255)
    green = random.randint(0, 255)
    blue = random.randint(0, 255)
    
    # Convert RGB values to hexadecimal
    hex_color = '#{:02x}{:02x}{:02x}'.format(red, green, blue)
    
    # Update label text and background color
    color_label.config(text=hex_color, bg=hex_color)

# Create the main window
window = tk.Tk()
window.title("Generate RGB Color")
window.geometry("200x100")

# Create a label to display the generated color
color_label = tk.Label(window, text="", width=20, height=5)
color_label.pack()

# # Create a button to generate a new color
# generate_button = tk.Button(window, text="Generate Color", command=generate_color)
# generate_button.pack()
generate_color()

# Run the Tkinter event loop
window.mainloop()
