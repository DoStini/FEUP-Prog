Oware Practical nº1 - Prog
André Moreira

This program is an Oware game using c++.

Status: I finished the project and all of its objectives.

Development: 

    Throughout the development of this program I found some problems  when 12 or more seeds were chosen, but I successfully changed the seeds spreading and capture system to work with this rule.
    The project also doesn't seem to work very well when trying to clear the screen using the functions provided in Moodle. One small part where it's supposed to have a blinking text animations when the game ends doesn't seem to work.
    Documented the whole program and all of its functions
    Tried to made it as readable as possible. Made improvements in that ambit and in terms of code efficiency.


Rules:

    I used all of the rules from wikipedia's page about oware.
    
    Some rules I think are worth mentioning here:
        -From what I understood, everytime the player has 0 seeds in his move, the player is skipped, and tests his available moves so that the game can go on.
        -A grand slam can occur in the ocasion that, after this move, they both have 0 pieces, ending the game. For example, if player 2 makes his move, he gets the seed from the other player and the game is finished.
                                    0-0-0-0-0-1   Player 1
                                    0-0-0-0-0-1   Player 2

Bot:
    I made the enhanced version of the bot, where, through the points of each move, he can choose a random move among the best ones analysed.
