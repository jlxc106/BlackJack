#!/usr/bin/python

from libavg import app, avg
import bj

class MainDiv(app.MainDiv):
	def onInit(self):
		self.numPlayers = int(raw_input("Enter the number of players:(2-4): "))
		self.obj = bj.BlackJack(self.numPlayers)
		self.toggleTouchVisualization()
		self.node = avg.WordsNode(pos=(10,10), text="Hello World", parent=self)
		self.node.subscribe(avg.Node.CURSOR_DOWN, self.onDown)
		print self.obj

	def onDown(self, event):
		for i in range(self.numPlayers*2):
			self.card = self.obj.DealwithIt(i%self.numPlayers)
			self.img = avg.ImageNode(href="/home/jlxc106/BlackJack/img/"+self.card, \
			size=(100,100), pos=(10+100*i, 30), parent=avg.Player.get().getRootNode())
		#self.card = lib.DealCard(self.obj, 0)
		#self.img = avg.ImageNode(href="/home/jlxc106/BlackJack/img/"+self.card , size=(100, 100), pos=(10, 30), parent=avg.Player.get().getRootNode())



#player = avg.Player.get()
#canvas = player.createMainCanvas(size=(640,480))
#rootNode = canvas.getRootNode()
#avg.WordsNode(pos=(10,10), font="arial", text="Hello World", parent=rootNode)
#newNode = avg.WordsNode(text='hello libavg', pos=(10,30), parent=player.getRootNode())
#imgNode = avg.ImageNode(href="/home/jlxc106/Desktop/AceofSpades.jpg", pos=(10,30), size=(100,100), parent=rootNode)
#imgNode = avg.ImageNode(href="/home/jlxc106/BlackJack/img/4_of_diamonds.png", size=(100,100), pos=(10,30), parent=player.getRootNode())
#player.play()


 


	
#	mesh = avg.MeshNode
	
#class Button(avg.DivNode):
#	CLICKED = avg.Publisher.getMessageID()
#	def __init__(self):
#		self.publish(self.CLICKED)





app.App().run(MainDiv())

