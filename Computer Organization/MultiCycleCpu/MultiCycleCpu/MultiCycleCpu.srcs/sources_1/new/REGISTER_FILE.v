`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 16:14:22
// Design Name: 
// Module Name: REGISTER_FILE
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


module REGISTER_FILE(
  input [4:0] rs, 
  input [4:0] rt, 
  input [4:0] rd,
  input [31:0] DATA_in,
  input RegWre, 
  input clk,
  output [31:0] DATA_out_1, 
  output [31:0] DATA_out_2,
  output [31:0] REGISTER_31 
);
  reg [31:0] register [0:31];

  integer i;
  initial begin 
    for (i = 0; i < 32; i = i + 1) begin
      register[i] = 0;
    end
  end

  assign DATA_out_1 = register[rs];
  assign DATA_out_2 = register[rt];
  assign REGISTER_31 = register[31];


  always @(negedge clk) begin
    if (RegWre)
      register[rd] = DATA_in;
  end
endmodule
