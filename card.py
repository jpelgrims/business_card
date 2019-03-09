import random
import math
import time
import os


def generate_heightmap(width, height):
	heightmap = [[0 for y in range(height)] for x in range(width)]

	MIN_HILL_RADIUS = 5
	MAX_HILL_RADIUS = 30

	for i in range(200):
		px = random.randint(0, width-1)     							# center of hill
		py = random.randint(0, height-1)    							# center of hill
		r =  random.randint(MIN_HILL_RADIUS, MAX_HILL_RADIUS)           # radius

		for x in range(width):
			for y in range(height):
				hill_height = r**2 - ((x-px)**2 + (y - py)**2)
				if hill_height > 0:
					new_height = heightmap[x][y] + hill_height
					heightmap[x][y] = new_height
	
	max_height = max([max(row) for row in heightmap])

	# flatten heightmap
	for x in range(width):
		for y in range(height):
			cur_height = heightmap[x][y]
			heightmap[x][y] = int((cur_height/max_height)*100)

	return heightmap


def generate_colormap(heightmap):
	width, height = len(heightmap), len(heightmap[0])

	max_height = max([max(row) for row in heightmap])

	colormap = [[0 for y in range(height)] for x in range(width)]
	for x in range(width):
		for y in range(height):
			grey_value = min(255, int((heightmap[x][y]/max_height)*255))
			rgb = (grey_value, grey_value, grey_value)
			colormap[x][y] = rgb

	for x in range(width):
		for y in range(height):

			rgb = colormap[x][y]
			rnd = random.uniform(-0.005, 0.005)

			# Coloring of terrain based on height
			if heightmap[x][y] <= max_height*(0.9+rnd):
				colormap[x][y] = (rgb[0]-40, rgb[1]-50, rgb[2]-40)
			if heightmap[x][y] <= max_height*(0.5+rnd):
				colormap[x][y] = (rgb[0]-10, rgb[1]+20, rgb[2]-10)
			if heightmap[x][y] <= max_height*(0.2+rnd):
				colormap[x][y] = (rgb[0]+120, rgb[1] + 80, rgb[2] + 40)
			if heightmap[x][y] <= max_height*0.1:
				colormap[x][y] = (rgb[0]-10, rgb[1]-10, rgb[2]+40)
			if heightmap[x][y] <= 5:
				 colormap[x][y] = (0, 0, 40)
			
			# Shading of terrain based on height of other blocks
			if (x > 0 and x < width and heightmap[x-1][y] > heightmap[x][y]):
				rgb = colormap[x][y]
				colormap[x][y] = (int(rgb[0]* 0.85),int(rgb[1]*0.85), int(rgb[2]*0.85))

	return colormap


def render(heightmap, colormap, p, height, horizon, scale_height, distance, fog_distance, screen_width, screen_height):
	# Default background color, doubles for sky
	buffer = [[(86+y-x, 213+y-x, 255+y-x) for y in range(screen_height)] for x in range(screen_width)]

	# Draw from back to the front
	for z in range(distance, 1, -1):
		# Find line on map. This calculation corresponds to a field of view of 90
		pleft  = (-z + p[0], -z + p[1])
		pright = (z + p[0], -z + p[1])
		
		# segment the line
		dx = (pright[0] - pleft[0]) / screen_width

		# Draw vertical lines
		for x in range(screen_width):
			height_on_screen = (height - heightmap[int(pleft[0])][int(pleft[1])]) / z * scale_height + horizon

			if (height_on_screen >= screen_height): continue
			if (height_on_screen < 0): height_on_screen = 0

			for y in range(math.floor(height_on_screen), math.floor(screen_height)):
				rgb = colormap[int(pleft[0])][int(pleft[1])]
				if z > fog_distance:
					m = 1-((fog_distance-z)/fog_distance)*1.5
					rgb = (int(rgb[0]*m),int(rgb[1]*m), int(rgb[2]*m))
				buffer[x][y] = rgb
			
			pleft = (pleft[0]+dx, pleft[1])
		
	return buffer


def draw(buffer, screenmap, screen_width, screen_height):
	line = "\033[?25l" + "\033[H"
	for y in range(0, screen_height, 2):
		for x in range(screen_width):
			char = "\033[38;2;{};{};{}m".format(*buffer[x][y])
			char += "\033[48;2;{};{};{}m▀".format(*buffer[x][y+1])
			line += char
		line += "\n"
	print(line[:-2], end='')


def fly():
	os.system("clear")
	screen_width =80
	screen_height = 48

	heightmap = generate_heightmap(200, 400)
	colormap = generate_colormap(heightmap)

	point = (100, 400)

	screenmap = [[None for y in range(screen_height)] for x in range(screen_width)]
	for i in range(int((400-100)-2)):
		buffer = render(heightmap, colormap, point, heightmap[point[0]-1][point[1]-5]+20, 7, 10, 100, 65, screen_width, screen_height)
		draw(buffer, screenmap, screen_width, screen_height)

		point = (point[0], point[1]-2)

fly()