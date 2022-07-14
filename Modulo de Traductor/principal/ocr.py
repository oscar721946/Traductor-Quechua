from ast import Try
from cProfile import label
from cgitb import text
from curses import window
from distutils import errors
from distutils.log import error
from importlib.resources import path
from subprocess import _TXT
from tkinter import *
from tkinter import filedialog
from tkinter import font
from PIL import Image, ImageFont, ImageDraw
from PIL import ImageTk
import cv2
from mysqlx import Column
import pytesseract
from mysql import Translator
import csv
import imutils 

try:
    from PIL import Image
except ImportError:
    import Image

# function to chaose the language to translate the image
def quechua_idiom():
    global image, ing_text

    if selected.get() == 1:
        # tesseract must be installed in windows and indicate the path so that it does not generate errors 
        pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-DCM\tesseract.exe'
        img_text = pytesseract.image_to_string(image)
        # image converted to text and translates into spanish
        p = Translator()
        p.translated = p.translate(ing.text, dest='spanish')
        translated = str(p.translated.text)
        # translated text font type settings, and on which image we will send the text
        imas = image.open('pictures/plantillaTraductor.jpg')
        draw = ImageDraw.Draw(imas)
        font = ImageFont.truetype(r'C:\fonts\Roboto-Black.ttf',18)
        text = translated
        draw.text ((15,20),text, fill="black", font=font align="right" )
        # image with the translated text that we will use late
        imas.save("test.png")
        src = cv2.inread("test.png")
        # we will display the image in the GUI in the lblOutputImage
        ImageToShowOutput = cv2.cvtcolor(src, cv2.COLOR_BGR2RGB)
        inn = image.fronarray(imageToShowOutput)
        ing = ImageTk.PhotoImage(image=ing)
        lblOutputImage.configure(image=ing)
        lblOutputImage.image =ing

        #output image label
        lblInfo3 = label(root,text="IMAGEN DE SALIDA")
        lblInfo3.grid(Column=1, row=0, padx=5, pady=5)

    with open('traduccion.txt',mode='x') as file:
        file.write(ing.text + "\n\n\n"+ translated)
        print("hecho!") 


# function to choose the language
def selected_image():
    # specify file type for images 
    path_image = filedialog.askopenfilename (filetypes=[
        ("image", ".jpeg"),
        ("image", ".png"),
        ("image", ".jpg")])
    #if there is a path we declare image globally
    if len(path_image) >0:
        global image
        # we read the image and resize it 
        image = cv2. inread(path_image)
        image = imutils.resize(image, width=340)
        # display image and input in GUI
        imageToShow = imutils.resize(image, width=320)
        inn = image. fromarray(imageToShow)
        ing = ImageTk.PhotoImage(image=inn) 
        lblInputImage.configure(image=ing)
        lblInputImage.image = ing

        # Label image to translate. image entrace
        lblInfo1 = Label(root, text="Imagen a traducir:")
        lblInfo1. grid(column=0, root=1, padx=5, pady=5)
        # we clean the radio buttom selection
        lblOutputImage.image = ""
        selected.set(0)


image = None

# modal principal
root = Tk()
root.title("Traductor de Imagenes")
# Label where the input image will be presented 
lblInputImage = Label(root)
lblInputImage.grid(column=0, row=2)

# Label where the output image will be presented 
lblOutputImage = Label(root)
lblOutputImage.grid(column=1, row=1, rowspan=0)

lblInfo2 = Label(root, text="Escoge el idioma para traducir",width=25)
lblInfo2.grid(column=0, row=3, padx=5, pady=5)
#Selected allows us the handle integers for radio button
selected = IntVar()
#radio buttom where we pass the modal root, and call the function of quechua_idiom 
radio1 = Radiobutton(root, text="Quechua", width=25, value=1, variable=selected, command=quechua_idiom)
radio2 = Radiobutton(root, text="Español", width=25, value=2, variable=selected, command=quechua_idiom)
radio1.grid(column=0, row=4)
radio2.grid(column=0, row=5)
# button selected input image
btn = Button(root, text="Seleccionar imagen", width=25, command=selected_image)
btn.grid(column=0, row=0, padx=5, pady=5)
# an endless loop is created where we have already declared root, until the user closes the window
root.mainloop()
 
  


 




