`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/18 23:02:14
// Design Name: 
// Module Name: Random
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


module Random(
    input                   [ 0 : 0]            clk,
    input                   [ 0 : 0]            rst,
    input                   [ 0 : 0]            generate_random,
    input                   [ 0 : 0]            random_en,
    output           reg    [11 : 0]            random_data
);
reg [11:0] targets [0: 119];
always @(posedge clk) begin
    // 这里用 initial 也可以，只要让 targets 中的数值保持不变即可。
    targets[0] <= 12'h012;
    targets[1] <= 12'h013;
    targets[2] <= 12'h014;
    targets[3] <= 12'h015;
    targets[4] <= 12'h021;
    targets[5] <= 12'h023;
    targets[6] <= 12'h024;
    targets[7] <= 12'h025;
    targets[8] <= 12'h031;
    targets[9] <= 12'h032;
    targets[10] <= 12'h034;
    targets[11] <= 12'h035;
    targets[12] <= 12'h041;
    targets[13] <= 12'h042;
    targets[14] <= 12'h043;
    targets[15] <= 12'h045;
    targets[16] <= 12'h051;
    targets[17] <= 12'h052;
    targets[18] <= 12'h053;
    targets[19] <= 12'h054;

    targets[20] <= 12'h102;
    targets[21] <= 12'h103;
    targets[22] <= 12'h104;
    targets[23] <= 12'h105;
    targets[24] <= 12'h120;
    targets[25] <= 12'h123;
    targets[26] <= 12'h124;
    targets[27] <= 12'h125;
    targets[28] <= 12'h130;
    targets[29] <= 12'h132;
    targets[30] <= 12'h134;
    targets[31] <= 12'h135;
    targets[32] <= 12'h140;
    targets[33] <= 12'h142;
    targets[34] <= 12'h143;
    targets[35] <= 12'h145;
    targets[36] <= 12'h150;
    targets[37] <= 12'h152;
    targets[38] <= 12'h153;
    targets[39] <= 12'h154;

    targets[40] <= 12'h201;
    targets[41] <= 12'h203;
    targets[42] <= 12'h204;
    targets[43] <= 12'h205;
    targets[44] <= 12'h210;
    targets[45] <= 12'h213;
    targets[46] <= 12'h214;
    targets[47] <= 12'h215;
    targets[48] <= 12'h230;
    targets[49] <= 12'h231;
    targets[50] <= 12'h234;
    targets[51] <= 12'h235;
    targets[52] <= 12'h240;
    targets[53] <= 12'h241;
    targets[54] <= 12'h243;
    targets[55] <= 12'h245;
    targets[56] <= 12'h250;
    targets[57] <= 12'h251;
    targets[58] <= 12'h253;
    targets[59] <= 12'h254;

    targets[60] <= 12'h301;
    targets[61] <= 12'h302;
    targets[62] <= 12'h304;
    targets[63] <= 12'h305;
    targets[64] <= 12'h310;
    targets[65] <= 12'h312;
    targets[66] <= 12'h314;
    targets[67] <= 12'h315;
    targets[68] <= 12'h320;
    targets[69] <= 12'h321;
    targets[70] <= 12'h324;
    targets[71] <= 12'h325;
    targets[72] <= 12'h340;
    targets[73] <= 12'h341;
    targets[74] <= 12'h342;
    targets[75] <= 12'h345;
    targets[76] <= 12'h350;
    targets[77] <= 12'h351;
    targets[78] <= 12'h352;
    targets[79] <= 12'h354;

    targets[80] <= 12'h401;
    targets[81] <= 12'h402;
    targets[82] <= 12'h403;
    targets[83] <= 12'h405;
    targets[84] <= 12'h410;
    targets[85] <= 12'h412;
    targets[86] <= 12'h413;
    targets[87] <= 12'h415;
    targets[88] <= 12'h420;
    targets[89] <= 12'h421;
    targets[90] <= 12'h423;
    targets[91] <= 12'h425;
    targets[92] <= 12'h430;
    targets[93] <= 12'h431;
    targets[94] <= 12'h432;
    targets[95] <= 12'h435;
    targets[96] <= 12'h450;
    targets[97] <= 12'h451;
    targets[98] <= 12'h452;
    targets[99] <= 12'h453;

    targets[100] <= 12'h501;
    targets[101] <= 12'h502;
    targets[102] <= 12'h503;
    targets[103] <= 12'h504;
    targets[104] <= 12'h510;
    targets[105] <= 12'h512;
    targets[106] <= 12'h513;
    targets[107] <= 12'h514;
    targets[108] <= 12'h520;
    targets[109] <= 12'h521;
    targets[110] <= 12'h523;
    targets[111] <= 12'h524;
    targets[112] <= 12'h530;
    targets[113] <= 12'h531;
    targets[114] <= 12'h532;
    targets[115] <= 12'h534;
    targets[116] <= 12'h540;
    targets[117] <= 12'h541;
    targets[118] <= 12'h542;
    targets[119] <= 12'h543;
end
reg [7 : 0] index;
always @(posedge clk) begin
    if (rst)
        index <= 0;
    else if (generate_random) begin
        if (index < 119)
            index <= index + 1;
        else
            index <= 0;
    end
end
always @(posedge clk) begin
    if(random_en)begin
        random_data <= targets[index]; 
    end
end

endmodule
