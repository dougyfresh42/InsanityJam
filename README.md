This is hopefully a README for the project.
I'm not entirely sure how git uses readme's,
but hopefully it shows up somewhere.

To compile the program I just used g++ *.cpp
No special libraries are currently needed.

Gameplay:
Basically you get a random faction.  The faction's
demographics are all randomly generated.  The options
can all be found in different files.  Demographics
all have a percentage in favor of each issue (50 if
they don't care.)
Issues all have a number of messages with two responses.
They each have a severity level as well, 1-4.  4 being
sever.
So a random message will be read with two responses,
one being affirmative to the issue, the other being
negative.  Factions will react based on which response
is chosen.

No win condition exists yet.  Only happiness changes.

demographics.txt:
[Number of Categories]
[Category] [Number of Demographics in Category]
[Demographic] [Stance Issue 1] [Stance Issue 2] [Etc]
[Demographic] [Stance Issue 1] [Stance Issue 2] [Etc]
[Category] ...etc.  Repeat ad infinitum.

issues.txt:
[Number of Issues]
[Issue 1]
[Issue 2]
etc.
(spaces are OK in this one)

[Issue 1, 2 etc].txt
[Number of Messages]
1
[Affirmative Response] [Negative Response] [Message]
2
[Affirmative Response] [Negative Response] [Message]
3
[Affirmative Response] [Negative Response] [Message]
4
[Affirmative Response] [Negative Response] [Message]
This can have any number of messages in each category.
No spaces in responses.
