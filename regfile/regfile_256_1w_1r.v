
module regfile_256_1w_1r
  (input                   clock,

   input       [7:0]       raddr0,

   input       [7:0]       waddr,
   input       [63:0]      wdata,
   input                   wena,

    output reg [63:0]       rdata0);

   reg [63:0]        rf[255:0];
   reg [ 7:0]        raddr_r0;


  // Flop input addresses

  always @(posedge clock) begin
    raddr_r0 <= raddr0;
  end

  // One-hot encoding address, flop it too
  reg [255:0] hot_raddr0_next;
  reg [255:0] hot_raddr0;
  always @(*) begin
    hot_raddr0_next = 1'b1<<raddr_r0;
  end
  always @(posedge clock) begin
    hot_raddr0 <= hot_raddr0_next;
  end

  // read the data (avoid mux with OR-gate)
  reg [63:0]       rdata0_next;
  integer i;
  always @(*) begin
    rdata0_next = 0;

    for(i=0;i<256;i=i+1) begin
      rdata0_next = rdata0_next | (rf[i] & {64{hot_raddr0[i]}});
    end
  end

  always @(posedge clock) begin
    rdata0 <= rdata0_next;
  end

   always @(posedge clock) begin
     if (wena) begin
       rf[waddr] <= wdata;
     end
   end
endmodule

