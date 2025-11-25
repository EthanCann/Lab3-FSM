module f1_sim #(
    parameter WIDTH = 16
)(
    // interface signals
    input logic                clk,      // clock
    input logic                rst,      // reset
    input logic                en_timer,      
    input logic  [WIDTH-1:0]   N,       
    output logic [7:0]         led_num

);

logic tick;

clktick timer (     // instantiate counter module and name it Timer
    .clk  (clk),
    .rst  (rst),
    .en   (en_timer),
    .N    (N),
    .tick (tick)
);

f1_fsm leds_fsm(
    .clk  (clk),
    .rst  (rst),
    .en   (tick),
    .data_out (led_num)
);

endmodule

