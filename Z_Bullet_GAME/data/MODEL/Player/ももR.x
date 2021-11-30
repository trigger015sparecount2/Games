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
 20;
 -4.85847;-26.48205;3.41569;,
 -6.41610;0.10039;5.07492;,
 -8.34676;0.08800;3.35039;,
 -6.93340;-26.48205;1.67809;,
 -2.11634;-26.48205;3.41569;,
 -0.34313;-0.26422;5.87119;,
 0.69150;-26.48205;3.03100;,
 2.45747;-0.07334;4.44303;,
 -8.32500;0.08186;-2.59939;,
 -6.90454;-26.48205;-1.74653;,
 -4.79614;-26.48205;-3.92443;,
 -6.40192;0.08815;-5.11478;,
 0.00000;0.00000;-5.78600;,
 -1.72815;-26.48205;-4.38849;,
 2.47922;-0.07953;-5.22645;,
 0.72036;-26.48205;-3.52654;,
 1.66435;-26.48205;1.56581;,
 3.43171;-0.07507;1.36165;,
 3.44088;-0.07764;-1.45283;,
 1.68230;-26.48205;-1.24968;;
 
 10;
 4;0,1,2,3;,
 4;4,5,1,0;,
 4;6,7,5,4;,
 4;3,2,8,9;,
 4;10,11,12,13;,
 4;9,8,11,10;,
 4;13,12,14,15;,
 4;16,17,7,6;,
 4;18,19,15,14;,
 4;18,17,16,19;;
 
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
   0.081600;0.081600;0.081600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.020400;0.020400;0.020400;;
  }
 }
 MeshNormals {
  10;
  0.075334;-0.063181;-0.995155;,
  -0.472760;-0.062998;-0.878937;,
  -0.934518;-0.064723;-0.349982;,
  -0.908257;-0.075394;0.411563;,
  -0.378820;-0.087116;0.921361;,
  0.118726;-0.087812;0.989037;,
  0.653629;-0.089812;0.751467;,
  0.688448;-0.082804;-0.720543;,
  0.972176;-0.071973;0.222920;,
  0.984795;-0.070443;-0.158795;;
  10;
  4;4,4,3,3;,
  4;5,5,4,4;,
  4;6,6,5,5;,
  4;3,3,2,2;,
  4;1,1,0,0;,
  4;2,2,1,1;,
  4;0,0,7,7;,
  4;8,8,6,6;,
  4;9,9,7,7;,
  4;9,8,8,9;;
 }
 MeshTextureCoords {
  20;
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.666670;,
  1.000000;0.666670;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.666670;,
  0.500000;0.666670;,
  1.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.500000;0.333330;,
  0.500000;0.613630;,
  0.500000;0.574980;,
  0.500000;0.434430;,
  0.500000;0.406320;;
 }
}
