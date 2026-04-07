# my_radar — Air Traffic Simulation
 
A 1920×1080 real-time air traffic simulation rendered with CSFML. Planes fly between waypoints, towers protect areas, and collisions are detected per frame.
 
## Usage
 
```sh
./my_radar [OPTIONS] path_to_script
```
 
### Options
 
| Flag | Description |
|------|-------------|
| `-h` | Print help and exit |
 
### Keybinds
 
| Key | Action |
|-----|--------|
| `L` | Toggle hitboxes and tower radii |
| `S` | Toggle plane/tower sprites |
| `F` | Toggle occlusion culling |
 
## Script format
 
```
A x1 y1 x2 y2 speed delay   # Plane
T x y radius                 # Tower
```
 
## Build
 
```sh
make
```
 
Requires `libcsfml-graphics`, `libcsfml-window`, `libcsfml-system`, and `libm`.
 
## Author
 
EPITECH PROJECT, 2025 — my_radar