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
 28;
 1.85969;-0.16496;-3.27000;,
 1.85969;-0.16496;1.59342;,
 3.27000;-3.70255;3.27000;,
 3.27000;-3.70255;-3.27000;,
 -1.91549;-0.16496;1.59342;,
 -1.91549;-0.16496;-3.27000;,
 -3.27000;-3.70255;-3.27000;,
 -3.27000;-3.70255;3.27000;,
 0.03111;-0.16496;3.78612;,
 1.85969;-0.16496;-3.27000;,
 0.03111;-0.16496;-5.06852;,
 -1.91549;-0.16496;-3.27000;,
 0.03111;-0.16496;3.78612;,
 -1.91549;-0.16496;1.59342;,
 -3.27000;-3.70255;3.27000;,
 0.03111;-3.70255;5.62020;,
 3.27000;-3.70255;3.27000;,
 1.85969;-0.16496;1.59342;,
 0.03111;-0.16496;-5.06852;,
 1.85969;-0.16496;-3.27000;,
 3.27000;-3.70255;-3.27000;,
 0.03111;-3.70255;-9.71536;,
 -3.27000;-3.70255;-3.27000;,
 -1.91549;-0.16496;-3.27000;,
 0.03111;-3.70255;5.62020;,
 -3.27000;-3.70255;-3.27000;,
 0.03111;-3.70255;-9.71536;,
 3.27000;-3.70255;-3.27000;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,1,9,10;,
 4;8,10,11,4;,
 4;12,13,14,15;,
 4;12,15,16,17;,
 4;18,19,20,21;,
 4;18,21,22,23;,
 4;24,7,25,26;,
 4;24,26,27,2;;
 
 MeshMaterialList {
  1;
  10;
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
   0.266667;0.266667;0.266667;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  10;
  -0.870780;0.392811;-0.295704;,
  0.870442;0.400633;-0.286050;,
  0.823951;0.445135;0.350656;,
  -0.823752;0.438930;0.358850;,
  0.000000;1.000000;0.000000;,
  -0.592099;0.455533;0.664762;,
  0.736981;0.396425;-0.547454;,
  0.603998;0.457820;0.652370;,
  -0.726986;0.391647;-0.564007;,
  0.000000;-1.000000;-0.000000;;
  10;
  4;1,2,2,1;,
  4;3,0,0,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,3,3,5;,
  4;7,7,2,2;,
  4;6,1,1,6;,
  4;8,8,0,0;,
  4;9,9,9,9;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  28;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.504757;0.000000;,
  1.000000;1.000000;,
  0.504757;1.000000;,
  0.000000;1.000000;,
  0.495243;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.495243;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.504757;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.504757;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.504757;1.000000;,
  0.000000;0.000000;,
  0.504757;0.000000;,
  1.000000;0.000000;;
 }
}
