import sys
import matplotlib.pyplot as plt
from datetime import datetime

def convert_milliseconds_to_hhmmss(milliseconds):
    seconds = milliseconds // 1000
    minutes, seconds = divmod(seconds, 60)
    hours, minutes = divmod(minutes, 60)
    return '{:02d}:{:02d}:{:02d}'.format(hours, minutes, seconds)

def plot_speed(filename):
    time = []
    speed_unfiltered = []
    speed_filtered = []

    with open(filename, 'r') as file:
        for line in file:    
            values = line.split()
            time.append(float(values[0]))
            speed_unfiltered.append(float(values[1]))
            speed_filtered.append(float(values[2]))

    plt.plot(time, speed_unfiltered, label='Raw', color='red')
    plt.plot(time, speed_filtered, label='Filtered', color='blue')
    plt.xlabel('Time (s)')
    plt.ylabel('')
    plt.legend()
    plt.gcf().autofmt_xdate()
    plt.show()

if len(sys.argv) < 2:
    #print("Missing filename")
    filename = "input_data.txt"
else:
    filename = sys.argv[1]

plot_speed(filename)