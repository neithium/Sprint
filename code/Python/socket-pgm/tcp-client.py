import socket

HOST = "127.0.0.1"
PORT = 5000

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect((HOST, PORT))

while True:
    message = input("You: ")

    client.sendall(message.encode())

    response = client.recv(1024)

    print("Server:", response.decode())

    if message.lower() == "bye":
        break

client.close()