class Context:
    def __init__(self):
        self.complied = False
        self.debug = False
        self.client_running = True
        self.server_running = False
        self.server_connected = False

    def set_compiled(self, compiled):
        self.compiled = compiled

    def set_debug(self, debug):
        self.debug = debug

    def set_client_running(self, running):
        self.client_running = running

    def set_server_running(self, running):
        self.server_running = running

    def set_server_connected(self, connected):
        self.server_connected = connected

instance = Context()
