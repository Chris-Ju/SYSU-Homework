`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:58:56
// Design Name: 
// Module Name: SingleStyleCPU
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


module SingleStyleCPU(
  input clk,
  input reset,

  
  output [1:0] PCSrc,
  output [2:0] ALUOp,
  output [31:0] curpc,
  output [31:0] instruction,
  output [ 5:0] opCode,

  output [ 4:0] rs, rt, rd, sa,
  output [15:0] imme,
  output [25:0] jump,
  output [31:0] readData1, readData2,
  output [31:0] ALUa, ALUb, ALUResult,
  output [31:0] RAMDataout, Result
  );


  wire zero, ALUSrcA, ALUSrcB, DBDataSrc, RegWre, mRD, mWR, RegDst, ExtSel;
  wire [ 4:0] rdout;
  wire [31:0] pc4;
  wire [31:0] jumpOut;
  wire [31:0] extendOut;
  wire [31:0] relativeOut;
  wire [31:0] nextpc;
  wire PCWre, InsMemRW;
  
  ALU my_alu(ALUOp, ALUa, ALUb, ALUResult, zero);
  ALUSrcSelect my_alusrcselect(ALUSrcA, ALUSrcB, readData1, readData2, sa, extendOut, ALUa, ALUb);
  ControlUnit my_controlunit(opCode, zero, PCWre, ALUSrcA, ALUSrcB, DBDataSrc, RegWre, InsMemRW, mRD, mWR, RegDst, ExtSel, PCSrc, ALUOp);
  DataMemory my_datamemory(clk, ALUResult, readData2, mRD, mWR, RAMDataout);
  DataSelect my_dataselect(ALUResult, RAMDataout, DBDataSrc, Result);
  InsMemRW my_insmemrw(curpc, InsMemRW, instruction);
  InstructionMemory my_instructionMemory(instruction, opCode, rs, rt, rd, sa, imme, jump);
  JumpOp my_jumpop(pc4, jump, jumpOut);
  PC my_pc(clk, reset, PCWre, nextpc, curpc);
  PC4 my_pc4(curpc, pc4);
  PCI my_pci(pc4, extendOut, relativeOut);
  PCSelect my_pcselect(pc4, relativeOut, jumpOut, PCSrc, nextpc);
  RegisterFile my_registerfile(clk, RegWre, rs, rt, rdout, Result, readData1, readData2);
  RegSelect my_regselect(RegDst, rt, rd, rdout);
  SignZeroExtend my_signzeroextend(imme, ExtSel, extendOut);



endmodule
