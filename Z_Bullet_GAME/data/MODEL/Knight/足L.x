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
 26;
 -0.00144;-2.04660;-6.55588;,
 0.01345;0.02847;-1.95780;,
 1.34327;0.02847;-1.21538;,
 2.21060;-2.04660;-1.83264;,
 1.54635;0.02849;0.04455;,
 2.54833;-2.04660;0.26285;,
 1.09748;-0.03808;1.17568;,
 1.80152;-2.04660;2.06581;,
 0.01344;-0.03808;1.62470;,
 -0.00144;-2.04660;2.81261;,
 -1.07060;-0.03808;1.17568;,
 -1.80439;-2.04660;2.06581;,
 -1.63547;0.08712;0.09767;,
 -2.55120;-2.04660;0.26285;,
 -1.31638;0.02847;-1.21538;,
 -2.21348;-2.04660;-1.83264;,
 0.01345;0.02847;-1.95780;,
 -0.00144;-2.04660;-6.55588;,
 -0.00144;-2.04660;0.26285;,
 -0.00144;-2.04660;0.26285;,
 -0.00144;-2.04660;0.26285;,
 -0.00144;-2.04660;0.26285;,
 -0.00144;-2.04660;0.26285;,
 -0.00144;-2.04660;0.26285;,
 -0.00144;-2.04660;0.26285;,
 -0.00144;-2.04660;0.26285;;
 
 24;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 3;18,0,3;,
 3;19,3,5;,
 3;20,5,7;,
 3;21,7,9;,
 3;22,9,11;,
 3;23,11,13;,
 3;24,13,15;,
 3;25,15,17;,
 3;16,14,2;,
 3;6,10,8;,
 3;10,12,14;,
 3;14,12,10;,
 3;4,6,2;,
 3;2,6,4;,
 4;10,6,2,14;,
 4;14,2,6,10;;
 
 MeshMaterialList {
  5;
  24;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  0,
  0,
  4,
  0,
  4,
  0,
  0,
  4;;
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
  28;
  0.000001;-1.000000;-0.000000;,
  0.577975;0.577185;-0.576891;,
  0.768219;0.518295;-0.375780;,
  0.890468;0.442691;0.105318;,
  0.618476;0.487295;0.616467;,
  0.000425;0.509064;0.860729;,
  -0.605915;0.473410;0.639336;,
  -0.897036;0.427517;0.112050;,
  -0.763891;0.509110;-0.396582;,
  0.325426;0.888027;-0.324816;,
  0.320720;0.933831;-0.158426;,
  0.000315;0.770348;0.637624;,
  -0.300176;0.938060;-0.173029;,
  -0.574995;0.582412;-0.574610;,
  0.000001;-1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000002;-1.000000;-0.000000;,
  0.000003;-1.000000;-0.000000;,
  0.000002;-1.000000;-0.000000;,
  0.000003;-1.000000;0.000000;,
  -0.035007;0.999276;0.014923;,
  0.068725;0.997571;0.011377;,
  -0.103148;-0.994519;-0.017076;,
  -0.205184;-0.978704;-0.006148;,
  0.205184;0.978704;0.006148;,
  0.104887;-0.994341;-0.016892;,
  0.052516;-0.998369;-0.022387;,
  -0.104887;0.994341;0.016892;;
  24;
  4;1,9,10,2;,
  4;2,10,3,3;,
  4;3,3,4,4;,
  4;4,4,11,5;,
  4;5,11,6,6;,
  4;6,6,7,7;,
  4;7,7,12,8;,
  4;8,12,13,13;,
  3;0,14,15;,
  3;0,15,15;,
  3;0,15,15;,
  3;0,15,16;,
  3;0,16,17;,
  3;0,17,18;,
  3;0,18,19;,
  3;0,19,14;,
  3;9,12,10;,
  3;20,21,11;,
  3;22,23,22;,
  3;12,24,21;,
  3;25,26,26;,
  3;10,20,27;,
  4;21,20,10,12;,
  4;22,26,26,22;;
 }
 MeshTextureCoords {
  26;
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  0.875000;1.000000;,
  0.875000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;;
 }
}
