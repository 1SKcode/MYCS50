# CS50 FinalProject - TimesTable - Sk.Code
#### Video Demo:  https://youtu.be/JUTCflxKVK0
#### Description:
Learning the times table for kids!
Study it playfully! Two modes for studying the multiplication table, a summary of the results and a nice design. Play and learn!
I implemented this project in C#. I started it at the age of 21, I wanted to finish it, but I left it. CS50 gave me a great reason to continue the project with new knowledge!
The source code of this project is always on my github! (https://github.com/1SKcode/TimesTable-ForKids)
In this project.
I used windows forms and my personal design! I hope you enjoy it. I really like it! There is a multiplication table and two game modes. Tiles and running mathematical examples.
In more detail:
1. __Main window__
In this menu, we can open the multiplication table itself, view our results for past games and, of course, switch to different game modes by clicking on one of the two right tiles.

- The results table is filled with information about the mode played, the level and the points scored. You can always clear the results by clicking on the cross next to the table.
- All __animations__ in the program are written according to the mat. the formulas of "smooth departure"

2. Viewing the table
- All elements react with animation when the mouse pointer is hovered over

3. TILE Mode
- The main logic of the game is to find a tile that matches the current expression or number
- There are 3 levels in the game: 2x2, 3x3 and 4x4 tiles
- Two modes: Search by answer and Search by example
- Modes can be changed with the corresponding button __"Change the mode"__
	- The button is animated by a smooth flight of elements
	- In the "Search by answer" mode, a number is given, the user needs to find a tile with an expression that is equivalent to the answer to this number
	- In the "Search by example" mode, the example itself is given, you just need to find a tile with the answer (number) to this example
- If the answer is incorrect, the tile is colored in the context color and the error counter is iterated by one
- When clearing the field of all tiles, the interface for further actions appears:
	- Repeat the level
	- Next level
	And there is also information on the level:
	- Number of errors
	- Number of points scored
- When you reach level 3, you can only start over or play again at this level
- Points for a level are awarded only after completing a level

THE ASSESSMENT SYSTEM:
- Upon completion of each level, the scores are recorded in a local file to store them on disk. When you exit the program, the results for previous games __ remain__
- The assessment is conducted on a 100-point scale
- For each mistake, a certain number of points are deducted, depending on the level. (at the first level, more points are deducted for 1 or more mistakes than at the second and third)

4. "Conveyor" mode
- The main logic of the game is to solve the expression that appears from the bottom, but do not let it reach the top line.
- In total, there will be 3 examples on the screen during the departure, you can solve any of them, BUT if the answer does not fit one of them, one life will be counted and removed
- At the beginning of the game, 4 lives are given (after the 4th mistake, the game ends and points are counted)
- If the given answer matches two or more expressions on the screen, points will be counted as for two or more correct examples, they will disappear, respectively, too
- Every 5 correct answers raise the level by 1
- As the level increases, the speed increases
- There is a log of answers on the left, where our correct answers, errors and examples that were not solved in the allotted time are recorded. The log expands downwards (a scrollbar appears) and after half of the examples from the multiplication table have already been on the screen, the entry goes to the second column and is also written down
 It was interesting and cool at CS50! Thanks!
