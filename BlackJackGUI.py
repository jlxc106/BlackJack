#!/usr/bin/python

from libavg import app, avg
import bj
from termios import tcflush, TCIFLUSH
import sys

class MainDiv(app.MainDiv):
    def onInit(self):
        self.toggleTouchVisualization()
	self.node = avg.WordsNode(pos=(10,10), text="Play", parent=self)
	self.node.subscribe(avg.Node.CURSOR_DOWN, self.DealCards)
	
	self.players2 = avg.WordsNode(id="2", pos=(100, 10), text="2 Player", color="009900", parent=self)
        self.players2.subscribe(avg.Node.CURSOR_DOWN, self.start_2)
	
        self.players3 = avg.WordsNode(id="3", pos=(200, 10), text="3 Player", color="009900", parent=self)
        self.players3.subscribe(avg.Node.CURSOR_DOWN, self.start_3)
        
        self.players4 = avg.WordsNode(id="4", pos=(300, 10), text="4 Player", color="009900", parent=self)
        self.players4.subscribe(avg.Node.CURSOR_DOWN, self.start_4)
        self.X = 1000
        self.inGame = False
        self.bool = False
        self.bool2 = False

    def onExit(self):
        #self.obj
        del self.obj
        print "Exiting"
    
    def onFrame(self):
        #end game
        if self.bool2 == True:
            D_value = self.obj.getHandValue(0)
            if D_value < 17:
                print "****************************"
                print "Dealer has %d" %D_value
                self.card=self.obj.DealwithIt(0)
                avg.ImageNode(href="/home/jlxc106/BlackJack/img/"+self.card, size=(100,100),\
		pos=(100+110*(self.obj.getNumCards(0)-1), 30),\
                parent=avg.Player.get().getRootNode())
            else:
                self.obj.soWhoWins()
                self.bool2 = False
                self.bool = False
                self.inGame = False

        #top players off - ask if they want to hit/stay
        elif self.bool == True:
            if self.j == self.numPlayers:
                self.bool2 = True
            if (self.j < self.numPlayers and self.obj.getHandValue(self.j)>20):
                self.j +=1
            if (self.j < self.numPlayers and self.obj.getHandValue(self.j)<21):
                print "player %d's turn: " %self.j
                print "player has %d" % self.obj.getHandValue(self.j)
                self.obj.bustPercentage(self.j)
                tcflush(sys.stdin, TCIFLUSH)
                #sys.stdout.flush()
                #raw_input()
                self.hit = raw_input("Hit? Type 'Y' for 'yes' or anything else for 'no': ")
                if(self.obj.getHandValue(self.j)<21 and self.hit == 'Y'):
                    self.card=self.obj.DealwithIt(self.j)
                    avg.ImageNode(href="/home/jlxc106/BlackJack/img/"+self.card, size=(100,100),\
		    pos=(100+110*(self.obj.getNumCards(self.j)-1), 30 + 110*(self.j)),\
                    parent=avg.Player.get().getRootNode())
                    #self.X +=1
                   # if(self.obj.getHandValue(self.j-1)<21):
                    #    self.obj.bustPercentage(self.j)
                     #   tcflush(sys.stdin, TCIFLUSH)
                      #  self.hit = raw_input("Hit? Type 'Y' for 'yes' or anything else for 'no': ")
                if (self.hit <> 'Y' or self.obj.getHandValue(self.j) >= 21):
                    self.j +=1

        #deal cards initially
        elif (self.inGame == True and self.bool == False):
            if self.Y < self.numPlayers*2:
                self.card = self.obj.DealwithIt(self.Y % self.numPlayers)
    	        avg.ImageNode(href="/home/jlxc106/BlackJack/img/"+self.card, size=(100,100),\
                pos=(100+110*((self.Y/self.numPlayers)), 30 + 110*(self.Y%self.numPlayers)),\
    	        parent=avg.Player.get().getRootNode())
                print ""
                self.Y += 1
                if self.Y == self.numPlayers*2:
                    print "\n"
                    self.bool = True
                    self.X = 2
                    self.j = 1

        #trigger to end game - who wins who loses
		
    def start_2(self, event):
        print "Starting 2 player game."
        self.Dealer = avg.WordsNode(pos=(10, 100), text="Dealer", parent=self)
        self.P1 = avg.WordsNode(pos=(10,200), text="Player 1", parent =self)
        self.obj = bj.BlackJack(2)
        self.numPlayers = 2
        self.players2.unlink(True)
        self.players4.unlink(True)
        self.players4.unlink(True)
    	self.new_game = avg.WordsNode(pos=(400, 400), text= "Start New Game", color = "009900", parent = self)	
	
    def start_3(self, event):
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
	
    def start_4(self, event):
    	print "Starting 4 player game."
    	self.Dealer = avg.WordsNode(pos=(10, 100), text="Dealer", parent=self)
    	self.P1 = avg.WordsNode(pos=(10,200), text="Player 1", parent=self)
    	self.P2 = avg.WordsNode(pos=(10,300), text="Player 2", parent=self)
    	self.P3 = avg.WordsNode(pos=(10,400), text="Player 3", parent=self)
    	self.obj = bj.BlackJack(4)
    	self.numPlayers = 4
    	self.players2.unlink(True)
    	self.players3.unlink(True)
    	self.players4.unlink(True)
    	self.new_game = avg.WordsNode(pos=(400, 400), text= "Start New Game", color = "009900", parent = self)	
	
    def DealCards(self, event):
        self.Y = 0
        self.inGame = True

app.App().run(MainDiv())

