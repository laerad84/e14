void snn2(float* oinp,float &out,float &nout) {
  //
  // created by NJetNet.
  //      at 123 th Epoch 
  //
  //
  //input
  //dimension of oinp should be 11
  //local param.
  int   ninp,nhid;
  float thre[19];
  float weig[216];
  int   nsigtr;
  int   nbkgtr;
  //local var
  float sn;


  ninp= 11;
  nhid= 18;

  thre[0] = -0.124683;
  thre[1] = 0.7634;
  thre[2] = 0.435769;
  thre[3] = 0.0341321;
  thre[4] = -0.138677;
  thre[5] = -1.63885;
  thre[6] = -0.683576;
  thre[7] = 0.305776;
  thre[8] = -0.0340849;
  thre[9] = -0.0580473;
  thre[10] = 0.791552;
  thre[11] = 0.981184;
  thre[12] = -1.07589;
  thre[13] = 0.501004;
  thre[14] = -0.290926;
  thre[15] = -0.387295;
  thre[16] = -0.292863;
  thre[17] = -0.0773534;
  thre[18] = 0.274453;

  weig[0] = 0.313809;
  weig[1] = -0.406663;
  weig[2] = -0.575229;
  weig[3] = 0.270098;
  weig[4] = 0.392944;
  weig[5] = -1.6006;
  weig[6] = -0.796908;
  weig[7] = 0.665847;
  weig[8] = 0.681014;
  weig[9] = 0.432852;
  weig[10] = -0.465856;
  weig[11] = -0.247627;
  weig[12] = 0.209092;
  weig[13] = -0.181571;
  weig[14] = 0.866404;
  weig[15] = -0.556303;
  weig[16] = 1.12192;
  weig[17] = -0.162907;
  weig[18] = -0.0334348;
  weig[19] = 1.51259;
  weig[20] = 0.791346;
  weig[21] = 0.649352;
  weig[22] = 0.0663079;
  weig[23] = 0.0960012;
  weig[24] = -0.054664;
  weig[25] = -0.0769765;
  weig[26] = -0.493128;
  weig[27] = -0.355929;
  weig[28] = -0.197067;
  weig[29] = 0.15425;
  weig[30] = -1.12308;
  weig[31] = 0.424829;
  weig[32] = 0.0646685;
  weig[33] = -0.314924;
  weig[34] = 0.41075;
  weig[35] = 0.293774;
  weig[36] = -0.0610907;
  weig[37] = -0.662518;
  weig[38] = 0.16116;
  weig[39] = -1.50044;
  weig[40] = -0.474674;
  weig[41] = -0.00555152;
  weig[42] = 0.49316;
  weig[43] = 0.336166;
  weig[44] = -1.79424;
  weig[45] = -0.0303695;
  weig[46] = 0.220892;
  weig[47] = -2.22643;
  weig[48] = -1.38723;
  weig[49] = 0.301479;
  weig[50] = -0.366581;
  weig[51] = -1.03325;
  weig[52] = 0.244533;
  weig[53] = 0.410967;
  weig[54] = -0.678635;
  weig[55] = 1.44644;
  weig[56] = 0.00843816;
  weig[57] = 0.794473;
  weig[58] = -0.418871;
  weig[59] = -1.10706;
  weig[60] = 0.0427432;
  weig[61] = -1.17453;
  weig[62] = -0.216171;
  weig[63] = -0.713225;
  weig[64] = -1.62801;
  weig[65] = 0.563284;
  weig[66] = 0.629757;
  weig[67] = 0.178821;
  weig[68] = 0.70325;
  weig[69] = -0.785555;
  weig[70] = -0.855617;
  weig[71] = -0.66302;
  weig[72] = -0.115755;
  weig[73] = 0.248427;
  weig[74] = 0.289598;
  weig[75] = -1.06855;
  weig[76] = 0.156426;
  weig[77] = 1.25585;
  weig[78] = 0.768427;
  weig[79] = 0.267802;
  weig[80] = 1.19801;
  weig[81] = -0.258241;
  weig[82] = -0.0404189;
  weig[83] = -0.242725;
  weig[84] = 0.885701;
  weig[85] = 0.201266;
  weig[86] = -0.355426;
  weig[87] = -0.0624959;
  weig[88] = -1.09526;
  weig[89] = 0.0993024;
  weig[90] = 0.181494;
  weig[91] = -0.0800807;
  weig[92] = 0.264904;
  weig[93] = -0.307917;
  weig[94] = -0.668169;
  weig[95] = -1.01196;
  weig[96] = -0.165116;
  weig[97] = 0.492903;
  weig[98] = 0.293225;
  weig[99] = 0.590397;
  weig[100] = 0.450955;
  weig[101] = 0.425382;
  weig[102] = -0.143943;
  weig[103] = -0.209632;
  weig[104] = 1.17351;
  weig[105] = -0.0829742;
  weig[106] = 0.364229;
  weig[107] = 0.40241;
  weig[108] = 0.403163;
  weig[109] = 0.0428497;
  weig[110] = 1.78445;
  weig[111] = 2.23372;
  weig[112] = 2.21669;
  weig[113] = 1.87605;
  weig[114] = 2.80741;
  weig[115] = 2.73913;
  weig[116] = 2.42954;
  weig[117] = 2.15869;
  weig[118] = 2.24206;
  weig[119] = 0.359888;
  weig[120] = -0.129953;
  weig[121] = 0.0556707;
  weig[122] = 0.118506;
  weig[123] = 0.594967;
  weig[124] = 0.74726;
  weig[125] = -0.17584;
  weig[126] = -0.175294;
  weig[127] = 0.288944;
  weig[128] = 0.217046;
  weig[129] = 0.770723;
  weig[130] = 1.21186;
  weig[131] = -0.130356;
  weig[132] = 0.0299258;
  weig[133] = 0.128715;
  weig[134] = -0.36843;
  weig[135] = 0.199728;
  weig[136] = 0.0904602;
  weig[137] = -0.315077;
  weig[138] = 0.063795;
  weig[139] = -0.613595;
  weig[140] = 0.20056;
  weig[141] = -1.59144;
  weig[142] = -0.0100777;
  weig[143] = 0.507202;
  weig[144] = -0.54614;
  weig[145] = -0.256693;
  weig[146] = 1.62434;
  weig[147] = 0.622903;
  weig[148] = -0.621877;
  weig[149] = 1.05084;
  weig[150] = -0.161754;
  weig[151] = -1.00193;
  weig[152] = 0.0295928;
  weig[153] = -0.191414;
  weig[154] = 0.0557493;
  weig[155] = -0.000775883;
  weig[156] = -1.04515;
  weig[157] = 0.164738;
  weig[158] = 0.109824;
  weig[159] = -1.29823;
  weig[160] = -0.440442;
  weig[161] = 0.67458;
  weig[162] = -0.122925;
  weig[163] = -0.163367;
  weig[164] = -0.119927;
  weig[165] = -0.0928814;
  weig[166] = 0.0288209;
  weig[167] = -0.501814;
  weig[168] = -0.592667;
  weig[169] = 0.179406;
  weig[170] = 0.0858155;
  weig[171] = -0.082783;
  weig[172] = -0.932768;
  weig[173] = -0.550443;
  weig[174] = 0.193341;
  weig[175] = -0.0568682;
  weig[176] = -1.7766;
  weig[177] = -1.51167;
  weig[178] = -0.00396187;
  weig[179] = -1.96813;
  weig[180] = -0.126788;
  weig[181] = 0.324299;
  weig[182] = -0.96344;
  weig[183] = 0.778807;
  weig[184] = -0.248255;
  weig[185] = -0.370013;
  weig[186] = 0.25727;
  weig[187] = 0.301803;
  weig[188] = -0.130182;
  weig[189] = -0.229956;
  weig[190] = 0.17964;
  weig[191] = -0.916918;
  weig[192] = 0.40729;
  weig[193] = -0.873678;
  weig[194] = -2.34777;
  weig[195] = -0.500682;
  weig[196] = -0.488222;
  weig[197] = 0.0576377;
  weig[198] = 0.274213;
  weig[199] = -0.215698;
  weig[200] = 0.703854;
  weig[201] = 0.365297;
  weig[202] = 0.475479;
  weig[203] = -0.713562;
  weig[204] = 0.603018;
  weig[205] = -0.46591;
  weig[206] = 0.348249;
  weig[207] = -0.6335;
  weig[208] = 0.12126;
  weig[209] = -0.370124;
  weig[210] = 0.554566;
  weig[211] = -0.149991;
  weig[212] = 0.320756;
  weig[213] = 0.179692;
  weig[214] = 0.620555;
  weig[215] = 0.425552;

  nsigtr = 531;
  nbkgtr = 505;


  ShapeANN::cnjfeed(ninp,nhid,thre,weig,oinp,out);

  sn = 1.*nsigtr/nbkgtr;
  //            = 1.05149
  nout = out/(out+sn*(1.-out));

  return;
}