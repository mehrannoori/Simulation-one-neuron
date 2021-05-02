################################################
# Plot script v.1.1                            #
# By Mehran noori                              #
# Run the script by command : $python3 plot.py #
################################################
import matplotlib.pyplot as plt

def read(file_name, t, v, m, h, n):
    file = open(file_name, 'r')
    while True:
        line = file.readline()
        if line == '':
            break
        elif line[0] == '#':
            pass
        else:
            r = line.split(',')
            t.append(float(r[0]))
            v.append(float(r[1]))
            m.append(float(r[2]))
            h.append(float(r[3]))
            n.append(float(r[4]))

def ploting(t, v, m, h, n):
    fig, ax = plt.subplots(2, 1)
    ax[0].plot(t, v, 'r')
    ax[1].plot(t, m, 'g')
    ax[1].plot(t, h, 'k')
    ax[1].plot(t, n, 'r')

    ax[0].grid(True)
    ax[0].set_title('Voltage')
    ax[0].legend(labels='V')
    ax[0].set_xlabel('time (ms)')
    ax[0].set_ylabel('V (mV)')

    ax[1].grid(True)
    ax[1].set_title('Probability')
    ax[1].legend(labels=('m','h','n'))
    ax[1].set_xlabel('time (ms)')
    ax[1].set_ylabel('m ,h, n')

    plt.tight_layout()
    plt.show()

def main():
    file_name = 'hh_data_euler.txt'
    
    t = []
    v = []
    m = []
    h = []
    n = []
    
    read(file_name, t, v, m,h,n)
    ploting(t, v, m, h, n)

if __name__ == "__main__":
    main()