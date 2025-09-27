# BankSimulation

A simulation program for comparing *single queue vs multiple queue systems* in a bank.  
The simulation analyzes customer wait times, teller service times, and overall efficiency.               

#Contributors

-Rudra Pratap Sahoo(24155648)
-Ankit Kumar(24155607)
-Ritesh Das(2405068)

# Folder Structure

BankSimulation/
├── src/               # All .c source files
│   ├── qSim.c
│   ├── customer.c
│   ├── event.c
│   ├── queue.c
│   └── teller.c
├── include/           # All header files
│   ├── event.h
│   ├── queue.h
│   ├── teller.h
│   └── customer.h
├── bin/                     # Executable
├── test/                   # Simulation results, logs, graphs
├── Makefile             # Build target for qSim
├── README.pdf        # Program summary & analysis

#Run programme with(command line codes)

-- gcc src\qSim.c src\event.c src\queue.c src\teller.c src\customer.c -Iinclude -o bin\qSim.exe      #for compile the Bank simulation

--./bin/qSim.exe #customers #tellers simulationTime averageServiceTime   
(inputs)

--.\bin\qSim.exe #customers #tellers simulationTime averageServiceTime    > .\test\output4.txt   (for save the outputs in test folder)

--gnuplot plot.gnu  (Run gnu plot)

--ii .\test\average_time_vs_tellers.png  (to see the graph)

#Parameters
#customers — number of customers to simulate (integer)
#tellers — number of tellers (integer)
simulationTime — simulation time in minutes (float)
averageServiceTime — average time to serve a customer in minutes (float)

#Issues 
-- Occasionally negative average wait times (due to arrival time/service time calculation method).
-- Large numbers of customers may slow simulation runtime.
#GNUPlot Graph
The project includes a GNUPlot script to plot average time in bank vs number of tellers: plot.gnu


