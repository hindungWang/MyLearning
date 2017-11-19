'''
@author:TangTiOne
'''
def is_leap_yaer(year):
	if year % 4 == 0 and year % 100 != 0 or year % 400 == 0:
		return True
	else:
		return False


def get_num_of_days_in_moth(year, month):
	if month in (1, 3, 5, 7, 8, 10, 12):
		return 31
	elif month in (4, 6, 9,11):
		return 30
	elif is_leap_yaer(year):
		return 29
	else:
		return 28

		
		
def get_total_num_of_days(year, month):
	days = 0
	for y in range(1800, year):
		if is_leap_yaer(y):
			days += 366
		else:
			days += 365
		
	for m in range(1, month):
		days += get_num_of_days_in_moth(year, m)
	return days
def get_star_day(year, month):
	return (3 + get_total_num_of_days(year, month)) % 7

def show(year, month, firstvalue):
	print "\t   ",
	if month == 1:
		print "\tJanuary\t",
		print year
	elif month == 2:
		print "\tFebruary\t",
		print year
	elif month == 3:
		print "\tMarch\t",
		print year
	elif month == 4:
		print "\tApril\t",
		print year
	elif month == 5:
		print "\tMay\t",
		print year
	elif month == 6:
		print "\tJune\t",
		print year
	elif month == 7:
		print "\tJuly\t",
		print year
	elif month == 8:
		print "\tAugust\t",
		print year
	elif month == 9:
		print "\tSeptember\t",
		print year
	elif month == 10:
		print "\tOctober\t",
		print year
	elif month == 11:
		print "\tNovember\t",
		print year
	else:
		print "\tDecember\t",
		print year
	print "--------------------------------------------------"
	print "Mon  ",
	print " Tues ",
	print "  Wed ",
	print "   Thur ",
	print "  Fri ",
	print "   Sat ",
	print "   Sun " 
	day = 1
	flag = firstvalue
	for x in range(0, firstvalue-1):
		print "\t",
	while day <= get_num_of_days_in_moth(year, month):
		print day,
		print "\t",
		if flag % 7 == 0:
			print " "
		day += 1
		flag += 1
		
show(2017,11,get_star_day(2017,11))
		
		
		
