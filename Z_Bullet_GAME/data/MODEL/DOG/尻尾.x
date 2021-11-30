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
 10;
 -0.70859;15.04628;16.75666;,
 0.93835;15.19752;16.54333;,
 -0.12710;15.79313;15.99889;,
 0.31422;14.08533;17.55990;,
 -1.00975;14.22028;17.43656;,
 0.11865;-0.59823;0.81718;,
 -0.12710;0.80931;-0.39424;,
 0.93835;0.21370;0.15016;,
 -1.00975;-0.76354;1.04338;,
 -1.19255;0.21370;0.15016;;
 
 16;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;5,6,7;,
 3;5,8,9;,
 3;5,9,6;,
 3;1,7,6;,
 3;1,6,2;,
 3;3,5,7;,
 3;3,7,1;,
 3;4,8,5;,
 3;4,5,3;,
 3;0,9,8;,
 3;0,8,4;,
 3;2,6,9;,
 3;2,9,0;;
 
 MeshMaterialList {
  3;
  16;
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
  0;;
  Material {
   0.000000;0.254118;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  25;
  0.025107;-0.649602;-0.759860;,
  0.014536;0.650333;0.759510;,
  -0.047470;-0.678729;-0.732853;,
  0.002286;-0.652098;-0.758131;,
  -0.034012;-0.666644;-0.744600;,
  0.031933;0.682395;0.730285;,
  -0.006882;0.637000;0.770833;,
  0.027901;0.701155;0.712463;,
  0.019002;0.667647;0.744235;,
  -0.014309;-0.661258;-0.750022;,
  0.603749;0.588413;-0.537826;,
  0.603742;0.588417;-0.537830;,
  0.603756;0.588409;-0.537823;,
  0.864023;-0.378197;0.332312;,
  0.325804;-0.707351;0.627301;,
  0.923880;-0.282468;0.258184;,
  0.050753;-0.743713;0.666570;,
  0.236476;-0.717189;0.655530;,
  -0.136763;-0.743970;0.654068;,
  -0.977031;0.167257;-0.132045;,
  -0.983155;0.149615;-0.104981;,
  -0.997583;0.057615;-0.038849;,
  -0.962493;0.200259;-0.183042;,
  -0.756817;0.490844;-0.431625;,
  -0.603742;0.588416;-0.537830;;
  16;
  3;8,5,7;,
  3;8,1,5;,
  3;8,6,1;,
  3;9,3,0;,
  3;9,2,4;,
  3;9,4,3;,
  3;10,11,10;,
  3;10,10,12;,
  3;13,14,13;,
  3;13,13,15;,
  3;16,17,14;,
  3;16,14,18;,
  3;19,20,21;,
  3;19,21,22;,
  3;23,24,24;,
  3;23,20,19;;
 }
 MeshTextureCoords {
  10;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
