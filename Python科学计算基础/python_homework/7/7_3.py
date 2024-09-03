# -*- coding: utf-8 -*-
"""
Created on Thu May  4 15:21:25 2023

@author: 28932
"""



def extract_data(filename):
    with open(filename,'r') as infile:
        infile.readline()
        Insentences = []
        for line in infile:
            if line.find('In') >= 0:
                everysentences = ''
                words = line.split()
                del words[0]
                for i in words:
                    everysentences = everysentences + i + ' '
                Insentences.append(everysentences)
        return Insentences
Insentences = extract_data('C:/Users/28932/Desktop/程序7.21.txt')
with open('C:/Users/28932/Desktop/输出.txt','w') as outfile:
    for i in Insentences:
        print(i)
        outfile.write(i)
        outfile.write('\n')
        