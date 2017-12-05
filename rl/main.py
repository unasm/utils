# -*- coding: UTF-8 -*-
#
# File Name    :    ./main.py
# Author       :    doujm
# Mail         :    doujm@jiedaibao.com
# Create Time  :    2017-12-04 23:36:17
############################################### 

import os
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from env import ArmEnv
from rl import DDPG

MAX_EPISODES = 500
MAX_EP_STEPS = 200

env = ArmEnv()
s_dim = env.state_dim
a_dim = env.action_dim
a_bound = env.action_bound


rl = DDPG(a_dim, s_dim, a_bound)
for i in range(MAX_EPISODES):
    s = evn.reset()
    for j in range(MAX_EP_STEPS):
        env.render()
        a = rl.choose_actions(s)
        s_, r, done = env.step(a)
        rl.store_transition(s, a, r, s_)
        if rl.memory_full():
            rl.learn()
        s = s_
