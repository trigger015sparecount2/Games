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
 44;
 -5.30397;6.31523;-3.27437;,
 -3.71453;0.12430;-2.14166;,
 -3.71453;0.12430;0.22462;,
 -4.54724;6.31523;2.38509;,
 4.99603;6.31523;-3.27437;,
 4.43950;6.31523;2.38509;,
 3.40659;0.12430;0.22462;,
 3.40659;0.12430;-2.14166;,
 -0.13293;6.31523;-7.88699;,
 4.99603;6.31523;-3.27437;,
 3.40659;0.12430;-2.14166;,
 -0.13943;0.12430;-5.35311;,
 -3.71453;0.12430;-2.14166;,
 -5.30397;6.31523;-3.27437;,
 -0.13293;6.31523;5.18944;,
 -4.54724;6.31523;2.38509;,
 -3.71453;0.12430;0.22462;,
 -0.13943;0.12430;3.32558;,
 3.40659;0.12430;0.22462;,
 4.43950;6.31523;2.38509;,
 -4.69764;7.42402;-2.83734;,
 -3.69130;9.26430;-2.11199;,
 -0.13293;9.26430;-5.26000;,
 -0.13293;7.42402;-7.57717;,
 3.65078;9.26430;-2.11199;,
 4.49025;7.42402;-2.83734;,
 3.65078;9.26430;0.94191;,
 -0.13293;9.26430;3.98162;,
 -3.69130;9.26430;0.94191;,
 -3.69130;9.26430;-0.85609;,
 -0.13293;9.26430;3.98162;,
 -0.13293;10.80515;-0.94198;,
 -0.13293;9.26430;-5.26000;,
 -3.69130;9.26430;-2.11199;,
 3.65078;9.26430;-1.03332;,
 3.65078;9.26430;-2.11199;,
 -0.13943;0.12430;-5.35311;,
 -0.13943;0.12430;3.32558;,
 -0.12225;7.76217;-6.64657;,
 4.05649;7.86143;-1.76886;,
 4.83675;6.18055;-3.08318;,
 -0.15831;5.92433;-7.22363;,
 -5.00554;6.18055;-3.13155;,
 -4.31260;7.49195;-2.39308;;
 
 20;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,11,12,13;,
 4;14,15,16,17;,
 4;14,17,18,19;,
 4;20,21,22,23;,
 4;23,22,24,25;,
 4;26,27,14,19;,
 4;27,28,15,14;,
 4;28,21,0,3;,
 4;24,26,5,4;,
 4;29,28,30,31;,
 4;29,31,32,33;,
 4;31,30,26,34;,
 4;31,34,35,32;,
 4;16,12,36,37;,
 4;10,18,37,36;,
 4;38,39,40,41;,
 4;38,41,42,43;;
 
 MeshMaterialList {
  2;
  20;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.380000;0.412000;0.518000;1.000000;;
   5.000000;
   0.320000;0.320000;0.320000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  29;
  -0.660799;0.708614;-0.247410;,
  -0.891046;-0.279652;-0.357537;,
  0.668860;0.694954;-0.263942;,
  0.887298;-0.283549;-0.363734;,
  0.671547;0.648611;0.358229;,
  0.845739;-0.287776;0.449344;,
  -0.666027;0.656630;0.353899;,
  -0.846148;-0.275411;0.456269;,
  -0.973533;-0.037762;-0.225407;,
  0.970313;-0.060000;-0.234292;,
  -0.874554;0.092061;0.476109;,
  0.878297;0.071165;0.472789;,
  -0.211807;0.917369;-0.337003;,
  0.640571;-0.293036;-0.709788;,
  0.458026;0.740387;0.491975;,
  -0.593145;0.064344;0.802520;,
  -0.570963;-0.289826;0.768116;,
  -0.549617;0.605334;-0.575753;,
  0.546467;0.588750;-0.595606;,
  -0.340605;0.940168;-0.008510;,
  0.322640;0.946482;-0.008652;,
  -0.009539;0.999913;-0.009096;,
  -0.637734;-0.292787;-0.712440;,
  0.581931;0.057248;0.811221;,
  0.564199;-0.300466;0.769025;,
  -0.474565;0.736018;0.482770;,
  0.000000;-1.000000;-0.000000;,
  -0.614280;0.438233;-0.656210;,
  0.610849;0.454270;-0.648461;;
  20;
  4;8,1,7,10;,
  4;9,11,5,3;,
  4;13,9,3,13;,
  4;22,22,1,8;,
  4;15,10,7,16;,
  4;23,24,5,11;,
  4;17,0,12,17;,
  4;18,18,2,18;,
  4;4,14,23,11;,
  4;25,6,10,15;,
  4;6,0,8,10;,
  4;2,4,11,9;,
  4;19,6,25,21;,
  4;19,21,12,0;,
  4;21,14,4,20;,
  4;21,20,2,12;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;28,28,28,28;,
  4;27,27,27,27;;
 }
 MeshTextureCoords {
  44;
  1.000000;0.204980;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.204980;,
  0.000000;0.204980;,
  1.000000;0.204980;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.502040;0.204980;,
  1.000000;0.204980;,
  1.000000;1.000000;,
  0.502040;1.000000;,
  0.000000;1.000000;,
  0.000000;0.204980;,
  0.497960;0.204980;,
  1.000000;0.204980;,
  1.000000;1.000000;,
  0.497960;1.000000;,
  0.000000;1.000000;,
  0.000000;0.204980;,
  0.000000;0.127910;,
  0.000000;0.000000;,
  0.502040;0.000000;,
  0.502040;0.127910;,
  1.000000;0.000000;,
  1.000000;0.127910;,
  1.000000;0.000000;,
  0.497960;0.000000;,
  0.000000;0.000000;,
  0.000000;0.588760;,
  0.502040;0.000000;,
  0.502040;0.532760;,
  0.502040;1.000000;,
  0.000000;1.000000;,
  1.000000;0.646790;,
  1.000000;1.000000;,
  0.502040;0.000000;,
  0.502040;1.000000;,
  0.510580;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.510580;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;;
 }
}
