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
 45;
 0.21713;-0.14068;-1.98929;,
 0.21711;1.58209;-0.99465;,
 13.92404;1.31339;-0.83951;,
 13.92404;-0.14067;-1.67900;,
 0.21711;1.58209;0.99465;,
 13.92404;1.31339;0.83951;,
 0.21713;-0.14068;1.98929;,
 13.92404;-0.14067;1.67900;,
 0.21713;-1.86346;0.99465;,
 13.92403;-1.59473;0.83951;,
 0.21713;-1.86346;-0.99465;,
 13.92403;-1.59473;-0.83951;,
 0.21713;-0.14068;-1.98929;,
 13.92404;-0.14067;-1.67900;,
 20.26144;0.35464;0.00001;,
 20.29416;-0.24617;-3.04205;,
 20.29416;-0.24617;3.04206;,
 20.26144;0.35464;0.00001;,
 20.26145;-0.79632;0.00001;,
 20.29416;-0.24617;-3.04205;,
 20.26145;-0.79632;0.00001;,
 0.21713;-0.14068;-0.00000;,
 0.21713;-0.14068;-0.00000;,
 0.21713;-0.14068;-0.00000;,
 0.21713;-0.14068;-0.00000;,
 0.21713;-0.14068;-0.00000;,
 0.21713;-0.14068;-0.00000;,
 20.26145;-0.79632;0.00001;,
 20.26144;0.35464;0.00001;,
 20.29416;-0.24617;-3.04205;,
 24.66988;-0.28134;-3.97410;,
 24.66988;-1.43135;-0.00000;,
 20.26145;-0.79632;0.00001;,
 24.67007;-0.28134;4.32268;,
 20.29416;-0.24617;3.04206;,
 20.26144;0.35464;0.00001;,
 24.66988;0.86867;0.00000;,
 24.66988;-0.28134;-3.97410;,
 20.29416;-0.24617;3.04206;,
 24.67007;-0.28134;4.32268;,
 42.81818;-0.28135;0.00001;,
 24.66988;-0.28134;-3.97410;,
 24.66988;-1.43135;-0.00000;,
 24.66988;-0.28134;-3.97410;,
 24.66988;0.86867;0.00000;;
 
 26;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;3,2,14,15;,
 4;5,7,16,17;,
 4;7,9,18,16;,
 4;11,13,19,20;,
 3;21,1,0;,
 3;22,4,1;,
 3;23,6,4;,
 3;24,8,6;,
 3;25,10,8;,
 3;26,12,10;,
 3;27,9,11;,
 3;28,2,5;,
 4;29,30,31,32;,
 4;32,31,33,34;,
 4;35,36,37,15;,
 4;38,39,36,35;,
 3;31,40,39;,
 3;40,36,39;,
 3;41,40,42;,
 3;43,44,40;;
 
 MeshMaterialList {
  2;
  26;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.439000;0.439000;0.439000;1.000000;;
   5.000000;
   0.590000;0.590000;0.590000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.941000;0.941000;0.941000;1.000000;;
   5.000000;
   0.220000;0.220000;0.220000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  33;
  -1.000000;-0.000006;0.000000;,
  0.019600;0.499901;-0.865861;,
  0.019599;0.999808;0.000000;,
  0.019600;0.499901;0.865861;,
  0.019601;-0.499900;0.865861;,
  0.019602;-0.999808;-0.000000;,
  0.055740;0.671873;-0.738566;,
  0.094741;0.843471;-0.528753;,
  0.090012;0.975490;0.200791;,
  0.055739;0.671873;0.738566;,
  0.077486;-0.846455;0.526792;,
  0.073545;-0.977270;-0.198832;,
  0.003382;0.909750;-0.415144;,
  0.017344;0.987745;-0.155110;,
  -0.000659;0.911971;0.410254;,
  -0.006216;-0.988966;0.148014;,
  -0.025364;-0.970972;0.237845;,
  -0.024212;-0.999673;-0.008179;,
  0.063236;-0.997940;-0.010814;,
  -0.013282;0.999878;-0.008167;,
  -0.021575;-0.967057;-0.253645;,
  0.044288;-0.675044;0.736447;,
  0.019601;-0.499900;-0.865861;,
  0.044289;-0.675044;-0.736447;,
  0.089254;0.812210;0.576497;,
  -0.022925;-0.914627;0.403648;,
  -0.018853;-0.912531;-0.408573;,
  0.066850;-0.817764;-0.571658;,
  -1.000000;-0.000012;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.010970;0.966233;-0.257436;,
  -0.014754;0.970246;0.241671;,
  0.063237;0.997940;-0.010814;;
  26;
  4;1,1,7,6;,
  4;2,2,8,2;,
  4;3,3,9,3;,
  4;4,4,10,21;,
  4;5,5,11,5;,
  4;22,22,23,22;,
  4;6,7,13,12;,
  4;8,9,14,24;,
  4;21,10,15,25;,
  4;11,23,26,27;,
  3;0,28,0;,
  3;0,28,28;,
  3;0,0,28;,
  3;0,29,0;,
  3;0,29,29;,
  3;0,0,29;,
  3;15,10,11;,
  3;13,7,8;,
  4;26,20,17,15;,
  4;15,17,16,25;,
  4;13,19,30,12;,
  4;14,31,19,13;,
  3;17,18,16;,
  3;32,19,31;,
  3;20,18,17;,
  3;30,19,32;;
 }
 MeshTextureCoords {
  45;
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.000000;,
  0.333330;0.500000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.666670;0.000000;,
  0.666670;0.500000;,
  0.833330;0.000000;,
  0.833330;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.833330;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.750000;1.000000;,
  0.250000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.500000;,
  1.000000;0.250000;,
  0.500000;0.000000;,
  1.000000;0.750000;,
  0.500000;1.000000;;
 }
}
