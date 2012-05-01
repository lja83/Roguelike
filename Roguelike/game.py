import libtcodpy as libtcod
import random

SCREEN_WIDTH = 46
SCREEN_HEIGHT = 20

def enum(*sequential, **named):
	enums = dict(zip(sequential, range(len(sequential))), **named)
	return type('Enum', (), enums)

MAPTEXT = [
	'##############################################',
	'#######################      #################',
	'#####################    #     ###############',
	'######################  ###        ###########',
	'##################      #####             ####',
	'################       ########    ###### ####',
	'###############      #################### ####',
	'################    ######                  ##',
	'########   #######  ######   #     #     #  ##',
	'########   ######      ###                  ##',
	'########                                    ##',
	'####       ######      ###   #     #     #  ##',
	'#### ###   ########## ####                  ##',
	'#### ###   ##########   ###########=##########',
	'#### ##################   #####          #####',
	'#### ###             #### #####          #####',
	'####           #     ####                #####',
	'########       #     #### #####          #####',
	'########       #####      ####################',
	'##############################################',
]

class Character:
	def __init__(self):
		self.hp = None
		self.mp = None
		self.symbol = '@'
		self.x = 0
		self.y = 0
	
	def move(self, x, y):
		self.x += x
		self.y += y

player = Character()
player.hp = 10
player.mp = 2
player.symbol = '@'
player.color = libtcod.white

player.x = 0
player.y = 0
while (MAPTEXT[player.y][player.x] != ' '):
	player.y = random.randint(0, len(MAPTEXT) - 1)
	print "y", player.y
	player.x = random.randint(0, len(MAPTEXT[player.y]) - 1)
	print "x", player.x

characters = [
	player,
]

libtcod.console_set_custom_font("consolas_unicode_16x16.png", libtcod.FONT_LAYOUT_ASCII_INROW | libtcod.FONT_TYPE_GREYSCALE, 32, 64)
libtcod.console_init_root(SCREEN_WIDTH, SCREEN_HEIGHT, "Stuff", False)
while (not libtcod.console_is_window_closed()):
	#Render screen
		#Clear screen
	libtcod.console_clear(0)
		#Draw map
	for y in range(len(MAPTEXT)):
		for x in range(len(MAPTEXT[y])):
			libtcod.console_put_char(0, x, y, MAPTEXT[y][x], libtcod.BKGND_NONE)
		#Draw items
		#Draw characters
	for character in characters:
		libtcod.console_put_char(0, character.x, character.y, character.symbol, libtcod.BKGND_NONE)
	libtcod.console_flush()
	
	#Handle input
	command = libtcod.console_wait_for_keypress(True)
	
	#Do actions
	if (command.vk == libtcod.KEY_UP):
		player.move(0, -1)
	elif (command.vk == libtcod.KEY_DOWN):
		player.move(0, 1)
	elif (command.vk == libtcod.KEY_LEFT):
		player.move(-1, 0)
	elif (command.vk == libtcod.KEY_RIGHT):
		player.move(1, 0)
	
	elif (command.vk == libtcod.KEY_ESCAPE):
		break