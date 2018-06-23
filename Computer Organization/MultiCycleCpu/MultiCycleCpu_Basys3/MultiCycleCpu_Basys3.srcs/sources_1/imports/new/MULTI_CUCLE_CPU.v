`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 22:21:55
// Design Name: 
// Module Name: MULTI_CUCLE_CPU
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


module MULTI_CUCLE_CPU(
  input CLK, 
  input CLK_Q,
  input RST,
  input [1:0] SW_in,
  output reg [10:0] display_out
  );
  parameter endReg = 5'b11111; 

  wire [ 2:0] cur_state;
  wire [31:0] ins;
  wire [31:0] cur_pc;
  wire [ 2:0] next_state;

  wire [31:0] next_pc, pc_4, pc_o, pc_j, number_e, data_w, register_31, register_out_1, register_out_2, 
              ALU_A_out, ALU_B_out, ALU_result, data_m, data_out;
  wire [31:0] IR_out, DBDR_out, ADR_out, BDR_out, ALUOUTDR_out;


  wire [ 5:0] opcode;
  wire [ 4:0] rs, rt, rd, sa;
  wire [15:0] imme;
  wire [25:0] addr_j;

  wire [ 4:0] reg_w;

  wire zero, sign;

  wire PCWre, InsMemRW, IRWre, WrRegDSrc, RegWre, ALUSrcA, ALUSrcB, mRD, mWR, DBDataSrc, ExtSel;
  wire [2:0] ALUop;
  wire [1:0] RegDst, PCSrc;

  wire [31:0] sa_extend;


  PC pc(CLK, RST, PCWre, next_pc, cur_pc);
  PC_ADD_FOUR pc_add_four(cur_pc, pc_4);
  PC_OFFSET pc_offset(pc_4, number_e, pc_o);
  PC_JUMP pc_jump(pc_4, addr_j, pc_j);

  FOUR_TO_ONE pc_select(pc_4, pc_o, register_31, pc_j, PCSrc, next_pc);

  INS_MEM_RW ins_mem_rw(InsMemRW, cur_pc, ins);
  IR ir(CLK, IRWre, ins, IR_out);
  INS_DEC ins_dec(IR_out, opcode, rs, rt, rd, sa, imme, addr_j);

  TWO_TO_ONE write_data_select(pc_4, DBDR_out, WrRegDSrc, data_w);
  THREE_TO_ONE write_reg_select(endReg, rt, rd, RegDst, reg_w);

  REGISTER_FILE register_file(rs, rt, reg_w, data_w, RegWre, CLK, register_out_1, register_out_2, register_31);
  DR adr(CLK, register_out_1, ADR_out);
  DR bdr(CLK, register_out_2, BDR_out);

  SA_EXTEND sa_e(sa, sa_extend);

  TWO_TO_ONE ALU_select_A(ADR_out, sa_extend, ALUSrcA, ALU_A_out);
  TWO_TO_ONE ALU_select_B(BDR_out, number_e, ALUSrcB, ALU_B_out);

  ALU alu(ALUop, ALU_A_out, ALU_B_out, ALU_result, zero, sign);

  DR aluoutdr(CLK, ALU_result, ALUOUTDR_out);
  DATA_MEM data_mem(ALUOUTDR_out, BDR_out, mRD, mWR, data_m);

  TWO_TO_ONE db_data_select(ALU_result, data_m, DBDataSrc, data_out);

  DR dbdr(CLK, data_out, DBDR_out);

  NUMBER_EXTEND number_extend(imme, ExtSel, number_e);

  CONTROL_UNIT control_unit(cur_state, opcode, zero, sign, PCWre, ALUSrcA, ALUSrcB, DBDataSrc, 
  RegWre, WrRegDSrc, InsMemRW, mRD, mWR, IRWre, ExtSel, PCSrc, RegDst, ALUop);

  NEXT_STATE state(cur_state, opcode, next_state);
  D_FLIP_FLOP d_flip_flop(next_state, RST, CLK, cur_state);
  

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

  SegLED seg1(next_pc[7:4], nextop1);
  SegLED seg2(next_pc[3:0], nextop2);
  SegLED seg3(cur_pc[7:4], curop1);
  SegLED seg4(cur_pc[3:0], curop2);
  SegLED seg5({4'b0000}, rs1);
  SegLED seg6(rs[3:0], rs2);
  SegLED seg7(register_out_1[7:4], rsValue1);
  SegLED seg8(register_out_1[3:0], rsValue2);
  SegLED seg9({4'b0000}, rt1);
  SegLED seg10(rt[3:0], rt2);
  SegLED seg11(register_out_2[7:4], rtValue1);
  SegLED seg12(register_out_2[3:0], rtValue2);
  SegLED seg13(ALU_result[7:4], alu1);
  SegLED seg14(ALU_result[3:0], alu2);
  SegLED seg15(DBDR_out[7:4], db1);
  SegLED seg16(DBDR_out[3:0], db2);

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
