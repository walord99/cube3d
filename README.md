# cube3D #

A small tech demo with rendering similar to wolfenstein 3D built according the specifications of the [42 project of the same name](https://github.com/walord99/cube3d/blob/main/extras/subject.pdf)

The rendering is done on the CPU, but since only 2D calculations are needed for each pixel an X axis to render an image, it is still very fast on modern processor. The main bottleneck that causes frames per second to drop is editing the memory of image that holds the wall, not the raycasting.

### map specification #
- a '0' or space represents a walkable tile
- '1' is a wall
- the player cannot be able to walk out of the map from his starting position
- 'N' 'S' 'E' 'W' are the start position of the player as well as the starting looking direction
- '-' is a door, it needs wall to the left and right of it
- '|' is a door, it needs walls above and below it

### texture and color specification #
- textures are "NO" "SO" "EA" and "WE" followed by a path to the file
- floor and ceiling colors are 'C' and 'F' followed by R, G, B

### controls ###

- WASD to move
- left and right arrow to look
- enable mouse by holding left alt
- esc to quit


![cube image](https://github.com/walord99/cube3d/blob/main/extras/cube_cap.png)