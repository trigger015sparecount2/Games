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
 87;
 -5.91388;0.00576;2.12322;,
 -5.91388;-1.48592;1.50535;,
 -0.02001;-1.48592;1.50535;,
 -0.02001;0.00576;2.12322;,
 -5.91388;-2.10379;0.01367;,
 -0.02000;-2.10379;0.01367;,
 -5.91388;-1.48592;-1.47800;,
 -0.02001;-1.48592;-1.47800;,
 -5.91388;0.00576;-2.09587;,
 -0.02001;0.00576;-2.09587;,
 -5.91388;1.49743;-1.47800;,
 -0.02001;1.49743;-1.47800;,
 -5.91388;2.11530;0.01367;,
 -0.02001;2.11530;0.01367;,
 -5.91388;1.49743;1.50535;,
 -0.02001;1.49743;1.50535;,
 -5.91388;0.00576;2.12322;,
 -0.02001;0.00576;2.12322;,
 -1.47380;0.22030;0.01367;,
 -1.47380;0.22030;0.01367;,
 -1.47380;0.22030;0.01367;,
 -1.47380;0.22030;0.01367;,
 -1.47380;0.22030;0.01367;,
 -1.47380;0.22030;0.01367;,
 -1.47380;0.22030;0.01367;,
 -1.47380;0.22030;0.01367;,
 1.83129;0.82347;-0.00000;,
 1.20884;1.70810;1.06481;,
 1.65886;0.74306;1.50587;,
 1.83129;0.82347;-0.00000;,
 1.02245;2.10784;-0.00000;,
 1.83129;0.82347;-0.00000;,
 1.20884;1.70810;-1.06481;,
 1.83129;0.82347;-0.00000;,
 1.65886;0.74306;-1.50587;,
 1.83129;0.82347;-0.00000;,
 2.10886;-0.22198;-1.06481;,
 1.83129;0.82347;-0.00000;,
 2.29527;-0.62172;-0.00000;,
 1.83129;0.82347;-0.00000;,
 2.10886;-0.22198;1.06481;,
 1.83129;0.82347;-0.00000;,
 1.65886;0.74306;1.50587;,
 0.33631;2.29725;1.96751;,
 1.16782;0.51409;2.78248;,
 -0.00812;3.03587;-0.00000;,
 0.33631;2.29725;-1.96751;,
 1.16782;0.51409;-2.78248;,
 1.99931;-1.26908;-1.96751;,
 2.34374;-2.00770;-0.00000;,
 1.99931;-1.26908;1.96751;,
 1.16782;0.51409;2.78248;,
 -0.65349;2.50122;2.57067;,
 0.43293;0.17140;3.63548;,
 -1.10349;3.46626;-0.00000;,
 -0.65349;2.50122;-2.57067;,
 0.43293;0.17140;-3.63548;,
 1.51935;-2.15842;-2.57067;,
 1.96935;-3.12346;-0.00000;,
 1.51935;-2.15842;2.57067;,
 0.43293;0.17140;3.63548;,
 -1.60985;2.28896;2.78248;,
 -0.43393;-0.23282;3.93502;,
 -2.09694;3.33352;-0.00000;,
 -1.60985;2.28896;-2.78248;,
 -0.43393;-0.23282;-3.93502;,
 0.74200;-2.75460;-2.78248;,
 1.22908;-3.79916;-0.00000;,
 0.74200;-2.75460;2.78248;,
 -0.43393;-0.23282;3.93502;,
 -6.94369;0.00576;1.69912;,
 -6.94369;-1.18604;1.20547;,
 -6.94369;0.00576;0.01367;,
 -6.94368;-1.67970;0.01367;,
 -6.94369;0.00576;0.01367;,
 -6.94369;-1.18604;-1.17812;,
 -6.94369;0.00576;0.01367;,
 -6.94369;0.00576;-1.67178;,
 -6.94369;0.00576;0.01367;,
 -6.94369;1.19755;-1.17812;,
 -6.94369;0.00576;0.01367;,
 -6.94369;1.69121;0.01367;,
 -6.94369;0.00576;0.01367;,
 -6.94369;1.19755;1.20547;,
 -6.94369;0.00576;0.01367;,
 -6.94369;0.00576;1.69912;,
 -6.94369;0.00576;0.01367;;
 
 64;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,3,2;,
 3;19,2,5;,
 3;20,5,7;,
 3;21,7,9;,
 3;22,9,11;,
 3;23,11,13;,
 3;24,13,15;,
 3;25,15,17;,
 3;26,27,28;,
 3;29,30,27;,
 3;31,32,30;,
 3;33,34,32;,
 3;35,36,34;,
 3;37,38,36;,
 3;39,40,38;,
 3;41,42,40;,
 4;28,27,43,44;,
 4;27,30,45,43;,
 4;30,32,46,45;,
 4;32,34,47,46;,
 4;34,36,48,47;,
 4;36,38,49,48;,
 4;38,40,50,49;,
 4;40,42,51,50;,
 4;44,43,52,53;,
 4;43,45,54,52;,
 4;45,46,55,54;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;53,52,61,62;,
 4;52,54,63,61;,
 4;54,55,64,63;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;70,71,1,0;,
 3;72,71,70;,
 4;71,73,4,1;,
 3;74,73,71;,
 4;73,75,6,4;,
 3;76,75,73;,
 4;75,77,8,6;,
 3;78,77,75;,
 4;77,79,10,8;,
 3;80,79,77;,
 4;79,81,12,10;,
 3;82,81,79;,
 4;81,83,14,12;,
 3;84,83,81;,
 4;83,85,16,14;,
 3;86,85,83;;
 
 MeshMaterialList {
  5;
  64;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
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
  0,
  1,
  0,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  0;;
  Material {
   0.432941;0.432941;0.432941;1.000000;;
   100.000000;
   0.000000;0.000000;0.000000;;
   0.108235;0.108235;0.108235;;
  }
  Material {
   0.586667;0.398431;0.241569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.709020;0.000000;1.000000;;
   100.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.724706;0.724706;0.724706;1.000000;;
   100.000000;
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
  71;
  -0.195128;-0.000000;0.980778;,
  -0.195127;-0.693515;0.693515;,
  -0.195127;-0.980778;-0.000000;,
  -0.195127;-0.693515;-0.693515;,
  -0.195128;-0.000000;-0.980778;,
  -0.195128;0.693515;-0.693514;,
  -0.195128;0.980778;0.000000;,
  -0.195128;0.693515;0.693514;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.707107;0.707107;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;-0.707107;-0.707107;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.707107;-0.707107;,
  0.000000;1.000000;0.000000;,
  0.000000;0.707107;0.707107;,
  0.999650;-0.026440;-0.000000;,
  0.906307;0.422620;0.000000;,
  0.875210;0.408117;0.259708;,
  0.797597;0.574556;0.183642;,
  0.765451;0.643494;0.000000;,
  0.797597;0.574556;-0.183642;,
  0.875210;0.408117;-0.259708;,
  0.952820;0.241678;-0.183645;,
  0.984968;0.172739;0.000000;,
  0.952820;0.241677;0.183645;,
  0.758915;0.353887;0.546637;,
  0.595558;0.704205;0.386531;,
  0.527894;0.849310;-0.000000;,
  0.595558;0.704205;-0.386531;,
  0.758915;0.353887;-0.546637;,
  0.922269;0.003570;-0.386532;,
  0.989933;-0.141534;0.000000;,
  0.922269;0.003570;0.386532;,
  0.482525;0.225005;0.846488;,
  0.229564;0.767483;0.598558;,
  0.124785;0.992184;-0.000000;,
  0.229563;0.767483;-0.598558;,
  0.482525;0.225005;-0.846488;,
  0.735487;-0.317471;-0.598558;,
  0.840267;-0.542172;-0.000000;,
  0.735487;-0.317471;0.598558;,
  0.270856;0.126302;0.954298;,
  -0.014321;0.737870;0.674790;,
  -0.132443;0.991191;0.000000;,
  -0.014321;0.737870;-0.674790;,
  0.270855;0.126302;-0.954298;,
  0.556034;-0.485266;-0.674791;,
  0.674159;-0.738586;-0.000000;,
  0.556034;-0.485266;0.674791;,
  -1.000000;-0.000001;0.000000;,
  -0.380793;-0.000000;0.924660;,
  -0.380791;-0.653834;0.653834;,
  -0.380789;-0.924662;-0.000000;,
  -0.380791;-0.653834;-0.653834;,
  -0.380793;-0.000000;-0.924660;,
  -0.380792;0.653834;-0.653834;,
  -0.380791;0.924661;-0.000000;,
  -0.380792;0.653834;0.653834;,
  0.823087;-0.006364;-0.567880;,
  0.841019;0.379571;-0.385503;,
  0.847794;0.530326;-0.000000;,
  0.841019;0.379571;0.385502;,
  0.823087;-0.006364;0.567879;,
  0.802674;-0.425123;0.418312;,
  0.793413;-0.608684;0.000000;,
  0.802674;-0.425123;-0.418312;,
  -1.000000;-0.000001;-0.000001;,
  -1.000000;0.000000;0.000000;,
  -1.000000;-0.000003;0.000000;,
  -1.000000;-0.000001;0.000001;;
  64;
  4;0,1,9,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,0,8,15;,
  3;16,59,60;,
  3;16,60,61;,
  3;16,61,62;,
  3;16,62,63;,
  3;16,63,64;,
  3;16,64,65;,
  3;16,65,66;,
  3;16,66,59;,
  3;17,19,18;,
  3;17,20,19;,
  3;17,21,20;,
  3;17,22,21;,
  3;17,23,22;,
  3;17,24,23;,
  3;17,25,24;,
  3;17,18,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,25,33,32;,
  4;25,18,26,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,26,34,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,34,42,49;,
  4;51,52,1,0;,
  3;50,67,68;,
  4;52,53,2,1;,
  3;50,69,67;,
  4;53,54,3,2;,
  3;50,70,69;,
  4;54,55,4,3;,
  3;50,68,70;,
  4;55,56,5,4;,
  3;50,68,68;,
  4;56,57,6,5;,
  3;50,68,68;,
  4;57,58,7,6;,
  3;50,68,68;,
  4;58,51,0,7;,
  3;50,68,68;;
 }
 MeshTextureCoords {
  87;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.062500;0.000000;,
  0.250000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.000000;,
  0.312500;0.000000;,
  0.500000;0.000000;,
  0.437500;0.000000;,
  0.625000;0.000000;,
  0.562500;0.000000;,
  0.750000;0.000000;,
  0.687500;0.000000;,
  0.875000;0.000000;,
  0.812500;0.000000;,
  1.000000;0.000000;,
  0.937500;0.000000;;
 }
}
