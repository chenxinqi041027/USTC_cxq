import numpy as np
import matplotlib.pyplot as plt
from points import *
import random
import time
import copy
n = 5
n_roads = 4
rand_range = 18
random.seed(2)

def GeneratePoints(n):
	points = {}
	for i in range(n):
		for j in range(n):
			points[(i*100, j*100)] = [(i*100, j*100+100), (i*100+100, j*100), (i*100, j*100-100), (i*100-100, j*100)]
	for i in range(n):
		for j in range(n):
			points[(i*100, -j*100)] = [(i*100, -j*100+100), (i*100+100, -j*100), (i*100, -j*100-100), (i*100-100, -j*100)]
	for i in range(n):
		for j in range(n):
			points[(-i*100, j*100)] = [(-i*100, j*100+100), (-i*100+100, j*100), (-i*100, j*100-100), (-i*100-100, j*100)]
	for i in range(n):
		for j in range(n):
			points[(-i*100, -j*100)] = [(-i*100, -j*100+100), (-i*100+100, -j*100), (-i*100, -j*100-100), (-i*100-100, -j*100)]
	n_1 = n - 1
	for i in range(n):
		points[(i*100, (n_1+1)*100)] = [(i*100, (n_1*100))]
		points[(-i*100, (n_1+1)*100)] = [(-i*100, (n_1*100))]
		points[(i*100, -(n_1+1)*100)] = [(i*100, -(n_1*100))]
		points[(-i*100, -(n_1+1)*100)] = [(-i*100, -(n_1*100))]  
	for j in range(n):
		points[((n_1+1)*100, j*100)] = [(n_1*100, j*100)] 
		points[((n_1+1)*100, -j*100)] = [(n_1*100, -j*100)] 
		points[(-(n_1+1)*100, j*100)] = [(-n_1*100, j*100)] 
		points[(-(n_1+1)*100, -j*100)] = [(-n_1*100, -j*100)]
	return points
points = GeneratePoints(n_roads)

def GenerateRoads(points):
	"""
	生成随机道路
	"""
	for point in points:
		# print(point)
		# np.random.seed(2)
		temp = (point[0]+random.randint(-rand_range, rand_range), point[1]+random.randint(-rand_range, rand_range))
		for point2 in points:
			# print(points[point2])
			for i in range(len(points[point2])):
				if point == points[point2][i]:
					points[point2][i] = temp
		temp2 = points[point]
		points.pop(point)
		points[temp] = temp2
	print("===========================")
	print(points)
	return points


def ComputeDistance(points):

	"""
	计算距离
	"""
	temp = {}
	for point in points:
		# print(point)
		temp[point] = {}
		for next_point in points[point]:
			# print(next_point)
			vector1 = np.array(point)
			vector2 = np.array(next_point)
			distance = int(np.sqrt(np.sum(np.square(vector1-vector2))))
			temp[point][next_point] = distance
	return temp  ## {point:{next_point:distance,---}}

def GetPointIndex(points):
	point_index = []
	for temp in points:
		point_index.append(temp)
	for i in range(len(point_index)-1):
		for j in range(i+1, len(point_index)):
			if point_index[i][0]>point_index[j][0] and point_index[i][1]>point_index[j][1]:
				temp = point_index[i]
				point_index[i] = point_index[j]
				point_index[j] = temp
	return point_index


def PlotMap(joint):
	plt.figure()
	plt.ion()
	plt.grid()
	point_index = []

	for temp in points:
		point_index.append(temp)
	for i in range(len(point_index)-1):
		for j in range(i+1, len(point_index)):
			if point_index[i][0]>point_index[j][0] and point_index[i][1]>point_index[j][1]:
				temp = point_index[i]
				point_index[i] = point_index[j]
				point_index[j] = temp

	temp = []
	for point in point_index:
		plt.xlim((-140*n_roads, 140*n_roads))
		plt.ylim((-110*n_roads, 110*n_roads))
		plt.scatter(point[0], point[1])
		plt.pause(0.01)
		for next_point in points[point]:
			# print(next_point)
			if ((next_point, point) not in temp) and ((point, next_point) not in temp) :
				# print(temp)
				temp.append((next_point, point))
				plt.scatter(next_point[0], next_point[1], color = "blue")
				plt.pause(0.01)
				plt.plot([point[0], next_point[0]], [point[1], next_point[1]], color="red")
				plt.pause(0.01)
				plt.text(x = 0.5*(point[0]+next_point[0]), y = 0.5*(point[1]+next_point[1]), s = str(joint[point][next_point]), color = "green")
				plt.pause(0.01)
	plt.pause(6)
	plt.show()


if __name__ == "__main__" :
	##joint = {point:{next_point:distance,---}}
	joint = ComputeDistance(GenerateRoads(points))
	print(joint)
	print(len(points))
	print(len(joint))
	print(len(GetPointIndex(joint)))
	PlotMap(joint)