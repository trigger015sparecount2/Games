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
 27;
 -1.04675;1.41775;11.63176;,
 -1.04675;1.41775;-11.05845;,
 -27.40748;1.41775;-11.05845;,
 -27.40748;1.41775;11.63176;,
 -5.29464;-68.36971;-7.40215;,
 -5.29464;-68.36971;7.97535;,
 -23.15964;-68.36971;7.97535;,
 -23.15964;-68.36971;-7.40215;,
 -27.40748;-22.22372;-11.05845;,
 -23.15964;-68.36971;-7.40215;,
 -27.40748;-22.22372;11.63176;,
 -27.40748;-22.22372;-11.05845;,
 -1.04675;-22.22372;-11.05845;,
 -5.29464;-68.36971;-7.40215;,
 -23.15964;-68.36971;-7.40215;,
 -27.40748;1.41775;-11.05845;,
 -1.04675;1.41775;-11.05845;,
 -27.40748;-22.22372;11.63176;,
 -1.04675;-22.22372;11.63176;,
 -1.04675;1.41775;11.63176;,
 -27.40748;1.41775;11.63176;,
 -23.15964;-68.36971;7.97535;,
 -5.29464;-68.36971;7.97535;,
 -1.04675;-22.22372;-11.05845;,
 -1.04675;-22.22372;11.63176;,
 -5.29464;-68.36971;-7.40215;,
 -1.04675;1.41775;-11.05845;;
 
 10;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,6,10;,
 4;11,12,13,14;,
 4;11,15,16,12;,
 4;17,18,19,20;,
 4;17,21,22,18;,
 4;23,24,5,25;,
 4;23,26,0,24;,
 4;2,8,10,3;;
 
 MeshMaterialList {
  2;
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
   0.752800;0.574400;0.370400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.501600;0.000000;0.009600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  14;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.998947;-0.045881;0.000000;,
  0.000000;-0.039524;-0.999219;,
  0.000000;-0.039525;0.999219;,
  -0.995790;-0.091665;0.000000;,
  0.000000;-0.078986;-0.996876;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.078988;0.996876;,
  0.998947;-0.045881;-0.000000;,
  0.995790;-0.091666;-0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;;
  10;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,5,5,2;,
  4;3,3,6,6;,
  4;3,7,7,3;,
  4;4,4,8,8;,
  4;4,9,9,4;,
  4;10,10,11,11;,
  4;10,12,12,10;,
  4;13,2,2,13;;
 }
 MeshTextureCoords {
  27;
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.472340;,
  0.000000;1.000000;,
  1.000000;0.472340;,
  1.000000;0.472340;,
  0.000000;0.472340;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.472340;,
  1.000000;0.472340;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.472340;,
  0.000000;0.472340;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
}
