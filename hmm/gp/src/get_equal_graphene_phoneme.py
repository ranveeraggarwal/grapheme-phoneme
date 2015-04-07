import json
import sys
from constants import cmu_dict, equal_graph_phones_file

a = []
try:
    with open(cmu_dict) as f:
        a = f.readlines()
except IOError as e:
    sys.stderr.write(e)
    sys.exit(0)

equal_phones = []

for elem in a:
    if set('\'"().-_').intersection(elem):
        continue
    temp = elem.split('\t')
    graph,phone = temp[0].strip('()123456789'), temp[1].strip('\n\r')
    graph_len = len(graph)
    phone_array = phone.split(' ')
    phone_len = len(phone_array)
    if graph_len == phone_len:
        equal_phones.append((graph, phone))

'''
for elem in a:
    temp = elem.split('\t')
    graph,phone = temp[0], temp[1].strip('\n\r')
    graph_len = len(graph)
    phone_array = phone.split(' ')
    phone_len = len(phone_array)
    if graph_len == phone_len:
        equal_phones.append((graph, phone))
'''

try:
    with open(equal_graph_phones_file, 'w') as outfile:
        json.dump(equal_phones, outfile)
except IOError as e:
    sys.stderr.write(e)
    sys.exit(0)

