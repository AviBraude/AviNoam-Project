import socket
PORT = 8820
IP = "127.0.0.1"


def main():
    # Open a socket and loop forever while waiting for clients
    my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    my_socket.connect((IP,PORT))
    # for i in range(10):

    msg = "hello"
    print("sending: "+msg)

    try:

        my_socket.send(msg.encode())
        msg = my_socket.recv(10)
        print("received: "+msg.decode())
    except :
        print("error with handling sockets")
    my_socket.close()


    # client_socket.settimeout(SOCKET_TIMEOUT)
    # handle_client(client_socket)


if __name__ == "__main__":
    # Call the main handler function
    main()