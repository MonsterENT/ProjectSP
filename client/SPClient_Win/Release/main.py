from SPScript.Module.SPModule import *
from SPScript.Module.ImageSys.SPImageModule import *
from SPScript.Module.Network.SPNetworkModule import *

class Object:
    c = 1

# class Data:
#     def init_data(self, code):
#         self.code = code

# def on_pre_process():
#     packed_data = []
#     for idx in range(0, 100):
#         t = Data()
#         t.init_data(idx)
#         packed_data.append(t)
#     return packed_data

def kernel():
    # sender = SPNetworkSender()
    # sender.InitSender("127.0.0.1", 27015)
    # print("Network Sender Result: ", sender.SendData("SPNetworkSender"))

    imageObj = SPImageModule()
    print(imageObj)
    imageObj.LoadImage("ground512.png")

    o1 = Object()
    o1.code = 12
    TestModule.Func0(0, 4)
    TestModule.Func1(o1)
    moduleObj = SPModule()
    moduleObj.ToString()
    return
