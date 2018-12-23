from tkinter import *
from tkinter import messagebox
from tkinter import filedialog
import time
import multiprocessing
import serial

def get_data():
    ser = serial.Serial('/dev/ttyUSB0', 9600)
    value = ser.readline()

def app_gui():
    root = Tk()
    root.geometry('800x600')
    root.title('Smart Home :: กลุ่มพ่อบ้านใจกล้า')
    def msgbox():
        contact = 'Powered by Python\nDeveloper :\nMr.Sathit Supmek \nMr.Phongsakorn Suttama'
        messagebox.showinfo('About US',contact)
    def load_config():
        fileload = Tk()
        fileload.filename =  filedialog.askopenfilename(initialdir = "/",title = "Select file",filetypes = (("csv file","*.csv"),("all files","*.*")))
        print (fileload.filename)
    menu = Menu(root)
    root.config(menu=menu, bg='#ffffff')
    fileMenu = Menu(menu, tearoff=0)
    fileMenu.add_command(label='Load Config', command=load_config)
    fileMenu.add_command(label='Exit',command=exit)
    menu.add_cascade(label='File', menu=fileMenu)
    helpMenu = Menu(menu, tearoff=0)
    helpMenu.add_command(label='About US',command=msgbox)
    menu.add_cascade(label='Help', menu=helpMenu)

    Label(root, text='Smart Home Dashboard System', font='arial 20',bg='#ffffff').pack()

    root.mainloop()

if __name__ == "__main__":
    p1 = multiprocessing.Process(target = app_gui)
    p2 = multiprocessing.Process(target = get_data)

    p1.start()
    p2.start()

    p1.join()
    p2.join()

    