from fnmatch import translate
from tkinter import *
from tkinter.ttk import *
from tkinter import scrolledtext
import tkinter

from numpy import inner, place
from pip import main
import pyttsx3 
from googletrans import Translator


#function to delete the text 
def eraser_text():
    #delete characters from the text box
    boxText.delete("0",END)
    boxText2.delete("0". END) 


# function to translate the entered text
def translate_text():
    inn = selected.get()
    if inn != "":
        
        if (selectOne.get() == "Español " and (selectTwo.get())) == "Quechua":
            out = Translator().translate(inn, dest="en")
            salida.set(out.text) 
        
        elif (selectOne.get() == "Quechua" and (selectTwo.get())) == "Español":
            out = Translator().translate(inn, dest="es" ) 
            salida.set(out.text)


# function to give audio to the translated text
def talk():
    # the button invokes a pyttsx3 instance 
    voiceEngine = pyttsx3.init()
    # instance to the speech engine queves a command for the engine that is rate the speech rate
    voiceEngine.setProperty("rate", 85)
    voiceEngine.say(boxText2.get())
    voiceEngine.runAndWait()


# modal or trasnlator window 
root = Tk()
root.title("Traductor de texto")
root.geometry("700x440")
root.config(relief="ridge", bo="5", bg="gray")

# we declare variables of type String to store the data of the boxes
selected = StringVar()
salida = StringVar()

# combobox = 1 we design the select and the style 
selectOne = Combobox(root, values=["Quechua", "Español"])
selectOne.place(x=80, y=60)
selectOne.current(1)
# combobox = 2 we design the select and the style
selectTwo = Combobox(root, values=["Quechua", "Español"])
selectTwo.place(x=450, y=60)
selectTwo.current(0)
# text box where the information to be trasnlated will be entered 
boxText = tkinter.Entry(justify=tkinter.LEFT, textvariable=selected, font=("Arial, 15"))
boxText.grid(column=0,pady=160, padx=65)
# placing cursor  in text area
boxText.focus()
# box text = 1 text box where the translated information will be sent
boxText2 = tkinter.Entry(justify=tkinter.LEFT, textvariable=salida, font=("Arial, 15"))
boxText2.place(x=400, y=150, height=200, width=250)

btn = Button(root, text="Limpiar", command=eraser_text).place (x=300, y=250)
btnTrad = Button(root, text="Traducir",command=translate_text).place(x=300, y=200)

btnVoi = Button(root, text="Audio", command=talk)
btnVoi,place(x=500, y=360)

#method in main window that repeats infinitely until user exits or stops
root,mainloop()


