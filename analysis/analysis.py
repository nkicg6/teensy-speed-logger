# analyze data from teensy speed logger
# Author: Nick George
# contact: nicholas.m.george@ucdenver.edu
# updated: 2018-03-10

# diameter of disc (magnet to center, not edge to center) = 14cm
#

import os
import numpy as np
import pandas as pd

# testing
TEST_FILE = "../test/data/SPEED_test.csv"




def clean_data(string_version):
    """take in string version from python's file read
    return a df with the correct formatting. all data
    separated by '---' will be assigned a different
    'series' number for clarity
    """
    segmented = string_version.split("----")
    cleaned = [i for i in segmented if i != "\n" and "#" not in i]
    list_version = [{"time_point":i.split("\n")} for i in cleaned for x in range(len(cleaned))]
    df_list = [pd.DataFrame.from_dict(i) for i in list_version]
    # join all the dfs with a label.
    concatenated_df = pd.concat(df_list, keys = [str(i) for i in range(len(df_list))], names = ["series"])
    return concatenated_df



# read in file for proper string formatting
with open(TEST_FILE, "r") as f:
    string_version = f.read()

cleaned = clean_data(string_version)

print(cleaned)
