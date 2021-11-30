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
 71;
 1.38268;-54.40385;-11.05845;,
 27.74337;-54.40385;-11.05845;,
 27.74337;-54.40385;11.63176;,
 1.38268;-54.40385;11.63176;,
 27.74337;-8.25790;-11.05845;,
 27.74337;-8.25790;11.63176;,
 27.74337;-54.40385;-11.05845;,
 27.74337;-8.25790;-11.05845;,
 27.74337;-54.40385;-11.05845;,
 1.38268;-54.40385;-11.05845;,
 1.38268;-8.25790;-11.05845;,
 1.38268;15.38353;-11.05845;,
 27.74337;15.38353;-11.05845;,
 27.74337;-8.25790;11.63176;,
 27.74337;15.38353;11.63176;,
 1.38268;15.38353;11.63176;,
 1.38268;-8.25790;11.63176;,
 1.38268;-54.40385;11.63176;,
 27.74337;-54.40385;11.63176;,
 1.38268;-8.25790;-11.05845;,
 1.38268;-54.40385;-11.05845;,
 1.38268;-8.25790;11.63176;,
 1.38268;15.38353;11.63176;,
 1.38268;15.38353;-11.05845;,
 31.54317;12.11070;-7.91720;,
 31.54317;-4.98478;-7.91720;,
 27.74337;15.38353;-11.05845;,
 31.54317;12.11070;8.49038;,
 27.74337;15.38353;11.63176;,
 31.54317;-4.98478;8.49038;,
 34.93426;8.65138;-4.59701;,
 34.93426;-1.52542;-4.59701;,
 34.93426;8.65138;5.17016;,
 34.93426;-1.52542;5.17016;,
 25.25238;18.77487;9.48753;,
 3.87369;18.77487;9.48753;,
 25.25238;18.77487;-8.91443;,
 27.74337;15.38353;-11.05845;,
 3.87369;18.77487;-8.91443;,
 1.38268;15.38353;-11.05845;,
 18.40818;21.13192;3.59635;,
 10.71795;21.13192;3.59635;,
 18.40818;21.13192;-3.02315;,
 10.71795;21.13192;-3.02315;,
 1.38268;1.41775;11.63176;,
 27.74337;1.41775;11.63176;,
 27.74337;1.41775;-11.05845;,
 1.38268;1.41775;-11.05845;,
 5.63057;-68.36971;-7.40215;,
 23.49556;-68.36971;-7.40215;,
 23.49556;-68.36971;7.97535;,
 5.63057;-68.36971;7.97535;,
 27.74337;-22.22372;-11.05845;,
 27.74337;-22.22372;11.63176;,
 23.49556;-68.36971;-7.40215;,
 27.74337;-22.22372;-11.05845;,
 23.49556;-68.36971;-7.40215;,
 5.63057;-68.36971;-7.40215;,
 1.38268;-22.22372;-11.05845;,
 1.38268;1.41775;-11.05845;,
 27.74337;1.41775;-11.05845;,
 27.74337;-22.22372;11.63176;,
 27.74337;1.41775;11.63176;,
 1.38268;1.41775;11.63176;,
 1.38268;-22.22372;11.63176;,
 5.63057;-68.36971;7.97535;,
 23.49556;-68.36971;7.97535;,
 1.38268;-22.22372;-11.05845;,
 5.63057;-68.36971;-7.40215;,
 1.38268;-22.22372;11.63176;,
 1.38268;1.41775;-11.05845;;
 
 36;
 4;0,1,2,3;,
 4;4,5,2,6;,
 4;7,8,9,10;,
 4;7,10,11,12;,
 4;13,14,15,16;,
 4;13,16,17,18;,
 4;19,20,3,21;,
 4;19,21,22,23;,
 4;24,25,4,26;,
 4;27,24,26,28;,
 4;29,27,28,5;,
 4;25,29,5,4;,
 4;30,31,25,24;,
 4;32,30,24,27;,
 4;33,32,27,29;,
 4;31,33,29,25;,
 4;31,30,32,33;,
 4;34,35,22,28;,
 4;36,34,28,37;,
 4;38,36,37,39;,
 4;35,38,39,22;,
 4;40,41,35,34;,
 4;42,40,34,36;,
 4;43,42,36,38;,
 4;41,43,38,35;,
 4;41,40,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,50,54;,
 4;55,56,57,58;,
 4;55,58,59,60;,
 4;61,62,63,64;,
 4;61,64,65,66;,
 4;67,68,51,69;,
 4;67,69,44,70;,
 4;46,45,53,52;;
 
 MeshMaterialList {
  2;
  36;
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
  48;
  0.000000;0.278163;-0.960534;,
  0.000000;-1.000000;-0.000000;,
  0.232117;0.194672;-0.953008;,
  0.232125;0.194688;0.953003;,
  0.000000;0.278185;0.960528;,
  0.904327;-0.299229;-0.304391;,
  0.904330;-0.299228;0.304385;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.668968;0.000000;-0.743292;,
  0.683971;0.729509;0.000000;,
  0.668977;0.000000;0.743283;,
  0.921845;0.000000;-0.387558;,
  0.925774;0.378078;0.000000;,
  0.921846;0.000000;0.387556;,
  -0.119809;0.886129;-0.447684;,
  0.413211;0.900476;-0.135646;,
  0.119808;0.886135;0.447673;,
  -0.119807;0.886135;0.447673;,
  -0.111662;0.985548;-0.127384;,
  0.111662;0.985548;-0.127384;,
  0.111662;0.985548;0.127386;,
  -0.111662;0.985548;0.127386;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.950250;0.311490;0.000000;,
  0.733973;0.679179;0.000000;,
  0.683989;-0.729492;-0.000000;,
  0.714114;0.700029;0.000000;,
  0.699601;0.000000;0.714534;,
  0.714118;-0.700025;-0.000000;,
  0.805951;0.591982;0.000000;,
  0.000000;0.534371;-0.845250;,
  -0.805948;0.591986;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.998947;-0.045880;-0.000000;,
  0.000000;-0.039524;-0.999219;,
  0.000000;-0.039525;0.999219;,
  0.995790;-0.091664;-0.000000;,
  0.000000;-0.078986;-0.996876;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.078988;0.996876;,
  -0.998947;-0.045881;0.000000;,
  -0.995790;-0.091666;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  36;
  4;1,1,1,1;,
  4;5,6,23,23;,
  4;7,7,7,7;,
  4;7,7,0,2;,
  4;8,3,4,8;,
  4;8,8,8,8;,
  4;24,24,24,24;,
  4;24,24,25,25;,
  4;9,9,5,2;,
  4;10,10,26,26;,
  4;11,11,3,6;,
  4;27,27,6,5;,
  4;12,12,9,9;,
  4;13,28,10,10;,
  4;14,29,11,11;,
  4;30,30,27,27;,
  4;12,12,13,14;,
  4;17,18,4,3;,
  4;16,31,26,26;,
  4;15,32,2,0;,
  4;33,33,25,25;,
  4;21,22,18,17;,
  4;20,21,17,16;,
  4;19,20,16,15;,
  4;22,19,15,18;,
  4;22,21,20,19;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,39,39;,
  4;37,40,40,37;,
  4;37,37,41,41;,
  4;38,42,42,38;,
  4;38,38,43,43;,
  4;44,45,45,44;,
  4;44,44,46,46;,
  4;47,47,36,36;;
 }
 MeshTextureCoords {
  71;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.472340;,
  1.000000;0.472340;,
  0.000000;1.000000;,
  1.000000;0.472340;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.472340;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.472340;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.472340;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.472340;,
  1.000000;1.000000;,
  0.000000;0.472340;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.472340;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.472340;,
  0.000000;0.000000;,
  0.000000;0.472340;,
  1.000000;0.000000;,
  1.000000;0.472340;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.472340;,
  1.000000;0.472340;,
  0.000000;1.000000;,
  1.000000;0.472340;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.472340;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.472340;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.472340;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.472340;,
  1.000000;1.000000;,
  0.000000;0.472340;,
  1.000000;0.000000;;
 }
}
