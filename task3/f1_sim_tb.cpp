#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_sim.h"
#include "vbuddy.cpp"     // include vbuddy code

#define MAX_SIM_CYC 1000000

int main(int argc, char **argv, char **env) {
  int simcyc;     // simulation clock count
  int tick;       // each clk cycle has two ticks for two edges

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vf1_sim* top = new Vf1_sim;
 
  // init Vbuddy
  if (vbdOpen()!=1) return(-1);
  vbdSetMode(1);

  // initialize simulation input 
  top->clk = 1;
  top->rst = 0;
  top->en_timer = 1;
  top->N = 50; // taken from previous experiment for flag number for a 1s metranome

  // run simulation for MAX_SIM_CYC clock cycles
  for (simcyc=0; simcyc<MAX_SIM_CYC; simcyc++) {
    // dump variables into VCD file and toggle clock
    for (tick=0; tick<2; tick++) {
        top->clk = !top->clk;
        top->eval();
        vbdBar(top->led_num & 0xFF);
    }

    // either simulation finished, or 'q' is pressed
    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
      exit(0);
  }

  vbdClose();     // ++++
  printf("Exiting\n");
  exit(0);
}