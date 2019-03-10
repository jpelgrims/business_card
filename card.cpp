#include <iostream>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <unistd.h>


int* generate_heightmap(int width, int height) {
	int* heightmap = new int[width*height]{0};

	const int MIN_HILL_RADIUS = 5;
	const int MAX_HILL_RADIUS = 30;
	const int NR_OF_HILLS = 200;

	for (int i = 0; i < NR_OF_HILLS; i++) {
		int hill_x = rand() % width;
		int hill_y = rand() % height;
		int hill_radius = rand() % (MAX_HILL_RADIUS - MIN_HILL_RADIUS + 1) + MIN_HILL_RADIUS;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				double hill_height = pow(hill_radius, 2) - (pow(x - hill_x, 2) + pow(y - hill_y, 2));
				if (hill_height > 0) {
					double new_height = heightmap[y*width + x] + hill_height;
					heightmap[y*width + x] = int(new_height);
				}
			}
		}
	}

	double max_height = *std::max_element(heightmap, heightmap + width * height);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int cur_height = heightmap[y*width + x];
			heightmap[y*width + x] = int((cur_height / max_height) * 100);
		}
	}

	return heightmap;
}


struct rgb {
	int r, g, b;
};

rgb* generate_colormap(int* heightmap, int map_width, int map_height) {
	double max_height = *std::max_element(heightmap, heightmap + map_width * map_height);

	rgb* colormap = new rgb[map_width*map_height];

	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			int grey_value = std::min(255, int((heightmap[y*map_width + x] / max_height) * 255));
			rgb color = { grey_value, grey_value, grey_value };
			colormap[y*map_width + x] = color;
		}
	}

	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			rgb color = colormap[y*map_width + x];
			int height = heightmap[y*map_width + x];

			if (height <= 5) {
				color = rgb{ 0, 0, 40 };
			} else if (height <= max_height * (0.1)) {
				color = rgb{ color.r - 10, color.g - 10, color.b + 40 };
			} else if (height <= max_height * (0.2)) {
				color = rgb{ color.r + 120, color.g + 80, color.b + 40 };
			} else if (height <= max_height * (0.5)) {
				color = rgb{ color.r - 10, color.g + 20, color.b - 10 };
			} else if (height <= max_height * (0.9)) {
				color = rgb{ color.r - 40, color.g - 50, color.b - 40 };
			}

			colormap[y*map_width + x] = color;

			if (x > 0 && x < map_width && heightmap[y*map_width + (x - 1)] > heightmap[y*map_width + x]) {
				rgb color = colormap[y*map_width + x];
				color.r *= 0.85;
				color.g *= 0.85;
				color.b *= 0.85;
                colormap[y*map_width + x] = color;
			}

		}
	}

	/**for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_height; y++) {
			printf("%d %d %d | ", colormap[y*map_width + x].r, colormap[y*map_width + x].g, colormap[y*map_width + x].b);
		}
		printf("\n");
	}

	getchar();**/

	return colormap;

}

struct pos {
	double x, y;
};

rgb* render(int* heightmap, rgb* colormap, pos p, int height, int horizon, int scale_height, int distance, int fog_distance, int screen_width, int screen_height, int map_width, int map_height) {
	rgb* buffer = new rgb[screen_width*screen_height];

    int actual_height = height + heightmap[int(p.y)*map_width + int(p.x)];

	for (int x = 0; x < screen_width; x++) {
		for (int y = 0; y < screen_height; y++) {
			buffer[y*screen_width + x] = rgb{ 86 + y - x, 213 + y - x, 255 + y - x };
		}
	}

	for (int z = distance; z > 1; z--) {
		pos pleft = { -z + p.x, -z + p.y };
		pos pright = { z + p.x, -z + p.y };

		double dx = (pright.x - pleft.x) / screen_width;

		for (int x = 0; x < screen_width; x++) {
			double height_on_screen = (actual_height - heightmap[int(pleft.y)*map_width + int(pleft.x)]) / double(z) * scale_height + horizon;

			if (height_on_screen >= screen_height) { continue; }
			if (height_on_screen < 0) { height_on_screen = 0; }

			for (int y = floor(height_on_screen); y < floor(screen_height); y++) {
				rgb color = colormap[int(pleft.y)*map_width + int(pleft.x)];
				if (z > fog_distance) {
					double m = 1 - ((fog_distance - z) / double(fog_distance))*1.5;
					color = rgb{int(color.r*m), int(color.g*m), int(color.b*m) };
				}
				buffer[y*screen_width + x] = color;
			}
			
			pleft.x += dx;
		}
	}

	return buffer;
}

// Should be okay
void draw(rgb* buffer, int screen_width, int screen_height) {
	printf("\e[?25l\e[H");

	for (int y = 0; y < screen_height; y += 2) {
		for (int x = 0; x < screen_width; x++) {
			rgb color1 = buffer[y*screen_width + x];
			rgb color2 = buffer[(y + 1)*screen_width + x];
			printf("\e[38;2;%d;%d;%dm", color1.r, color1.g, color1.b);
			printf("\e[48;2;%d;%d;%dm▀", color2.r, color2.g, color2.b);
		}
	}
	fflush(stdout);
}

//Should also be okay
void fly() {
	system("clear");
    srand( time(0) );

	int screen_width = 80;
	int screen_height = 48;

	int map_width = 200;
	int map_height = 400;

	int* heightmap = generate_heightmap(map_width, map_height);
	rgb* colormap = generate_colormap(heightmap, map_width, map_height);

	pos point = { 100, 400 };

	rgb* screenmap = new rgb[screen_width*screen_height];

    for (; point.y > int(100-2); point.y-=2) {
        rgb* buffer = render(heightmap, colormap, point, 50, 7, 10, 100, 65, screen_width, screen_height, map_width, map_height);
        draw(buffer, screen_width, screen_height);
        usleep(50000);
	}
}

int main()
{
	fly();
	printf("\e[0m");
	return 0;
}
