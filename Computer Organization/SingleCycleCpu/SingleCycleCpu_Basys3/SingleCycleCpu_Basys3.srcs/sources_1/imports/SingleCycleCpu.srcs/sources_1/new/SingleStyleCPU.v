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
    
  input CLK_Q,
  input CLK,
  input Reset,
  input [1:0] SW_in,
  output reg [10:0] display_out
  );

  wire [1:0] PCSrc;
  wire [2:0] ALUO;
  wire [31:0] curpc;
  wire [31:0] instruction;
  wire [ 5:0] opCode;

  wire [ 4:0] rs, rt, rd, sa;
  wire [15:0] imme;
  wire [25:0] jump;
  wire [31:0] readData1, readData2;
  wire [31:0] ALUa, ALUb, ALUResult;
  wire [31:0] RAMDataout, Result;

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
  DataMemory my_datamemory(CLK, ALUResult, readData2, mRD, mWR, RAMDataout);
  DataSelect my_dataselect(ALUResult, RAMDataout, DBDataSrc, Result);
  InsMemRW my_insmemrw(curpc, InsMemRW, instruction);
  InstructionMemory my_instructionMemory(instruction, opCode, rs, rt, rd, sa, imme, jump);
  JumpOp my_jumpop(pc4, jump, jumpOut);
  PC my_pc(CLK, Reset, PCWre, nextpc, curpc);
  PC4 my_pc4(curpc, pc4);
  PCI my_pci(pc4, extendOut, relativeOut);
  PCSelect my_pcselect(pc4, relativeOut, jumpOut, PCSrc, nextpc);
  RegisterFile my_registerfile(CLK, RegWre, rs, rt, rdout, Result, readData1, readData2);
  RegSelect my_regselect(RegDst, rt, rd, rdout);
  SignZeroExtend my_signzeroextend(imme, ExtSel, extendOut);



  wire [7:0] nextop1;
  wire [7:0] nextop2;
  wire [7:0] curop1;
  wire [7:0] curop2;
  wire [7:0] rs1;
  wire [7:0] rs2;
  wire [7:0] rsValue1;
  wire [7:0] rsValue2;
  wire [7:0] rt1;
  wire [7:0] rt2;
  wire [7:0] rtValue1;
  wire [7:0] rtValue2;
  wire [7:0] alu1;
  wire [7:0] alu2;
  wire [7:0] db1;
  wire [7:0] db2;

  SegLED seg1(nextpc[7:4], nextop1);
  SegLED seg2(nextpc[3:0], nextop2);
  SegLED seg3(curpc[7:4], curop1);
  SegLED seg4(curpc[3:0], curop2);
  SegLED seg5({4'b0000}, rs1);
  SegLED seg6(rs[3:0], rs2);
  SegLED seg7(readData1[7:4], rsValue1);
  SegLED seg8(readData1[3:0], rsValue2);
  SegLED seg9({4'b0000}, rt1);
  SegLED seg10(rt[3:0], rt2);
  SegLED seg11(readData2[7:4], rtValue1);
  SegLED seg12(readData2[3:0], rtValue2);
  SegLED seg13(ALUResult[7:4], alu1);
  SegLED seg14(ALUResult[3:0], alu2);
  SegLED seg15(Result[7:4], db1);
  SegLED seg16(Result[3:0], db2);

  parameter T1MS = 50000;
  reg [19:0] count = 0;
  reg [2:0] sel = 0;

  always @(posedge CLK_Q) begin
    count <= count + 1;
    if(count == T1MS) begin
      count <= 0;
      sel <= sel + 1;
      if (sel == 4)
          sel <= 0;
    end
    
    if(SW_in == 2'b00) begin
      case(sel)
        0: begin
          display_out[10:7] = 4'b0111;
          display_out[6:0] = curop1;
        end
        1: begin
          display_out[10:7] = 4'b1011;
          display_out[6:0] = curop2;
        end
        2: begin
          display_out[10:7] = 4'b1101;
          display_out[6:0] = nextop1;
        end
        3: begin
          display_out[10:7] = 4'b1110;
          display_out[6:0] = nextop2;
        end
      endcase
    end
    else if(SW_in == 2'b01) begin
      case(sel)
        0: begin
          display_out[10:7] = 4'b0111;
          display_out[6:0] = rs1;
        end
        1: begin
          display_out[10:7] = 4'b1011;
          display_out[6:0] = rs2;
        end
        2: begin
            display_out[10:7] = 4'b1101;
            display_out[6:0] = rsValue1;
        end
        3: begin
            display_out[10:7] = 4'b1110;
            display_out[6:0] = rsValue2;
        end
      endcase
    end
    else if(SW_in == 2'b10) begin
      case(sel)
        0: begin
          display_out[10:7] = 4'b0111;
          display_out[6:0] = rt1;
        end
        1: begin
          display_out[10:7] = 4'b1011;
          display_out[6:0] = rt2;
        end
        2: begin
          display_out[10:7] = 4'b1101;
          display_out[6:0] = rtValue1;
        end
        3: begin
          display_out[10:7] = 4'b1110;
          display_out[6:0] = rtValue2;
        end
      endcase
    end
    else if(SW_in == 2'b11) begin
      case(sel)
        0: begin
          display_out[10:7] = 4'b0111;
          display_out[6:0] = alu1;
        end
        1: begin
          display_out[10:7] = 4'b1011;
          display_out[6:0] = alu2;
        end
        2: begin
          display_out[10:7] = 4'b1101;
          display_out[6:0] = db1;
        end
        3: begin
          display_out[10:7] = 4'b1110;
          display_out[6:0] = db2;
        end
      endcase
    end
  end


endmodule
