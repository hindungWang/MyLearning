d = 0
def hanoi(n, A, B, C):
	global d
	if n == 0:
		return
	else:
		hanoi(n - 1, A, C, B)
		'''print 'Move', n, 'from', A, 'to', C'''
		d += 1
		hanoi(n - 1, B, A, C)

hanoi(1, "left", "center", "right")
print d