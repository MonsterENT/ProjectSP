from SPScript.Module.SPModule import *
import SPImageModule

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
    imageObj = SPImageModule.SPImageModule()
    print(imageObj)
    imageObj.LoadImage("ground512.png")

    o1 = Object()
    o1.code = 12
    TestModule.Func0(0, 4)
    TestModule.Func1(o1)
    moduleObj = SPModule()
    moduleObj.ToString()
    return
