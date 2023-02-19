# Part 2

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtu.be/DpwxYc-8l2A).

---------------------------------------------------------------------------------------------------------------

## Minimum Requirements
### Completed

---------- (Part 1 progress) ----------

1. Two-dimension board (odd numbers, alien placed in the middle)
2. Player can customize settings (game board dimensions and number of zombies)
3. Rows and column numbers are displayed correctly
4. Game characters with attributes:
    * Alien (life, attack)
    * Zombie (life, attack, range)
5. Health pack gains 20 health to alien
6. Rock stops game characters from moving, discovers hidden item
7. Alien's movement and behaviour (up, down, left, right)

---------- (Part 2 progress) ----------

8. Quit game
9. Trail reset
10. Alien attacks zombie
11. Pods targets ONE closest zombie
12. Alien's attack starts with 0 each turn
13. Game character's attributes are initialized with random numbers
14. Differentiate each zombies
15. Change game board arrows
16. Active turns
17. Zombie move
18. Zombie attack
19. Remove defeated zombies from the board
20. Defeated zombies skips their turn, attributes remain displayed
21. Prompt to replay when game over
22. Different game difficulty (Normal / Hard)
23. New game objects (Spike - deals 10 damage when approached)
24. Save & load game

---------------------------------------------------------------------------------------------------------------

### To Do
-- Rui ern --
1. Game character's attributes are initialized with random numbers ✅
2. Differentiate each zombies ✅
3. Change game board arrows ✅
4. Zombie move ✅
5. Zombie attack ✅


-- Ju Wei --
1. Trail resets ✅
2. Hits zombie ✅
3. Alien's attack starts with 0 each turn ✅
4. Active turns ✅
5. Defeated zombies skips their turn, attributes remain displayed ✅
6. Limit zombie_count <= 5, rows_ & columns_ >= 3 ✅
7. Prompt to replay when game over ✅
8. Different game difficulties ✅
9. Create a new game object (spike, deals damage to alien when being approached) ✅
10. Fixed arrow inputs and looping problem ✅

-- Jia Hen --
1. Pods targets ONE closest zombie (maybe can save zombie position when creating) ✅
2. Quit game ✅
3. Save and load game

---------------------------------------------------------------------------------------------------------------

## Additional Features
1. Prevent zombie and alien overlaps when creating a new game --- (DONE)
2. Prevent zombies overlaps each other when creating zombies --- (DONE)
3. Prevent looping in arrow section when there's no arrow in board --- (DONE)
4. Random value assigned to characters attributes should be sensible [ (life > attack) & (dimension > range) ] --- (DONE)
5. Create a new game object (spike, deals damage to alien when being approached) --- (DONE)
6. Different game difficulties (Normal / Hard) --- (DONE)
7. Prevent zombies from going out of game board --- (DONE)
8. Prevent zombies from replacing alien, spikes, and zombies themselves --- (DONE)
9. Zombie can't move when it is blocked in all directions --- (DONE)

---------------------------------------------------------------------------------------------------------------


## Contributions

Wong Ju Wei
1. Customize settings
2. Game board
3. Display rows and columns
4. Random generated items in game board
5. Alien's movement and behaviour (up, down, left, right)
6. Trail resets 
7. Alien attacks zombie
8. Alien's attack starts with 0 each turn 
9. Active turns 
10. Remove defeated zombies from the board
11. Defeated zombies skips their turn, attributes remain displayed 
12. Limit zombie_count <= 5, rows_ & columns_ >= 3 
13. Prompt to replay when game over 
14. Different game difficulties
15. Create a new game object (spike, deals damage to alien when being approached)
16. Fixed arrow inputs and looping problem

Yap Rui Ern
1. Alien and zombie character
2. Game character's attributes are initialized with random numbers
3. Change game board arrows
4. Differentiate each zombies 
6. Zombie move 
7. Zombie attack

Lim Jia Hen
1. Rock stops game characters from moving, discovers hidden item
2. Health pack gains 20 health to alien
3. Pods targets ONE closest zombie
4. Quit game
5. Save & load game

---------------------------------------------------------------------------------------------------------------

## Problems Encountered & Solutions

1. Problem  : Display rows and columns (quite complicated logic)
   Solution : Trial and error
2. Problem  : pause(), have to press ENTER x2
   Solution : Couldn't find the error (not solved)
3. Problem  : Differentiate each zombie
   Solution : Vector of a class
   
   ---------------------------------------------------------------------------------------------------------------
