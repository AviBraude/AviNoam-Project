import socket
import sys
import os


#######################
### Message Related ###
#######################

def hello(sock):
    send_from = 0
    sock.send(b'Hello')
    message = sock.recv(5).decode("ASCII")
    if (message == 'Hello'):
        cprint("Hello message received successfully", "green", "black")
    else:
        cprint("Received wrong message, expected 'Hello' but received '" + str(message) + "'", "red", "black")
    exit()


#####################
### Error Related ###
#####################

def print_error_message(err_msg):
    cprint(err_msg, "red", "black")
    os.system('pause')


def connection_error_message():
    print_error_message("Could not connect to the server,\nplease check if the server is accepting connections")


def wrong_option_error():
    print_error_message("wrong choice, please select a valid option")


def port_error_message():
    print_error_message("wrong port number, port number should be 1024-65535")


#######################
### Display Related ###
#######################

# copied from https://pypi.org/project/colorama/
from colorama import init, Fore, Back, Style

init()


def cprint(msg, foreground="black", background="white"):
    fground = foreground.upper()
    bground = background.upper()
    style = getattr(Fore, fground) + getattr(Back, bground)
    print(style + msg + Style.RESET_ALL)


####################
### Menu Related ###
####################

def intro_screen():
    print("\n"
          + " __  __  __  _  _  __    _      __  __  __  __  __  __  \n"
          + "(_  )(  _ \(  )( \/ )(  )  /\    (  )( _)/ _)(_  )( __)(  _ \ \n"
          + "  )(   )   / )(  \  /  )(  /(_)\     )(   )) \_ \  )(   )__)  )   / \n"
          + " (_) ()\)(_)  \/  (_)()()   () (_)(_/ (_) (_)()\) \n\n"
          + "                                                                     V1.0.1 \n")


try:
    os.system('cls')
    #intro_screen()

    # get port number
    port = input("Enter the server port number: ")
    if int(port) < 1024 or int(port) > 65535:
        raise ValueError
    print("\ntrying to connect...\n")

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', int(port)))
    print("\nSending \'Hello\' to client...\n")
    hello(client_socket)

except TypeError:
    wrong_option_error()

except ValueError:
    port_error_message()

except ConnectionRefusedError:
    connection_error_message()