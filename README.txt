Caltech CS2 Assignment 9: Othello

See [assignment9_part1.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part1.html) and [assignment9_part2.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part2.html)

I started off by implementing an AI that made random moves after checking that they were available.
It was not very good and lost most of the time, but the framework was built.

Then, I used a heuristic and set each square on the board to a certain value. The AI would consider
these values when choosing the next move. I played around with the values a bit and came up with
a set that represented the board state fairly well. Corners are weighted highly, as are edges, because
they are impossible/hard to capture. However, the 3 squares that surround a corner are weighted
poorly because they can lead to a corner being captured by the other player. The heuristic function is
pretty good at capturing the game state and beats the Simple, ConstantTime, and Better players.
A recursive minimax function was implemented as well, but the heuristic does better so I will be using
that for the tournament.