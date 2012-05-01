import libtcodpy as libtcod

SCREEN_WIDTH = 46
SCREEN_HEIGHT = 20

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

def enum(*sequential, **named):
	enums = dict(zip(sequential, range(len(sequential))), **named)
	return type('Enum', (), enums)

class Tile:
	def __init__(self, passable, transparent, symbol):
		self.passable = passable
		self.transparent = transparent
		self.symbol = symbol

class Map:
	def __init__(self, width=0, height=0):
		self.width = width
		self.height = height
		self.map = []
	
	def generate_map(self):
		y = 0
		for row in MAPTEXT:
			self.map.append([])
			for char in row:
				if (char == '#'):
					tile = Tile(False, False, '#')
				elif (char == ' '):
					tile = Tile(True, True, ' ')
				elif (char == '='):
					tile = Tile(False, True, '=')
				self.map[-1].append(tile)
		self.height = len(self.map)
		self.width = len(self.map[0])

RNG = libtcod.random_get_instance()

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

gameMap = Map()
gameMap.generate_map()

player = Character()
player.hp = 10
player.mp = 2
player.symbol = '@'
player.color = libtcod.white

print gameMap.height
print gameMap.width

player.x = 0
player.y = 0
while (gameMap.map[player.y][player.x].passable != True):
	player.y = libtcod.random_get_int(RNG, 0, gameMap.height - 1)
	print "y", player.y
	player.x = libtcod.random_get_int(RNG, 0, gameMap.width - 1)
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
	for y in range(gameMap.height):
		for x in range(gameMap.width):
			libtcod.console_put_char(0, x, y, gameMap.map[y][x].symbol, libtcod.BKGND_NONE)
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