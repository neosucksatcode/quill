#ifndef QUILL_STD_GEOMETRY_H_
#define QUILL_STD_GEOMETRY_H_

typedef struct {
  float x, y;
} Vertex2D;

typedef struct {
  float x, y, z;
} Vertex3D;

typedef struct {
  Vertex3D v1, v2, v3;
} Triangle;

// Mesh

typedef struct {
  Triangle triangles[12];
} Cube;

typedef struct {
  // VertexNormal *normals;
  Vertex3D *vertices;
} Mesh;

#endif // QUILL_STD_GEOMETRY_H_
