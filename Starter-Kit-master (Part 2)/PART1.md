# Part 1

## Video Demo
Please provide the YouTube link to your [Video Demo](https://www.youtube.com/watch?v=pO5W0PhPbMc).

---------------------------------------------------------------------------------------------------------------

## Minimum Requirements
### Completed
1. Two-dimension board (odd numbers, alien placed in the middle)
2. Player can customize settings (game board dimensions and number of zombies)
3. Rows and column numbers are displayed correctly
4. Game characters with attributes:
    * Alien (life, attack)
    * Zombie (life, attack, range)
5. Health pack gains 20 health to alien
6. Rock blocks game characters from moving, discovers hidden item
7. Alien's movement and behaviour (up, down, left, right)

### To Do
-- Rui ern --
1. Game character's attributes are initialized with random numbers
2. Differentiate each zombies
3. Change game board arrows

-- Ju Wei --
1. Trail resets
2. Hits zombie
3. Alien's attack starts with 0 each turn
4. Defeated zombies skips their turn, attributes remain displayed

-- Jia Hen --
1. Pods targets ONE closest zombie
2. Save, load, quit

### Cool Features
1. Prevent zombie and alien overlaps when creating a new game
2. Random value assigned to characters attributes should be sensible [ (life > attack) & (dimension > range) ] --- (not done)
3. Number of zombies - (1 to N) Maximum differs depends on the dimension of the game board ----------------------- (not done)

---------------------------------------------------------------------------------------------------------------

## Additional Features
Describe the additional features that has been implemented. (not yet implement, ideas only)
1. Create a game object (spike, deals damage to alien when approached)
2. Different game difficulties

---------------------------------------------------------------------------------------------------------------

## Contributions
*List down the contribution of each group members.*

### Wong Ju Wei
1. Customize settings
2. Game board
3. Display rows and columns
4. Random generated items in game board
5. Alien's movement and behaviour (up, down, left, right)

### Yap Rui Ern
1. Alien and zombie
2. Zombie movement and attack behaviour. (in progress)
3. *add more*

### Lim Jia Hen
1. Pods, health pack, rock
2. Implement all game objects.
3. *add more*

---------------------------------------------------------------------------------------------------------------

## Problems Encountered & Solutions
*Describe the problems encountered and provide the solutions / plan for the solutions.*
1. Problem  : Display rows and columns (quite complicated logic)
   Solution : Trial and error
2. Problem  : pause(), have to press ENTER x2
   Solution : Couldn't find the error (not solved)
3. Problem  : Differentiate each zombie
   Solution : Haven't find a solution

---------------------------------------------------------------------------------------------------------------