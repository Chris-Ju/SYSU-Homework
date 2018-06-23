`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 17:45:34
// Design Name: 
// Module Name: NEXT_STATE
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


module NEXT_STATE(
  input [2:0] STATE_in,
  input [5:0] opcode,
  output reg[2:0] STATE_next
);
  parameter [2:0] IF = 3'b000, 
                  ID = 3'b001,
                  aEXE = 3'b110, 
                  bEXE = 3'b111, 
                  cEXE = 3'b010, 
                  MEM = 3'b100, 
                  WB = 3'b011;
  always @(STATE_in or opcode) begin
    case (STATE_in)
      IF: STATE_next = ID;
      ID: begin
        case (opcode[5:3])
          3'b110: begin
            if (opcode[2] == 1) 
              STATE_next = bEXE;
            else 
              STATE_next = cEXE;
          end
          3'b111: STATE_next = IF; 
          default: STATE_next = aEXE; 
        endcase
      end
      aEXE: STATE_next = WB;
      bEXE: STATE_next = IF;
      cEXE: STATE_next = MEM;
      MEM: begin
          if (opcode == 6'b110001) 
            STATE_next = WB; 
          else 
            STATE_next = IF; 
      end
      WB: STATE_next = IF;
      default: STATE_next = IF;
    endcase
  end
endmodule
