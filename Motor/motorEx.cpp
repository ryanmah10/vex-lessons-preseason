#include "vex.h"
using namespace vex;

brain Brain;
motor leftMotor  = motor(PORT1, ratio18_1, false);
motor rightMotor = motor(PORT2, ratio18_1, true);

// --- Drive Forward ---
void driveForward() {
  leftMotor.setVelocity(75, percent);
  rightMotor.setVelocity(75, percent);

  leftMotor.setStopping(brake);
  rightMotor.setStopping(brake);

  leftMotor.setMaxTorque(80, percent);
  rightMotor.setMaxTorque(80, percent);

  leftMotor.setTimeout(3, seconds);
  rightMotor.setTimeout(3, seconds);

  // Reset encoders
  leftMotor.setPosition(0, degrees);
  rightMotor.setPosition(0, degrees);

  // Drive forward 2 turns
  leftMotor.spinFor(forward, 2, turns, false);
  rightMotor.spinFor(forward, 2, turns, false);

  // Wait until both motors finish
  while (!leftMotor.isDone() || !rightMotor.isDone()) {
    wait(20, msec);
  }
}

// --- Turn Right ---
void turnRight() {
  leftMotor.setVelocity(50, percent);
  rightMotor.setVelocity(50, percent);

  // Spin left forward, right reverse to turn
  leftMotor.spinFor(forward, 1, turns, false);
  rightMotor.spinFor(reverse, 1, turns, false);

  while (!leftMotor.isDone() || !rightMotor.isDone()) {
    wait(20, msec);
  }
}

// --- Arm Lift ---
void liftArm() {
  motor armMotor = motor(PORT3, ratio36_1, false);

  armMotor.setVelocity(40, percent);
  armMotor.setStopping(hold);       // Hold position when done
  armMotor.setMaxTorque(100, percent);
  armMotor.setTimeout(2, seconds);  // Timeout in case arm hits a limit
  armMotor.setPosition(0, degrees);

  armMotor.spinToPosition(180, degrees); // Lift arm to 180 degrees

  while (armMotor.isSpinning()) {
    wait(20, msec);
  }

  armMotor.stop();
}

// --- Voltage Controlled Spin ---
void voltageSpin() {
  motor intakeMotor = motor(PORT4, ratio18_1, false);

  // Spin intake using direct voltage
  intakeMotor.spin(forward, 9, volt);
  wait(2, seconds);

  intakeMotor.setStopping(coast);  // Let it coast to a stop
  intakeMotor.stop();
}

// --- Safety Check ---
// Checks motor health before running, aborts if overheating or pulling too much current
bool safetyCheck(motor m) {
  if (m.temperature(percent) > 80) {
    return false;   // Too hot
  }
  if (m.current(amp) > 2.0) {
    return false;   // Drawing too much current
  }
  return true;
}

// --- Monitor and Log Motor Stats ---
void logMotorStats(motor m) {
  double pos   = m.position(degrees);
  double vel   = m.velocity(percent);
  double amps  = m.current(amp);
  double watts = m.power(watt);
  double torq  = m.torque(Nm);
  double eff   = m.efficiency(percent);
  double temp  = m.temperature(percent);

  // Use values to make decisions
  if (temp > 70) {
    m.setVelocity(30, percent);   // Throttle down if getting hot
  }
  if (eff < 20) {
    m.setMaxTorque(50, percent);  // Reduce torque if efficiency is low
  }
  if (amps > 1.8) {
    m.setStopping(coast);
    m.stop();                     // Stop if current is dangerously high
  }
}

// --- Main ---
int main() {
  // Safety check before doing anything
  if (!safetyCheck(leftMotor) || !safetyCheck(rightMotor)) {
    return 0;  // Abort if motors are not safe to run
  }

  driveForward();
  logMotorStats(leftMotor);
  logMotorStats(rightMotor);

  turnRight();
  logMotorStats(leftMotor);
  logMotorStats(rightMotor);

  liftArm();
  voltageSpin();

  // Final stop — ensure everything is off
  leftMotor.stop();
  rightMotor.stop();

  return 0;
}
