`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:51:22
// Design Name: 
// Module Name: ControlUnit
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

module ControlUnit(
  input [5:0] opCode,
  input zero,
  output reg PCWre,
  output reg ALUSrcA,
  output reg ALUSrcB,
  output reg DBDataSrc,
  output reg RegWre,
  output reg InsMemRW,
  output reg mRD,
  output reg mWR,
  output reg RegDst,    
  output reg ExtSel,
  output reg [1:0] PCSrc,
  output reg [2:0] ALUOp
  );

  initial begin
      InsMemRW = 1;
      PCWre = 1;
      PCSrc = 0;
      mRD = 0;
      mWR = 0;
  end
  always @(opCode or zero) begin 

    PCWre <= (opCode == 6'b111111) ? 0 : 1;
    ALUSrcA <= (opCode == 6'b011000) ? 1 : 0;
    ALUSrcB <= (opCode == 6'b000001 || opCode == 6'b010000 || opCode == 6'b100110 || opCode == 6'b100111 || opCode == 6'b011011) ? 1 : 0;
    DBDataSrc <= (opCode == 6'b100111) ? 1 : 0;
    RegWre <= (opCode == 6'b110001 || opCode == 6'b100110 || opCode == 6'b111000 || opCode == 6'b110000 || opCode == 6'b111111) ? 0 : 1;
    mRD <= (opCode == 6'b100111) ? 1 : 0;
    mWR <= (opCode == 6'b100110) ? 1 : 0;
    ExtSel <= (opCode == 6'b010000) ? 0 : 1;
    RegDst <= (opCode == 6'b000001 || opCode == 6'b010000 || opCode == 6'b100111 || opCode == 6'b011011) ? 0 : 1;

    PCSrc[1] <= (opCode == 6'b111000) ? 1 : 0;
    PCSrc[0] <= (opCode == 6'b110000 && zero == 1 || opCode == 6'b110001 && zero == 0) ? 1 : 0;

    ALUOp[2] <= (opCode == 6'b010001 || opCode == 6'b011011) ? 1 : 0;
    ALUOp[1] <= (opCode == 6'b011000 || opCode == 6'b010000 || opCode == 6'b010010) ? 1 : 0;
    ALUOp[0] <= (opCode == 6'b000010 || opCode == 6'b010010 || opCode == 6'b110001 || opCode == 6'b110000 || opCode == 6'b010000 || opCode == 6'b011011) ? 1 : 0;
  end
endmodule
