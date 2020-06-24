import sp_sys

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
    print("hello python")
    return

def data_print(t):
    print(t.code)