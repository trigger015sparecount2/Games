xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 124;
 0.00000;17.13358;0.00000;,
 3.72837;15.98002;-2.15257;,
 0.00000;15.98002;-4.30515;,
 0.00000;17.13358;0.00000;,
 0.00000;15.98002;4.30515;,
 3.72837;15.98002;2.15257;,
 0.00000;17.13358;0.00000;,
 -3.72837;15.98002;2.15257;,
 0.00000;17.13358;0.00000;,
 0.00000;15.98002;-4.30515;,
 -3.72837;15.98002;-2.15257;,
 0.00000;8.52328;-8.61029;,
 7.45673;8.52328;-4.30515;,
 6.45772;4.21814;-3.72837;,
 0.00000;4.21814;-7.45673;,
 7.45673;8.52328;4.30515;,
 0.00000;8.52328;8.61029;,
 0.00000;4.21814;7.45673;,
 6.45772;4.21814;3.72837;,
 -7.45673;8.52328;4.30515;,
 -6.45772;4.21814;3.72837;,
 -7.45673;8.52328;-4.30515;,
 0.00000;8.52328;-8.61029;,
 0.00000;4.21814;-7.45673;,
 -6.45772;4.21814;-3.72837;,
 3.72837;1.06655;-2.15257;,
 0.00000;1.06655;-4.30515;,
 0.00000;1.06655;4.30515;,
 3.72837;1.06655;2.15257;,
 -3.72837;1.06655;2.15257;,
 0.00000;1.06655;-4.30515;,
 -3.72837;1.06655;-2.15257;,
 0.00000;-0.08701;-0.00000;,
 0.00000;-0.08701;-0.00000;,
 0.00000;-0.08701;-0.00000;,
 0.00000;-0.08701;-0.00000;,
 -3.36641;9.36859;-5.11728;,
 -3.04300;9.36859;-5.48249;,
 -3.04300;9.36859;-6.72500;,
 -3.36641;9.36859;-6.52478;,
 -2.71959;9.36859;-5.48249;,
 -2.71959;9.36859;-6.88998;,
 -3.36641;7.11801;-6.34778;,
 -3.04300;7.11801;-6.54801;,
 -3.04300;7.11801;-5.48249;,
 -3.36641;7.11801;-5.11728;,
 -2.71959;7.11801;-6.71300;,
 -2.71959;7.11801;-5.48249;,
 2.71938;9.36859;-5.48249;,
 3.04279;9.36859;-5.48249;,
 3.04279;9.36859;-6.72500;,
 2.71938;9.36859;-6.88998;,
 3.36619;9.36859;-5.11728;,
 3.36619;9.36859;-6.52478;,
 2.71938;7.11801;-6.71300;,
 3.04279;7.11801;-6.54801;,
 3.04279;7.11801;-5.48249;,
 2.71938;7.11801;-5.48249;,
 3.36619;7.11801;-6.34778;,
 3.36619;7.11801;-5.11728;,
 6.02211;12.82843;-3.72837;,
 0.00000;12.82843;-7.45673;,
 0.00000;12.82843;7.17884;,
 6.45772;12.82843;3.72837;,
 -6.45772;12.82843;3.72837;,
 0.00000;12.82843;-7.45673;,
 -6.45772;12.82843;-3.43033;,
 0.00000;11.01895;-8.09998;,
 6.75859;11.01895;-4.04918;,
 0.00000;11.01895;-8.09998;,
 -7.01620;11.01895;-3.87293;,
 7.01620;11.01895;4.05243;,
 0.00000;11.01895;7.93889;,
 -7.01620;11.01895;4.05243;,
 -7.01620;11.01895;0.08975;,
 -7.45673;8.52328;0.00000;,
 -6.45772;12.82843;0.14902;,
 -6.45772;4.21814;0.00000;,
 -3.72837;15.98002;0.00000;,
 -3.72837;1.06655;0.00000;,
 0.00000;17.13358;0.00000;,
 0.00000;-0.08701;-0.00000;,
 6.88739;11.01895;0.00162;,
 7.45673;8.52328;0.00000;,
 6.23992;12.82843;0.00000;,
 6.45772;4.21814;0.00000;,
 3.72837;15.98002;0.00000;,
 3.72837;1.06655;0.00000;,
 0.00000;17.13358;0.00000;,
 0.00000;-0.08701;-0.00000;,
 -3.04300;8.50524;-6.88177;,
 -3.04300;9.36859;-6.72500;,
 -2.71959;9.36859;-6.88998;,
 -2.71959;8.50524;-7.04675;,
 -2.71959;7.11801;-6.71300;,
 -3.04300;7.11801;-6.54801;,
 -3.36641;7.11801;-6.34778;,
 -3.36641;8.50524;-6.68155;,
 -3.36641;9.36859;-6.52478;,
 -2.71959;8.50524;-7.04675;,
 -2.71959;9.36859;-6.88998;,
 -2.71959;8.50524;-5.48249;,
 -2.71959;7.11801;-6.71300;,
 -3.36641;8.50524;-6.68155;,
 -3.36641;7.11801;-6.34778;,
 -3.36641;8.50524;-5.11728;,
 -3.36641;9.36859;-6.52478;,
 2.71938;8.49085;-7.05289;,
 2.71938;9.36859;-6.88998;,
 3.04279;9.36859;-6.72500;,
 3.04279;8.49085;-6.88791;,
 3.04279;7.11801;-6.54801;,
 2.71938;7.11801;-6.71300;,
 2.71938;8.49085;-7.05289;,
 2.71938;7.11801;-6.71300;,
 2.71938;8.49085;-5.48249;,
 2.71938;9.36859;-6.88998;,
 3.36619;9.36859;-6.52478;,
 3.36619;8.49085;-6.68769;,
 3.36619;7.11801;-6.34778;,
 3.36619;8.49085;-6.68769;,
 3.36619;9.36859;-6.52478;,
 3.36619;8.49085;-5.11728;,
 3.36619;7.11801;-6.34778;;
 
 80;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,4;,
 3;8,9,10;,
 4;11,12,13,14;,
 4;15,16,17,18;,
 4;16,19,20,17;,
 4;21,22,23,24;,
 4;14,13,25,26;,
 4;18,17,27,28;,
 4;17,20,29,27;,
 4;24,23,30,31;,
 3;26,25,32;,
 3;28,27,33;,
 3;27,29,34;,
 3;31,30,35;,
 4;36,37,38,39;,
 4;37,40,41,38;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;1,60,61,2;,
 4;5,4,62,63;,
 4;7,64,62,4;,
 4;10,9,65,66;,
 4;67,61,60,68;,
 4;67,68,12,11;,
 4;69,22,21,70;,
 4;69,70,66,65;,
 4;71,63,62,72;,
 4;71,72,16,15;,
 4;73,19,16,72;,
 4;73,72,62,64;,
 4;74,70,21,75;,
 4;74,75,19,73;,
 4;74,73,64,76;,
 4;74,76,66,70;,
 4;75,21,24,77;,
 4;75,77,20,19;,
 4;76,64,7,78;,
 4;76,78,10,66;,
 4;77,24,31,79;,
 4;77,79,29,20;,
 3;78,80,10;,
 3;78,7,80;,
 3;79,81,29;,
 3;79,31,81;,
 4;82,71,15,83;,
 4;82,83,12,68;,
 4;82,68,60,84;,
 4;82,84,63,71;,
 4;83,15,18,85;,
 4;83,85,13,12;,
 4;84,60,1,86;,
 4;84,86,5,63;,
 4;85,18,28,87;,
 4;85,87,25,13;,
 3;86,88,5;,
 3;86,1,88;,
 3;87,89,25;,
 3;87,28,89;,
 4;90,91,92,93;,
 4;90,93,94,95;,
 4;90,95,96,97;,
 4;90,97,98,91;,
 4;99,100,40,101;,
 4;99,101,47,102;,
 4;103,104,45,105;,
 4;103,105,36,106;,
 4;107,108,109,110;,
 4;107,110,111,112;,
 4;113,114,57,115;,
 4;113,115,48,116;,
 4;110,109,117,118;,
 4;110,118,119,111;,
 4;120,121,52,122;,
 4;120,122,59,123;;
 
 MeshMaterialList {
  6;
  80;
  2,
  2,
  2,
  2,
  0,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  1,
  0,
  0,
  1,
  1,
  2,
  2,
  1,
  2,
  2,
  1,
  1,
  0,
  2,
  2,
  2,
  0,
  0,
  2,
  2,
  0,
  0,
  2,
  2,
  1,
  1,
  2,
  0,
  2,
  2,
  0,
  0,
  2,
  2,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.674400;0.439200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.247843;0.210196;0.138039;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.661600;0.439200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.131765;0.131765;0.131765;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  78;
  0.000000;1.000000;0.000000;,
  0.000183;0.866820;-0.498621;,
  0.442971;0.859171;-0.256128;,
  0.434396;0.865912;0.247983;,
  0.000000;0.862540;0.505988;,
  -0.427399;0.867966;0.252914;,
  -0.431550;0.867486;-0.247453;,
  -0.000158;0.544908;-0.838495;,
  0.727618;0.535575;-0.428640;,
  0.730755;0.543175;0.413470;,
  0.000000;0.533315;0.845917;,
  -0.723050;0.541043;0.429501;,
  -0.733988;0.538671;-0.413637;,
  -0.000082;-0.014948;-0.999888;,
  0.503512;-0.014392;-0.863868;,
  0.496073;-0.013682;0.868173;,
  0.000000;-0.015758;0.999876;,
  -0.496073;-0.013682;0.868173;,
  -0.503981;-0.011433;-0.863639;,
  0.000000;-0.506749;-0.862094;,
  0.746595;-0.506749;-0.431047;,
  0.746595;-0.506749;0.431047;,
  0.000000;-0.506749;0.862094;,
  -0.746595;-0.506749;0.431047;,
  -0.746595;-0.506749;-0.431047;,
  0.000000;-0.870413;-0.492322;,
  0.426364;-0.870413;-0.246161;,
  0.426364;-0.870413;0.246161;,
  0.000000;-0.870413;0.492322;,
  -0.426364;-0.870413;0.246161;,
  -0.426364;-0.870413;-0.246161;,
  0.000000;-1.000000;-0.000000;,
  0.496391;0.256777;-0.829253;,
  0.816488;0.315450;-0.483569;,
  -0.835825;0.282749;-0.470585;,
  0.468631;0.259025;0.844566;,
  -0.710809;0.305213;0.633716;,
  0.000000;0.293216;0.956046;,
  -0.972037;0.234828;0.000000;,
  -0.999645;-0.026645;0.000000;,
  -0.874427;0.485158;0.000000;,
  -0.891174;-0.453661;0.000000;,
  -0.546824;0.837248;0.000000;,
  -0.546824;-0.837248;0.000000;,
  0.959656;0.279673;-0.029025;,
  0.999966;-0.002042;-0.007953;,
  0.873257;0.486136;-0.033082;,
  0.891174;-0.453661;-0.000000;,
  0.563831;0.825804;-0.011946;,
  0.546824;-0.837248;-0.000000;,
  -0.490698;-0.024857;-0.870975;,
  -0.454270;-0.025376;-0.890503;,
  -0.875704;-0.013796;-0.482652;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.454255;-0.026607;-0.890475;,
  0.490690;-0.026065;-0.870944;,
  -1.000000;-0.000000;0.000000;,
  0.875813;-0.014462;-0.482434;,
  -0.497138;0.262165;-0.827117;,
  -0.984775;0.173831;0.000000;,
  0.966195;0.256159;-0.029147;,
  0.999867;-0.014265;-0.007930;,
  0.999916;0.010250;-0.007975;,
  -0.484810;0.156261;-0.860548;,
  -0.448586;0.159678;-0.879360;,
  -0.444326;-0.209557;-0.871011;,
  -0.480419;-0.205154;-0.852707;,
  -0.870550;-0.115106;-0.478428;,
  -0.871843;0.087505;-0.481905;,
  0.448329;0.163119;-0.878859;,
  0.484552;0.159632;-0.860074;,
  0.479831;-0.210857;-0.851646;,
  0.443751;-0.215372;-0.869885;,
  -1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  0.871769;0.089402;-0.481691;,
  0.870378;-0.118336;-0.477952;;
  80;
  3;0,2,1;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,1,6;,
  4;13,14,20,19;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;18,13,19,24;,
  4;19,20,26,25;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;24,19,25,30;,
  3;25,26,31;,
  3;27,28,31;,
  3;28,29,31;,
  3;30,25,31;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;2,8,7,1;,
  4;3,4,10,9;,
  4;5,11,10,4;,
  4;6,1,7,12;,
  4;32,7,8,33;,
  4;32,33,14,13;,
  4;59,13,18,34;,
  4;59,34,12,7;,
  4;35,9,10,37;,
  4;35,37,16,15;,
  4;36,17,16,37;,
  4;36,37,10,11;,
  4;38,34,39,39;,
  4;38,39,39,60;,
  4;38,36,11,40;,
  4;38,40,12,34;,
  4;39,39,24,41;,
  4;39,41,23,39;,
  4;40,11,5,42;,
  4;40,42,6,12;,
  4;41,24,30,43;,
  4;41,43,29,23;,
  3;42,0,6;,
  3;42,5,0;,
  3;43,31,29;,
  3;43,30,31;,
  4;44,61,62,45;,
  4;44,45,63,33;,
  4;44,33,8,46;,
  4;44,46,9,61;,
  4;45,62,21,47;,
  4;45,47,20,63;,
  4;46,8,2,48;,
  4;46,48,3,9;,
  4;47,21,27,49;,
  4;47,49,26,20;,
  3;48,0,3;,
  3;48,2,0;,
  3;49,31,26;,
  3;49,27,31;,
  4;50,64,65,51;,
  4;50,51,66,67;,
  4;50,67,68,52;,
  4;50,52,69,64;,
  4;53,53,53,53;,
  4;53,53,53,53;,
  4;52,68,54,54;,
  4;52,54,54,69;,
  4;55,70,71,56;,
  4;55,56,72,73;,
  4;57,74,74,57;,
  4;57,57,75,75;,
  4;56,71,76,58;,
  4;56,58,77,72;,
  4;58,76,53,53;,
  4;58,53,53,77;;
 }
 MeshTextureCoords {
  124;
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.333330;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.833330;0.166670;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.500000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.500000;,
  0.666670;0.666670;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  1.000000;0.666670;,
  0.833330;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.500000;0.833330;,
  0.333330;0.833330;,
  0.666670;0.833330;,
  1.000000;0.833330;,
  0.833330;0.833330;,
  0.083330;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.500000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.833330;0.333330;,
  0.000000;0.403383;,
  0.166670;0.403383;,
  1.000000;0.403383;,
  0.833330;0.403383;,
  0.333330;0.403383;,
  0.500000;0.403383;,
  0.666670;0.403383;,
  0.750000;0.403383;,
  0.750000;0.500000;,
  0.750000;0.333330;,
  0.750000;0.666670;,
  0.750000;0.166670;,
  0.750000;0.833330;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.250000;0.403383;,
  0.250000;0.500000;,
  0.250000;0.333330;,
  0.250000;0.666670;,
  0.250000;0.166670;,
  0.250000;0.833330;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.500000;0.383611;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.383611;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.383611;,
  0.000000;0.000000;,
  0.000000;0.383611;,
  0.000000;0.000000;,
  1.000000;0.383611;,
  0.000000;1.000000;,
  1.000000;0.383611;,
  1.000000;1.000000;,
  0.000000;0.383611;,
  1.000000;0.000000;,
  0.000000;0.398639;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.398639;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.398639;,
  1.000000;1.000000;,
  0.000000;0.398639;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.398639;,
  1.000000;1.000000;,
  0.000000;0.398639;,
  0.000000;0.000000;,
  1.000000;0.398639;,
  0.000000;1.000000;;
 }
}