class SPImageModule:
        width = 0
        height = 0
        comp = 0

        def LoadImage(self, fileName):
            if(_SPImageModule.LoadImage(self, fileName)):
                prinf("Success width ", width, " height ", height, " comp ", comp)
            else:
                prinf("Fail")
            return