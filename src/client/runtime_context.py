class Context:
    def __init__(self):
        self.compiled = False
        self.debug = False
        self.client_running = True

    def set_compiled(self, compiled):
        self.compiled = compiled

    def set_debug(self, debug):
        self.debug = debug

    def set_client_running(self, running):
        self.client_running = running

instance = Context()
