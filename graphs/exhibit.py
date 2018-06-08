import argparse
import matplotlib.pyplot as plt
import csv
import math

parser = argparse.ArgumentParser(description="Exhibit.")
parser.add_argument('-r', '--runs', type=int, default=5, help="number of runs to graph")
parser.add_argument('-t', '--testcase', type=int, help="number of the testcase (for the label)")
parser.add_argument('-i', '--in-csv', type=str, help="path to CSV report to read")
parser.add_argument('-o', '--out-png', type=str, help="filename for the final PNG")
parser.add_argument('-w', '--width', type=int, default=20, help="width of the PNG, in inches")
parser.add_argument('-y', '--height', type=int, default=8, help="height of the PNG, in inches")

args = parser.parse_args()

# avg
a_ys_by_run = []
a_xs_by_run = []

# best
b_ys_by_run = []
b_xs_by_run = []

for _ in range(args.runs):
    a_ys_by_run.append([])
    b_ys_by_run.append([])
    a_xs_by_run.append([])
    b_xs_by_run.append([])

# Read from CSV
with open(args.in_csv, 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
        run = int(row['Run']) - 1 # 1-based indexing in csv

        a_xs_by_run[run].append(int(row['Iteration']))
        b_xs_by_run[run].append(int(row['Iteration']))

        a_ys_by_run[run].append(float(row['Area']))
        b_ys_by_run[run].append(float(row['BestArea']))

# Plot
fig = plt.figure(figsize=(args.width, args.height))

a_ax = fig.add_subplot(121)
a_ax.set(xlabel="Iteracija", ylabel="Energija (E)", title="Energija trenutnog rešenja za primer {}".format(args.testcase))

for i in range(args.runs):
    a_ax.plot(a_xs_by_run[i], a_ys_by_run[i], label="Pokretanje {}".format(i + 1))
a_ax.legend(loc='upper right')

b_ax = fig.add_subplot(122)
b_ax.set(xlabel="Iteracija", ylabel="Energija (E)", title="Najbolja energija rešenja za primer {}".format(args.testcase))
for i in range(args.runs):
    b_ax.plot(b_xs_by_run[i], b_ys_by_run[i], label="Pokretanje {}".format(i + 1))

b_ax.legend(loc='upper right')

fig.savefig(args.out_png)
