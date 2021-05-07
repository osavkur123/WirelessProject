import numpy as np
import pandas as pd
from collections import defaultdict
MAC3="B8:27:EB:CC:AA:D5"
MAC2="B8:27:EB:75:C1:31"
MAC1="B8:27:EB:6C:F0:84"

def def_value():
    return "NULL"


def parsefile(filename):
    entries = []
    with open(filename) as fd:
        entry = defaultdict(def_value)
        for line in fd :
            print(line)
            if "Address:" in line :
                split_array = line.split("Address:")
                mac = split_array[1].strip()
                fd.readline()
                fd.readline()
                req_str = fd.readline()
                signal_strength = req_str.split("Signal level=")[1].strip().split(" ")[0]
                if mac == MAC1 :
                    entry["MAC1"] = signal_strength
                if mac == MAC2 :
                    entry["MAC2"] = signal_strength
                if mac == MAC3 :
                    entry["MAC3"] = signal_strength
            if line.strip().startswith("2021-"):
                entry["TIMESTAMP"] = line.strip()
            if line.strip() == "*-*" :
                print(entry)
                if (entry["MAC1"] == "NULL"):
                    entry["MAC1"] = "NULL"
                if (entry["MAC2"] == "NULL"):
                    entry["MAC2"] = "NULL"
                if (entry["MAC3"] == "NULL"):
                    entry["MAC3"] = "NULL"
                entries.append(entry)
                entry = defaultdict(def_value)
                print(entry)
    print(entries)
    df = pd.DataFrame(entries)
    print(df)
    df.to_csv("network_data.csv")

parsefile(input("Enter network log path to parse: "))
