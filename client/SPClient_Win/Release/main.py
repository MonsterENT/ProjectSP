# import sp_sys
from SPScript.SPModule import *

class Object:
    c = 1

class Data:
    def init_data(self, code):
        self.code = code

def on_pre_process():
    packed_data = []
    for idx in range(0, 100):
        t = Data()
        t.init_data(idx)
        packed_data.append(t)
    return packed_data

def kernel():
    sp_sys.sys_print(0, 4)
    o1 = Object()
    o1.code = 12
    sp_sys.sys_check(o1)
    print("hello python")

    moduleObj = SPModule()
    moduleObj.ToString()
    return

def data_print(t):
    print(t.code)