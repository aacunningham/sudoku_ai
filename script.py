import datetime
import re
import requests

reg = re.compile(r".*tmda='([0-9]*).*")


for x in range(5):
    date = datetime.datetime.now()
    difficulty = x
    with open("tests/{}_sudoku.txt".format(difficulty), 'w') as f:
        for i in range(20):
            print ("Retrieving puzzle for {}/{}/{}, Difficulty: {}".format(date.month, date.day, date.year, difficulty))
            url = "http://sudokupuzzle.org/printable.php?nd={}&y={}&m={}&d={}".format(difficulty, date.year, date.month, date.day)
            puzzle_site = requests.get(url)
            puzzle_string = reg.match(puzzle_site.text.replace("\n", "")).group(1)

            for j in range(81):
                f.write(puzzle_string[j] + ' ')
                if ((j + 1) % 9) == 0:
                    f.write('\n')
            
            f.write('\n')

            date = date - datetime.timedelta(days=1)

