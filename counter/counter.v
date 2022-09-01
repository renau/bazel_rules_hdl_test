module counter(
  input clk,
  input reset,
  input enable,
  output [7:0] out
);


  reg [7:0] counter_reg;
  always @(posedge clk) begin
    if (reset) begin
      counter_reg <= 0;
    end else if (enable) begin
      counter_reg <= counter_reg + 1;
    end
  end

  assign out = counter_reg;

endmodule
