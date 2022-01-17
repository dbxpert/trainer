import socket
import time
from config import get_config
from runtime_context import instance as context

def raise_server_disconnected_error():
    context.set_server_connected(False)
    raise Exception("Server is disconnected")

def get_msg_length(socket):
    received = socket.recv(4)
    len = int.from_bytes(received, byteorder="little", signed=True)
    return len

class Communicator:
    def __init__(self):
        cfg = get_config()
        self.host = cfg["HOST"]["HOST"]
        self.port = int(cfg["PORT"]["PORT_NUMBER"])

    def connect(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        if not context.server_running:
            raise Exception("Server is not running")

        sleep_count = 0
        while self.socket.connect_ex((self.host, self.port)) != 0:
            if sleep_count > 10:
                raise_server_disconnected_error()
            sleep_count = sleep_count + 1
            time.sleep(1)

        context.set_server_connected(True)

    def close(self):
        self.send_message("TERMINATE")
        self.socket.close()
        context.set_server_connected(False)

    def send_message(self, message):
        buf = bytes(message, encoding="utf-8")
        msg_length = len(buf)
        total_sent = 0
        while total_sent < msg_length:
            sent = self.socket.send(buf[total_sent:])
            if sent == 0:
                raise_server_disconnected_error()
            total_sent = total_sent + sent

    def recv_message(self):
        chunks = []
        msg_length = get_msg_length(self.socket)
        total_received = 0
        max_msg_len = 1024

        while total_received < msg_length:
            msg = self.socket.recv(min(msg_length, max_msg_len))
            if msg == b'':
                raise_server_disconnected_error()

            chunks.append(msg)
            total_received = total_received + len(msg)

        return b''.join(chunks)

instance = Communicator()
