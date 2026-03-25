Getters
    Motor.isDone()
            Returns true if the motor has completed its movement, false if it's still in motion.

    Motor.isSpinning()
        Returns true if the motor is currently spinning, false if it's stopped.

    Motor.position(degrees)
        Returns the motor's current position in degrees.

    Motor.velocity(percent)
        Returns the motor's current velocity as a percentage of its maximum speed.

    Motor.current(amp)
        Returns the current draw of the motor in amps.

    Motor.power(watt)
        Returns the power consumption of the motor in watts.

    Motor.torque(nm)
        eturns the torque output of the motor in Newton-meters.

    Motor.efficiency(percent)
        Returns how efficiently the motor is running, as a percentage.

    Motor.temperature(percent)
        Returns the motor's current temperature as a percentage of its maximum safe temperature.

Mutators
    Motor.setPosition(position, units)
    Sets the motor's position to any given value. Commonly used to reset the encoder by setting the position to 0.

    units: degrees or turns


    Motor.setVelocity(velocity, units)
    Sets the motor's speed without causing it to move. A negative value spins in the opposite direction; 0 stops the motor.
    UnitsRangeNotespercent-100 to 100rpm-600 to 600Depends on installed gear cartridge
    Cartridge RPM limits:

    🔴 Red — ±100 rpm
    🟢 Green — ±200 rpm
    🔵 Blue — ±600 rpm


    Motor.setStopping(brakeType)
    Sets how the motor behaves when stopped.

        brake — stops immediately, but won't resist outside forces
        coast — gradually slows to a stop
        hold — stops immediately and holds position against outside forces using the built-in encoder


    Motor.setMaxTorque(value, units)
        Sets the maximum torque output of the motor.

    units: percent — range: 0 to 100


    Motor.setTimeout(time, seconds)
        Sets a time limit for movement commands. If the motor can't reach its target (e.g. a claw hitting a mechanical limit), the timeout prevents it from blocking the rest of the program indefinitely.


Motor Actions
    Parameters

        directionType — forward or reverse
        rotations — distance to travel
        units — turns or degrees
        blocking (optional) — pass false to allow the program to continue before the action completes


    Methods
        Motor.spin(directionType)
            Spins continuously in the given direction until stopped.

            Optional voltage control: Motor.spin(directionType, voltage, volt)

            Range: -12V to 12V
            Negative voltage reverses the spin direction




        Motor.spinFor(directionType, rotations, units)
            Moves a set distance from the motor's current position.

            Optional: pass false as a final argument to run non-blocking


        Motor.spinToPosition(rotations, units)
            Moves to a specific position based on the motor's current position.

            Optional: pass false as a final argument to run non-blocking


        Motor.stop()
            Immediately stops the motor. Use Motor.setStopping() beforehand to configure stop behavior:

            coast — drifts to a stop
            brake — stops quickly
            hold — stops and holds position
