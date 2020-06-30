class SPImageModule:
        width = 0
        height = 0
        comp = 0

        def LoadImage(self, fileName):
            if(_SPImageModule._LoadImage(self, fileName)):
                print("Success width ", self.width, " height ", self.height, " comp ", self.comp)
            else:
                print("Fail")
            return