#!/usr/bin/python

from libavg import app, avg
import bj
from termios import tcflush, TCIFLUSH
import sys

class MainDiv(app.MainDiv):
	def onInit(self):
		#player = avg.Player.get()
		#self.canvas = player.createCanvas(size=(self.settings.getPoint2D('app_resolution')))
		#self.numPlayers = int(raw_input("Enter the number of players:(2-4): "))
		#self.obj = bj.BlackJack(self.numPlayers)
		self.toggleTouchVisualization()
		self.node = avg.WordsNode(pos=(10,10), text="Play", parent=self)
		self.node.subscribe(avg.Node.CURSOR_DOWN, self.DealCards)
		
		self.players2 = avg.WordsNode(id="2", pos=(100, 10), text="2 Player", color="009900", parent=self)
		self.players2.subscribe(avg.Node.CURSOR_DOWN, self.funct2)
		#print self.num
		self.players3 = avg.WordsNode(id="3", pos=(200, 10), text="3 Player", color="009900", parent=self)
		self.players3.subscribe(avg.Node.CURSOR_DOWN, self.funct3)
		#print self.num
		self.players4 = avg.WordsNode(id="4", pos=(300, 10), text="4 Player", color="009900", parent=self)
		#self.players4.setEventHandler(avg.Node.CURSOR_DOWN, avg.MouseEvent, self.funct(4))
		self.players4.subscribe(avg.Node.CURSOR_DOWN, self.funct4)
		
		self.bool = False
		#print self.settings
		#player = avg.Player.get()
		#offscreenCanvas = player.createCanvas(id="playercanvas", size=(self.settings.getPoint2D('app_resolution')))
		#self.canvas = player.createCanvas(size=(self.settings.getPoint2D('app_resolution')))
		
		
		#self.node.connectEventHandler(self.players4, avg.Node.CURSOR_DOWN, self, self.funct1(2))
		#print self.num
		#player = avg.Player.get()
		#self.canvas = player.createCanvas(size=self.settings.getPoint2D('app_resolution'))
		#self.new_game = avg.WordsNode(pos=(300, 300), text= "Start New Game", color = "000000", parent = self)


	def onExit(self):
		print "Exit"
	
	

	#def onFrame(self):
	#	if self.bool == True:
	#		avg.ImageNode(href="/home/jlxc106/BlackJack/img/"+self.card, size=(100,100),\
	#		pos=(100+110*((self.i/self.numPlayers)), 30 + 110*(self.i%self.numPlayers)),\
	#		parent=avg.Player.get().getRootNode())
		#self.bool = False

		
	def funct2(self, event):
		#print avg.Player.getCurrentEvent
		#print self.getID
		#print self.num
		print "Starting 2 player game."
		self.Dealer = avg.WordsNode(pos=(10, 100), text="Dealer", parent=self)
		self.P1 = avg.WordsNode(pos=(10,200), text="Player 1", parent =self)
		self.obj = bj.BlackJack(2)
		self.numPlayers = 2
		self.players2.unlink(True)
		self.players3.unlink(True)
		self.players4.unlink(True)
		self.new_game = avg.WordsNode(pos=(400, 400), text= "Start New Game", color = "009900", parent = self)
		
	
	def funct3(self, event):
		print "Starting 3 player game."
		self.Dealer = avg.WordsNode(pos=(10, 100), text="Dealer", parent=self)		
		self.P1 = avg.WordsNode(pos=(10,200), text="Player 1", parent =self)
		self.P2 = avg.WordsNode(pos=(10,300), text="Player 2", parent =self)
		self.obj = bj.BlackJack(3)
		self.numPlayers = 3
		self.players2.unlink(True)
		self.players3.unlink(True)
		self.players4.unlink(True)
		self.new_game = avg.WordsNode(pos=(400, 400), text= "Start New Game", color = "009900", parent = self)
		
	
	def funct4(self, event):
		print "Starting 4 player game."
		self.Dealer = avg.WordsNode(pos=(10, 100), text="Dealer", parent=self)
		self.P1 = avg.WordsNode(pos=(10,200), text="Player 1", parent =self)
		self.P2 = avg.WordsNode(pos=(10,300), text="Player 2", parent =self)
		self.P3 = avg.WordsNode(pos=(10,400), text="Player 3", parent =self)
		self.obj = bj.BlackJack(4)
		self.numPlayers = 4
		self.players2.unlink(True)
		self.players3.unlink(True)
		self.players4.unlink(True)
		self.new_game = avg.WordsNode(pos=(400, 400), text= "Start New Game", color = "009900", parent = self)
		
	
	def DealCards(self, event):
		for self.i in range(self.numPlayers*2):
			self.DealCard()
			#self.card = self.obj.DealwithIt(self.i % self.numPlayers)
			avg.ImageNode(href="/home/jlxc106/BlackJack/img/"+self.card, size=(100,100),\
			pos=(100+80*((self.i/self.numPlayers)), 30 + 110*(self.i%self.numPlayers)),\
			parent=avg.Player.get().getRootNode())
			#self.canvas.render()
		self.button = avg.WordsNode(pos=(300,300), text="Hit or Bust?", color = "009900", parent=self)
		for j in range (1, self.numPlayers):
			x = 2
			print "player %d's turn" %j
			print "player has %d" %self.obj.getHandValue(j-1)
			self.obj.bustPercentage(j)
			tcflush(sys.stdin, TCIFLUSH)
			self.hit = raw_input("Hit? Type 'Y' for 'yes' or anything else for 'no': ")
			while(self.obj.getHandValue(j-1)<21 and self.hit == 'Y'):
				self.card=self.obj.DealwithIt(j)
				avg.ImageNode(href="/home/jlxc106/BlackJack/img/"+self.card, size=(100,100),\
				pos=(100+80*(x), 30 + 110*(j)), parent=avg.Player.get().getRootNode())
				x += 1
				if(self.obj.getHandValue(j-1)<21):
					self.obj.bustPercentage(j)
					tcflush(sys.stdin, TCIFLUSH)	
					self.hit = raw_input("Hit? Type 'Y' for 'yes' or anything else for 'no': ")
					
		while self.obj.getHandValue(3) < 17:
			print "*****************************"
			print "Dealer has %d" %self.obj.getHandValue(3)
			self.obj.DealwithIt(self.numPlayers)
		self.obj.soWhoWins()
		self.onExit()

	def DealCard(self):
		self.card = self.obj.DealwithIt(self.i % self.numPlayers)



app.App().run(MainDiv())

