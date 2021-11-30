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
 16;
 0.00000;0.00405;6.37946;,
 4.22186;0.00405;4.75241;,
 4.28923;11.16749;5.38294;,
 0.00000;9.64400;7.01000;,
 6.13175;0.00405;0.40392;,
 6.26893;8.11548;0.40392;,
 3.23024;0.00405;-4.94596;,
 0.00000;0.00405;-6.36097;,
 0.00000;6.19901;-6.68721;,
 3.43723;7.30699;-5.27219;,
 -4.28923;11.16749;5.38294;,
 -4.22186;0.00405;4.75241;,
 -6.26893;8.11548;0.40392;,
 -6.13175;0.00405;0.40392;,
 -3.23024;0.00405;-4.94596;,
 -3.43723;7.30699;-5.27219;;
 
 8;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;4,6,9,5;,
 4;0,3,10,11;,
 4;11,10,12,13;,
 4;14,15,8,7;,
 4;13,12,15,14;;
 
 MeshMaterialList {
  2;
  8;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
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
  8;
  0.000000;-0.062041;0.998074;,
  0.000000;-0.054682;-0.998504;,
  0.696133;-0.042888;0.716630;,
  0.998886;-0.028769;-0.037404;,
  0.681628;-0.042888;-0.730441;,
  -0.696133;-0.042888;0.716630;,
  -0.998886;-0.028769;-0.037404;,
  -0.681628;-0.042888;-0.730441;;
  8;
  4;0,2,2,0;,
  4;2,3,3,2;,
  4;4,1,1,4;,
  4;3,4,4,3;,
  4;0,0,5,5;,
  4;5,5,6,6;,
  4;7,7,1,1;,
  4;6,6,7,7;;
 }
 MeshTextureCoords {
  16;
  0.500000;1.000000;,
  0.721790;1.000000;,
  0.721790;1.000000;,
  0.500000;1.000000;,
  0.721790;0.666670;,
  0.721790;0.666670;,
  0.721790;0.333330;,
  0.500000;0.333330;,
  0.500000;0.333330;,
  0.721790;0.333330;,
  0.721790;1.000000;,
  0.721790;1.000000;,
  0.721790;0.666670;,
  0.721790;0.666670;,
  0.721790;0.333330;,
  0.721790;0.333330;;
 }
}
