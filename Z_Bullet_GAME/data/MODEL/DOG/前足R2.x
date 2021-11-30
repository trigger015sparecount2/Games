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
 15;
 -2.49330;-17.53506;-5.04066;,
 -2.60419;-15.20380;-0.83641;,
 -2.49330;-15.15694;-1.95919;,
 -2.49330;0.82166;2.00430;,
 -2.49330;-15.20380;2.00430;,
 -0.49792;-15.20380;2.00430;,
 -0.49792;0.82166;2.00430;,
 -0.49792;-15.15694;-1.95919;,
 -0.49792;0.82166;-1.86865;,
 -2.49330;0.82166;-1.86865;,
 -0.55336;-19.42242;2.00430;,
 -2.43786;-19.42242;2.00430;,
 -2.49330;-19.43125;-5.70089;,
 -0.49792;-19.43125;-5.70089;,
 -0.49792;-17.53506;-5.04066;;
 
 16;
 3;0,1,2;,
 4;3,4,5,6;,
 4;7,8,6,5;,
 4;8,7,2,9;,
 3;4,9,2;,
 3;9,4,3;,
 4;10,11,12,13;,
 4;5,10,13,7;,
 3;7,13,14;,
 4;7,14,0,2;,
 3;0,14,13;,
 3;0,13,12;,
 4;1,12,11,4;,
 3;12,1,0;,
 3;5,4,11;,
 3;5,11,10;;
 
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
  19;
  0.000000;-0.000000;1.000000;,
  0.999994;-0.003241;0.001174;,
  1.000000;0.000000;0.000000;,
  -0.997107;0.060176;-0.046441;,
  0.000000;0.005666;-0.999984;,
  -0.998770;0.035955;-0.034156;,
  0.000000;-0.999999;0.001147;,
  -0.995856;0.065817;-0.062762;,
  0.999987;-0.004861;0.001762;,
  0.000000;0.443583;-0.896233;,
  -0.999939;-0.007947;0.007708;,
  -1.000000;0.000000;0.000000;,
  0.999947;-0.009723;0.003523;,
  0.000000;0.584521;-0.811379;,
  0.000000;0.501577;-0.865113;,
  0.000000;0.328825;-0.944391;,
  0.000000;0.328825;-0.944391;,
  -0.999969;-0.006235;-0.004776;,
  -0.999448;-0.023837;0.023121;;
  16;
  3;7,5,3;,
  4;0,0,0,0;,
  4;1,2,2,8;,
  4;4,9,9,4;,
  3;10,11,3;,
  3;11,10,11;,
  4;6,6,6,6;,
  4;8,12,8,1;,
  3;1,8,2;,
  4;9,13,14,9;,
  3;14,13,15;,
  3;14,15,16;,
  4;5,17,18,10;,
  3;17,5,7;,
  3;0,0,0;,
  3;0,0,0;;
 }
 MeshTextureCoords {
  15;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
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
