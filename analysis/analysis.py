# analyze data from teensy speed logger
# Author: Nick George
# contact: nicholas.m.george@ucdenver.edu
# updated: 2018-03-10

import os
import numpy as np
import pandas as pd

TEST_FILE = "../test/data/SPEED_test.csv"
with open(TEST_FILE, "r") as f:
    string_version = f.read()


segmented = string_version.split("----")
cleaned = [i for i in segmented if i != "\n" and "#" not in i]
joined = {"timestamp":"\n".join(cleaned)}
print(joined)
df = pd.DataFrame(data = joined, dtype = np.int8)
#print(df)
#data = pd.read_csv(TEST_FILE, comment = "#")
