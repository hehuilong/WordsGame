#Words Game Online in C/PHP and Javascript 

Author : HE Huilong, Vincent STUDER

**For local test and play**

Makefile is in the directory "src"

Use the ELF executable "test" in console for testing the game functions with a text interface

Use the ELF executable "wordgame" to play with GTK interface.

**Introduction to algorithms**

I want the placement of words in the grid to be randomized.

Say the size of grille is N\*N, the length of longest word is L and the number of words is M.

The M words are randomly picked up from a dictionary.
 
*1st step:

Generate M sequences of N\*N integers without duplication from 1 to N*N which can represent the positions in the grid.

Randomize the order of these number sequences by shuffling technique.

Time: o(M\*N\*N)
 
*2nd step:

Generate M sequences of 8 integers without duplication from 1 to 8 which can represent the directions in the grid.

Randomize the order of these number sequences by shuffling technique.

Time : o(8\*M)
 
*3rd step:

Put M words in the grid using DFS.

The DFS order for each word is based on the sequences generated.

Time : o(N\*N\*8\*L\*M)

END

