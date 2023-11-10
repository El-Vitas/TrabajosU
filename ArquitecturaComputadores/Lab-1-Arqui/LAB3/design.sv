// Code your design here
// Code your design here
module main();
  wire [5:0] direction;
  up_counter dut(direction);
  
  wire [18:0]ins;
  ROM memoryRom(direction, ins);
  
  reg [2:0] alu_control;
  reg [7:0] A, B;
  splitter spl(ins, alu_control, B, A);
  
  reg [7:0] res;
  reg ignorado;
  ALU alu(A, B, alu_control, res, ignorado);
  
  result displayResult(res, ignorado, ins, A, B, direction);
endmodule
  

module up_counter(count);
  logic clk, rst;
  output reg [5:0] count;
  
  always@(posedge clk) begin
    if(rst==1) begin
      count <= 0;
    end
    
    else count <= count +1;
  end
  
  initial begin
    clk = 0;
    forever #5ns clk = ~clk;
  end
  
  initial begin 
    rst = 1;
    $display("< Ins > <Op > < Inmed A> < Inmed B> < Result >");
    #6ns;
    rst=0;
   
    #640ns;
    $finish;
  end
endmodule

module ROM(direction, ins);
  input reg [5:0]direction;
  output reg[18:0]ins;
  
  reg [18:0]memory [63:0];
  initial begin
    //memory[0] = 19'h55D52;
    //memory[1] = 19'h65D52;
    //memory[2] = 19'h75D52;
    //memory[3] = 19'h07F01;
    //memory[4] = 19'h01713;
    //memory[5] = 19'h1074C;
    //memory[26] = 19'h45D52;
    
    memory[0] = 19'h0A8A8;
    memory[1] = 19'h6B580;
    memory[2] = 19'h5B0A9;
    memory[3] = 19'h6CF8C;
    memory[4] = 19'h1069D;
    memory[5] = 19'h6B433;
    memory[6] = 19'h52A36;
    memory[7] = 19'h4DFC9;
    memory[8] = 19'h72B4F;
    memory[9] = 19'h0A92F;
    memory[10] = 19'h26F7E;
    memory[11] = 19'h1ADFF;
    memory[12] = 19'h5A220;
    memory[13] = 19'h0A195;
    memory[14] = 19'h68F6F;
    memory[15] = 19'h36D63;
    memory[16] = 19'h60578;
    memory[17] = 19'h1099E;
    memory[18] = 19'h0F5E9;
    memory[19] = 19'h70A5A;
    memory[20] = 19'h2C87E;
    memory[21] = 19'h49EED;
    memory[22] = 19'h11540;
    memory[23] = 19'h5C297;
    memory[24] = 19'h26C3B;
    memory[25] = 19'h7C66B;
    memory[26] = 19'h4BC01;
    memory[27] = 19'h74CB2;
    memory[28] = 19'h45FC6;
    memory[29] = 19'h143ED;
    memory[30] = 19'h4F17D;
    memory[31] = 19'h6E29A;
    memory[32] = 19'h7052F;
    memory[33] = 19'h78A3F;
    memory[34] = 19'h097F8;
    memory[35] = 19'h69493;
    memory[36] = 19'h0FAC2;
    memory[37] = 19'h10829;
    memory[38] = 19'h382B0;
    memory[39] = 19'h5784F;
    memory[40] = 19'h446BE;
    memory[41] = 19'h26747;
    memory[42] = 19'h0C26B;
    memory[43] = 19'h4D718;
    memory[44] = 19'h44330;
    memory[45] = 19'h5C78E;
    memory[46] = 19'h38170;
    memory[47] = 19'h04302;
    memory[48] = 19'h7B58B;
    memory[49] = 19'h6E81E;
    memory[50] = 19'h62FA3;
    memory[51] = 19'h4CEC4;
    memory[52] = 19'h191DE;
    memory[53] = 19'h1767A;
    memory[54] = 19'h50F1C;
    memory[55] = 19'h2F18C;
    memory[56] = 19'h71104;
    memory[57] = 19'h67123;
    memory[58] = 19'h12117;
    memory[59] = 19'h68ED6;
    memory[60] = 19'h2BAA5;
    memory[61] = 19'h446D8;
    memory[62] = 19'h67607;
    memory[63] = 19'h5F132;
    
  end
  
  always@(direction) begin
    ins <= memory[direction];
  end
endmodule

module splitter(
  	input reg [18:0] instruction,
  	output reg [2:0] alu_control,
  	output reg [7:0] B,
  	output reg [7:0] A);
  
  	assign alu_control = instruction[18:16];
  	assign A = instruction[15:8];
  	assign B = instruction[7:0];
endmodule

module ALU(
  	input logic [7:0] A,
  	input logic [7:0] B,
  	input logic [2:0] alu_control,
    output logic [7:0] result,
  	output reg ignorado
);
  	
  	logic[7:0] temp;
  	logic[7:0] c2_B;
  	c2 c2_inst(B,alu_control,c2_B);
  	prefix_adder pfx_inst(A,c2_B,temp);  // Suma
  always @(*) begin
    case (alu_control)
      3'b000: result = temp; // Suma
      3'b001: result = temp;  // Resta
      3'b010: result = A << B;  // BITSHIFT IZQ
      3'b011: result = A >> B;  // BITSHIFT DER
      3'b100: result = A & B;  // AND
      3'b101: result = A | B; // OR
      3'b110: result = A ^ B;  // XOR
      3'b111: result = ~A; // NOT
    endcase

    if (alu_control == 3'b111) begin
      ignorado = 1;
    end
    else begin
      ignorado = 0;
    end
  end
endmodule
  
module result(res, ignorado, ins, A, B, direction);
  input [7:0] A, B;
  input [7:0] res;
  input ignorado;
  input reg [5:0]direction;
  input reg [18:0]ins;
  always@(direction) begin
 	if(!$isunknown(ins))begin
      if (ignorado == 0) begin
          $display("<%h> <%b> <%b> <%b> <%b>",ins,ins[18:16],A,B,res);
        end
        else begin
          $display("<%h> <%b> <%b> <Ignorado> <%b>",ins,ins[18:16],A,res);
        end
    end
  end
endmodule

module prefix_adder(
  input [7:0] A,
  input [7:0] B,
  output [7:0] sum
);
  
  reg[8:0] G, P;
  reg[7:0] cp,cg;
  logic cp32,cg32,cp54,cg54,cp76,cg76,cp65,cg65,cp75,cg75;

  //Bloques Amarillo
  assign G[0] = 1'b0;
  assign P[0] = 1'b0;
  
  assign G[1] = A[0] & B[0];
  assign P[1] = A[0] | B[0];
  
  assign G[2] = A[1] & B[1];
  assign P[2] = A[1] | B[1];
  
  assign G[3] = A[2] & B[2];
  assign P[3] = A[2] | B[2];
  
  assign G[4] = A[3] & B[3];
  assign P[4] = A[3] | B[3];
  
  assign G[5] = A[4] & B[4];
  assign P[5] = A[4] | B[4];
  
  assign G[6] = A[5] & B[5];
  assign P[6] = A[5] | B[5];
  
  assign G[7] = A[6] & B[6];
  assign P[7] = A[6] | B[6];
  
  assign G[8] = A[7] & B[7];
  assign P[8] = A[7] | B[7];
  //End Bloques Amarillo
  
  //Bloques negros y azules
  assign cg[0] = G[0];
  assign cp[1] = (P[1] & P[0]);
  assign cg[1] = (G[1] |(G[0] & P[1]));
  assign cp32 = (P[3] & P[2]);
  assign cg32 = (G[3] |(G[2] & P[3]));
  assign cp54 = (P[5] & P[4]);
  assign cg54 = (G[5] |(G[4] & P[5]));
  assign cp76 = (P[7] & P[6]);
  assign cg76 = (G[7] |(G[6] & P[7]));
  
  assign cp[2] = (P[2] & cp[1]);
  assign cg[2] = (G[2] |(cg[1] & P[2]));
  assign cp[3] = (cp32 & cp[1]);
  assign cg[3] = (cg32 | (cg[1] & cp32));
  assign cp65 = (P[6] & cp54);
  assign cg65 = (G[6] | (cg54 & P[6]));
  assign cp75 = (cp76 & cp54);
  assign cg75 = (cg76 | (cg54 & cp76));
  
  assign cp[4] = (P[4] & cp[3]);
  assign cg[4] = (G[4] | (cg[3] & P[4]));
  assign cp[5] = (cp54 & cp[3]);
  assign cg[5] = (cg54 | (cg[3] & cp54));
  assign cp[6] = (cp65 & cp[3]);
  assign cg[6] = (cg65 | (cg[3] & cp65));
  assign cp[7] = (cp75 & cp[3]);
  assign cg[7] = (cg75 | (cg[3] & cp75));
  //End Bloques negros y azules
  
  //Suma
  
  assign sum[0] = (cg[0] ^ (A[0] ^ B[0]));
  assign sum[1] = (cg[1] ^ (A[1] ^ B[1]));
  assign sum[2] = (cg[2] ^ (A[2] ^ B[2]));
  assign sum[3] = (cg[3] ^ (A[3] ^ B[3]));
  assign sum[4] = (cg[4] ^ (A[4] ^ B[4]));
  assign sum[5] = (cg[5] ^ (A[5] ^ B[5]));
  assign sum[6] = (cg[6] ^ (A[6] ^ B[6]));
  assign sum[7] = (cg[7] ^ (A[7] ^ B[7]));
endmodule

module c2(
  input [7:0] B,
  input [2:0] alu_control,
  output [7:0] c2_B
);

  assign c2_B = (alu_control == 3'b001) ? (~B + 1) : B;
endmodule

  
      
