`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/26 16:56:52
// Design Name: 
// Module Name: PCSelect
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


module PCSelect(
  input [31:0] pc4,
  input [31:0] pci,
  input [31:0] jump,
  input [1:0] PCSrc,
  output reg [31:0] address
  );
  always @ (PCSrc or pc4 or pci or jump) begin
    case (PCSrc)
      2'b00: address = pc4;
      2'b01: address = pci;
      2'b10: address = jump;
      2'b11: address = address;
    endcase
  end

endmodule
