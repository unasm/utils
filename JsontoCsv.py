# -*- coding: UTF-8 -*-
#
# File Name    :    JsontoCsv.py
# Author       :    doujm
# Mail         :    doujm@jiedaibao.com
# Create Time  :    2017-06-24 17:27:56
############################################### 

import os
import sys
import json

fd = open(sys.argv[1])
data =  fd.readline()
firstLine = json.loads(data)
template = {}
idxPos = 0
for key in firstLine:
    template[key] = idxPos
    idxPos += 1
#print template

linePos = 1
lenTemplate = len(template)
resStr = "\t" . join(firstLine.values()) + "\n"
try: 
    for line in fd:
        #print line
        row = json.loads(line)
        if len(row) != lenTemplate:
            raise ValueError("数值不统一 line : %s , value : %s" % (linePos, line))
        tempBuf = []
        for key in template:
            if not row.has_key(key):
                raise ValueError("异常key : %s , line : %s, value : %s" % (key, linePos, line))
            tempBuf.append(row[key])

        resStr += "\t" . join(tempBuf) + "\n"
        #resStr += "\t" . join(row.values()) + "\n"
        linePos += 1
    #print resStr
    print resStr
finally:
    fd.close()

