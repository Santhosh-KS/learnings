import socket

class Server:
    '''
     Ip: Ip address of the server.
     Port: Port on which server will be listening on.
     Flag to indecate if the socket should be open for ever
     or limit it for only one connection.
     RunOnce = True -> Stop on one connection.
     RunOnce = False -> Keep the socket open as long as program runs.

    '''
    def __init__(self, ip, port, loop=False):
        self.Ip = ip
        self.Port = port
        self.RunOnce = loop 

    def Run(self, loop=True):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((self.Ip, self.Port))
            s.listen()
            print('Server listing on port : {}'.format(self.Port))
            if not loop:
               loop = True
               self.RunOnce = True 
            while loop:
                conn, addr = s.accept()
                with conn:
                    print('Connected by {}'.format(addr))
                    while True:
                        data = conn.recv(1024)
                        if not data:
                            break
                        print('Received Data: {}'.format(data.decode("utf-8")))
                        conn.sendall(data)
                if self.RunOnce:
                    break

#Example:
serverConnection = {}
serverConnection['Ip'] = 'localhost'
serverConnection['Port'] = 7890 
srv = Server(serverConnection['Ip'], serverConnection['Port'])
srv.Run()

