class LCS(object):
	UP = 1
	LEFT = 2
	DIAG = 3

def get_lcs(mx, s1, s2, i, j):
	if i == 0 and j == 0:
		return ''
	elif mx[i][j] == LCS.DIAG:
		return get_lcs(mx, s1, s2, i - 1, j - 1) + s1[i - 1]
	elif mx[i][j] == LCS.UP:
		return get_lcs(mx, s1, s2, i - 1, j)
	else:
		return get_lcs(mx, s1, s2, i, j - 1)

def lcs(s1, s2):
	mx = [[0 for j in range(0, len(s2) + 1)] for i in range(0, len(s1) + 1)]
	mxDir = [[LCS.UP for j in range(0, len(s2) + 1)] for i in range(0, len(s1) + 1)]
	mxDir[0] = [LCS.LEFT for i in range(0, len(mxDir[0]))]

	for i in range(1, len(s1) + 1):
		for j in range(1, len(s2) + 1):
			if s1[i - 1] == s2[j - 1]:
				mx[i][j] = mx[i - 1][j - 1] + 1
				mxDir[i][j] = LCS.DIAG
			else:
				mx[i][j] = max(mx[i - 1][j], mx[i][j - 1])
				mxDir[i][j] = LCS.LEFT

				if mx[i - 1][j] > mx[i][j - 1]:
					mxDir[i][j] = LCS.UP

	return get_lcs(mxDir, s1, s2, len(s1), len(s2))

print(lcs('abcdefghijklmno', 'aacbedjkppq'))