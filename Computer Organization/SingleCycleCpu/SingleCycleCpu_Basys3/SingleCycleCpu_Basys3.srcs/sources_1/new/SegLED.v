`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/30 20:11:35
// Design Name: 
// Module Name: SegLED
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


module SegLED(
    input [3:0] display_data,
    output reg [6:0] dispCode
    );
    
    always @(display_data) begin
      case (display_data)
        4'b0000 : dispCode <= 8'b100_0000;  
        4'b0001 : dispCode <= 8'b111_1001;  
        4'b0010 : dispCode <= 8'b010_0100;  
        4'b0011 : dispCode <= 8'b011_0000;  
        4'b0100 : dispCode <= 8'b001_1001;  
        4'b0101 : dispCode <= 8'b001_0010;   
        4'b0110 : dispCode <= 8'b000_0010;  
        4'b0111 : dispCode <= 8'b101_1000;  
        4'b1000 : dispCode <= 8'b000_0000;  
        4'b1001 : dispCode <= 8'b001_0000;  
        4'b1010 : dispCode <= 8'b000_1000;  
        4'b1011 : dispCode <= 8'b000_0011;  
        4'b1100 : dispCode <= 8'b100_0110;  
        4'b1101 : dispCode <= 8'b010_0001;  
        4'b1110 : dispCode <= 8'b000_0110;  
        4'b1111 : dispCode <= 8'b000_1110; 
        default : dispCode <= 8'b000_0000; 
      endcase  
    end
endmodule
