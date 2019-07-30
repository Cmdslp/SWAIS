from tkinter import *
import sys


sys.path.append(r"C:/Users/César Penha/Desktop/SWAIS PY")

class App(Frame):
	def run_script(self):
		
		sys.stdout = self
		sys.stderr = self
		try:
			
			del(sys.modules["swaisGenerator2.py"])
		except:
           
			pass
		import swaisGenerator2
		
		swaisGenerator2.callback()
		sys.stdout = sys.__stdout__
		## sys.stderr = __stderr__

	def build_widgets(self):
		root.iconbitmap("swaisApp/swais_ico.ico")
		root.title('SWAIS Log')
		frame = Frame(self, height=500, width=600)
		frame.grid(row=3, column=3, columnspan=3, rowspan=3)
		# buttonGenerate.grid(row=2, column=2, columnspan=10, rowspan=10)
		self.text1 = Text(self)
		self.text1.grid(row=3, column=2, columnspan=3, rowspan=3)
		self.button = Button(self)
		self.button["text"] = "GENERATE CODE"
		self.button["command"] = self.run_script
		
		self.button.grid(row=0, column=2, columnspan=3, rowspan=3)
		#self.button.trace("w", callback)
		self.w = Label(self)
		self.w.grid(row=6, column=4, columnspan=3, rowspan=1)
		self.w["text"] = "      SWAIS By César Penha @2019"
	def write(self, txt):
		self.text1.insert(INSERT, txt)

	def __init__(self, master=None):
		
		Frame.__init__(self, master)
		self.pack()
		self.build_widgets()
		
root = Tk()
app = App(master = root)
app.mainloop()