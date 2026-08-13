import socket

HOST = "127.0.0.1"
PORT = 5000

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    message = input("You: ")

    client.sendto(
        message.encode(),
        (HOST, PORT)
    )

    response, addr = client.recvfrom(1024)

    print("Server:", response.decode())

    if message.lower() == "bye":
        break

client.close()