*This project has been created as part of the 42 curriculum by by jotong*

## Description
This assignment consists of a 3D graphical representation of the inside of a maze from a
first-person perspective, created using the ray-casting principles. <br>

## Instructions

once in the folder for each exercise, do 
make (for mandatory)
make bonus (for bonus)

then run: `./cub3D` <br>

## Resources

AI was used to help learn about digital differential algorithms.<br>

The Raycasting Engine: DDA AlgorithmTo render the 3D view, this project implements the Digital Differential Analyzer (DDA) algorithm.<br>

Unlike a simple "step-by-step" ray increment, DDA is highly optimized for grid-based maps.<br>
- The Logic: Instead of checking for a wall every 0.01 units (which is slow and prone to "missing" corners), DDA jumps directly to the next grid line on the $x$ or $y$ axis.<br>
- The Efficiency: It guarantees that every single tile intersection is checked with the minimum number of calculations, preventing "ghosting" through walls and ensuring pixel-perfect collision detection.<br>
- Mathematical Principle:<br>
	- Side Dist: The distance the ray has to travel from its start point to the first grid line.<br>
	- Delta Dist: The constant distance the ray travels to jump from one grid line to the next.<br>
	- Perpendicular Distance: Calculated to avoid the "fish-eye" effect, ensuring walls remain flat rather than curved.<br>

"DDA is the heartbeat of the engine, turning a 2D array into a volumetric experience."
