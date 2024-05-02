import socket
import time

def send_data(ip, port, data):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((ip, port))
        s.sendall(data.encode())
        print(f"Sent data to {ip}:{port}")

if __name__ == "__main__":
    server_ip = "127.0.0.1"  # Remplacez ceci par l'adresse IP de votre serveur
    server_port = 4241  # Remplacez ceci par le port sur lequel votre serveur écoute

    while True:
        message = input("Enter message to send (type 'exit' to quit): ")
        if message.lower() == "exit":
            break
        send_data(server_ip, server_port, message)
        time.sleep(1)  # Attendez 1 seconde entre chaque envoi
