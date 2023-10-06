# Nuclear and subnuclear physics laboratory

The goal of my group's experiment was to determine the velocity and flux of cosmic muons on the ground using two organic scintillators. 
The steps and measures needed to complete the project are listed in the [project sheet](/muons_factsheet.pdf) and their execution is well described in this repository.

# Instrumentation
To detect the passage of cosmic muons in our laboratory and process the signals were used:
- 2 scintillators S1 and S2 with an area of 30x80 cm<sup>2</sup>.
- 2 test scintillators T1 and T2 (smaller).
- A Threshold discriminator, when a linear signal exceeds the set threshold, it produces a logic signal.
- A Coincidence unit, receives two or more inear signals and provides a logical output if the time interval between the inputs is less than a fixed time limit.
- TDC ("Time to Digital Converter"), converts the time interval between the logical start and logical stop inputs to a linear signal whose amplitude is proportional to the said time interval.
- ADC ("Analog to Digital Converter"), can address multiple linear inputs and a logic input (gate). When the gate is open the analog signals are recorded by distributing their amplitude in 1024 channels.
- LEMO cables to induce delays.
- Oscilloscope.
- CAMAC BUS which allows data exchange between plug-in [CAMAC modules](/CAMAC_modules) and a CRATE CONTROLLER interfaced with a PC.

# Optimization and characterization of scintillators
The instrumentation preparation phase was organized as follows.
- Search for the optimal [threshold](/Threshold_optimization) to remove noise and background signals. This process was necessary both for [large](/Threshold_optimization/Large_scintillators) and [small](/Threshold_optimization/Small_scintillators) scintillators.
- Choosing the optimal supply voltage to achieve the best [efficiency](/Efficiency).
- Linear [TDC calibration](/TDC_calibration), necessary to interpret the number of channels in terms of nanoseconds.
- Evaluation the rate of [accidental coincidences](/Accidental_coincidences), to extablish whether the number of counts should be corrected before the muon flux is determined.

# Flux and velocity measures
- My group verified the zenith angle dependence of the muon flux according the cos<sup>2</sup>($\theta$) function and its East-West [asymmetry](/Est_Ovest_asymmetry) due to the Earth's magnetic field.
- [Trajectory simulations](/Trajectory_simulation) helped evaluate the maximum the maximum viable path in the detector for a muon for it to be detected by both scintillators (necessary to measure velocity).
- A plot of different relative distances S1-S2 and the time elapsed between passing through one detector and the other has been interpolated with a line in order to determine the average [muons velocity](/Muons_velocity) to the ground.
