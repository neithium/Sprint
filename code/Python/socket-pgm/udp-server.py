import socket

HOST = "127.0.0.1"
PORT = 5000

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server.bind((HOST, PORT))

print("UDP server listening...")

while True:
    data, addr = server.recvfrom(1024)

    message = data.decode()

    print("Client:", message)

    if message.lower() == "bye":
        server.sendto(b"Goodbye!", addr)
        break

    response = "Server received: " + message

    server.sendto(response.encode(), addr)

server.close()