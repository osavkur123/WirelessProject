import numpy as np
import pandas as pd
from collections import defaultdict
def def_value():
	return "NULL"
def parsefile(filename):
	entries = []
	with open(filename) as fd:
		# Timestamp, Bit Rate, Mac address, Signal Strength
		entry = defaultdict(def_value)
		for line in fd :
			if("Access Point:" in line):
				split_array = line.split("Access Point:")
				if(split_array[1].strip().startswith("Not-")):
					entry['MAC_ADDRESS'] = "NULL"
				else:
					entry['MAC_ADDRESS'] = split_array[1].strip()

			if("Bit Rate=" in line):
				entry['BIT_RATE'] = line.split("=")[1].split(" ")[0]
			if("Signal level=" in line):
				entry["SIGNAL_STRENGTH"] = line.split("Signal level=")[1].strip().split(" ")[0]
			if(line.strip().startswith("2021-")):
				entry["TIMESTAMP"] = line.strip()
			if(line.strip() == "*-*"):
				print(entry)
				if(entry["BIT_RATE"] == "NULL"):
					entry["BIT_RATE"] = "NULL"
				if(entry["SIGNAL_STRENGTH"] == "NULL"):
					entry["SIGNAL_STRENGTH"] = "NULL"
				entries.append(entry)
				entry = defaultdict(def_value)
				print(entry)

	df = pd.DataFrame(entries)
	df.to_csv("ssid_data.csv")

parsefile(input("Enter file name:"))
