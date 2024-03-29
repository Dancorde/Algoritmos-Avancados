# -*- coding: utf-8 -*-
import sys
import copy
from operator import itemgetter, attrgetter

########################################
#                                      #
# Função que verifica se chegou no fim #
#                                      #
########################################
def endGame(board, R, C):
	count = 0
	for i in range(R):
		count += board[i].count(0)
	if(count == R * C - 1):
		return 1
	else:
		return 0
final_states = []
def findSolutions(board, R, C):

	if endGame(board, R, C) == 0:
		for i in range(R):
			for j in range(C):
				#if is not a empty cell
				if board[i][j] != 0:

					#move for the four sides
					type = board[i][j]
					#up, check boundery first
					if i > 0:
						if move(type, board[i-1][j]):
							board_copy = copy.deepcopy(board)
							board_copy[i][j] = 0
							board_copy[i-1][j] = type


							findSolutions(board_copy, R, C)
					#right
					if j < C-1:
						if move(type, board[i][j+1]):
							board_copy = copy.deepcopy(board)
							board_copy[i][j] = 0
							board_copy[i][j+1] = type


							findSolutions(board_copy, R, C)
						#down
					if i < R-1:
						if move(type, board[i+1][j]):
							board_copy = copy.deepcopy(board)
							board_copy[i][j] = 0
							board_copy[i+1][j] = type


							findSolutions(board_copy, R, C)
					#left
					if j > 0:
						if move(type, board[i][j-1]):
							board_copy = copy.deepcopy(board)
							board_copy[i][j] = 0
							board_copy[i][j-1] = type


							findSolutions(board_copy, R, C)
	else:
		#save just the line, column and piece
		for line in range(R):
			for column in range(C):
				if board[line][column] != 0:
					final_states.append(str(line+1) + " " + str(column+1) + " " +str(board[line][column]))
					break
		#final_states.append("".join(([str(item) for line in board for item in line])))

def order_final(final_states):
	final_states = [item.split(r" ")  for item in final_states]
	#print(final_states)
	final = sorted(final_states)
	for item in final:
		print(*item)


def move(from_piece, to_piece):


	if from_piece == 1:
		if to_piece == 2 :
			return 1
	if from_piece == 2:
		if to_piece == 3 :
			return 1
	if from_piece == 3:
		if to_piece == 1 :
			return 1
	return 0

########################################
#                                      #
#         Função principal             #
#                                      #
########################################
if __name__ == "__main__":
	board = []
	[R, C] = [int(x) for x in input().split()]

	for i in range(R):
		board.append([int(x) for x in input().split()])

	findSolutions(board, R, C)
	print(len(final_states))
	print(len(set(final_states)))
	order_final(list(set(final_states)))
	# printBoard(board)
	#printSol(board)

#	print(endGame(board, R, C))
