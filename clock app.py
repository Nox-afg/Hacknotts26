#import the tkinter module to create the window
import tkinter as tk
from time import strftime

#create the main window
base = tk.Tk()
base.title("Clock Example")

timelabel = tk.Label(base, font = ("Courier", 35))
timelabel.pack()

#create the function that makes the clock update automatically
def clockrun():
    #get the current time as string
    timenow = strftime("%H:%M:%S") #H, M and S, are hour, min, sec
    timelabel.config(text = timenow)
    timelabel.after(1000, clockrun)
    #the clock will update automatically
clockrun()
base.mainloop()