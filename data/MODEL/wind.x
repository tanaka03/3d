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
 43;
 21.56037;76.01706;-15.66453;,
 21.84345;88.41816;-15.87021;,
 8.34345;74.55168;-25.67853;,
 8.23533;62.15061;-25.34574;,
 21.84345;88.41816;-15.87021;,
 21.56037;76.01706;-15.66453;,
 8.23533;62.15061;-25.34574;,
 8.34345;74.55168;-25.67853;,
 -8.34345;65.58903;-25.67853;,
 -8.23533;53.18793;-25.34574;,
 -8.72205;54.36987;-26.46921;,
 -8.34345;65.58903;-25.67853;,
 -21.84345;57.68823;-15.87021;,
 -21.56037;45.28713;-15.66453;,
 -21.56037;45.28713;-15.66453;,
 -21.84345;57.68823;-15.87021;,
 -27.00000;49.58655;0.00000;,
 -26.65008;37.18548;0.00000;,
 -26.65008;37.18548;0.00000;,
 -27.00000;49.58655;0.00000;,
 -21.84345;43.26042;15.87021;,
 -21.56037;30.85929;15.66453;,
 -21.56037;30.85929;15.66453;,
 -21.84345;43.26042;15.87021;,
 -8.34345;36.93630;25.67853;,
 -8.23533;24.53520;25.34574;,
 -8.23533;24.53520;25.34574;,
 -8.34345;36.93630;25.67853;,
 8.34345;30.23082;25.67853;,
 8.23533;17.82972;25.34574;,
 8.23533;17.82972;25.34574;,
 8.34345;30.23082;25.67853;,
 21.84348;22.48347;15.87018;,
 21.56037;10.08234;15.66453;,
 21.56037;10.08234;15.66453;,
 21.84348;22.48347;15.87018;,
 27.00000;15.23292;0.00000;,
 26.65008;2.83176;0.00000;,
 26.65008;2.83176;0.00000;,
 27.00000;15.23292;0.00000;,
 -21.56037;45.28713;-15.66453;,
 -8.23533;53.18793;-25.34574;,
 8.23533;62.15061;-25.34574;;
 
 20;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,2,8,9;,
 4;7,6,10,11;,
 4;9,8,12,13;,
 4;11,10,14,15;,
 4;13,12,16,17;,
 4;15,14,18,19;,
 4;17,16,20,21;,
 4;19,18,22,23;,
 4;21,20,24,25;,
 4;23,22,26,27;,
 4;25,24,28,29;,
 4;27,26,30,31;,
 4;29,28,32,33;,
 4;31,30,34,35;,
 4;33,32,36,37;,
 4;35,34,38,39;,
 3;40,10,41;,
 3;42,41,10;;
 
 MeshMaterialList {
  1;
  20;
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
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  -0.947024;0.026824;-0.320041;,
  -0.605573;0.026819;0.795338;,
  -0.326403;0.028237;0.944809;,
  0.295891;0.028211;0.954805;,
  -0.107800;-0.356605;-0.928015;,
  0.801018;0.028203;0.597976;,
  0.999534;0.028218;0.011673;,
  0.814668;0.028204;-0.579241;,
  0.318902;0.028200;-0.947368;,
  -0.297753;0.028196;-0.954226;,
  -0.801504;0.028207;-0.597324;,
  0.605573;-0.026819;-0.795338;,
  0.340836;-0.211536;-0.916015;,
  0.331205;-0.003004;-0.943554;,
  -0.319298;0.024232;-0.947345;,
  -0.818661;-0.001247;-0.574275;,
  -0.999534;-0.028218;-0.011673;,
  -0.814668;-0.028204;0.579241;,
  -0.318902;-0.028200;0.947368;,
  0.297753;-0.028196;0.954226;,
  0.801504;-0.028207;0.597324;,
  0.947024;-0.026824;0.320041;,
  -0.092009;-0.705674;-0.702537;,
  0.114968;-0.659104;-0.743212;;
  20;
  4;1,1,2,2;,
  4;11,11,12,13;,
  4;2,2,3,3;,
  4;13,12,4,14;,
  4;3,3,5,5;,
  4;14,4,15,15;,
  4;5,5,6,6;,
  4;15,15,16,16;,
  4;6,6,7,7;,
  4;16,16,17,17;,
  4;7,7,8,8;,
  4;17,17,18,18;,
  4;8,8,9,9;,
  4;18,18,19,19;,
  4;9,9,10,10;,
  4;19,19,20,20;,
  4;10,10,0,0;,
  4;20,20,21,21;,
  3;22,4,23;,
  3;12,23,4;;
 }
 MeshTextureCoords {
  43;
  0.100000;0.000000;,
  0.100000;0.250000;,
  0.200000;0.250000;,
  0.200000;0.000000;,
  0.100000;0.500000;,
  0.100000;0.750000;,
  0.200000;0.750000;,
  0.200000;0.500000;,
  0.300000;0.250000;,
  0.300000;0.000000;,
  0.300000;0.750000;,
  0.300000;0.500000;,
  0.400000;0.250000;,
  0.400000;0.000000;,
  0.400000;0.750000;,
  0.400000;0.500000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.750000;,
  0.500000;0.500000;,
  0.600000;0.250000;,
  0.600000;0.000000;,
  0.600000;0.750000;,
  0.600000;0.500000;,
  0.700000;0.250000;,
  0.700000;0.000000;,
  0.700000;0.750000;,
  0.700000;0.500000;,
  0.800000;0.250000;,
  0.800000;0.000000;,
  0.800000;0.750000;,
  0.800000;0.500000;,
  0.900000;0.250000;,
  0.900000;0.000000;,
  0.900000;0.750000;,
  0.900000;0.500000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.400000;0.875000;,
  0.300000;1.000000;,
  0.200000;0.875000;;
 }
}