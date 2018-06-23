`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/14 11:27:20
// Design Name: 
// Module Name: sim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sim;
  reg CLK;
  reg RST;
  wire [ 2:0] cur_state;
  wire [31:0] ins, cur_pc;

  MULTI_CUCLE_CPU uut (
    .CLK(CLK), 
    .RST(RST), 
    .cur_state(cur_state),
    .ins(ins),
    .cur_pc(cur_pc)
  );

  initial begin
    CLK = 0;
    RST = 0;
    #25; 
      CLK = !CLK;
    #25;
      RST = 1;
    forever #50 begin 
      CLK = !CLK;
    end
  end

endmodule
