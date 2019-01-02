# coding:utf-8
import numpy as np
import serial
import os
import time


def random_action():
	return np.random.choice([0, 1])

def get_action(next_state, episode):
	epsilon = 0.5 * (1 / (episode + 1))#徐々に最適行動のみをとる、ε-greedy法
	if epsilon <= np.random.uniform(0, 1):
		a = np.where(q_table[next_state]==q_table[next_state].max())[0]
		next_action = np.random.choice(a)
	else:
		next_action = random_action()
	return next_action

def step(state, action):
	reward = 0
	time.sleep(2)
	if action==0:
		ser.write('b'.encode('utf-8'))			# ブザーを鳴らして電源をON/OFF
	else:
		ser.write('l'.encode('utf-8'))			# LEDを光らせて餌を貰う
	time.sleep(1)
	# arduinoからstateとrewardが送られてくる
	state	= int(ser.read())
	reward	= int(ser.read())
	return state, reward

def update_Qtable(q_table, state, action, reward, next_state):
	gamma = 0.9
	alpha = 0.5
	next_maxQ=max(q_table[next_state])
	q_table[state, action] = (1 - alpha) * q_table[state, action] +\
			alpha * (reward + gamma * next_maxQ)

	return q_table

max_number_of_steps = 5  #1試行のstep数
num_episodes = 10  #総試行回数
q_table = np.zeros((2, 2))

# シリアル通信の設定
ser = serial.Serial()
ser.baudrate = 9600
for file in os.listdir('/dev'):
	if "tty.usbmodem" in file:
		ser.port = '/dev/'+file
		ser.open()


for episode in range(num_episodes):  #試行数分繰り返す
	state = 0
	episode_reward = 0

	for t in range(max_number_of_steps):  #1試行のループ
		action = get_action(state, episode)	# a_{t+1} 
		next_state, reward = step(state, action)
		print(state, action, reward)
		episode_reward += reward  #報酬を追加
		q_table = update_Qtable(q_table, state, action, reward, next_state)
		state = next_state
	ser.write('r'.encode('utf-8'))      # arduinoリセット
	time.sleep(2)

	print('episode : %d total reward %d' %(episode+1, episode_reward))
	print(q_table)
