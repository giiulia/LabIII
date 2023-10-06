# Nuclear and subnuclear physics laboratory

The goal of my group's experiment was to determine the velocity and flux of cosmic muons on the ground using two organic scintillators. 
The steps and measures needed to complete the project are listed in the [project sheet](/muons_factsheet.pdf) and their execution is well described in this repository.

# Instrumentation
The instrumentation needed to detect the passage of cosmic muons in our laboratory and process the signals:
- Scintillators S1 and S2 30x80 cm<sup>2</sup>.
- Test scintillators T1 and T2 (smaller).
- Threshold discriminator.
- Coincidence unit.
- TDC ("Time to Digital Converter"), converts the time interval between the logical start and logical stop inputs to a linear signal whose amplitude is proportional to the said time interval.
- ADC ("Analog to Digital Converter"), can address multiple linear inputs and a logic input (gate). When the gate is open the analog signals are recorded by distributing their amplitude in 1024 channels.
- LEMO cables to induce delays.
- Oscilloscope.
- CAMAC BUS which allows data exchange between plug-in [CAMAC modules](/CAMAC_modules) and a CRATE CONTROLLER interfaced with a PC.

# Optimization and characterization of scintillators
The instrumentation preparation phase was organized as follows.
- Search for the optimal threshold to remove noise and background signals. This process was necessary both for [large](/Threshold_big_scintillators) and [small](/Threshold_small_scintillators) scintillators.
- Choosing the optimal supply voltage to achieve the best [efficiency](/Efficiency).
- Evaluation the rate of [accidental coincidences](/Accidental_coincidences).
- [TDC calibration](/TDC_calibration)

# Flux and velocity measures
- [asymmetry](/Est_Ovest_asymmetry)
- [trajectory simulation](/Trajectory_simulation)
- [velocity](/Muons_velocity)
- 
