#from functools import reduce
inveseted_money = 1_000
from_education_in_year = 2_000
for i in range(1, 30):
    print("current money: ", inveseted_money, ", and year: ", i, sep='')
    inveseted_money += from_education_in_year
    print("and money from education added: ", inveseted_money, sep='')
    inveseted_money*=1.05

print("current money: ", inveseted_money, ", and year: ", i+1, sep='')