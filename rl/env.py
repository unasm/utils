# -*- coding: UTF-8 -*-
#
# File Name    :    env.py
# Author       :    doujm
# Mail         :    doujm@jiedaibao.com
# Create Time  :    2017-12-04 23:03:37
############################################### 

import os
import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import pyglet

class ArmEnv(object):
    viewer = None

    action_dim = 2
    state_dim = 2 
    # x, y 位置， l 长宽
    goal = {'x' : 100, 'y' : 100, 'l' : 40}
    action_bound = [-1, 1]
    dt = 0.01


    def __init__(self):
        # 记录了两个arm的长度和角度
        self.arm_info = np.zeros(
                2, dtype=[('l', np.float32), ('r', np.float32)])
        self.arm_info['l'] = 100
        self.arm_info['r'] = np.pi / 6
    
    def step(self, action):
        done = False
        r = 0.
        action = np.clip(action, *self.action_bound)
        self.arm_info['r'] += action * self.dt 
        self.arm_info['r'] %= np.pi * 2
        s = self.arm_info['r']
        (a1l, a2l) = self.arm_info['l']
        (a1r, a2r) = self.arm_info['r']
        a1xy = np.array([200., 200.])
        a1xy_ = np.array([np.cos(a1r), np.sin(a1r)]) * a1l + a1xy
        finger = np.array([np.cos(a1r + a2r), np.sin(a1r + a2r)]) * a2l + a1xy_
        
        # 检测finger 是否在 goal 的范围内
        if (self.goal['x'] - self.goal['l'] / 2.0) < finger[0] < (self.goal['x'] + self.goal['l'] / 2.0) :
            if (self.goal['y'] - self.goal['l'] / 2.0) < finger[1] < (self.goal['y'] + self.goal['l'] / 2.0):
                done = True
                r = 1.
        return s, r, done

    def reset(self):
        self.arm_info['r'] = 2 * np.pi * np.random.rand(2)
        return self.arm_info['r']

    def render(self):
        if self.viewer is None:
            self.viewer = Viewer(self.arm_info, self.goal)
        self.viewer.render()

    def sample_action(self):
        return np.random.rand(2) - 0.5


class Viewer(pyglet.window.Window):
    #手臂的宽度
    bar_thc = 5
    batch = None

    def __init__(self, arm_info, goal):
        super(Viewer, self).__init__(width=400, height=400, resizable=False, caption='Arm', vsync=False)
        pyglet.gl.glClearColor(1, 1, 1, 1)
        self.arm_info = arm_info
        self.center_coord = np.array([200, 200])

        self.batch = pyglet.graphics.Batch()

        self.point = self.batch.add(
            4, pyglet.gl.GL_QUADS, None,      
            ('v2f', [
                #四个顶点的位置
                50, 50, 
                50, 100, 
                100, 100, 
                100, 50]), 
            ('c3B' , (86, 109, 249) * 4)
        )

        
        self.arm1 = self.batch.add(
            4, pyglet.gl.GL_QUADS, None, 
            ('v2f', [
                    250, 250, 
                    250, 300, 
                    260, 300, 
                    260, 250
                 ]
            ), 
            ('c3B', (249, 86, 86) * 4)
        )

        self.arm2 = self.batch.add(
            4, pyglet.gl.GL_QUADS, None, 
            ('v2f', [
                    100, 150, 
                    100, 160, 
                    200, 160, 
                    200, 150
                 ]
            ), 
            ('c3B', (249, 86, 86) * 4)
        )


    
        self.drawPoint([
            200 - 5, 200 - 5,
            200 + 5, 200 - 5,
            200 - 5, 200 + 5,
            200 + 5, 200 + 5,
        ])
    def drawPoint(self, positions):
        self.testPoint = self.batch.add(
            4, pyglet.gl.GL_QUADS, None, 
            ('v2f', positions), 
            ('c3B', (149, 80, 16) * 4)
        )

    
    def render(self):
        self._update_arm()
        self.switch_to()
        self.dispatch_events()
        self.dispatch_event('on_draw')
        self.flip()

    def on_draw(self):
        self.clear()
        self.batch.draw()

    def _update_arm(self):
        (a1l, a2l) = self.arm_info['l']
        (a1r, a2r) = self.arm_info['r']
        #print self.arm_info['l'], self.arm_info['r']
        a1xy = self.center_coord
        a1xy_ = np.array([np.cos(a1r), np.sin(a1r)]) * a2l + a1xy
        a2xy_ = np.array([np.cos(a1r + a2r), np.sin(a1r + a2r)]) * a2l + a1xy_

        a1tr, a2tr = np.pi / 2 - self.arm_info['r'][0], np.pi / 2 - self.arm_info['r'].sum()
        xy01 = a1xy + np.array([-np.cos(a1tr), np.sin(a1tr)]) * self.bar_thc
        xy02 = a1xy + np.array([np.cos(a1tr), -np.sin(a1tr)]) * self.bar_thc
        xy11 = a1xy_ + np.array([np.cos(a1tr), -np.sin(a1tr)]) * self.bar_thc
        xy12 = a1xy_ + np.array([-np.cos(a1tr), np.sin(a1tr)]) * self.bar_thc

        xy11_ = a1xy_ + np.array([np.cos(a2tr), -np.sin(a2tr)]) * self.bar_thc
        xy12_ = a1xy_ + np.array([-np.cos(a2tr), np.sin(a2tr)]) * self.bar_thc
        xy21 = a2xy_ + np.array([-np.cos(a2tr), np.sin(a2tr)]) * self.bar_thc
        xy22 = a2xy_ + np.array([np.cos(a2tr), -np.sin(a2tr)]) * self.bar_thc

        armOneInfo = (xy01, xy02, xy11, xy12)
        #print armOneInfo
        self.arm1.vertices = np.concatenate(armOneInfo)
        self.arm2.vertices = np.concatenate((xy11_, xy12_, xy21, xy22))

if __name__ == "__main__":
    env = ArmEnv()
    while True:
        env.render()
        for i  in range(400):
            env.render()
            #print i, env.sample_action()
            env.step(env.sample_action())
