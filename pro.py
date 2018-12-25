#import libraly
from tkinter import *
from tkinter import messagebox
from tkinter import filedialog
from tkinter.ttk import Notebook
import time
import multiprocessing
import serial
import csv

#define global variable
livingroom_var = 'livingroom' ; fire_lr = 0 ; ldr_lr = 0
bedroom_var = 'bedroom' ; fire_bd = 0 ; ldr_bd = 0
kitchen_var = 'kitchen' ; fire_kc = 0 ; ldr_kt = 0
bathroom_var = 'bathroom' ; fire_br = 0 ; ldr_br = 0

def get_data():
    ser = serial.Serial('/dev/ttyUSB0', 9600) #define defult serial port 
    value = ser.readline() #read data from serial
    data = value.split(',') #equal value to data for split with ','
    

def app_gui():
    root = Tk() #main window
    root.geometry('800x600') #resolution
    root.title('Smart Home :: กลุ่มพ่อบ้านใจกล้า') #title name
    
    def msgbox():
        contact = 'Powered by Python\nDeveloper :\nMr.Sathit Supmek \nMr.Phongsakorn Suttama' #text info
        messagebox.showinfo('About US',contact) #call message box title About us label use in contact variable
    def load_config():
        fileload = filedialog.askopenfilename(initialdir = "/",title = "Select file",filetypes = (("csv file","*.csv"),("all files","*.*"))) #make find file window

    def save_config():
        filesave = filedialog.asksaveasfile(mode='w', defaultextension=".csv") #call save function
        csvData = [[livingroom_var,fire_lr,ldr_lr],[bedroom_var,fire_bd,ldr_bd],[kitchen_var,fire_kc,ldr_kt],[bathroom_var,fire_br,ldr_br]] #add data to csv
        filesave.write(csvData) #write file from data
        filesave.close() #close file

    menu = Menu(root) # make munubar
    root.config(menu=menu, bg='#ffffff') #config menubar to call with menu
    fileMenu = Menu(menu, tearoff=0) #create filemenu with fix position
    fileMenu.add_command(label='Save Config', command=save_config) #add menu to main filemenu
    fileMenu.add_command(label='Load Config', command=load_config) #add menu to main filemenu
    fileMenu.add_command(label='Exit',command=exit) #add menu to main filemenu
    menu.add_cascade(label='File', menu=fileMenu) ##add menu to root window
    helpMenu = Menu(menu, tearoff=0) #create helpmenu with fix position
    helpMenu.add_command(label='About US',command=msgbox) #add about as menu
    menu.add_cascade(label='Help', menu=helpMenu) #create helpmenu with fix position

    Label(root, text='Smart Home Dashboard System', font='arial 20',bg='#ffffff').pack() #main label on root screen
    
    tab_control = Notebook(root) #add notebook tab
    summary = Frame(tab_control) #add summary frame
    living_room = Frame(tab_control) #add livingroom frame
    kitchen_room = Frame(tab_control) #add kitchen frame
    bedroom_room = Frame(tab_control) #add bedroom frame
    bathroom = Frame(tab_control) #add bathroom frame

    tab_control.add(summary, text='Summary') #add title summary
    tab_control.add(living_room, text='Livingroom') #add title living room
    tab_control.add(kitchen_room, text='Kitchen') #add title kitchen
    tab_control.add(bedroom_room, text='Bedroom') #add title bedroom
    tab_control.add(bathroom, text='Bathroom') #add title bathroom
    tab_control.pack(expand=1, fill='both') #add position to pack


    root.mainloop() #show root window

if __name__ == "__main__":
    p1 = multiprocessing.Process(target = app_gui) #define multi process
    p2 = multiprocessing.Process(target = get_data) #define multi process

    p1.start() #start process
    p2.start() #start process

    p1.join() #join function
    p2.join() #join function