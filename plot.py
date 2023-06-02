import numpy as np
from scipy import signal
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from serial import Serial


#initialize serial port
ser = Serial()
ser.port = 'COM5' #Arduino serial port
ser.baudrate = 9600
ser.timeout = 10 #specify timeout when using readline()
ser.open()
if ser.is_open==True:
	print("\nAll right, serial port now open. Configuration:\n")
	print(ser, "\n") #print serial parameters

# Create figure for plotting
fig, ax = plt.subplots()
freq = 0
duty = 0

# This function is called periodically from FuncAnimation
def animate(i, xs, ys):
    #Aquire and parse data from serial port
    global freq
    global duty
    line = ser.readline()
    line = line.decode("ascii")
    line = line.split(",")
    line[1] = line[1].replace("\r\n","")

    if (int(line[0]) == 0):
        if int(line[1] != 0):
            try: 
                freq = 1000/int(line[1])
            except:
                freq = 1
            
    if (int(line[0]) == 1):
        if freq != 0:
            duty = int(line[1])/(1000/freq)

    print(freq, duty)

    # Draw x and y lists
    ax.clear()
    title = "PWM Waveform at " + str(freq) +"Hz, " + str(duty*100) + "% Active"
    ax.set_title(title)
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("Amplitude (v)")
    
    t = np.linspace(0, (1/freq)*3, 2000, endpoint=False)
    ax.plot(t, signal.square(2 * np.pi * freq * t, duty=duty), label="Waveform", alpha=0.8)
    ax.plot(t, signal.sawtooth(2 * np.pi * freq * t), label="Counter Value", alpha=0.8)
    ax.plot(t, np.ones_like(t)*(duty*2-1), label="CCR Value", alpha=0.8)
    #ax.ylim(-2, 2)
    plt.legend(loc='upper right')
            

# # Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(freq, duty), interval=50)
plt.show()