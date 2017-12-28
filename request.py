# -*- coding: UTF-8 -*-
#
# File Name    :    request.py
# Author       :    doujm
# Mail         :    doujm@jiedaibao.com
# Create Time  :    2017-08-05 17:38:41
############################################### 

import os
import sys
import numpy as np
import pandas as pd
import time
import subprocess
import re
import hashlib
import csv
from pprint import pprint
import requests
from bs4 import BeautifulSoup
from multiprocessing import Pool


isLocal = True


def getPageData(url):
    cnt = 3
    try :
        while cnt > 0 :
            req = requests.get(url, timeout=3)
            if len(req.text) > 0:
                content = req.text.encode('UTF-8')
                soup = BeautifulSoup(content, 'lxml')
                data = soup.select("#credit-info-data")
                #print len(data)
                if len(data) > 0:
                    #print data[0].get_text().strip()

                    # 直接返回 json 信息
                    return 0, data[0].get_text().strip().encode("UTF-8")
                # 如果http请求本身是成功的，就不用继续获取数据
                if req.status_code == 200:
                    return 1, url
                #return req.text.encode('UTF-8')
            cnt -= 1
        #raise Exception("get_data_exception\t" + url)
    except Exception , e:
        print e
        #因为异常
        return 2, url
    return 3, url


if __name__ == "__main__":

    #url = "https://www.renrendai.com/lend/detailPage.action?loanId=13611" 
    #url = "https://www.renrendai.com/lend/detailPage.action?loanId=2385060"
    #isOk, data = getPageData(url)
    #print isOk
    #print data
    #print len(data)
    #exit()
    #getListOne("one.html");
    #getListTwo("two.html");
    dataFile = "/Users/tianyi/Documents/lizhiyong/renrendai/data/jsonData_secTime.txt"
    logError = "/Users/tianyi/Documents/lizhiyong/renrendai/data/missDataLog_secTime.txt"
    errIdPath = "/Users/tianyi/Documents/lizhiyong/renrendai/data/missid.txt"
    #if os.path.isfile(dataFile):
    #    print "数据文件存在，请首先删除或者备份"
    #    exit()
    fp = open(dataFile, "a")
    fpLog = open(logError, "a")
    processNum = 10
    pool = Pool(processes=processNum)    #  并发数

    resultArr = []

    startTime = time.time()
    
    #maxLoanId = 6
    maxLoanId = 2385265
    #maxLoanId = 2385
    try:
        #for loadIn in (1, 2385265):
        #for loanId in range(280553, maxLoanId):
        for loanId in open(errIdPath):
            url = "https://www.renrendai.com/lend/detailPage.action?loanId=%s" % loanId.strip()
            print url
            result = pool.apply_async(getPageData, (url, ))
            resultArr.append(result)
            if len(resultArr) >= processNum * 28 or loanId == (maxLoanId - 1):
                #多写日志，防止崩溃
                writeBuffer = ""
                errMsgBuffer = ""
                for res in resultArr:
                    isOk, resData = res.get()
                    #print isOk, resData
                    if isOk == 0:
                        writeBuffer = writeBuffer + resData + "\n"
                    else:
                        errMsg = "%d\t%s" % (isOk, resData)
                        print errMsg
                        errMsgBuffer = errMsgBuffer + "\n" + errMsg
                # 重新清空 result 数组
                fp.write(writeBuffer)
                fpLog.write(errMsgBuffer)
                resultArr = []
    except Exception , e:
        print (e)
        print (str(e))
        print ("exception_2\t %s" % str(e))
        raise e
    pool.close()
    pool.join()
    print("Done")
    fp.close()
    fpLog.close()
    print "runtime ", (time.time() - startTime)

