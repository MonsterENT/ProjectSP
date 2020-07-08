class SPNetworkSender:
        _Addr = ""
        _Port = 0

        def InitSender(self, Addr, Port):
            self._Addr = Addr
            self._Port = Port
            return
        def SendData(self, data):            
            return _SPNetworkModule._SendData(self, data)