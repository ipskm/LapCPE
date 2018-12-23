from tkinter import *
from tkinter.ttk import Notebook


class Window(Frame):


    def __init__(self, master=None):

        Frame.__init__(self, master)
        self.master = master
        self.init_window()
        self.init_notebook()

    def init_window(self):

        self.master.title("Smart System :: กลุ่มพ่อบ้านใจกล้า")
        
        menu = Menu(self.master)
        self.master.config(menu=menu)
        fileMenu = Menu(menu, tearoff = 0)
        fileMenu.add_command(label='New Configuration')
        fileMenu.add_command(label="Load Configuration")
        fileMenu.add_command(label="Exit", command=self.client_exit)
        menu.add_cascade(label="File", menu=fileMenu)
        editMenu = Menu(menu, tearoff=0)
        editMenu.add_command(label="Undo")
        editMenu.add_command(label="Redo")
        menu.add_cascade(label="Edit", menu=editMenu)
        helpMenu = Menu(menu, tearoff=0)
        helpMenu.add_command(label="Contact")
        helpMenu.add_command(label="About us")
        menu.add_cascade(label="Help", menu=helpMenu)
        Label(self.master, text='Smart Home System Dashboard', font='Arial 24').pack()



    def init_notebook(self):
        def Summary_tab():
            exit()

        tab_control = Notebook(self.master)
        summary = Frame(tab_control)
        living_room = Frame(tab_control)
        kitchen_room = Frame(tab_control)
        bedroom_room = Frame(tab_control)
        bathroom_room = Frame(tab_control)
        balcony = Frame(tab_control)

        tab_control.add(summary, text='Summary', command=Summary_tab())
        tab_control.add(living_room, text='Livingroom')
        tab_control.add(kitchen_room, text='Kitchen')
        tab_control.add(bedroom_room, text='Bedroom')
        tab_control.add(bathroom_room, text='Bathroom')
        tab_control.add(balcony, text='Balcony')
        tab_control.pack(expand=1, fill='both')
        Button(summary, text="Click Me!").grid()
        

            
    
    def client_exit(self):
        exit()

root = Tk()
root.geometry("800x600")
app = Window(root)
root.mainloop()  
