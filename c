import os
import re
import time
my_fpath=input("enter the file path\n")#数据源目录
my_efpath=input("enter the end file path\n")#导出数据目录
def makelist(line):
        #按空格区分字符串，并存入列表
        reallist=[]
        realstr=""
        for i in line:
            if i!=" ":
                realstr+=i
            else:
                reallist.append(realstr)
                realstr=""
        reallist.append(realstr)
        return reallist
def set(lis):#
    strc=[]
    for i in lis:
        strc.append(i)
    return strc
num=[]#有问题，每次循环num会被初始化
n=1
while True: 
    num.append(n)
    x=num[n-1]
    for filename in os.listdir(my_fpath):#遍历文件夹下的文件名
        if re.match("Z_SURF_I_00016-REG_",filename):#str.startwith()(
            with open(my_efpath+"\\"+filename+"导出数据.txt","a+") as before:
                before.write("\n"+"第"+"".join(str(x))+"次记录如下\n")
            with open(my_fpath+"\\"+filename) as f:#打开其中一个文件
                sstr=""
                for line in f.readlines():
                    line.strip()
                    reallist = makelist(line)
                    if reallist[0]=="00016":
                        str1="此区间号为"+reallist[0]+"\n"
                        strs=set(reallist[1])
                        str2="测试时间为 "+''.join(strs[0:4])+"年"+''.join(strs[4:6])+"月"+''.join(strs[6:8])+"日"+''.join(strs[8:10])+"时"+''.join(strs[10:12])+"分00秒"+'\n'
                        strs=set(reallist[2])
                        str3="维度为 "+"".join(strs[:2])+"度"+"".join(strs[2:4])+"分"+"".join(strs[-2:])+"秒"+"\t"
                        strs=set(reallist[3])
                        str4="经度为 "+"".join(strs[:3])+'度'+"".join(strs[3:5])+'分'+"".join(strs[-2:])+'秒'+"\n"
                        strs=set(reallist[4])
                        str5="海拔为 "+"".join(strs[-3:-2])+'.'+"".join(strs[-1])+"米"+"\t"
                        str6="质量控制标识为 "+reallist[5]+"\n"
                        sstr=str1+str2+str3+str4+str5+str6               
                    elif reallist[0]=="TH":
                        str1="当前气温为 "+reallist[1][0:3]+'.'+reallist[1][3]+'℃\n'
                        str2="最高气温为 "+reallist[2][0:3]+'.'+reallist[2][3]+'℃\t'+"出现时间为"+reallist[3][0:2]+':'+reallist[3][2:4]+'\n'
                        str3="最低气温为 "+reallist[4][0:3]+'.'+reallist[4][3]+'℃\t'+"出现时间为"+reallist[5][0:2]+':'+reallist[5][2:4]+'\n'
                        str4='露点温度为 '+reallist[6][0:3]+'.'+reallist[6][3]+'℃\n'
                        str5='相对湿度为 '+reallist[7][-2:]+'%'+'\t'
                        str6='最小相对湿度为 '+reallist[8][-2:]+'%'+'\t'
                        str7='最小相对湿度出现时间为 '+reallist[9][0:2]+':'+reallist[9][2:4]+'\n'
                        str8='水汽压为 '+reallist[10][1]+'.'+reallist[10][2]+'hpa'+'\n'
                        sstr='\n'+str1+str2+str3+str4+str5+str6+str7+str8+'\n'
                    elif reallist[0]=="RE":
                        str1="小时降水量为"+reallist[1][0:3]+'.'+reallist[1][3]+"mm"+'\n'
                        sstr=str1+'\n'
                    elif reallist[0]=="RT":
                        str1="当前路面温度为"+reallist[1][0:3]+'.'+reallist[1][3]+'℃\n'
                        str2="路面最高温度为"+reallist[2][0:3]+'.'+reallist[2][3]+'℃\t'
                        str3='路面最高温度出现时间为'+reallist[3][0:2]+':'+reallist[3][2:4]+'\n'
                        str4='路面最低温度为'+reallist[4][0:3]+'.'+reallist[4][3]+'℃\t'
                        str5='路面最低温度出现时间为'+reallist[5][0:2]+':'+reallist[5][2:4]+'\n'
                        str6='路基温度为'+reallist[6][0:3]+'.'+reallist[6][3]+'℃\n'
                        sstr=str1+str2+str3+str4+str5+str6+'\n'
                    elif reallist[0]=="VV":
                        str1="1分钟平均水平能见度"+reallist[1][-4:]+'米\n'
                        str2='最小能见度'+reallist[2][-4:]+'米\n'
                        str3='最小能见度出现时间'+reallist[3][:2]+':'+reallist[3][-2:]+'\n'
                        sstr=str1+str2+str3+'\n'
                    else:
                        sstr="这一行格式错误或本程序不支持读取\n"
                    with open(my_efpath+"\\"+filename+"导出数据.txt","a+") as mw:#打开导出目录的一个新文件
                        mw.write(sstr)
        else:
            print("找到了一个文件名为"+filename+"的格式错误的文件，无法读取")
    print("we will check again in 3 seconds")
    n+=1
    time.sleep(3)
