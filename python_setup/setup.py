import tkinter as tk
import socket

def send_data():
    ip = entry_ip.get()
    port = int(entry_port.get())
    data = entry_data.get()

    try:
        # Socket-Verbindung herstellen
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((ip, port))

        # Daten senden
        client_socket.send(data.encode())

        # Verbindung schließen
        client_socket.close()

        # Erfolgsmeldung anzeigen
        messagebox.showinfo("Erfolg", "Daten erfolgreich gesendet!")
    except Exception as e:
        # Fehlermeldung anzeigen
        messagebox.showerror("Fehler", str(e))

# Erstellen des Hauptfensters
window = tk.Tk()
window.title("Daten an IP senden")

# IP-Eingabefeld
label_ip = tk.Label(window, text="IP-Adresse:")
label_ip.pack()
entry_ip = tk.Entry(window)
entry_ip.pack()

# Port-Eingabefeld
label_port = tk.Label(window, text="Port:")
label_port.pack()
entry_port = tk.Entry(window)
entry_port.pack()

# Daten-Eingabefeld
label_data = tk.Label(window, text="Daten:")
label_data.pack()
entry_data = tk.Entry(window)
entry_data.pack()

# Senden-Button
button_send = tk.Button(window, text="Senden", command=send_data)
button_send.pack()

# Schleife zum Aktualisieren des Fensters
window.mainloop()
