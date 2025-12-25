#include "helper.h"

Mesh* CreateRGBCube(int gridSize)
{
    int vertexCount = pow(gridSize+1, 2);
    int triangleCount = 2*pow(gridSize, 2);

    Mesh *meshes = (Mesh *)RL_MALLOC(6*sizeof(Mesh));
    // Allocate memory for vertices (x, y, z for each vertex)
    Vector3 *vertices = (Vector3 *)RL_MALLOC(vertexCount*sizeof(Vector3));
    // Allocate memory for colors (r, g, b, a for each vertex)
    Color *colors = (Color *)RL_MALLOC(vertexCount*sizeof(Color));

    // Back Face
    for (int y = 0; y < gridSize+1; y++)
    {
        // [0:1/gridSize:1]
        float yPos = (float)y/gridSize;
        for (int x = 0; x < gridSize+1; x++)
        {
            // [0:1/gridSize:1]
            float xPos = (float)x/gridSize;
            vertices[x + y*(gridSize+1)] = (Vector3){ xPos, yPos, 0.0f };
            colors[x + y*(gridSize+1)] = (Color){ vertices[x + y*(gridSize+1)].x*255, \
                                                vertices[x + y*(gridSize+1)].y*255, \
                                                vertices[x + y*(gridSize+1)].z*255,  255 };
        }
    }
    meshes[0] = CreateRGBFace(vertices, colors, gridSize);


    // Front Face
    Matrix matRotation = MatrixRotateY(180*DEG2RAD);
    Matrix matTranslation = MatrixTranslate(1.0f, 0.0f, 1.0f);
    Matrix matTransform = MatrixMultiply(matRotation, matTranslation);
    for (int y = 0; y < gridSize+1; y++)
    {
        // [0:1/gridSize:1]
        float yPos = (float)y/gridSize;
        for (int x = 0; x < gridSize+1; x++)
        {
            // [0:1/gridSize:1]
            float xPos = (float)x/gridSize;
            vertices[x + y*(gridSize+1)] = Vector3Transform((Vector3){ xPos, yPos, 0.0f }, matTransform);
            colors[x + y*(gridSize+1)] = (Color){ vertices[x + y*(gridSize+1)].x*255, \
                                                vertices[x + y*(gridSize+1)].y*255, \
                                                vertices[x + y*(gridSize+1)].z*255,  255 };
        }
    }
    meshes[1] = CreateRGBFace(vertices, colors, gridSize);

    

    // Left Face
    matRotation = MatrixRotateY(90*DEG2RAD);
    matTranslation = MatrixTranslate(0.0f, 0.0f, 1.0f);
    matTransform = MatrixMultiply(matRotation, matTranslation);
    for (int y = 0; y < gridSize+1; y++)
    {
        // [0:1/gridSize:1]
        float yPos = (float)y/gridSize;
        for (int x = 0; x < gridSize+1; x++)
        {
            // [0:1/gridSize:1]
            float xPos = (float)x/gridSize;
            vertices[x + y*(gridSize+1)] = Vector3Transform((Vector3){ xPos, yPos, 0.0f }, matTransform);
            colors[x + y*(gridSize+1)] = (Color){ vertices[x + y*(gridSize+1)].x*255, \
                                                vertices[x + y*(gridSize+1)].y*255, \
                                                vertices[x + y*(gridSize+1)].z*255,  255 };
        }
    }
    meshes[2] = CreateRGBFace(vertices, colors, gridSize);

    // Right Face
    matRotation = MatrixRotateY(-90*DEG2RAD);
    matTranslation = MatrixTranslate(1.0f, 0.0f, 0.0f);
    matTransform = MatrixMultiply(matRotation, matTranslation);
    for (int y = 0; y < gridSize+1; y++)
    {
        // [0:1/gridSize:1]
        float yPos = (float)y/gridSize;
        for (int x = 0; x < gridSize+1; x++)
        {
            // [0:1/gridSize:1]
            float xPos = (float)x/gridSize;
            vertices[x + y*(gridSize+1)] = Vector3Transform((Vector3){ xPos, yPos, 0.0f }, matTransform);
            colors[x + y*(gridSize+1)] = (Color){ vertices[x + y*(gridSize+1)].x*255, \
                                                vertices[x + y*(gridSize+1)].y*255, \
                                                vertices[x + y*(gridSize+1)].z*255,  255 };
        }
    }
    meshes[3] = CreateRGBFace(vertices, colors, gridSize);

    // Top Face
    matRotation = MatrixRotateX(90*DEG2RAD);
    matTranslation = MatrixTranslate(0.0f, 1.0f, 0.0f);
    matTransform = MatrixMultiply(matRotation, matTranslation);
    for (int y = 0; y < gridSize+1; y++)
    {
        // [0:1/gridSize:1]
        float yPos = (float)y/gridSize;
        for (int x = 0; x < gridSize+1; x++)
        {
            // [0:1/gridSize:1]
            float xPos = (float)x/gridSize;
            vertices[x + y*(gridSize+1)] = Vector3Transform((Vector3){ xPos, yPos, 0.0f }, matTransform);
            colors[x + y*(gridSize+1)] = (Color){ vertices[x + y*(gridSize+1)].x*255, \
                                                vertices[x + y*(gridSize+1)].y*255, \
                                                vertices[x + y*(gridSize+1)].z*255,  255 };
        }
    }
    meshes[4] = CreateRGBFace(vertices, colors, gridSize);

    // Bottom Face
    matRotation = MatrixRotateX(-90*DEG2RAD);
    matTranslation = MatrixTranslate(0.0f, 0.0f, 1.0f);
    matTransform = MatrixMultiply(matRotation, matTranslation);
    for (int y = 0; y < gridSize+1; y++)
    {
        // [0:1/gridSize:1]
        float yPos = (float)y/gridSize;
        for (int x = 0; x < gridSize+1; x++)
        {
            // [0:1/gridSize:1]
            float xPos = (float)x/gridSize;
            vertices[x + y*(gridSize+1)] = Vector3Transform((Vector3){ xPos, yPos, 0.0f }, matTransform);
            colors[x + y*(gridSize+1)] = (Color){ vertices[x + y*(gridSize+1)].x*255, \
                                                vertices[x + y*(gridSize+1)].y*255, \
                                                vertices[x + y*(gridSize+1)].z*255,  255 };
        }
    }
    meshes[5] = CreateRGBFace(vertices, colors, gridSize);



    RL_FREE(vertices);
    RL_FREE(colors);

    return meshes;

} 

Mesh CreateRGBFace(Vector3 *vertices, Color *colors, int gridSize)
{
    Mesh mesh = { 0 };

    int vertexCount = pow(gridSize+1, 2);

    // Triangles definition (indices)
    int numFaces = gridSize*gridSize;
    int *triangles = (int *)RL_MALLOC(numFaces*6*sizeof(int));
    int t = 0;
    for (int face = 0; face < numFaces; face++)
    {
        // Retrieve lower left corner from face ind
        int i = face + face/gridSize;

        triangles[t++] = i + gridSize + 1;
        triangles[t++] = i + 1;
        triangles[t++] = i;

        triangles[t++] = i + gridSize + 1;
        triangles[t++] = i + gridSize + 2;
        triangles[t++] = i + 1;
    }

    mesh.vertexCount = vertexCount;
    mesh.triangleCount = numFaces*2;
    mesh.vertices = (float *)RL_MALLOC(mesh.vertexCount*3*sizeof(float));
    mesh.colors = (unsigned char *)RL_MALLOC(mesh.vertexCount*4*sizeof(unsigned char));
    mesh.indices = (unsigned short *)RL_MALLOC(mesh.triangleCount*3*sizeof(unsigned short));


    // Mesh vertices position array
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        mesh.vertices[3*i] = vertices[i].x;
        mesh.vertices[3*i + 1] = vertices[i].y;
        mesh.vertices[3*i + 2] = vertices[i].z;
    }

    // Mesh vertices color array
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        mesh.colors[4*i] = colors[i].r;
        mesh.colors[4*i + 1] = colors[i].g;
        mesh.colors[4*i + 2] = colors[i].b;
        mesh.colors[4*i + 3] = colors[i].a;
    }

    // Mesh indices array initialization
    for (int i = 0; i < mesh.triangleCount*3; i++) mesh.indices[i] = triangles[i];

    
    RL_FREE(triangles);
    // Upload the mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}

Mesh CreateColoredSquare(Vector3 norm, int gridSize)
{
    Mesh mesh = { 0 };

    int vertexCount = pow(gridSize+1, 2);
    int triangleCount = 2*pow(gridSize, 2);

    // Allocate memory for vertices (x, y, z for each vertex)
    Vector3 *vertices = (Vector3 *)RL_MALLOC(vertexCount*sizeof(Vector3));
    // Allocate memory for colors (r, g, b, a for each vertex)
    Color *colors = (Color *)RL_MALLOC(vertexCount*sizeof(Color));

    for (int y = 0; y < gridSize+1; y++)
    {
        // [0:1/gridSize:1]
        float yPos = (float)y/gridSize;
        for (int x = 0; x < gridSize+1; x++)
        {
            // [0:1/gridSize:1]
            float xPos = (float)x/gridSize;
            vertices[x + y*(gridSize+1)] = (Vector3){ xPos, yPos, 0.0f };
            colors[x + y*(gridSize+1)] = (Color){ xPos*255, yPos*255, 0,  255 };
        }
    }

    // Triangles definition (indices)
    int numFaces = gridSize*gridSize;
    int *triangles = (int *)RL_MALLOC(numFaces*6*sizeof(int));
    int t = 0;
    for (int face = 0; face < numFaces; face++)
    {
        // Retrieve lower left corner from face ind
        int i = face + face/gridSize;

        triangles[t++] = i + gridSize + 1;
        triangles[t++] = i;
        triangles[t++] = i + 1;

        triangles[t++] = i + gridSize + 1;
        triangles[t++] = i + 1;
        triangles[t++] = i + gridSize + 2;
    }

    mesh.vertexCount = vertexCount;
    mesh.triangleCount = numFaces*2;
    mesh.vertices = (float *)RL_MALLOC(mesh.vertexCount*3*sizeof(float));
    mesh.colors = (unsigned char *)RL_MALLOC(mesh.vertexCount*4*sizeof(unsigned char));
    mesh.indices = (unsigned short *)RL_MALLOC(mesh.triangleCount*3*sizeof(unsigned short));


    // Mesh vertices position array
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        mesh.vertices[3*i] = vertices[i].x;
        mesh.vertices[3*i + 1] = vertices[i].y;
        mesh.vertices[3*i + 2] = vertices[i].z;
    }

    // Mesh vertices color array
    for (int i = 0; i < mesh.vertexCount; i++)
    {
        mesh.colors[4*i] = colors[i].r;
        mesh.colors[4*i + 1] = colors[i].g;
        mesh.colors[4*i + 2] = colors[i].b;
        mesh.colors[4*i + 3] = colors[i].a;
    }

    // Mesh indices array initialization
    for (int i = 0; i < mesh.triangleCount*3; i++) mesh.indices[i] = triangles[i];

    RL_FREE(vertices);
    RL_FREE(triangles);
    RL_FREE(colors);
    // Upload the mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}

Mesh CreateColoredTriangle()
{
    Mesh mesh = { 0 };
    mesh.vertexCount = 3;
    mesh.triangleCount = 1;

    // Allocate memory for vertices (x, y, z for each vertex)
    mesh.vertices = (float*)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
    // Allocate memory for colors (r, g, b, a for each vertex)
    mesh.colors = (unsigned char*)MemAlloc(mesh.vertexCount * 4 * sizeof(unsigned char));
    
    // Check if allocation was successful (optional but good practice)
    if (mesh.vertices == NULL || mesh.colors == NULL)
    {
        TraceLog(LOG_ERROR, "Failed to allocate mesh memory");
        // Free allocated memory if one fails
        if (mesh.vertices) MemFree(mesh.vertices);
        if (mesh.colors) MemFree(mesh.colors);
        return mesh; // return empty mesh
    }

    // Define vertex positions
    mesh.vertices[0] = 0.0f; mesh.vertices[1] = 1.0f; mesh.vertices[2] = 0.0f;   // Top
    mesh.vertices[3] = -1.0f; mesh.vertices[4] = -1.0f; mesh.vertices[5] = 0.0f; // Bottom-left
    mesh.vertices[6] = 1.0f; mesh.vertices[7] = -1.0f; mesh.vertices[8] = 0.0f;  // Bottom-right

    // Define vertex colors (RGBA: 0-255)
    mesh.colors[0] = 255; mesh.colors[1] = 0; mesh.colors[2] = 0; mesh.colors[3] = 255;   // Red
    mesh.colors[4] = 0; mesh.colors[5] = 255; mesh.colors[6] = 0; mesh.colors[7] = 255;   // Green
    mesh.colors[8] = 0; mesh.colors[9] = 0; mesh.colors[10] = 255; mesh.colors[11] = 255; // Blue

    // You may also want to generate normals for proper lighting if you plan to use lights
    // GenMeshNormals(&mesh); 

    // Upload the mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);

    return mesh;
}