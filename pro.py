from tkinter import *
from tkinter import messagebox
from tkinter import filedialog
import time
import multiprocessing
import serial

def get_data():
    ser = serial.Serial('/dev/ttyUSB0', 9600) #define defult serial port 
    value = ser.readline() #read data from serial
    data = value.split(',') #equal value to data for split with ,
    

def app_gui():
    root = Tk() #main window
    root.geometry('800x600') #resolution
    root.title('Smart Home :: กลุ่มพ่อบ้านใจกล้า') #title name
    
    def msgbox():
        contact = 'Powered by Python\nDeveloper :\nMr.Sathit Supmek \nMr.Phongsakorn Suttama' #text info
        messagebox.showinfo('About US',contact) #call message box title About us label use in contact variable
    def load_config():
        fileload = Tk() #define fileload as windows
        fileload.filename =  filedialog.askopenfilename(initialdir = "/",title = "Select file",filetypes = (("csv file","*.csv"),("all files","*.*"))) #make find file window
        # print (fileload.filename)

    menu = Menu(root) # make munubar
    root.config(menu=menu, bg='#ffffff') #config menubar to call with menu
    fileMenu = Menu(menu, tearoff=0) #create filemenu with fix position
    fileMenu.add_command(label='Load Config', command=load_config) #add menu to main filemenu
    fileMenu.add_command(label='Exit',command=exit) #add menu to main filemenu
    menu.add_cascade(label='File', menu=fileMenu) ##add menu to root window
    helpMenu = Menu(menu, tearoff=0) #create helpmenu with fix position
    helpMenu.add_command(label='About US',command=msgbox) #add about as menu
    menu.add_cascade(label='Help', menu=helpMenu) #create helpmenu with fix position

    Label(root, text='Smart Home Dashboard System', font='arial 20',bg='#ffffff').pack() #main label on root screen



    root.mainloop() #show root window

if __name__ == "__main__":
    p1 = multiprocessing.Process(target = app_gui) #define multi process
    p2 = multiprocessing.Process(target = get_data) #define multi process

    p1.start() #start process
    p2.start() #start process

    p1.join() #join function
    p2.join() #join function