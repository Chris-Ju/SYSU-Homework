`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:44:46
// Design Name: 
// Module Name: ALU
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


module ALU(
  input [ 2:0] ALUop,
  input [31:0] rega,
  input [31:0] regb,
  output reg [31:0] result,
  output zero 
  );
  assign zero = (result == 0) ? 1 : 0;

  always @( ALUop or rega or regb ) begin
    case (ALUop)
      3'b000 : result = rega + regb;              
      3'b001 : result = rega - regb;              
      3'b010 : result = regb << rega;             
      3'b011 : result = rega | regb;            
      3'b100 : result = rega & regb;              
      3'b101 : result = (rega < regb) ? 1 : 0;    
      3'b110 : begin                            
          if(rega < regb && (rega[31] == regb[31])) 
            result = 1;
          else if (rega[31] == 1 && regb[31] == 0) 
            result = 1;
          else 
            result = 0;
      end
      3'b111 : result = rega ^ regb;            
    endcase
  end

endmodule
