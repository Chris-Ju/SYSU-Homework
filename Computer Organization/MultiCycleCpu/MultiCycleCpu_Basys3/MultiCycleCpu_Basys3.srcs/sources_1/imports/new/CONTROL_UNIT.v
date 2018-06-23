`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 16:32:54
// Design Name: 
// Module Name: CONTROL_UNIT
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


module CONTROL_UNIT(
  input [2:0] state,
  input [5:0] opCode,
  input zero,
  input sign,
  output reg PCWre,
  output reg ALUSrcA,
  output reg ALUSrcB,
  output reg DBDataSrc,
  output reg RegWre,
  output reg WrRegDSrc,
  output reg InsMemRW,
  output reg mRD,
  output reg mWR,
  output reg IRWre,
  output reg ExtSel,
  output reg [1:0] PCSrc,
  output reg [1:0] RegDst,   
  output reg [2:0] ALUOp
  );

  parameter [2:0] IF = 3'b000, 
                  ID = 3'b001,
                  aEXE = 3'b110, 
                  bEXE = 3'b111, 
                  cEXE = 3'b010, 
                  MEM = 3'b100, 
                  WB = 3'b011;

  parameter [5:0] add  = 6'b000000,
                  sub  = 6'b000001,
                  addi = 6'b000010,
                  ori  = 6'b010010,
                  Or   = 6'b010000,
                  And  = 6'b010001,
                  sll  = 6'b011000,
                  slt  = 6'b100110,
                  sltiu= 6'b100111,
                  sw   = 6'b110000,
                  lw   = 6'b110001,
                  beq  = 6'b110100,
                  bltz = 6'b110110,
                  j    = 6'b111000,
                  jr   = 6'b111001,
                  jal  = 6'b111010,
                  halt = 6'b111111;
  initial begin
    InsMemRW = 1;
    PCWre = 0;
  end

  always @(opCode or state) begin 
  
    
    PCWre <= (opCode != halt && state == IF) ? 1 : 0;
    ALUSrcA <= (opCode == sll) ? 1 : 0;
    ALUSrcB <= (opCode == addi || opCode == ori || opCode == sw || opCode == sltiu || opCode == lw) ? 1 : 0;
    DBDataSrc <= (state == WB && opCode == lw) ? 1 : 0;
    RegWre <= (state == WB || opCode == jal) ? 1 : 0;
    WrRegDSrc <= (opCode == jal) ? 0 : 1;
    mRD <= (opCode == lw && state == WB) ? 1 : 0;
    mWR <= (opCode == sw && state == MEM) ? 1 : 0;
    ExtSel <= (opCode == ori || opCode == sltiu) ? 0 : 1;
    IRWre <= (state == ID) ? 1 : 0;

    RegDst[1] <= (opCode == addi || opCode == ori || opCode == sltiu || opCode == lw || opCode == jal) ? 0 : 1;
    RegDst[0] <= (opCode == addi || opCode == ori || opCode == sltiu || opCode == lw) ? 1 : 0;

    PCSrc[1] <= (opCode == j || opCode == jal || opCode == jr) ? 1 : 0;
    PCSrc[0] <= (opCode == beq && zero == 1 || opCode == bltz && sign == 1 && zero == 0 || opCode == jal || opCode == j) ? 1 : 0;

    ALUOp[2] <= (opCode == Or || opCode == And || opCode == ori || opCode == sll) ? 1 : 0;
    ALUOp[1] <= (opCode == And || opCode == slt || opCode == sltiu) ? 1 : 0;
    ALUOp[0] <= (opCode == sub || opCode == Or || opCode == ori || opCode == slt || opCode == beq || opCode == bltz) ? 1 : 0;



    if (state == IF) begin
      RegWre = 0;
      mRD = 0;
      mWR = 0;
    end
  end
endmodule
