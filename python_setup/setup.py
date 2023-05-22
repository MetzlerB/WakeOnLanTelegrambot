import tkinter as tk
import socket

DEFAULT_IP = "192.168.0.1"  # Standard-IP-Adresse
DEFAULT_PORT = "1234"  # Standard-Port

def send_data():
    ip = entry_ip.get() or DEFAULT_IP  # Verwende die eingegebene IP-Adresse oder den Standardwert
    port = int(entry_port.get() or DEFAULT_PORT)  # Verwende die eingegebene Portnummer oder den Standardwert
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
entry_ip.insert(0, DEFAULT_IP)  # Einfügen des Standardwerts

# Grauer Hinweistext für den Standardwert der IP-Adresse
entry_ip.config(fg="grey")
entry_ip.bind("<FocusIn>", lambda event: on_entry_click(event, entry_ip, DEFAULT_IP))
entry_ip.bind("<FocusOut>", lambda event: on_focus_out(event, entry_ip, DEFAULT_IP))

def on_entry_click(event, entry, default_value):
    if entry.get() == default_value:
        entry.delete(0, "end")
        entry.config(fg="black")

def on_focus_out(event, entry, default_value):
    if entry.get() == "":
        entry.insert(0, default_value)
        entry.config(fg="grey")

# Port-Eingabefeld
label_port = tk.Label(window, text="Port:")
label_port.pack()

entry_port = tk.Entry(window)
entry_port.pack()
entry_port.insert(0, DEFAULT_PORT)  # Einfügen des Standardwerts

# Grauer Hinweistext für den Standardwert des Ports
entry_port.config(fg="grey")
entry_port.bind("<FocusIn>", lambda event: on_entry_click(event, entry_port, DEFAULT_PORT))
entry_port.bind("<FocusOut>", lambda event: on_focus_out(event, entry_port, DEFAULT_PORT))

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