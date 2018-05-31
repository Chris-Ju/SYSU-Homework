`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 18:52:48
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

  reg clk, reset;

  wire [1:0] PCSrc;
  wire [2:0] ALUOp;
  wire [31:0] curpc;
  wire [ 5:0] opCode;
  wire [ 4:0] rs, rt, rd, sa;
  wire [15:0] imme;
  wire [25:0] jump;
  wire [31:0] readData1, readData2;
  wire [31:0] ALUa, ALUb, ALUResult;
  wire [31:0] RAMDataout, Result; 
  wire [31:0] instruction;
  always #25 clk = !clk;

  initial begin
    clk = 0;
    reset = 0;
    #30;
    reset = 1;
  end

  SingleStyleCPU uut(clk, reset, PCSrc, ALUOp, 
  curpc, instruction, opCode, rs, rt, rd, sa, imme, jump, 
  readData1, readData2, ALUa, ALUb, ALUResult, RAMDataout, Result);

endmodule
