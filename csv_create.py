#!/usr/bin/python3

import csv
import sys
import re

tabulka = "tabulka_cansat.csv"

main_catch = re.compile(r"""(?P<hodiny>\d{1,2}):(?P<minuty>\d{1,2}):(?P<sekundy>\d{1,2})TD(?P<teplota_dht>\d{2}\.\d{2})C\s?VL(?P<vlhkost>\d{2})TB(?P<teplota_bmp>\d{2}\.\d{2})\sTl(?P<tlak>\d{5})NV(?P<nadm_vyska>\d{3}\.\d{2})Sv(?P<svetlo>\d{2,3}\.\d{2})""")

if len(sys.argv) > 0 and sys.argv[1] in {"-h", "--help"}:
    print("usage: {} <file>".format(sys.argv[0]))
    data = False
else:
    data = sys.argv[1]

finalni_data = []

if data:
    with open(data, "r") as file:
        content = file.readlines()
        for row in content:
            for match in main_catch.finditer(row):
                hodiny = match.group("hodiny") + ":" + str(int(match.group("minuty"))+20) + ":" + match.group("sekundy")
                teplota_dht = match.group("teplota_dht")
                vlhkost = match.group("vlhkost")
                teplota_bmp = match.group("teplota_bmp")
                tlak = str(float(match.group("tlak")) * 0.03024858021) #*0.03024858021
                nadm_vyska = str(float(match.group("nadm_vyska")) + 116) #+116
                svetlo = match.group("svetlo")
                print("hodiny: {}, teplota_dht: {}C, vlhkost: {}%, teplota_bmp: {}C, tlak: {}P, nadm_vyska: {}mnm, svetlo: {}lux".format(hodiny, teplota_dht, vlhkost, teplota_bmp, tlak, nadm_vyska, svetlo))
                finalni_data.append([hodiny, teplota_dht, vlhkost, teplota_bmp, tlak, nadm_vyska, svetlo])
    with open(tabulka, "w", newline="") as tabulka2:
        vypsat = csv.writer(tabulka2, delimiter=",")
        vypsat.writerows(finalni_data)
