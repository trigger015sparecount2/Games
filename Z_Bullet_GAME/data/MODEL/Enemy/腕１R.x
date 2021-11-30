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
 32;
 -2.41454;1.49600;-1.61195;,
 -2.41454;-3.03531;-1.61195;,
 -5.76839;-3.03531;-1.61195;,
 -5.76839;0.26000;-1.61195;,
 -2.41454;-12.99019;-1.61195;,
 -5.76839;-12.99019;-1.61195;,
 -5.76839;0.26000;-1.61195;,
 -5.76839;-3.03531;-1.61195;,
 -5.76839;-3.03531;1.74190;,
 -5.76839;0.26000;1.74190;,
 -5.76839;-12.99019;-1.61195;,
 -5.76839;-12.99019;1.74190;,
 -5.76839;0.26000;1.74190;,
 -5.76839;-3.03531;1.74190;,
 -2.41454;-3.03531;1.74190;,
 -2.41454;1.49600;1.74190;,
 -5.76839;-12.99019;1.74190;,
 -2.41454;-12.99019;1.74190;,
 -2.41454;-3.03531;1.74190;,
 -2.41454;-12.99019;1.74190;,
 -2.41454;-12.99019;-1.61195;,
 -2.41454;-3.03531;-1.61195;,
 -2.41454;1.49600;1.74190;,
 -2.41454;1.49600;-1.61195;,
 -5.76839;0.26000;-1.61195;,
 -2.41454;-12.99019;-1.61195;,
 -5.76839;-12.99019;-1.61195;,
 -0.04250;1.49600;-1.61195;,
 -2.41454;1.49600;-1.61195;,
 -0.04250;1.49600;1.74190;,
 -0.04250;-3.03531;-1.61195;,
 -0.04250;-3.03531;1.74190;;
 
 14;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;18,19,20,21;,
 4;22,23,24,9;,
 4;25,19,11,26;,
 4;27,28,22,29;,
 4;30,21,28,27;,
 4;31,18,21,30;,
 4;29,22,18,31;,
 4;29,31,30,27;;
 
 MeshMaterialList {
  1;
  14;
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
   0.000000;0.172549;0.018824;1.000000;;
   5.000000;
   0.490000;0.490000;0.490000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  8;
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.175628;0.984456;0.000000;,
  -0.345797;0.938309;0.000000;;
  14;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;6,6,7,7;,
  4;4,4,4,4;,
  4;3,6,6,3;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  32;
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;;
 }
}
