# -*- coding: utf-8 -*-
import sys

######################################
#                                    #
#    Função para ler o Arquivo       #
#                                    #
######################################
def readFile(fileName):

	file = open(fileName, 'r')

	board = []

	R = 0
	C = 0
	i = 0

	for line in file:
		if(i == 0):
			R = int(line.split(" ")[0])
			C = int(line.split(" ")[1])
			i += 1
		else:
			board.append( [int(x) for x in line.split()])	

	file.close()

	return (R, C), board

######################################
#                                    #
#  Função para imprimir o tabuleiro  #
#                                    #
######################################
def printBoard(board):
	for i in range(len(board)):
		print(*board[i])


######################################
#                                    #
#  Função para imprimir a solução    #
#                                    #
######################################
def printSol(board):
	for i in range(len(board)):
		for j in range(len(board[i])):
			if (board[i][j] != 0):
				print(i, j, board[i][j])


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



########################################
#                                      #
#         Função principal             #
#                                      #
########################################
if __name__ == "__main__":
	info = readFile(sys.argv[1])
	[R, C] = info[0]
	board = info[1]
	
	printBoard(board)
	printSol(board)

	print(endGame(board, R, C))